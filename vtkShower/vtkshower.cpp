#include "vtkshower.h"
#include "vtkRenderWindow.h"

#include "vtkCylinderSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkInteractorStyleTrackballCamera.h"

#include "vtkLSDynaReader.h"
#include "vtkMultiBlockDataSet.h"
#include "vtkUnstructuredGrid.h"
#include "vtkCellData.h"
#include "vtkCompositeDataGeometryFilter.h"
#include "vtkDataSetMapper.h"
#include "vtkHexahedron.h"
#include "vtkTextActor.h"
#include "vtkTextProperty.h"
#include "vtkTextRenderer.h"

#include "vtkTextMapper.h"
#include "vtkArrowSource.h"
#include "vtkMatrix4x4.h"
#include "vtkTransform.h"
#include "vtkAxesActor.h"
#include "vtkOrientationMarkerWidget.h"
#include "vtkVectorText.h"
#include "vtkFollower.h"
#include "vtkTextActor3D.h"
#include "vtkCallbackCommand.h"
#include "vtkObjectFactory.h"


#include <QFileDialog>
#include <QDir>
#include <QEvent>
#include <QTextEncoder>

#include "ColorMapping.h"

//鼠标交互事件
class customMouseInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
	static customMouseInteractorStyle* New();
	vtkTypeMacro(customMouseInteractorStyle, vtkInteractorStyleTrackballCamera);

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
};

vtkStandardNewMacro(customMouseInteractorStyle);

vtkShower* vtkShower::instance = NULL;

