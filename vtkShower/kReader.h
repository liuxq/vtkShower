#include <string>
#include <vector>
#include <map>

#include "vec3.h"
#include "vtktype.h"

using namespace std;

class vtkUnstructuredGrid;
class vtkDataSet;
class vtkPoints;


enum readType
{
	NONE,
	NODE,
	ELEMENT_SOLID,
	ELEMENT_SHELL,
	ELEMENT_BEAM,
	SET_NODE_LIST,
	SET_SEGMENT
};

struct Node
{
	int id;
	double x;
	double y;
	double z;
};

struct Element
{
	readType type;
	int eid;
	int pid;
	int nids[8];
	void GetOffsetNid(vtkIdType* outnids, int offset)
	{
		for (int i = 0; i < 8; i++)
		{
			outnids[i] = nids[i] - offset;
		}
	}
};

struct Segment
{
	int nids[4];
	void GetOffsetNid(vtkIdType* outnids, int offset)
	{
		for (int i = 0; i < 4; i++)
		{
			outnids[i] = nids[i] - offset;
		}
	}
};

struct NodeList
{
	int nids[8];
	void GetOffsetNid(vtkIdType* outnids, int offset)
	{
		for (int i = 0; i < 8; i++)
		{
			outnids[i] = nids[i] - offset;
		}
	}
};

class kReader
{
public:
	kReader();
	void read(std::string file);
	vtkDataSet* GetAllElement();
	vtkDataSet* GetSetNodeList(int index);
	vtkDataSet* GetSetSeg(int index);
	vtkPoints* GetVtkPoints();
	vtkDataSet* GetElementByIndex(int index);
	int GetSetSegArrow(int index, vector<Vec3d>& startPos, vector<Vec3d>& endPos);
	void Clear();
	vector<int>& GetParts()
	{
		return m_partIndexs;
	}
	vector<int>& GetSetNode()
	{
		return m_setNodeIndexs;
	}
	vector<int>& GetSetSeg()
	{
		return m_setSegIndexs;
	}
private:
	int m_nodeOffset;
	vtkPoints* m_points;
	vector<Node> m_nodes;
	vector<Element> m_eles;
	
	map<int, vector<NodeList> > m_setNodeList;
	map<int, vector<Segment> > m_setSegment;

	vector<int> m_partIndexs;
	vector<int> m_setNodeIndexs;
	vector<int> m_setSegIndexs;
};