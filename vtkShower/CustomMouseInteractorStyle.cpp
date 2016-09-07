#include "CustomMouseInteractorStyle.h"
#include "vtkPolyDataMapper.h"
#include "vtkPropPicker.h"
#include "vtkSphereSource.h"
#include "vtkCellPicker.h"
#include "vtkSelectionNode.h"
#include "vtkSelection.h"
#include "vtkExtractSelection.h"
#include "vtkUnstructuredGrid.h"
#include "vtkDataSetMapper.h"
#include "vtkProperty.h"
#include "vtkPointPicker.h"
#include "vtkTextActor.h"

vtkStandardNewMacro(customMouseInteractorStyle);

customMouseInteractorStyle::customMouseInteractorStyle()
{
	actor = NULL;
	textActor = NULL;
	selectedMapper = vtkDataSetMapper::New();
	selectedActor = vtkActor::New();
	pointPicker = vtkPointPicker::New();
	cellForPointPicker = vtkCellPicker::New();
	cellPicker = vtkCellPicker::New();
	sphereSource = vtkSphereSource::New();
}

void customMouseInteractorStyle::OnLeftButtonDown()
{
	if (keyCode == 'd')
	{
		int* clickPos = this->GetInteractor()->GetEventPosition();

		cellForPointPicker->SetTolerance(0.0005);
		cellForPointPicker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());

		if (cellForPointPicker->GetCellId() != -1)
		{
			curActor = cellForPointPicker->GetActor();
			
			isPoint = true;

			double* realpos = cellForPointPicker->GetPickPosition();
			vtkCell* cell = cellForPointPicker->GetActor()->GetMapper()->GetInputAsDataSet()->GetCell(cellForPointPicker->GetCellId());
			int pointid = -1;
			double* pos;
			double p1, p2, p3;
			double minLen = 0xfffffff;
			for (int i = 0; i < cell->GetNumberOfPoints(); i++)
			{
				pos = cell->GetPoints()->GetPoint(i);
				
				double len = (pos[0] - realpos[0])*(pos[0] - realpos[0]) + (pos[1] - realpos[1])*(pos[1] - realpos[1]) + (pos[2] - realpos[2])*(pos[2] - realpos[2]);
				if (len < minLen)
				{
					minLen = len;
					pointid = cell->GetPointId(i);
					p1 = pos[0];
					p2 = pos[1];
					p3 = pos[2];
				}
			}

			pointId = pointid;

			if (textActor)
			{
				this->GetDefaultRenderer()->RemoveActor(textActor);
				textActor->Delete();
			}
			textActor = vtkTextActor::New();
			QString str = "pointid:" + QString::number(pointid);
			str += "pos:" + QString::number(p1);
			str += "," + QString::number(p2);
			str += "," + QString::number(p3);
			textActor->SetInput(str.toUtf8().constData());

			this->GetDefaultRenderer()->AddActor2D(textActor);
			
			//set sphere pos
			sphereSource->SetCenter(p1, p2, p3);
			sphereSource->SetRadius(0.1);

			this->GetDefaultRenderer()->RemoveActor(selectedActor);
			//Create a mapper and actor
			vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
			mapper->SetInputConnection(sphereSource->GetOutputPort());
			selectedActor->SetMapper(mapper);

			this->GetDefaultRenderer()->AddActor(selectedActor);

		}
	}
	else if (keyCode == 'c')
	{
		int* clickPos = this->GetInteractor()->GetEventPosition();

		cellPicker->SetTolerance(0.0005);
		// Pick from this location.
		cellPicker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());

		if (cellPicker->GetCellId() != -1)
		{
			curActor = cellPicker->GetActor();
			cellId = cellPicker->GetCellId();
			isPoint = false;

			vtkSmartPointer<vtkIdTypeArray> ids = vtkSmartPointer<vtkIdTypeArray>::New();
			ids->SetNumberOfComponents(1);
			ids->InsertNextValue(cellPicker->GetCellId());

			vtkSmartPointer<vtkSelectionNode> selectionNode =
				vtkSmartPointer<vtkSelectionNode>::New();
			selectionNode->SetFieldType(vtkSelectionNode::CELL);
			selectionNode->SetContentType(vtkSelectionNode::INDICES);
			selectionNode->SetSelectionList(ids);

			vtkSmartPointer<vtkSelection> selection =
				vtkSmartPointer<vtkSelection>::New();
			selection->AddNode(selectionNode);

			vtkSmartPointer<vtkExtractSelection> extractSelection =
				vtkSmartPointer<vtkExtractSelection>::New();

			extractSelection->SetInputData(0, cellPicker->GetActor()->GetMapper()->GetInputAsDataSet());
			extractSelection->SetInputData(1, selection);

			extractSelection->Update();

			// In selection
			vtkSmartPointer<vtkUnstructuredGrid> selected =
				vtkSmartPointer<vtkUnstructuredGrid>::New();
			selected->ShallowCopy(extractSelection->GetOutput());

			selectedMapper->SetInputData(selected);

			this->GetDefaultRenderer()->RemoveActor(selectedActor);

			selectedActor->SetMapper(selectedMapper);
			selectedActor->GetProperty()->SetRepresentationToWireframe();
			selectedActor->GetProperty()->EdgeVisibilityOn();
			selectedActor->GetProperty()->SetEdgeColor(1, 0, 0);
			selectedActor->GetProperty()->SetLineWidth(3);

			this->GetDefaultRenderer()->AddActor(selectedActor);
		}
	}
	
	// Forward events
	vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}