vtkShower::vtkShower(QWidget *parent)
: QMainWindow(parent)
{
	if (instance == NULL)
		instance = this;

	ui.setupUi(this);

	m_pRenderder = vtkSmartPointer< vtkRenderer >::New();
	m_pRenWin = vtkSmartPointer<vtkRenderWindow>::New();
	m_pRenWin->AddRenderer(m_pRenderder);
	iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(m_pRenWin);
	vtkSmartPointer<customMouseInteractorStyle> style = vtkSmartPointer<customMouseInteractorStyle>::New();
	iren->SetInteractorStyle(style);

	connect(ui.comboBox, SIGNAL(activated(int)), this, SLOT(ComboChange(int)));
	connect(ui.radioButton_solid, SIGNAL(clicked()), this, SLOT(onRadioClickSolid()));
	connect(ui.radioButton_wareline, SIGNAL(clicked()), this, SLOT(onRadioClickWareline()));
	connect(ui.radioButton_setnode, SIGNAL(clicked()), this, SLOT(onRadioClickSetNode()));
	connect(ui.radioButton_setSeg, SIGNAL(clicked()), this, SLOT(onRadioClickSetSeg()));
	connect(ui.action, SIGNAL(triggered()), this, SLOT(OnMenuOpenKFile()));
	
}
void vtkShower::Clear()
{
	m_pRenderder->Clear();
	for (int i = 0; i < m_partActors.size(); i++)
		m_partActors[i]->ReleaseGraphicsResources();
	m_partActors.clear();

	for (int i = 0; i < m_setNodeActors.size(); i++)
		m_setNodeActors[i].Clear();
	m_setNodeActors.clear();

	for (int i = 0; i < m_setSegActors.size(); i++)
		m_setSegActors[i].Clear();
	m_setSegActors.clear();

	m_textActor->clear();

	vtkTextActor* m_textActor;
	map<int, vector<vtkActor*> > m_setSegArrowActors;
}
void vtkShower::LoadKFile(QString file)
{
	
	m_showType = Solid;
	m_kReader.read(file.toStdString());
	//体
	ColorMapping cm(m_kReader.GetParts().size() - 1, 0);
	for (int i = 0; i < m_kReader.GetParts().size(); i++)
	{
		vtkDataSetMapper* geoMapper = vtkDataSetMapper::New();
		geoMapper->SetInputData(m_kReader.GetElementByIndex(m_kReader.GetParts()[i]));

		vtkActor* partActor = vtkActor::New();
		partActor->SetMapper(geoMapper);

		Color c(cm.GetColor(i));
		partActor->GetProperty()->SetColor(c.r / 255.0, c.g / 255.0, c.b / 255.0);
		partActor->GetProperty()->EdgeVisibilityOn();
		m_pRenderder->AddActor(partActor);
		m_partActors.push_back(partActor);
	}
	//节点集合
	for (int i = 0; i < m_kReader.GetSetNode().size(); i++)
	{
		vtkDataSetMapper* geoMapper = vtkDataSetMapper::New();
		geoMapper->SetInputData(m_kReader.GetSetNodeList(m_kReader.GetSetNode()[i]));

		vtkActor* geoActor = vtkActor::New();
		geoActor->SetMapper(geoMapper);
		geoActor->GetProperty()->SetPointSize(5);
		geoActor->GetProperty()->SetColor(1, 0, 0);
		m_pRenderder->AddActor(geoActor);
		m_setNodeActors.push_back(geoActor);
		geoActor->VisibilityOff();
	}
	//节点面集合
	for (int i = 0; i < m_kReader.GetSetSeg().size(); i++)
	{
		vtkDataSetMapper* geoMapper = vtkDataSetMapper::New();
		geoMapper->SetInputData(m_kReader.GetSetSeg(m_kReader.GetSetSeg()[i]));

		vtkActor* geoActor = vtkActor::New();
		geoActor->SetMapper(geoMapper);
		geoActor->GetProperty()->SetLineWidth(3);
		geoActor->GetProperty()->SetColor(1, 1, 1);
		m_pRenderder->AddActor(geoActor);
		geoActor->GetProperty()->SetRepresentationToWireframe();
		m_setSegActors.push_back(geoActor);
		geoActor->VisibilityOff();

		//箭头
		vector<Vec3d> start, end;
		int count = m_kReader.GetSetSegArrow(m_kReader.GetSetSeg()[i], start, end);
		for (int j = 0; j < count; j++)
		{
			Vec3d dir = end[j] - start[j];
			double length = dir.Length();
			Vec3d normalX = dir / length;
			Vec3d arbi(vtkMath::Random(-10, 10), vtkMath::Random(-10, 10), vtkMath::Random(-10, 10));
			Vec3d normalZ = (normalX / arbi).Normalize();
			Vec3d normalY = normalZ / normalX;
			vtkMatrix4x4* matrix = vtkMatrix4x4::New();

			// Create the direction cosine matrix
			matrix->Identity();
			for (unsigned int k = 0; k < 3; k++)
			{
				matrix->SetElement(k, 0, normalX[k]);
				matrix->SetElement(k, 1, normalY[k]);
				matrix->SetElement(k, 2, normalZ[k]);
			}

			// Apply the transforms
			vtkTransform* transform = vtkTransform::New();
			transform->Translate(start[j]);
			transform->Concatenate(matrix);
			transform->Scale(length, length, length);

			vtkArrowSource* arrowSource = vtkArrowSource::New();
			arrowSource->Update();
			vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
			mapper->SetInputConnection(arrowSource->GetOutputPort());
			vtkActor* actor = vtkActor::New();
			actor->SetMapper(mapper);
			actor->SetUserMatrix(transform->GetMatrix());
			actor->VisibilityOff();
			m_pRenderder->AddActor(actor);
			m_setSegArrowActors[i].push_back(actor);
		}
	}

	//坐标系

	vtkAxesActor* axes = vtkAxesActor::New();

	vtkOrientationMarkerWidget* widget = vtkOrientationMarkerWidget::New();
	widget->SetOutlineColor(0.9300, 0.5700, 0.1300);
	widget->SetOrientationMarker(axes);
	widget->SetInteractor(iren);
	widget->SetViewport(0.0, 0.0, 0.2, 0.35);
	widget->SetEnabled(1);
	widget->InteractiveOff();

	//汉字
	m_textActor = vtkTextActor::New();
	m_textActor->SetPosition(0, 0);
	m_textActor->GetTextProperty()->SetFontFamily(VTK_FONT_FILE);
	m_textActor->GetTextProperty()->SetFontFile("ttf/楷体.ttf");
	m_textActor->GetTextProperty()->SetFontSize(24);
	m_textActor->GetTextProperty()->SetColor(1.0, 0.0, 0.0);
	m_pRenderder->AddActor2D(m_textActor);
	m_coordinate = vtkCoordinate::New();
	m_coordinate->SetCoordinateSystemToWorld();

	m_pRenderder->SetBackground(0.2, 0.2, 0.2);

	m_pRenderder->ResetCamera();
	m_pRenderder->GetActiveCamera()->Zoom(1.5);
	ui.qvtkWidget->SetRenderWindow(m_pRenWin);
	ui.qvtkWidget->GetRenderWindow()->Render();



	// init UI
	for (int i = 0; i < m_kReader.GetParts().size(); i++)
	{
		ui.comboBox->addItem(QString::number(m_kReader.GetParts()[i]));
	}
}

void vtkShower::UpdateTextActorPos()
{
	m_coordinate->SetValue(m_textPos);
	int* view = m_coordinate->GetComputedDisplayValue(vtkShower::instance->GetRenderer());
	m_textActor->SetPosition((double)view[0], (double)view[1]);
	m_pRenWin->Render();
}

