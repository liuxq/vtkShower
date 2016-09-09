#pragma once

#include <QWidget>
#include <QString>
#include <QPushButton>
#include <vector>

class LineWidget: public QWidget
{
public:
	LineWidget(QWidget* parrent = NULL);
	void setData(std::vector<double>* theMotion);
	void setName(QString filename);
	void setCurStep(int stepIndex);
	void setIsSolved(bool);
protected:
	void paintEvent(QPaintEvent *);
	void calculate();
private:
	void drawWhenSolving(QPaintEvent* e);
	void drawAfterSolving(QPaintEvent* e);
	float miny;
	float maxy;
	std::vector<double>* theMotion;
	int stepIndex;
	bool isSolved;
	int X_showLength;
	QString name;
};