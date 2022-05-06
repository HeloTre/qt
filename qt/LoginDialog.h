#ifndef __STUDENTDIALOG_H
#define __STUDENTDIALOG_H

#include "ui_LoginDialog.h"
#include <QMessageBox>
#include <QDebug>
#include "SqliteDb.h"

class LoginDialog:public QDialog{
	Q_OBJECT
public:
	LoginDialog(void);
	~LoginDialog(void);
	public slots:
		void onAccepted(void);
		void onRejected(void);
		void onShow(void);
signals:
		void login_page(void);
		void student_page(int id);
		void mes_switch(void);
		void admin_page(void);
public:
	Ui::LoginDialog* ui;
};

#endif
