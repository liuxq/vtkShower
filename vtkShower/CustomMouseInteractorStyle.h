#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkObjectFactory.h"
#include "vtkshower.h"




//��꽻���¼�
class customMouseInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
	static customMouseInteractorStyle* New();

	vtkTypeMacro(customMouseInteractorStyle, vtkInteractorStyleTrackballCamera);
	customMouseInteractorStyle();

	virtual void OnMouseMove()
	{
		vtkInteractorStyleTrackballCamera::OnMouseMove();

		if (vtkShower::instance->GetShowType() == ShowType::SetSeg)
		{
			vtkShower::instance->UpdateTextActorPos();
		}
	}
	virtual void OnMouseWheelForward()
	{
		vtkInteractorStyleTrackballCamera::OnMouseWheelForward();

		if (vtkShower::instance->GetShowType() == ShowType::SetSeg)
		{
			vtkShower::instance->UpdateTextActorPos();
		}
	}
	virtual void OnMouseWheelBackward()
	{
		vtkInteractorStyleTrackballCamera::OnMouseWheelBackward();

		if (vtkShower::instance->GetShowType() == ShowType::SetSeg)
		{
			vtkShower::instance->UpdateTextActorPos();
		}
	}

	virtual void OnKeyDown()
	{
		keyCode = this->GetInteractor()->GetKeyCode();
	}

	virtual void OnKeyUp()
	{
		keyCode = 255;
	}

	virtual void OnLeftButtonDown();

public:
	vtkActor* actor;
	char keyCode;
	vtkUnstructuredGrid* Data;
	vtkDataSetMapper* selectedMapper;
	vtkActor* selectedActor;
};

