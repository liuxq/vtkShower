#include "LineWidget.h"
#include <QPainter>
#define MIN_DOUBLE -100000
#define MAX_DOUBLE 100000

QString formatText(double data)
{
	if (data < 1000 && data > 0.0001 || data > -1000 && data < -0.0001 || data == 0)
		return QString("%1").arg(data, 0, 'f', 1);
	else
		return QString("%1").arg(data, 0, 'e', 1);
}

LineWidget::LineWidget(QWidget* parrent):QWidget(parrent)
{
	this->theMotion = NULL;
	this->stepIndex = 0;
	this->isSolved = false;
	X_showLength = 10;
}

void LineWidget::setName(QString Name)
{
	name = Name;
}
void LineWidget::setData(std::vector<double>* theMotion)
{
	this->theMotion = theMotion;
	calculate();
}
void LineWidget::setCurStep(int stepIndex)
{
	this->stepIndex = stepIndex;
	calculate();
}

void LineWidget::calculate()
{
	if (!theMotion)
		return;
	miny = MAX_DOUBLE;
	maxy = MIN_DOUBLE;
	for (int i = 0; i < theMotion->size(); i++)
	{
		if (miny > theMotion->at(i)) miny = theMotion->at(i);
		if (maxy < theMotion->at(i)) maxy = theMotion->at(i);
	}
	if (miny == maxy)
		maxy = miny +1;
	update();
}
#define WAVE_MARGIN 30
#define WAVE_X_DIMENTION 10
#define WAVE_Y_DIMENTION 5
void LineWidget::drawWhenSolving(QPaintEvent* e)
{
	if (!theMotion || theMotion->empty())
		return;

	int X_increase = 0;//递增步长
	X_showLength = X_increase;
	if (theMotion->size() > X_showLength)
	{
		X_showLength = theMotion->size()  - 1 + X_increase;
	}

	int X_length = this->width() - WAVE_MARGIN*2;
	double X_offset = (double)X_length/WAVE_X_DIMENTION;
	int Y_length = this->height()- WAVE_MARGIN*2;
	double Y_offset = (double)Y_length/WAVE_Y_DIMENTION;
	float X_rate = 1.0*X_length/X_showLength;
	float Y_rate = Y_length/(maxy - miny);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing,true);

	//画背景
	painter.setBrush(QBrush(Qt::black));
	painter.drawRect(0,0,this->width(),this->height());

	//画曲线
	painter.setPen(QPen(Qt::yellow,2));
	QPainterPath path;
	for (int i = 0; i < theMotion->size(); i++)
	{

		int x = i*X_rate + WAVE_MARGIN;//x坐标
		int y = Y_length - (theMotion->at(i)- miny)*Y_rate + WAVE_MARGIN;//y坐标
		if (i == 0)
		{
			path.moveTo(x,y);
		}
		else
		{
			path.lineTo(x,y);
		}
	}
	painter.drawPath(path);

	//画当前step点
	//painter.setPen(QPen(Qt::white));
	//int x = (theMotion->size()-1)*X_rate + WAVE_MARGIN;//x坐标
	//painter.drawLine(x,WAVE_MARGIN,x,this->height()-WAVE_MARGIN);

	//横向的
	for ( int i = 0; i < WAVE_Y_DIMENTION + 1; i++)
	{
		if (i == 0 || i == WAVE_Y_DIMENTION)
			painter.setPen(QPen(Qt::red, 1));
		else
			painter.setPen(QPen(Qt::red, 1, Qt::DotLine));
		double y = this->height() - WAVE_MARGIN - i * Y_offset;
		painter.drawLine(WAVE_MARGIN,y,this->width() - WAVE_MARGIN ,y);
		float text = miny + i*(maxy - miny)/WAVE_Y_DIMENTION;

		painter.setFont(QFont("Arial",6,QFont::Bold));
		painter.drawText(WAVE_MARGIN - 25,y,formatText(text));
	}
	//纵向的
	for ( int i = 0; i < WAVE_X_DIMENTION + 1; i++)
	{
		if (i == 0 || i == WAVE_X_DIMENTION)
			painter.setPen(QPen(Qt::red,1));
		else
			painter.setPen(QPen(Qt::red, 1, Qt::DotLine));
		double x = WAVE_MARGIN + i * X_offset;
		painter.drawLine(x,WAVE_MARGIN,x ,this->height() - WAVE_MARGIN);
		float text = i*X_showLength/WAVE_X_DIMENTION;

		painter.setFont(QFont("Arial",6,QFont::Bold));
		painter.drawText(x,this->height()-15,formatText(text));
	}

	//当前单元\点
	painter.setFont(QFont("Arial",8,QFont::Bold));
	painter.drawText(WAVE_MARGIN, WAVE_MARGIN / 2, name);
}
void LineWidget::drawAfterSolving(QPaintEvent* e)
{
	if (!theMotion || theMotion->empty())
		return;
	int X_length = this->width() - WAVE_MARGIN*2;
	double X_offset = (double)X_length/WAVE_X_DIMENTION;
	int Y_length = this->height()- WAVE_MARGIN*2;
	double Y_offset = (double)Y_length/WAVE_Y_DIMENTION;
	float X_rate = 1.0*X_length/theMotion->size();
	float Y_rate = Y_length/(maxy - miny);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing,true);

	//画背景
	painter.setBrush(QBrush(Qt::black));
	painter.drawRect(0,0,this->width(),this->height());

	//画曲线
	painter.setPen(QPen(Qt::yellow,2));
	QPainterPath path;
	for (int i = 0; i < theMotion->size(); i++)
	{
		if (i > stepIndex)
		{
			break;
		}
		int x = i*X_rate + WAVE_MARGIN;//x坐标
		int y = Y_length - (theMotion->at(i)- miny)*Y_rate + WAVE_MARGIN;//y坐标
		if (i == 0)
		{
			path.moveTo(x,y);
		}
		else
		{
			path.lineTo(x,y);
		}
	}
	painter.drawPath(path);

	//画当前step点
	painter.setPen(QPen(Qt::white));
	int x = stepIndex*X_rate + WAVE_MARGIN;//x坐标
	painter.drawLine(x,WAVE_MARGIN,x,this->height()-WAVE_MARGIN);

	//横向的
	for ( int i = 0; i < WAVE_Y_DIMENTION + 1; i++)
	{
		if (i == 0 || i == WAVE_Y_DIMENTION)
			painter.setPen(QPen(Qt::blue,1));
		else
			painter.setPen(QPen(Qt::blue,1,Qt::DotLine));
		double y = this->height() - WAVE_MARGIN - i * Y_offset;
		painter.drawLine(WAVE_MARGIN,y,this->width() - WAVE_MARGIN ,y);
		float text = miny + i*(maxy - miny)/WAVE_Y_DIMENTION;

		painter.setFont(QFont("Arial",6,QFont::Bold));
		painter.drawText(WAVE_MARGIN - 25,y,formatText(text));
	}
	//纵向的
	for ( int i = 0; i < WAVE_X_DIMENTION + 1; i++)
	{
		if (i == 0 || i == WAVE_X_DIMENTION)
			painter.setPen(QPen(Qt::blue,1));
		else
			painter.setPen(QPen(Qt::blue,1,Qt::DotLine));
		double x = WAVE_MARGIN + i * X_offset;
		painter.drawLine(x,WAVE_MARGIN,x ,this->height() - WAVE_MARGIN);
		float text = i*theMotion->size()/WAVE_X_DIMENTION;

		painter.setFont(QFont("Arial",6,QFont::Bold));
		painter.drawText(x,this->height()-15,formatText(text));
	}

	//当前单元\点
	painter.setFont(QFont("Arial",8,QFont::Bold));
	painter.drawText(WAVE_MARGIN,WAVE_MARGIN/2,"Motion");
}
void LineWidget::paintEvent(QPaintEvent* e)
{
	if (!theMotion)
		return;
	if (isSolved)
	{
		drawAfterSolving(e);
	}
	else
	{
		drawWhenSolving(e);
	}

}
void LineWidget::setIsSolved(bool isSolved)
{
	this->isSolved = isSolved;
}