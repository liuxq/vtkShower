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
#include "vtkLookupTable.h"
#include "CustomMouseInteractorStyle.h"
#include "vtkScalarBarActor.h"
#include "vtkPointData.h"
#include "linewidget.h"
#include "vtkFloatArray.h"
#include "vtkDoubleArray.h"


#include <QFileDialog>
#include <QDir>
#include <QEvent>
#include <QTextEncoder>
#include <QTimer>
#include <QTextCodec>
#include <qcheckbox>

#include "ColorMapping.h"


vtkShower* vtkShower::instance = NULL;

vtkShower::vtkShower(QWidget *parent)
: QMainWindow(parent), m_iCurStep(0), m_iDataIndex(0), m_rangeMode(0), 
m_rangeMin(-1), m_rangeMax(1), m_TypeMode(2)
{
	if (instance == NULL)
		instance = this;

	m_textKElementActor = NULL;
	ui.setupUi(this);

	m_dialogLine = new QDialog(this);
	ui_dialog.setupUi(m_dialogLine);
	m_dialogLine->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);

	m_pRenderder = vtkSmartPointer< vtkRenderer >::New();
	m_pRenWin = vtkSmartPointer<vtkRenderWindow>::New();
	m_pRenWin->AddRenderer(m_pRenderder);
	iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(m_pRenWin);
	m_style = customMouseInteractorStyle::New();
	iren->SetInteractorStyle(m_style);
	m_style->SetDefaultRenderer(m_pRenderder);
	m_pRenderder->SetBackground(0.2, 0.2, 0.2);
	ui.qvtkWidget->SetRenderWindow(m_pRenWin);
	ui.qvtkWidget->GetRenderWindow()->Render();
	lut = vtkLookupTable::New();
	colorTableBar = vtkScalarBarActor::New();

	m_textLSDRangeActor = vtkTextActor::New();
	m_textLSDRangeActor->SetPosition(0, 0);
	m_textLSDRangeActor->GetTextProperty()->SetFontSize(16);
	m_textLSDRangeActor->GetTextProperty()->SetColor(1.0, 0.0, 0.0);
	
	ui.comboBox_data_color->addItem(QString::fromLocal8Bit("自动"));
	ui.comboBox_data_color->addItem(QString::fromLocal8Bit("自定义"));

	m_pRenderder->ResetCamera();
	m_pRenderder->GetActiveCamera()->Zoom(1.5);

	SetAxis();
	UISet(m_TypeMode);

	connect(ui.comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onPartComboChange(int)));
	connect(ui.comboBox_data_name, SIGNAL(currentIndexChanged(int)), this, SLOT(onDataComboChange(int)));
	connect(ui.radioButton_solid, SIGNAL(clicked()), this, SLOT(onRadioClickSolid()));
	connect(ui.radioButton_wareline, SIGNAL(clicked()), this, SLOT(onRadioClickWareline()));
	connect(ui.radioButton_setnode, SIGNAL(clicked()), this, SLOT(onRadioClickSetNode()));
	connect(ui.radioButton_setSeg, SIGNAL(clicked()), this, SLOT(onRadioClickSetSeg()));
	connect(ui.action, SIGNAL(triggered()), this, SLOT(OnMenuOpenKFile()));

	connect(ui.comboBox_data_color, SIGNAL(currentIndexChanged(int)), this, SLOT(onDataRangeComboChange(int)));
	//connect(ui.comboBox_part, SIGNAL(currentIndexChanged(int)), this, SLOT(onLsdPartComboChange(int)));
	connect(ui.action_LSDyna, SIGNAL(triggered()), this, SLOT(OnMenuOpenLSDFile()));
	connect(ui.pushButton_play, SIGNAL(clicked()), this, SLOT(OnButtonPlay()));
	connect(ui.pushButton_stop, SIGNAL(clicked()), this, SLOT(OnButtonStop()));
	connect(ui.radioButton_point_data, SIGNAL(clicked()), this, SLOT(onRadioClickPointData()));
	connect(ui.radioButton_shell_data, SIGNAL(clicked()), this, SLOT(onRadioClickShellData()));
	connect(ui.horizontalSlider_frame, SIGNAL(valueChanged(int)), this, SLOT(onSliderValueChange(int)));
	connect(ui.pushButton_line, SIGNAL(clicked()), this, SLOT(onButtonLine()));
	connect(ui.pushButton_range_change, SIGNAL(clicked()), this, SLOT(onButtonChangeRange()));
	
	connect(ui_dialog.pushButton, SIGNAL(clicked()), this, SLOT(OnButtonCloseLine()));

	LsdPlaytimer = new QTimer(this);
	connect(LsdPlaytimer, SIGNAL(timeout()), this, SLOT(OnTimerOut()));

	//OnMenuOpenLSDFile();
}

