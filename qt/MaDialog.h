#ifndef MADIALOG_H
#define MADIALOG_H

#include "ui_MaDialog.h"
#include "SqliteDb.h"
class MaDialog: public QDialog {
	Q_OBJECT
public:	
	MaDialog();
	~MaDialog();
	public slots:
		void onUpdated();
		void onTable();
		void onInserted();
		void onShow();
		void onRecorded(int a, int b);
		void onSelected();
private:
	vector<pair<int, int>> rec;
	Ui::MaDialog *ui;
};

#endif