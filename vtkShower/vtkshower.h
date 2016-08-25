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
class vtkMultiBlockDataSet;
class vtkLSDynaReader;
class vtkLookupTable;
class vtkDataSetMapper;
class vtkScalarBarActor;


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
	void RemoveLsdActors();
	void visPipeline();
	void visColorBar();

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
	vector<vtkMultiBlockDataSet*> m_vFrames;
	vector<vtkActor*> m_lsdPartActors;

	vtkDataSetMapper* unMapper;
	vtkScalarBarActor* colorTableBar;

	Vec3d m_textPos;
	vtkCoordinate* m_coordinate;
	vtkLSDynaReader* rdr;
	vtkLookupTable* lut;

	ShowType m_showType;
	int m_iCurStep;

public slots:
	void ComboChange(int);
	void onRadioClickSolid();
	void onRadioClickWareline();
	void onRadioClickSetNode();
	void onRadioClickSetSeg();
	void OnMenuOpenKFile();
	void OnButtonPlay();
};

#endif // VTKSHOWER_H
