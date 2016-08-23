#include "kReader.h"
#include <fstream>
#include <sstream>
#include "vtkDataSet.h"
#include "vtkUnstructuredGrid.h"
#include "vtkCell.h"


using namespace std;



kReader::kReader()
{
	m_points = nullptr;
}
vtkPoints* kReader::GetVtkPoints()
{
	if (m_points == nullptr)
	{
		m_points = vtkPoints::New();
		m_points->SetNumberOfPoints(m_nodes.size());
		for (vector<Node>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
		{
			int id = (*it).id;
			if (id != -1) m_points->SetPoint(id - m_nodeOffset, (*it).x, (*it).y, (*it).z);
		}
	}
	return m_points;
}
vtkDataSet* kReader::GetElementByIndex(int index)
{
	bool flag = false;
	for (int i = 0; i < m_partIndexs.size(); i++)
	{
		if (m_partIndexs[i] == index)
		{
			flag = true;
			break;
		}
	}
	if (!flag)
	{
		return NULL;
	}

	vtkUnstructuredGrid * ug = vtkUnstructuredGrid::New();
	ug->SetPoints(GetVtkPoints());

	vtkIdType ids[8];
	for (vector<Element>::iterator it = m_eles.begin(); it != m_eles.end(); it++)
	{
		if ((*it).pid == index)
		{
			it->GetOffsetNid(ids, m_nodeOffset);
			if (it->type == ELEMENT_SOLID)
			{
				if (ids[3] == ids[4])
				{
					ug->InsertNextCell(VTK_TETRA, 4, ids);
				}
				else
				{
					ug->InsertNextCell(VTK_HEXAHEDRON, 8, ids);
				}
			}
			else if (it->type == ELEMENT_SHELL)
			{
				ug->InsertNextCell(VTK_TETRA, 4, ids);
			}
			else if (it->type == ELEMENT_BEAM)
			{
				ug->InsertNextCell(VTK_TRIANGLE, 3, ids);
			}
			
		}
	}
	return ug;
}
vtkDataSet* kReader::GetSetNodeList(int index)
{
	vtkUnstructuredGrid * ug = vtkUnstructuredGrid::New();
	ug->SetPoints(GetVtkPoints());

	vtkIdType nids[8];
	for (map<int, vector<NodeList> >::iterator it = m_setNodeList.begin(); it != m_setNodeList.end(); it++)
	{
		if (it->first == index)
		{
			for (int i = 0; i < it->second.size(); i++)
			{
				it->second[i].GetOffsetNid(nids, m_nodeOffset);
				ug->InsertNextCell(VTK_POLY_VERTEX, 8, nids);
			}
			break;
		}
	}
	return ug;
}

vtkDataSet* kReader::GetSetSeg(int index)
{
	vtkUnstructuredGrid * ug = vtkUnstructuredGrid::New();
	ug->SetPoints(GetVtkPoints());

	vtkIdType nids[8];
	for (map<int, vector<Segment> >::iterator it = m_setSegment.begin(); it != m_setSegment.end(); it++)
	{
		if (it->first == index)
		{
			for (int i = 0; i < it->second.size(); i++)
			{
				it->second[i].GetOffsetNid(nids, m_nodeOffset);
				ug->InsertNextCell(VTK_TETRA, 4, nids);
			}
			break;
		}
	}
	return ug;
}

int kReader::GetSetSegArrow(int index, vector<Vec3d>& startPos, vector<Vec3d>& endPos)
{
	for (map<int, vector<Segment> >::iterator it = m_setSegment.begin(); it != m_setSegment.end(); it++)
	{
		if (it->first == index)
		{
			for (int i = 0; i < it->second.size(); i++)
			{
				int* nids = it->second[i].nids;
				Vec3d p1(m_nodes[nids[0] - m_nodeOffset].x, m_nodes[nids[0] - m_nodeOffset].y, m_nodes[nids[0] - m_nodeOffset].z);
				Vec3d p2(m_nodes[nids[1] - m_nodeOffset].x, m_nodes[nids[1] - m_nodeOffset].y, m_nodes[nids[1] - m_nodeOffset].z);
				Vec3d p3(m_nodes[nids[2] - m_nodeOffset].x, m_nodes[nids[2] - m_nodeOffset].y, m_nodes[nids[2] - m_nodeOffset].z);
				Vec3d p4(m_nodes[nids[3] - m_nodeOffset].x, m_nodes[nids[3] - m_nodeOffset].y, m_nodes[nids[3] - m_nodeOffset].z);
				Vec3d mid = (p1 + p2 + p3 + p4) * 0.25;
				Vec3d dir = (p2 - p1) / (p3 - p2);
				Vec3d endp = mid + dir.Normalize() * 0.005;
				startPos.push_back(mid);
				endPos.push_back(endp);
			}
			break;
		}
	}
	return startPos.size();
}
vtkDataSet* kReader::GetAllElement()
{
	vtkUnstructuredGrid * ug = vtkUnstructuredGrid::New();
	ug->SetPoints(GetVtkPoints());

	vtkIdType nids[8];
	for (vector<Element>::iterator it = m_eles.begin(); it != m_eles.end(); it++)
	{
		it->GetOffsetNid(nids, m_nodeOffset);
		if (it->type == ELEMENT_SOLID)
		{
			if (nids[3] == nids[4])
			{
				ug->InsertNextCell(VTK_TETRA, 4, nids);
			}
			else
			{
				ug->InsertNextCell(VTK_HEXAHEDRON, 8, nids);
			}
		}
	}
	return ug;
}

void kReader::Clear()
{
	m_nodes.clear();
	m_eles.clear();

	m_setNodeList.clear();
	m_setSegment.clear();

	m_partIndexs.clear();
	m_setNodeIndexs.clear();
	m_setSegIndexs.clear();
	if (m_points)
	{
		m_points->Delete();
		m_points = nullptr;
	}
	
}

void kReader::read(string file)
{
	ifstream input(file);
	if (!input.is_open())
	{
		return;
	}
	bool partId[1000];
	memset(partId, 0, 1000);
	string line;
	double x, y, z;
	Node node;
	Element ele;
	NodeList nodeList;
	Segment seg;
	readType _readType = NONE;
	int setIndex = -1;
	bool isSetStart = false;
	m_nodeOffset = 0x7fffffff;
	while (getline(input, line))
	{
		if (line.empty())
			continue;
		switch (line[0])
		{
		case '$'://×¢ÊÍ
			break;;
		case '*':
			if (line == "*NODE")
			{
				_readType = NODE;
			}
			else if (line == "*ELEMENT_SOLID")
			{
				_readType = ELEMENT_SOLID;
			}
			else if (line == "*ELEMENT_SHELL")
			{
				_readType = ELEMENT_SHELL;
			}
			else if (line == "*ELEMENT_BEAM")
			{
				_readType = ELEMENT_BEAM;
			}
			else if (line == "*SET_NODE_LIST")
			{
				_readType = SET_NODE_LIST;
				isSetStart = true;
			}
			else if (line == "*SET_SEGMENT")
			{
				_readType = SET_SEGMENT;
				isSetStart = true;
			}
			
			break;
		default:
			stringstream ss(line);
			if (_readType == NODE)
			{
				ss >> node.id >> node.x >> node.y >> node.z;
				if (m_nodeOffset > node.id)
					m_nodeOffset = node.id;
				m_nodes.push_back(node);
			}
			else if (_readType == ELEMENT_SOLID)
			{
				ele.type = ELEMENT_SOLID;
				ss >> ele.eid >> ele.pid;
				partId[ele.pid] = true;
				for (int i = 0; i < 8; i++)
				{
					ss >> ele.nids[i];
				}
				m_eles.push_back(ele);
			}
			else if (_readType == ELEMENT_SHELL)
			{
				ele.type = ELEMENT_SHELL;
				ss >> ele.eid >> ele.pid;
				partId[ele.pid] = true;
				int arg, i = 0;
				while (ss >> arg)
				{
					ele.nids[i++] = arg;
				}
				m_eles.push_back(ele);
			}
			else if (_readType == ELEMENT_BEAM)
			{
				ele.type = ELEMENT_BEAM;
				ss >> ele.eid >> ele.pid;
				partId[ele.pid] = true;
				int arg, i = 0;
				while (ss >> arg)
				{
					ele.nids[i++] = arg;
				}
				m_eles.push_back(ele);
			}
			else if (_readType == SET_NODE_LIST)
			{
				if (isSetStart)
				{
					ss >> setIndex;
					m_setNodeIndexs.push_back(setIndex);
					isSetStart = false;
				}
				else
				{
					for (int i = 0; i < 8; i++)
					{
						ss >> nodeList.nids[i];
					}
					m_setNodeList[setIndex].push_back(nodeList);
				}
			}
			else if (_readType == SET_SEGMENT)
			{
				if (isSetStart)
				{
					ss >> setIndex;
					m_setSegIndexs.push_back(setIndex);
					isSetStart = false;
				}
				else
				{
					for (int i = 0; i < 4; i++)
					{
						ss >> seg.nids[i];
					}
					m_setSegment[setIndex].push_back(seg);
				}
			}
		}
	}
	for (int i = 0; i < 1000; i++)
	{
		if (partId[i])
		{
			m_partIndexs.push_back(i);
		}
	}
}