void vtkShower::SetAxis()
{
	//坐标系
	vtkAxesActor* axes = vtkAxesActor::New();
	vtkOrientationMarkerWidget* widget = vtkOrientationMarkerWidget::New();
	widget->SetOutlineColor(0.9300, 0.5700, 0.1300);
	widget->SetOrientationMarker(axes);
	widget->SetInteractor(iren);
	widget->SetViewport(0.0, 0.0, 0.2, 0.35);
	widget->SetEnabled(1);
	widget->InteractiveOff();
}

void vtkShower::UISet(int index)
{
	if (index == 0)
	{
		ui.right_widget_k->setVisible(false);
		ui.right_widget_lsd->setVisible(true);
		ui.playWidget->setVisible(true);
	}
	else if (index == 1)
	{
		ui.right_widget_k->setVisible(true);
		ui.right_widget_lsd->setVisible(false);
		ui.playWidget->setVisible(false);
	}
	else
	{
		ui.right_widget_k->setVisible(false);
		ui.right_widget_lsd->setVisible(false);
		ui.playWidget->setVisible(false);
	}
}

void vtkShower::RemoveKActors()
{
	m_kReader.Clear();
	m_pRenderder->Clear();
	for (int i = 0; i < m_partActors.size(); i++)
	{
		m_pRenderder->RemoveActor(m_partActors[i]);
		m_partActors[i]->Delete();
	}
	m_partActors.clear();

	for (int i = 0; i < m_setNodeActors.size(); i++)
	{
		m_pRenderder->RemoveActor(m_setNodeActors[i]);
		m_setNodeActors[i]->Delete();
	}
	m_setNodeActors.clear();

	for (int i = 0; i < m_setSegActors.size(); i++)
	{
		m_pRenderder->RemoveActor(m_setSegActors[i]);
		m_setSegActors[i]->Delete();
	}
	m_setSegActors.clear();
	
	if (m_textKElementActor)
	{
		m_pRenderder->RemoveActor2D(m_textKElementActor);
		m_textKElementActor->Delete();
		m_textKElementActor = NULL;
	}

	for (int i = 0; i < m_setSegArrowActors.size(); i++)
	{
		for (int j = 0; j < m_setSegArrowActors[i].size(); j++)
		{
			m_pRenderder->RemoveActor(m_setSegArrowActors[i][j]);
			m_setSegArrowActors[i][j]->Delete();
		}
		m_setSegArrowActors[i].clear();
	}
	m_setSegArrowActors.clear();
}
void vtkShower::LoadKFile(QString file)
{
	m_kShowType = Solid;
	m_kReader.read((const char*)file.toLocal8Bit());
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

	

	//汉字
	m_textKElementActor = vtkTextActor::New();
	m_textKElementActor->SetPosition(0, 0);
	m_textKElementActor->GetTextProperty()->SetFontFamily(VTK_FONT_FILE);
	m_textKElementActor->GetTextProperty()->SetFontFile("ttf/楷体.ttf");
	m_textKElementActor->GetTextProperty()->SetFontSize(24);
	m_textKElementActor->GetTextProperty()->SetColor(1.0, 0.0, 0.0);
	m_pRenderder->AddActor2D(m_textKElementActor);
	m_coordinate = vtkCoordinate::New();
	m_coordinate->SetCoordinateSystemToWorld();

	
	m_pRenderder->ResetCamera();
	m_pRenderder->GetActiveCamera()->Zoom(1.5);

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
	m_textKElementActor->SetPosition((double)view[0], (double)view[1]);
	m_pRenWin->Render();
}

