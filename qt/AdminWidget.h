#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include "ui_AdminWidget.h"
#include "SqliteDb.h"

class AdminWidget: public QWidget{
	Q_OBJECT
public:
	int adminid;
	AdminWidget();
	~AdminWidget();
	public slots:
		void maUser();
		void maCourse();
		void maShow(int i);
		void maGrade();
private:
	Ui::AdminWidget *ui;
};
#endif