#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkObjectFactory.h"
#include "vtkshower.h"


class vtkPointPicker;
class vtkCellPicker;
class vtkSphereSource;

//鼠标交互事件
class customMouseInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
	static customMouseInteractorStyle* New();

	vtkTypeMacro(customMouseInteractorStyle, vtkInteractorStyleTrackballCamera);
	customMouseInteractorStyle();

	virtual void OnMouseMove()
	{
		vtkInteractorStyleTrackballCamera::OnMouseMove();

		if (vtkShower::instance->GetShowType() == KShowType::SetSeg)
		{
			vtkShower::instance->UpdateTextActorPos();
		}
	}
	virtual void OnMouseWheelForward()
	{
		vtkInteractorStyleTrackballCamera::OnMouseWheelForward();

		if (vtkShower::instance->GetShowType() == KShowType::SetSeg)
		{
			vtkShower::instance->UpdateTextActorPos();
		}
	}
	virtual void OnMouseWheelBackward()
	{
		vtkInteractorStyleTrackballCamera::OnMouseWheelBackward();

		if (vtkShower::instance->GetShowType() == KShowType::SetSeg)
		{
			vtkShower::instance->UpdateTextActorPos();
		}
	}

	//virtual void OnKeyDown()
	//{
	//	keyCode = this->GetInteractor()->GetKeySym();
	//}

	//virtual void OnKeyUp()
	//{
	//	keyCode = "";
	//}

	virtual void OnLeftButtonDown();

public:
	vtkActor* actor;
	string keyCode;
	vtkUnstructuredGrid* Data;
	vtkDataSetMapper* selectedMapper;
	vtkActor* selectedActor;

	vtkTextActor* textActor;
	vtkPointPicker*  pointPicker;
	vtkCellPicker*  cellForPointPicker;
	vtkCellPicker*  cellPicker;
	vtkSphereSource* sphereSource;

	vtkActor* curActor;
	bool isPoint;
	int pointId;
	int cellId;
	bool isPointSelectMode;
};