void vtkShower::onPartComboChange(int index)
{
	if (Solid == m_kShowType)
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
	else if (SetNode == m_kShowType)
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
	else if (SetSeg == m_kShowType)
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
			m_textKElementActor->SetInput(QString::fromLocal8Bit("压力").toUtf8().constData());
			vector<Vec3d> start, end;
			m_kReader.GetSetSegArrow(m_kReader.GetSetSeg()[index], start, end);
			m_textPos = start[0];
		}
		else if (index > 0)
		{
			m_textKElementActor->SetInput(QString::fromLocal8Bit("集中力").toUtf8().constData());
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
	m_kShowType = Solid;
	SetAllPartWireLine(false);
	m_textKElementActor->SetInput(nullptr);
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
	m_kShowType = Wireline;
	SetAllPartWireLine(true);
	m_textKElementActor->SetInput(nullptr);
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
	m_kShowType = SetNode;
	SetAllPartWireLine(true);
	m_textKElementActor->SetInput(nullptr);
	SetAllSetSegVisible(false);

	ui.label_doc->setHidden(false);
	ui.comboBox->setHidden(false);
	ui.label_doc->setText(QString::fromLocal8Bit("节点集合编号："));
	ui.comboBox->clear();
	for (int i = 0; i < m_kReader.GetSetNode().size(); i++)
	{
		ui.comboBox->addItem(QString::number(m_kReader.GetSetNode()[i]));
	}
	onPartComboChange(0);
}

void vtkShower::onRadioClickSetSeg()
{
	m_kShowType = SetSeg;
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
	onPartComboChange(0);
}

void vtkShower::onRadioClickPointData()
{
	if (m_iCurStep >= m_vFrames.size())
		return;
	m_lShowType = Point;
	m_style->isPointSelectMode = true;
	ui.comboBox_data_name->clear();

	vtkMultiBlockDataSet* mbds = m_vFrames[m_iCurStep];
	//找到第一个要显示的part，并设置数据
	for (int j = 0; j < m_partsCbs.size(); j++)
	{
		if (m_partsCbs[j]->isChecked())
		{
			int type = mbds->GetBlock(j)->GetDataObjectType();
			if (type == VTK_UNSTRUCTURED_GRID)
			{
				vtkUnstructuredGrid* ugrid = vtkUnstructuredGrid::SafeDownCast(mbds->GetBlock(j));
				for (int i = 0; i < ugrid->GetPointData()->GetNumberOfArrays(); i++)
				{
					ui.comboBox_data_name->addItem(QString(ugrid->GetPointData()->GetArrayName(i)));
				}
				if (ugrid->GetPointData()->GetNumberOfArrays() > 0)
					onDataComboChange(0);
			}
			break;
		}
	}
	
}

void vtkShower::onRadioClickShellData()
{
	if (m_iCurStep >= m_vFrames.size())
		return;
	m_lShowType = Shell;
	m_style->isPointSelectMode = false;
	ui.comboBox_data_name->clear();
	vtkMultiBlockDataSet* mbds = m_vFrames[m_iCurStep];

	//找到第一个要显示的part，并设置数据
	for (int j = 0; j < m_partsCbs.size(); j++)
	{
		if (m_partsCbs[j]->isChecked())
		{
			int type = mbds->GetBlock(j)->GetDataObjectType();
			if (type == VTK_UNSTRUCTURED_GRID)
			{
				vtkUnstructuredGrid* ugrid = vtkUnstructuredGrid::SafeDownCast(mbds->GetBlock(j));
				for (int i = 0; i < ugrid->GetCellData()->GetNumberOfArrays(); i++)
				{
					ui.comboBox_data_name->addItem(QString(ugrid->GetCellData()->GetArrayName(i)));
				}
				if (ugrid->GetCellData()->GetNumberOfArrays() > 0)
					onDataComboChange(0);
			}
			break;
		}
	}
}

void vtkShower::onDataComboChange(int index)
{
	m_iDataIndex = index;
	if (m_iDataIndex >= 0)
	{
		RenderLsd();
	}
}