void vtkShower::ComboChange(int index)
{
	if (Solid == m_showType)
	{
		for (int i = 0; i < m_partActors.size(); i++)
		{
			if (i == index)
			{
				m_partActors[i]->GetProperty()->SetRepresentationToSurface();
			}
			else
			{
				m_partActors[i]->GetProperty()->SetRepresentationToWireframe();
			}
		}
	}
	else if (SetNode == m_showType)
	{
		for (int i = 0; i < m_setNodeActors.size(); i++)
		{
			if (i == index)
			{
				m_setNodeActors[i]->VisibilityOn();
			}
			else
			{
				m_setNodeActors[i]->VisibilityOff();
			}
		}
	}
	else if (SetSeg == m_showType)
	{
		if (m_setSegActors.empty())
		{
			return;
		}
		for (int i = 0; i < m_setSegActors.size(); i++)
		{
			if (i == index)
			{
				m_setSegActors[i]->VisibilityOn();
				for (int j = 0; j < m_setSegArrowActors[i].size(); j++)
				{
					m_setSegArrowActors[i][j]->VisibilityOn();
				}
			}
			else
			{
				m_setSegActors[i]->VisibilityOff();
				for (int j = 0; j < m_setSegArrowActors[i].size(); j++)
				{
					m_setSegArrowActors[i][j]->VisibilityOff();
				}
			}
		}
		if (index == 0)
		{
			m_textActor->SetInput(QString::fromLocal8Bit("压力").toUtf8().constData());
			vector<Vec3d> start, end;
			m_kReader.GetSetSegArrow(m_kReader.GetSetSeg()[index], start, end);
			m_textPos = start[0];
		}
		else
		{
			m_textActor->SetInput(QString::fromLocal8Bit("集中力").toUtf8().constData());
			vector<Vec3d> start, end;
			m_kReader.GetSetSegArrow(m_kReader.GetSetSeg()[index], start, end);
			m_textPos = start[0];
		}
		UpdateTextActorPos();
			
	}
	
	m_pRenWin->Render();
}

void vtkShower::SetAllSetSegVisible(bool bVisible)
{
	for (int i = 0; i < m_setSegActors.size(); i++)
	{
		m_setSegActors[i]->SetVisibility(bVisible);
		for (int j = 0; j < m_setSegArrowActors[i].size(); j++)
		{
			m_setSegArrowActors[i][j]->SetVisibility(bVisible);
		}	
	}
}
void vtkShower::SetAllPartWireLine(bool beWireline)
{
	for (int i = 0; i < m_partActors.size(); i++)
	{
		if (beWireline)
			m_partActors[i]->GetProperty()->SetRepresentationToWireframe();
		else
			m_partActors[i]->GetProperty()->SetRepresentationToSurface();
	}
}
void vtkShower::onRadioClickSolid()
{
	m_showType = Solid;
	SetAllPartWireLine(false);
	m_textActor->SetInput(nullptr);
	for (int i = 0; i < m_setNodeActors.size(); i++)
	{
		m_setNodeActors[i]->VisibilityOff();
	}
	SetAllSetSegVisible(false);
	m_pRenWin->Render();
	

	ui.label_doc->setHidden(false); 
	ui.comboBox->setHidden(false);
	ui.label_doc->setText(QString::fromLocal8Bit("体编号："));
	ui.comboBox->clear();
	for (int i = 0; i < m_kReader.GetParts().size(); i++)
	{
		ui.comboBox->addItem(QString::number(m_kReader.GetParts()[i]));
	}

	//ComboChange(0);
}

void vtkShower::onRadioClickWareline()
{
	m_showType = Wireline;
	SetAllPartWireLine(true);
	m_textActor->SetInput(nullptr);
	for (int i = 0; i < m_setNodeActors.size(); i++)
	{
		m_setNodeActors[i]->VisibilityOff();
	}
	SetAllSetSegVisible(false);
	m_pRenWin->Render();
	ui.label_doc->setHidden(true);
	ui.comboBox->setHidden(true);
}

void vtkShower::onRadioClickSetNode()
{
	m_showType = SetNode;
	SetAllPartWireLine(true);
	m_textActor->SetInput(nullptr);
	SetAllSetSegVisible(false);

	ui.label_doc->setHidden(false);
	ui.comboBox->setHidden(false);
	ui.label_doc->setText(QString::fromLocal8Bit("节点集合编号："));
	ui.comboBox->clear();
	for (int i = 0; i < m_kReader.GetSetNode().size(); i++)
	{
		ui.comboBox->addItem(QString::number(m_kReader.GetSetNode()[i]));
	}
	ComboChange(0);
}

void vtkShower::onRadioClickSetSeg()
{
	m_showType = SetSeg;
	SetAllPartWireLine(true);
	for (int i = 0; i < m_setNodeActors.size(); i++)
	{
		m_setNodeActors[i]->VisibilityOff();
	}
	ui.label_doc->setHidden(false);
	ui.comboBox->setHidden(false);
	ui.label_doc->setText(QString::fromLocal8Bit("节点面编号："));

	ui.comboBox->clear();
	for (int i = 0; i < m_kReader.GetSetSeg().size(); i++)
	{
		ui.comboBox->addItem(QString::number(m_kReader.GetSetSeg()[i]));
	}
	ComboChange(0);
}

void vtkShower::resizeEvent(QResizeEvent * event) {
	ui.horizontalLayoutWidget->resize(this->size());
}

void vtkShower::OnMenuOpenKFile()
{
	QString filter;
	filter = "k file (*.k)";
	QDir dir;
	QString fileName = QFileDialog::getOpenFileName(this, QString(tr("打开k文件")), dir.absolutePath(), filter);
	if (fileName.isEmpty() == true) return;

	LoadKFile(fileName);
}

vtkShower::~vtkShower()
{

}
