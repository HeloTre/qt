#ifndef __LOGINDIALOG_H
#define __LOGINDIALOG_H

#include "ui_StudentDialog.h"
#include <QMessageBox>
#include <QDebug>
#include "SqliteDb.h"
#include "GradeDialog.h"

class StudentDialog:public QDialog{
	Q_OBJECT
public:
	int ss_id;
	StudentDialog();
	~StudentDialog(void);
	public slots:
		void onInquired(void);
		void onSelected(void);
		void onQuited(void);
		void onShow(int id);
signals:
		void show_grade_page(void);
private:
	Ui::StudentDialog* ui;
};

#endif//__LOGINDIALOG_H