void vtkShower::onSliderValueChange(int index)
{
	if (index >= rdr->GetNumberOfTimeSteps())
		index = rdr->GetNumberOfTimeSteps() - 1;
	if (index < 0)
		index = 0;
	m_iCurStep = index;
	ui.label_frame->setText(QString::number(m_iCurStep));
	RenderLsd();
}

void vtkShower::resizeEvent(QResizeEvent * event) {
	ui.horizontalLayoutWidget->resize(this->size().width(), this->size().height() - 50);
}

void vtkShower::OnMenuOpenLSDFile()
{
	QDir dir;
	QString dirName = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("打开Lsdyna文件库"), dir.absolutePath());
	if (dirName.isEmpty() == true) return;

	m_TypeMode = 0;

	RemoveKActors();
	RemoveLsdActors();

	rdr = vtkLSDynaReader::New();
	rdr->SetDatabaseDirectory(dirName.toLocal8Bit());
	//rdr->SetDatabaseDirectory("D:/result_demo32");
	//rdr->SetDatabaseDirectory("C:/EM");
	rdr->Update();

	/*ofstream lxq("lxq.txt");
	vtkIndent vi;
	rdr->PrintSelf(lxq, vi);*/

	for (int i = 0; i < m_partsCbs.size(); i++)
	{
		ui.verticalLayout_part->removeWidget(m_partsCbs[i]);
		disconnect(m_partsCbs[i], SIGNAL(stateChanged(int)), this, SLOT(onLsdPartSelect(int)));
		m_partsCbs[i]->deleteLater();
	}
	m_partsCbs.clear();
	vtkMultiBlockDataSet* mbds1 = vtkMultiBlockDataSet::SafeDownCast(rdr->GetOutput());
	for (int j = 0; j < mbds1->GetNumberOfBlocks(); j++)
	{
		QCheckBox* cb = new QCheckBox(ui.right_widget_lsd);
		cb->setChecked(true);
		cb->setText(QString::number(j));
		ui.verticalLayout_part->addWidget(cb);
		m_partsCbs.push_back(cb);
		connect(cb, SIGNAL(stateChanged(int)), this, SLOT(onLsdPartSelect(int)));
	}

	for (int i = 0; i < rdr->GetNumberOfTimeSteps(); i++)
	{
		rdr->SetTimeStep(i);
		rdr->Update();
		vtkMultiBlockDataSet* mbds = vtkMultiBlockDataSet::SafeDownCast(rdr->GetOutput());
		vtkMultiBlockDataSet* mbds2 = vtkMultiBlockDataSet::New();
		mbds2->DeepCopy(mbds);
		m_vFrames.push_back(mbds2);
		
	}
	onRadioClickPointData();

	ui.horizontalSlider_frame->setMaximum(rdr->GetNumberOfTimeSteps());
	ui.verticalWidget_range->setHidden(true);
	UISet(m_TypeMode);
	m_pRenderder->ResetCamera();
	m_pRenderder->GetActiveCamera()->Zoom(1.5);
}

void vtkShower::OnMenuOpenKFile()
{
	LsdPlaytimer->stop();
	QString filter;
	filter = "k file (*.k)";
	QDir dir;
	QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("打开k文件"), dir.absolutePath(), filter);
	if (fileName.isEmpty() == true) return;

	m_TypeMode = 1;
	RemoveKActors();
	RemoveLsdActors();
	UISet(m_TypeMode);
	LoadKFile(fileName);
}

void vtkShower::OnButtonPlay()
{
	LsdPlaytimer->start(100);
}

void vtkShower::OnButtonStop()
{
	LsdPlaytimer->stop();
}

void vtkShower::visColorBar()
{
	colorTableBar->SetLookupTable(lut);
	colorTableBar->SetTitle(ui.comboBox_data_name->itemText(m_iDataIndex).toUtf8().constData());
	colorTableBar->GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
	colorTableBar->GetPositionCoordinate()->SetValue(0.9, 0.1);
	colorTableBar->SetOrientationToVertical();
	colorTableBar->SetWidth(0.1);
	colorTableBar->SetHeight(0.8);
	//colorTableBar->SetMaximumHeightInPixels(500);
	colorTableBar->SetNumberOfLabels(10);
	colorTableBar->SetLabelFormat("%-#6.3g");/*( "%-#6.4f" );*/
	m_pRenderder->AddActor2D(colorTableBar);
}

