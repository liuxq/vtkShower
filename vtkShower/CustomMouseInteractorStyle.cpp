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

vtkStandardNewMacro(customMouseInteractorStyle);

customMouseInteractorStyle::customMouseInteractorStyle()
{
	actor = NULL;
	selectedMapper = vtkDataSetMapper::New();
	selectedActor = vtkActor::New();
}

void customMouseInteractorStyle::OnLeftButtonDown()
{
	if (keyCode == 'd')
	{
		int* clickPos = this->GetInteractor()->GetEventPosition();

		// Pick from this location.
		vtkSmartPointer<vtkPointPicker>  pointPicker = vtkSmartPointer<vtkPointPicker>::New();
		pointPicker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());

		if (pointPicker->GetPointId() != -1)
		{
			double* pos = pointPicker->GetActor()->GetMapper()->GetInputAsDataSet()->GetPoint(pointPicker->GetPointId());
			//Create a sphere
			vtkSmartPointer<vtkSphereSource> sphereSource =
				vtkSmartPointer<vtkSphereSource>::New();
			sphereSource->SetCenter(pos[0], pos[1], pos[2]);
			sphereSource->SetRadius(0.1);

			//Create a mapper and actor
			vtkSmartPointer<vtkPolyDataMapper> mapper =
				vtkSmartPointer<vtkPolyDataMapper>::New();
			mapper->SetInputConnection(sphereSource->GetOutputPort());

			if (actor)
			{
				this->GetDefaultRenderer()->RemoveActor(actor);
				actor->Delete();
			}

			actor = vtkActor::New();
			actor->SetMapper(mapper);

			this->GetDefaultRenderer()->AddActor(actor);
		}	
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