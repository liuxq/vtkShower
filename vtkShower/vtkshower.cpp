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


#include <QFileDialog>
#include <QDir>
#include <QEvent>
#include <QTextEncoder>

#include "ColorMapping.h"


vtkShower* vtkShower::instance = NULL;

vtkShower::vtkShower(QWidget *parent)
: QMainWindow(parent)
{
	if (instance == NULL)
		instance = this;

	m_textActor = NULL;
	ui.setupUi(this);

	m_pRenderder = vtkSmartPointer< vtkRenderer >::New();
	m_pRenWin = vtkSmartPointer<vtkRenderWindow>::New();
	m_pRenWin->AddRenderer(m_pRenderder);
	iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(m_pRenWin);
	vtkSmartPointer<customMouseInteractorStyle> style = vtkSmartPointer<customMouseInteractorStyle>::New();
	iren->SetInteractorStyle(style);
	style->SetDefaultRenderer(m_pRenderder);
	m_pRenderder->SetBackground(0.2, 0.2, 0.2);
	ui.qvtkWidget->SetRenderWindow(m_pRenWin);
	ui.qvtkWidget->GetRenderWindow()->Render();
	lut = vtkLookupTable::New();
	colorTableBar = vtkScalarBarActor::New();

	rdr = vtkLSDynaReader::New();
	rdr->SetDatabaseDirectory("D:/result_demo");
	rdr->Update();
	onRadioClickPointData();

	ui.horizontalSlider_frame->setMaximum(rdr->GetNumberOfTimeSteps());

	m_iCurStep = 0;
	m_iDataIndex = 0;

	m_pRenderder->ResetCamera();
	m_pRenderder->GetActiveCamera()->Zoom(1.5);

	SetAxis();
	
	UISet(0);

	connect(ui.comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onPartComboChange(int)));
	connect(ui.comboBox_data_name, SIGNAL(currentIndexChanged(int)), this, SLOT(onDataComboChange(int)));
	connect(ui.radioButton_solid, SIGNAL(clicked()), this, SLOT(onRadioClickSolid()));
	connect(ui.radioButton_wareline, SIGNAL(clicked()), this, SLOT(onRadioClickWareline()));
	connect(ui.radioButton_setnode, SIGNAL(clicked()), this, SLOT(onRadioClickSetNode()));
	connect(ui.radioButton_setSeg, SIGNAL(clicked()), this, SLOT(onRadioClickSetSeg()));
	connect(ui.action, SIGNAL(triggered()), this, SLOT(OnMenuOpenKFile()));

	connect(ui.action_LSDyna, SIGNAL(triggered()), this, SLOT(OnMenuOpenLSDFile()));
	connect(ui.pushButton_play, SIGNAL(clicked()), this, SLOT(OnButtonPlay()));
	connect(ui.radioButton_point_data, SIGNAL(clicked()), this, SLOT(onRadioClickPointData()));
	connect(ui.radioButton_shell_data, SIGNAL(clicked()), this, SLOT(onRadioClickShellData()));
	connect(ui.horizontalSlider_frame, SIGNAL(valueChanged(int)), this, SLOT(onSliderValueChange(int)));
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
	}
	else
	{
		ui.right_widget_k->setVisible(true);
		ui.right_widget_lsd->setVisible(false);
	}
}

void vtkShower::Clear()
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
	
	if (m_textActor)
	{
		m_pRenderder->RemoveActor2D(m_textActor);
		m_textActor->Delete();
		m_textActor = NULL;
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
	m_textActor->SetPosition((double)view[0], (double)view[1]);
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
	m_kShowType = Solid;
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
	m_kShowType = Wireline;
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
	m_kShowType = SetNode;
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
	m_lShowType = Point;
	ui.comboBox_data_name->clear();
	for (int i = 0; i < rdr->GetNumberOfPointArrays(); i++)
	{
		ui.comboBox_data_name->addItem(QString(rdr->GetPointArrayName(i)));
	}
	if (rdr->GetNumberOfPointArrays() > 0)
		onDataComboChange(0);
}

void vtkShower::onRadioClickShellData()
{
	m_lShowType = Shell;
	ui.comboBox_data_name->clear();
	for (int i = 0; i < rdr->GetNumberOfShellArrays(); i++)
	{
		ui.comboBox_data_name->addItem(QString(rdr->GetShellArrayName(i)));
	}
	if (rdr->GetNumberOfShellArrays() > 0)
		onDataComboChange(0);
}