void vtkShower::RenderLsd()
{
	RemoveLsdActors();
	visColorBar();
	visPipeline();
}

void vtkShower::visPipeline(void)
{
	if (m_iCurStep >= m_vFrames.size())
		return;
	vtkUnstructuredGrid* ugrid = (vtkUnstructuredGrid*)0;
	vtkMultiBlockDataSet* mbds = m_vFrames[m_iCurStep];

	float rangeMin = 0xffffffe;
	float rangeMax = -0xffffffe;

	for (int k = 0; k < mbds->GetNumberOfBlocks(); ++k)
	{
		if (!m_partsCbs[k]->isChecked() || k >= m_partsCbs.size())
			continue;

		int type = mbds->GetBlock(k)->GetDataObjectType();
		if (type == VTK_UNSTRUCTURED_GRID)
		{
			ugrid = vtkUnstructuredGrid::SafeDownCast(mbds->GetBlock(k));

			if (m_lShowType == Shell && ugrid->GetNumberOfCells() > 0)
			{
				ugrid->GetCellData()->SetActiveScalars(ugrid->GetCellData()->GetArrayName(m_iDataIndex));
				if (m_rangeMode == 0)
				{
					vtkDataArray* vda = ugrid->GetCellData()->GetScalars(ugrid->GetCellData()->GetArrayName(m_iDataIndex));
					if (vda->GetDataType() == VTK_ID_TYPE)
					{
						vtkIdTypeArray* ida = vtkIdTypeArray::SafeDownCast(vda);
						if (ida)
						{
							double range[2];
							ida->GetRange(range);
							if (rangeMin > range[0]) rangeMin = range[0];
							if (rangeMax < range[1]) rangeMax = range[1];
						}
					}
					else if (vda->GetDataType() == VTK_FLOAT)
					{
						vtkFloatArray* fa = vtkFloatArray::SafeDownCast(vda);
						if (fa)
						{
							double range[2];
							fa->GetRange(range);
							if (rangeMin > range[0]) rangeMin = range[0];
							if (rangeMax < range[1]) rangeMax = range[1];
						}
					}
					else if (vda->GetDataType() == VTK_DOUBLE)
					{
						vtkDoubleArray* da = vtkDoubleArray::SafeDownCast(vda);
						if (da)
						{
							double range[2];
							da->GetRange(range);
							if (rangeMin > range[0]) rangeMin = range[0];
							if (rangeMax < range[1]) rangeMax = range[1];
						}
					}
				}

				unMapper = vtkDataSetMapper::New();
				unMapper->SetInputData(ugrid);
				unMapper->UseLookupTableScalarRangeOn();
				unMapper->SetScalarModeToUseCellData();

				vtkActor* partActor = GetLSDActorByIndex(k);
				partActor->SetMapper(unMapper);
				partActor->GetProperty()->SetEdgeVisibility(true);

				m_pRenderder->AddActor(partActor);
				unMapper->Delete();
			}
			else if (m_lShowType == Point && ugrid->GetNumberOfPoints() > 0)
			{
				ugrid->GetPointData()->SetActiveScalars(ugrid->GetPointData()->GetArrayName(m_iDataIndex));

				if (m_rangeMode == 0)
				{
					vtkDataArray* vda = ugrid->GetPointData()->GetScalars(ugrid->GetPointData()->GetArrayName(m_iDataIndex));
					if (vda->GetDataType() == VTK_ID_TYPE)
					{
						vtkIdTypeArray* ida = vtkIdTypeArray::SafeDownCast(vda);
						if (ida)
						{
							double range[2];
							ida->GetRange(range);
							if (rangeMin > range[0]) rangeMin = range[0];
							if (rangeMax < range[1]) rangeMax = range[1];
						}
					}
					else if (vda->GetDataType() == VTK_FLOAT)
					{
						vtkFloatArray* fa = vtkFloatArray::SafeDownCast(vda);
						if (fa)
						{
							double range[2];
							fa->GetRange(range);
							if (rangeMin > range[0]) rangeMin = range[0];
							if (rangeMax < range[1]) rangeMax = range[1];
						}
					}	
					else if (vda->GetDataType() == VTK_DOUBLE)
					{
						vtkDoubleArray* da = vtkDoubleArray::SafeDownCast(vda);
						if (da)
						{
							double range[2];
							da->GetRange(range);
							if (rangeMin > range[0]) rangeMin = range[0];
							if (rangeMax < range[1]) rangeMax = range[1];
						}
					}
				}

				unMapper = vtkDataSetMapper::New();
				unMapper->SetInputData(ugrid);
				unMapper->UseLookupTableScalarRangeOn();
				unMapper->SetScalarModeToUsePointData();

				vtkActor* partActor = GetLSDActorByIndex(k);
				partActor->SetMapper(unMapper);
				partActor->GetProperty()->SetEdgeVisibility(true);

				m_pRenderder->AddActor(partActor);
				unMapper->Delete();
			}
		
		}
	}

	if (m_rangeMode == 0)
	{
		m_rangeMin = rangeMin;
		m_rangeMax = rangeMax;
	}

	if (m_rangeMin > m_rangeMax)
	{
		m_rangeMax = 1;
		m_rangeMin = -1;
	}
	lut->SetTableRange(m_rangeMin, m_rangeMax);
	lut->SetHueRange(0, 0.67);
	lut->SetSaturationRange(1, 1);
	lut->SetValueRange(1, 1);
	lut->SetAlphaRange(1, 1);
	lut->SetNumberOfColors(256);
	lut->Build();

	for (int m = 0; m < m_lsdPartActors.size(); m++)
	{
		if (m_partsCbs[m]->isChecked())
			m_lsdPartActors[m]->GetMapper()->SetLookupTable(lut);
	}

	m_textLSDRangeActor->SetInput((QString("Range min:") + QString::number(m_rangeMin) + "   max:" + QString::number(m_rangeMax)).toUtf8().constData());
	m_pRenderder->AddActor2D(m_textLSDRangeActor);
	m_pRenWin->Render();
}
vtkActor* vtkShower::GetLSDActorByIndex(int index)
{
	while (index >= m_lsdPartActors.size())
	{
		vtkActor* partActor = vtkActor::New();
		m_lsdPartActors.push_back(partActor);
	}
	return m_lsdPartActors[index];
}
void vtkShower::onButtonLine()
{
	if (!m_style->curActor)
		return;

	int curSelectPart = -1;
	vtkMultiBlockDataSet* mbds = m_vFrames[m_iCurStep];
	for (int k = 0; k < mbds->GetNumberOfBlocks(); ++k)
	{
		int type = mbds->GetBlock(k)->GetDataObjectType();

		if (type == VTK_UNSTRUCTURED_GRID)
		{
			if (vtkUnstructuredGrid::SafeDownCast(mbds->GetBlock(k)) == m_style->curActor->GetMapper()->GetInputAsDataSet())
			{
				curSelectPart = k;
			}
		}
	}

	if (curSelectPart >= 0)
	{
		m_lines.clear();
		if (m_style->isPoint)
		{
			for (int i = 0; i < m_vFrames.size(); i++)
			{
				vtkUnstructuredGrid* ugrid = (vtkUnstructuredGrid*)0;
				vtkMultiBlockDataSet* mbds = m_vFrames[i];

				int type = mbds->GetBlock(curSelectPart)->GetDataObjectType();
				{
					if (type == VTK_UNSTRUCTURED_GRID)
					{
						ugrid = vtkUnstructuredGrid::SafeDownCast(mbds->GetBlock(curSelectPart));

						vtkDataArray* vda = ugrid->GetPointData()->GetScalars(ugrid->GetPointData()->GetArrayName(m_iDataIndex));
						if (vda->GetDataType() == VTK_ID_TYPE)
						{
							vtkIdTypeArray* ida = vtkIdTypeArray::SafeDownCast(vda);
							if (ida)
							{
								m_lines.push_back(ida->GetValue(m_style->pointId));
							}
						}
						else if (vda->GetDataType() == VTK_FLOAT)
						{
							vtkFloatArray* fa = vtkFloatArray::SafeDownCast(vda);
							if (fa)
							{
								m_lines.push_back(fa->GetValue(m_style->pointId));
							}
						}
						else if (vda->GetDataType() == VTK_DOUBLE)
						{
							vtkDoubleArray* da = vtkDoubleArray::SafeDownCast(vda);
							if (da)
							{
								m_lines.push_back(da->GetValue(m_style->pointId));
							}
						}
					}
				}

			}
		}
		else
		{
			for (int i = 0; i < m_vFrames.size(); i++)
			{
				vtkUnstructuredGrid* ugrid = (vtkUnstructuredGrid*)0;
				vtkMultiBlockDataSet* mbds = m_vFrames[i];

				int type = mbds->GetBlock(curSelectPart)->GetDataObjectType();
				{
					if (type == VTK_UNSTRUCTURED_GRID)
					{
						ugrid = vtkUnstructuredGrid::SafeDownCast(mbds->GetBlock(curSelectPart));
						
						vtkDataArray* vda = ugrid->GetCellData()->GetScalars(ugrid->GetCellData()->GetArrayName(m_iDataIndex));
						if (vda->GetDataType() == VTK_ID_TYPE)
						{
							vtkIdTypeArray* ida = vtkIdTypeArray::SafeDownCast(vda);
							if (ida)
							{
								m_lines.push_back(ida->GetValue(m_style->cellId));
							}
						}
						else if (vda->GetDataType() == VTK_FLOAT)
						{
							vtkFloatArray* fa = vtkFloatArray::SafeDownCast(vda);
							if (fa)
							{
								m_lines.push_back(fa->GetValue(m_style->cellId));
							}
						}
						else if (vda->GetDataType() == VTK_DOUBLE)
						{
							vtkDoubleArray* da = vtkDoubleArray::SafeDownCast(vda);
							if (da)
							{
								m_lines.push_back(da->GetValue(m_style->cellId));
							}
						}
					}
				}

			}
		}
	}
	
	ui_dialog.verticalWidget->setData(&m_lines);
	ui_dialog.verticalWidget->setName(ui.comboBox_data_name->itemText(m_iDataIndex) + (m_style->isPoint ? ("  PointID:" + QString::number(m_style->pointId)) : ("  CellID:" + QString::number(m_style->cellId))));
	m_dialogLine->show();
}

