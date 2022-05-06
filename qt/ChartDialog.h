#ifndef CHARTDIALOG_H 
#define CHARTDIALOG_H

#include "ui_ChartDialog.h"
#include <QtGui>
#include <QMessageBox>
#include <QDebug>
using namespace std;


class ChartDialog:public QDialog{
	Q_OBJECT
public:
	ChartDialog();
	~ChartDialog();
	void Paint(vector<QString> &cname,vector<float> &cgrade);
protected:
	void paintEvent(QPaintEvent *){
		QPainter painter(this);
		painter.drawImage(0,0,image);
	}
private:
	Ui::ChartDialog* ui;
	QImage image;
};

#endif