void vtkShower::onDataComboChange(int index)
{
	m_iDataIndex = index;
	if (m_iDataIndex >= 0)
	{
		visColorBar();
		visPipeline();
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
	visColorBar();
	visPipeline();
}

void vtkShower::resizeEvent(QResizeEvent * event) {
	ui.horizontalLayoutWidget->resize(this->size().width(), this->size().height() - 50);
}

void vtkShower::OnMenuOpenLSDFile()
{
	QDir dir;
	QString dirName = QFileDialog::getExistingDirectory(this, QString(tr("打开Lsdyna文件库")), dir.absolutePath());
	if (dirName.isEmpty() == true) return;

}

void vtkShower::OnMenuOpenKFile()
{
	QString filter;
	filter = "k file (*.k)";
	QDir dir;
	QString fileName = QFileDialog::getOpenFileName(this, QString(tr("打开k文件")), dir.absolutePath(), filter);
	if (fileName.isEmpty() == true) return;

	Clear();
	RemoveLsdActors();
	UISet(1);
	LoadKFile(fileName);
}

void vtkShower::OnButtonPlay()
{
	visColorBar();
	visPipeline();
	m_iCurStep = (m_iCurStep + 1) % rdr->GetNumberOfTimeSteps();
	ui.label_frame->setText(QString::number(m_iCurStep));
	ui.horizontalSlider_frame->setValue(m_iCurStep);
}

void vtkShower::visColorBar()
{
	if (colorTableBar)
	{
		m_pRenderder->RemoveActor2D(colorTableBar);
	}

	colorTableBar->SetLookupTable(lut);
	colorTableBar->SetTitle(ui.comboBox_data_name->itemText(m_iDataIndex).toUtf8().constData());
	colorTableBar->GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
	colorTableBar->GetPositionCoordinate()->SetValue(0.9, 0.1);
	colorTableBar->SetOrientationToVertical();
	colorTableBar->SetWidth(0.07);
	colorTableBar->SetHeight(0.8);
	//colorTableBar->SetMaximumHeightInPixels(500);
	colorTableBar->SetNumberOfLabels(10);
	colorTableBar->SetLabelFormat("%-#6.3g");/*( "%-#6.4f" );*/
	m_pRenderder->AddActor2D(colorTableBar);

	
}
void vtkShower::visPipeline(void)
{
	RemoveLsdActors();
	vtkUnstructuredGrid* shell = (vtkUnstructuredGrid*)0;
	rdr->SetTimeStep(m_iCurStep);
	rdr->Update();
	vtkMultiBlockDataSet* mbds = vtkMultiBlockDataSet::SafeDownCast(rdr->GetOutput());

	for (int k = 0; k < mbds->GetNumberOfBlocks(); ++k)
	{
		int type = mbds->GetBlock(k)->GetDataObjectType();

		if (type == VTK_UNSTRUCTURED_GRID)
		{
			shell = vtkUnstructuredGrid::SafeDownCast(mbds->GetBlock(k));

			if (m_lShowType == Shell && shell->GetNumberOfCells() > 0)
			{
				shell->GetCellData()->SetActiveScalars("Stress");
				double rang[2];
				shell->GetCellData()->GetScalars("Stress")->GetRange(rang);
				vtkDataArray* lxq = shell->GetCellData()->GetScalars("Stress");

				unMapper = vtkDataSetMapper::New();
				unMapper->SetInputData(shell);
				unMapper->UseLookupTableScalarRangeOn();
				unMapper->SetScalarModeToUseCellData();

				lut->SetTableRange(-35000, 35000);
				lut->SetHueRange(0, 0.67);
				lut->SetSaturationRange(1, 1);
				lut->SetValueRange(1, 1);
				lut->SetAlphaRange(1, 1);
				lut->SetNumberOfColors(256);
				lut->Build();

				unMapper->SetLookupTable(lut);

				vtkActor* partActor = vtkActor::New();
				partActor->SetMapper(unMapper);
				partActor->GetProperty()->SetEdgeVisibility(true);

				m_lsdPartActors.push_back(partActor);
				m_pRenderder->AddActor(partActor);
				unMapper->Delete();
			}
			else if (m_lShowType == Point && shell->GetNumberOfPoints() > 0)
			{
				shell->GetPointData()->SetActiveScalars(rdr->GetPointArrayName(m_iDataIndex));
				double rang[2];
				shell->GetPointData()->GetScalars(rdr->GetPointArrayName(m_iDataIndex))->GetRange(rang);

				unMapper = vtkDataSetMapper::New();
				unMapper->SetInputData(shell);
				unMapper->UseLookupTableScalarRangeOn();
				unMapper->SetScalarModeToUsePointData();

				lut->SetTableRange(rang[0], rang[1]);
				lut->SetHueRange(0, 0.67);
				lut->SetSaturationRange(1, 1);
				lut->SetValueRange(1, 1);
				lut->SetAlphaRange(1, 1);
				lut->SetNumberOfColors(256);
				lut->Build();

				unMapper->SetLookupTable(lut);

				vtkActor* partActor = vtkActor::New();
				partActor->SetMapper(unMapper);
				partActor->GetProperty()->SetEdgeVisibility(true);

				m_lsdPartActors.push_back(partActor);
				m_pRenderder->AddActor(partActor);
				unMapper->Delete();
			}
		
		}
	}
	
	m_pRenWin->Render();
}

void vtkShower::RemoveLsdActors()
{
	for (int i = 0; i < m_lsdPartActors.size(); i++)
	{
		m_pRenderder->RemoveActor(m_lsdPartActors[i]);
		m_lsdPartActors[i]->Delete();
	}
	m_lsdPartActors.clear();
}

vtkShower::~vtkShower()
{

}
