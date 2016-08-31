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
}

void customMouseInteractorStyle::OnLeftButtonDown()
{
	if (keyCode == 'd')
	{
		int* clickPos = this->GetInteractor()->GetEventPosition();

		vtkSmartPointer<vtkCellPicker>  cellpicker = vtkSmartPointer<vtkCellPicker>::New();
		cellpicker->SetTolerance(0.0005);
		cellpicker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());

		if (cellpicker->GetCellId() != -1)
		{
			double* realpos = cellpicker->GetPickPosition();
			vtkCell* cell = cellpicker->GetActor()->GetMapper()->GetInputAsDataSet()->GetCell(cellpicker->GetCellId());
			int pointid = -1;
			double* pos;
			double minLen = 0xfffffff;
			for (int i = 0; i < cell->GetNumberOfPoints(); i++)
			{
				pos = cell->GetPoints()->GetPoint(i);
				double len = pos[0] * realpos[0] + pos[1] * realpos[1] + pos[2] * realpos[2];
				if (len < minLen)
				{
					minLen = len;
					pointid = cell->GetPointId(i);
				}
			}

			if (textActor)
			{
				this->GetDefaultRenderer()->RemoveActor(textActor);
				textActor->Delete();
			}
			textActor = vtkTextActor::New();
			QString str = "pointid:" + QString::number(pointid);
			str += "pos:" + QString::number(pos[0]);
			str += "," + QString::number(pos[1]);
			str += "," + QString::number(pos[2]);
			//	+ "pos:" + pos[0] + "," + pos[1] + "," + pos[2];
			textActor->SetInput(str.toUtf8().constData());

			this->GetDefaultRenderer()->AddActor2D(textActor);
			//Create a sphere
			vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
			sphereSource->SetCenter(pos[0], pos[1], pos[2]);
			sphereSource->SetRadius(0.1);

			this->GetDefaultRenderer()->RemoveActor(selectedActor);
			//Create a mapper and actor
			vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
			mapper->SetInputConnection(sphereSource->GetOutputPort());
			selectedActor->SetMapper(mapper);

			this->GetDefaultRenderer()->AddActor(selectedActor);

		}
		//// Pick from this location.
		//pointPicker->SetTolerance(0.002);
		//pointPicker->UseCellsOn();
		//pointPicker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());
		//if (pointPicker->GetPointId() != -1)
		//{
		//	//pointid = pointPicker->GetPointId();
		//	//double* pos = actor->GetMapper()->GetInputAsDataSet()->GetPoint(pointPicker->GetPointId());
		//	//this->pos[0] = pos[0];
		//	//this->pos[1] = pos[1];
		//	//this->pos[2] = pos[2];

		//	//if (textActor)
		//	//{
		//	//	this->GetDefaultRenderer()->RemoveActor(textActor);
		//	//	textActor->Delete();
		//	//}
		//	//textActor = vtkTextActor::New();
		//	//QString str = "pointid:" + QString::number(pointid);
		//	//str += "pos:" + QString::number(pos[0]);
		//	//str += "," + QString::number(pos[1]);
		//	//str += "," + QString::number(pos[2]);
		//	////	+ "pos:" + pos[0] + "," + pos[1] + "," + pos[2];
		//	//textActor->SetInput(str.toUtf8().constData());

		//	//this->GetDefaultRenderer()->AddActor2D(textActor);
		//	////Create a sphere
		//	//vtkSmartPointer<vtkSphereSource> sphereSource =	vtkSmartPointer<vtkSphereSource>::New();
		//	//sphereSource->SetCenter(pos[0], pos[1], pos[2]);
		//	//sphereSource->SetRadius(0.1);

		//	////Create a mapper and actor
		//	//vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		//	//mapper->SetInputConnection(sphereSource->GetOutputPort());

		//	vtkSmartPointer<vtkIdTypeArray> ids = vtkSmartPointer<vtkIdTypeArray>::New();
		//	ids->SetNumberOfComponents(1);
		//	ids->InsertNextValue(pointPicker->GetPointId());

		//	vtkSmartPointer<vtkSelectionNode> selectionNode =
		//		vtkSmartPointer<vtkSelectionNode>::New();
		//	selectionNode->SetFieldType(vtkSelectionNode::POINT);
		//	selectionNode->SetContentType(vtkSelectionNode::INDICES);
		//	selectionNode->SetSelectionList(ids);

		//	vtkSmartPointer<vtkSelection> selection =
		//		vtkSmartPointer<vtkSelection>::New();
		//	selection->AddNode(selectionNode);

		//	vtkSmartPointer<vtkExtractSelection> extractSelection =
		//		vtkSmartPointer<vtkExtractSelection>::New();

		//	extractSelection->SetInputData(0, pointPicker->GetActor()->GetMapper()->GetInputAsDataSet());
		//	extractSelection->SetInputData(1, selection);

		//	extractSelection->Update();

		//	// In selection
		//	vtkSmartPointer<vtkUnstructuredGrid> selected =
		//		vtkSmartPointer<vtkUnstructuredGrid>::New();
		//	selected->ShallowCopy(extractSelection->GetOutput());

		//	selectedMapper->SetInputData(selected);

		//	this->GetDefaultRenderer()->RemoveActor(selectedActor);

		//	selectedActor->SetMapper(selectedMapper);
		//	//selectedActor->GetProperty()->SetRepresentationToWireframe();
		//	//selectedActor->GetProperty()->EdgeVisibilityOn();
		//	selectedActor->GetProperty()->SetEdgeColor(1, 0, 0);
		//	selectedActor->GetProperty()->SetPointSize(10);
		//	//selectedActor->GetProperty()->SetLineWidth(3);

		//	this->GetDefaultRenderer()->AddActor(selectedActor);
		//}	
	}
	else if (keyCode == 'c')
	{
		int* clickPos = this->GetInteractor()->GetEventPosition();

		// Pick from this location.
		vtkSmartPointer<vtkCellPicker>  picker = vtkSmartPointer<vtkCellPicker>::New();
		picker->SetTolerance(0.0005);
		// Pick from this location.
		picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());

		if (picker->GetCellId() != -1)
		{
			vtkSmartPointer<vtkIdTypeArray> ids = vtkSmartPointer<vtkIdTypeArray>::New();
			ids->SetNumberOfComponents(1);
			ids->InsertNextValue(picker->GetCellId());

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

			extractSelection->SetInputData(0, picker->GetActor()->GetMapper()->GetInputAsDataSet());
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