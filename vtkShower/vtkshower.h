#ifndef VTKSHOWER_H
#define VTKSHOWER_H

#include <QtWidgets/QMainWindow>
#include "ui_vtkshower.h"
#include "QVTKWidget.h"
#include "vtkImageViewer2.h"
#include "vtkSmartPointer.h"
#include "vtkRenderer.h"
#include "kReader.h"

#include <map>

class vtkTextActor;
class vtkCoordinate;

enum ShowType
{
	Solid,
	Wireline,
	SetNode,
	SetSeg
};

class vtkShower : public QMainWindow
{
	Q_OBJECT

public:
	vtkShower(QWidget *parent = 0);
	~vtkShower();

	static vtkShower* instance;
	vtkSmartPointer< vtkRenderer >   GetRenderer(){ return  m_pRenderder; }
	vtkSmartPointer<vtkRenderWindow>	GetRenWin(){ return	m_pRenWin; }
	vtkTextActor* GetTextActor(){ return m_textActor; }
	ShowType GetShowType() { return m_showType; }
	void UpdateTextActorPos();

protected:
	void resizeEvent(QResizeEvent * event);
	void SetAllPartWireLine(bool);
	void SetAllSetSegVisible(bool bVisible);
	void LoadKFile(QString);
	void Clear();

private:
	Ui::vtkShowerClass ui;

	//自定义控件
	vtkSmartPointer< vtkImageViewer2 >          m_pImageViewer;
	vtkSmartPointer< vtkRenderer >              m_pRenderder;
	vtkSmartPointer<vtkRenderWindow>			m_pRenWin;
	vtkRenderWindowInteractor* iren;
	kReader m_kReader;

	vector<vtkActor*> m_partActors;
	vector<vtkActor*> m_setNodeActors;
	vector<vtkActor*> m_setSegActors;
	vtkTextActor* m_textActor;
	map<int, vector<vtkActor*> > m_setSegArrowActors;

	Vec3d m_textPos;
	vtkCoordinate* m_coordinate;

	ShowType m_showType;

public slots:
	void ComboChange(int);
	void onRadioClickSolid();
	void onRadioClickWareline();
	void onRadioClickSetNode();
	void onRadioClickSetSeg();
	void OnMenuOpenKFile();
};

#endif // VTKSHOWER_H