void vtkShower::OnButtonCloseLine()
{
	m_dialogLine->close();
}

void vtkShower::OnTimerOut()
{
	m_iCurStep = (m_iCurStep + 1) % rdr->GetNumberOfTimeSteps();
	ui.label_frame->setText(QString::number(m_iCurStep));
	ui.horizontalSlider_frame->setValue(m_iCurStep);
}

void vtkShower::onDataRangeComboChange(int index)
{
	m_rangeMode = index;
	if (index == 0)
	{
		ui.verticalWidget_range->setHidden(true);
	}
	else
		ui.verticalWidget_range->setHidden(false);
	
	RenderLsd();
}

void vtkShower::onLsdPartSelect(int index)
{
	if (m_lShowType == Point)
	{
		onRadioClickPointData();
	}
	else
	{
		onRadioClickShellData();
	}
	/*m_pRenderder->ResetCamera();
	m_pRenderder->GetActiveCamera()->Zoom(1.5);
	m_pRenWin->Render();*/
}

void vtkShower::onButtonChangeRange()
{
	m_rangeMin = ui.lineEdit_min->text().toFloat();
	m_rangeMax = ui.lineEdit_max->text().toFloat();
	
	RenderLsd();
}

void vtkShower::RemoveLsdActors()
{
	if (colorTableBar)
	{
		m_pRenderder->RemoveActor2D(colorTableBar);
	}
	for (int i = 0; i < m_lsdPartActors.size(); i++)
	{
		m_pRenderder->RemoveActor(m_lsdPartActors[i]);
	}
	m_pRenderder->RemoveActor2D(m_textLSDRangeActor);
}

vtkShower::~vtkShower()
{

}
