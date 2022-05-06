#ifndef __GRADEDIALOG_H
#define __GRADEDIALOG_H

#include "ui_GradeDialog.h"
#include <QMessageBox>
#include <QDebug>
#include "SqliteDb.h"


class GradeDialog:public QTabWidget{
	Q_OBJECT
public:
	int s_id;

	GradeDialog(void);
	~GradeDialog(void);
	public slots:
		void onView();
		void onInquired(void);
		void onSelected(void);
		void onQuited(void);
		void onShow(int id);
		void onList(void);
		void onTable(void);
signals:
		void show_student_page(void);
public:
	Ui::GradeDialog* ui;
};

#endif