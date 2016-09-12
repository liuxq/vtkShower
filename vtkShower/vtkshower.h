#ifndef VTKSHOWER_H
#define VTKSHOWER_H

#include <QtWidgets/QMainWindow>
#include "ui_vtkshower.h"
#include "ui_lineDialog.h"
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
class customMouseInteractorStyle;
class QTimer;


enum KShowType
{
	Solid,
	Wireline,
	SetNode,
	SetSeg
};

enum LsdShowType
{
	Point,
	Shell,
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
	vtkTextActor* GetTextActor(){ return m_textKElementActor; }
	KShowType GetShowType() { return m_kShowType; }
	void UpdateTextActorPos();
	int m_TypeMode;//1 k, 0 lsd, 2 none

protected:
	void resizeEvent(QResizeEvent * event);
	void SetAllPartWireLine(bool);
	void SetAllSetSegVisible(bool bVisible);
	void LoadKFile(QString);
	void RemoveKActors();
	void RemoveLsdActors();
	void visPipeline();
	void visColorBar();
	void RenderLsd();
	void UISet(int);
	void SetAxis();
	vtkActor* GetLSDActorByIndex(int);

private:
	Ui::vtkShowerClass ui;
	Ui::Dialog_line ui_dialog;
	QDialog* m_dialogLine;
	//LineWidget* m_widgetLine;

	//自定义控件
	vtkSmartPointer< vtkImageViewer2 >          m_pImageViewer;
	vtkSmartPointer< vtkRenderer >              m_pRenderder;
	vtkSmartPointer<vtkRenderWindow>			m_pRenWin;
	vtkRenderWindowInteractor* iren;
	kReader m_kReader;

	vector<vtkActor*> m_partActors;
	vector<vtkActor*> m_setNodeActors;
	vector<vtkActor*> m_setSegActors;
	vtkTextActor* m_textKElementActor;
	vtkTextActor* m_textLSDRangeActor;
	map<int, vector<vtkActor*> > m_setSegArrowActors;
	vector<vtkMultiBlockDataSet*> m_vFrames;
	vector<vtkActor*> m_lsdPartActors;

	vtkDataSetMapper* unMapper;
	vtkScalarBarActor* colorTableBar;

	Vec3d m_textPos;
	vtkCoordinate* m_coordinate;
	vtkLSDynaReader* rdr;
	vtkLookupTable* lut;
	customMouseInteractorStyle* m_style;

	KShowType m_kShowType;

	LsdShowType m_lShowType;
	int m_iDataIndex;
	int m_iCurStep;

	vector<double> m_lines;

	QTimer *LsdPlaytimer;

	float m_rangeMin;
	float m_rangeMax;
	bool m_rangeMode;//0 auto, 1 custom
	int m_iCurPartIndex;
	

public slots:
	void onPartComboChange(int);
	void onDataComboChange(int);
	void onRadioClickSolid();
	void onRadioClickWareline();
	void onRadioClickSetNode();
	void onRadioClickSetSeg();
	void onRadioClickPointData();
	void onRadioClickShellData();
	void onSliderValueChange(int);
	void onButtonLine();
	void OnButtonCloseLine();
	void OnTimerOut();
	
	void OnMenuOpenKFile();
	void OnMenuOpenLSDFile();
	void OnButtonPlay();
	void OnButtonStop();
	void onDataRangeComboChange(int);
	void onLsdPartComboChange(int);
	void onButtonChangeRange();
};

#endif // VTKSHOWER_H
