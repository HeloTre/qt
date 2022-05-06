#ifndef SCDIALOG_H
#define SCDIALOG_H

#include "ui_ScDialog.h"
#include "SqliteDb.h"
class ScDialog: public QDialog {
	Q_OBJECT
public:	
	ScDialog();
	~ScDialog();
	public slots:
		void onUpdated();
		void onTable();
		void onInserted();
		void onShow();
		void onRecorded(int a, int b);
		void indRec(int a, int b);
		void onSelected();
		void onDeleted();

private:
	vector<pair<int, int>> rec;
	int inrec;
	Ui::ScDialog *ui;
};

#endif