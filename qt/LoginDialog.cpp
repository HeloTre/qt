#include "LoginDialog.h"
#include <QPushButton>
#include <QDir>
#include <QPluginLoader>
#include "StudentDialog.h"
#include "AdminWidget.h"

LoginDialog::LoginDialog(void):ui(new Ui::LoginDialog)
{
	ui->setupUi(this);
	ui->loginBox->button(QDialogButtonBox::Ok)->setText(QString::fromLocal8Bit("��¼"));
	ui->loginBox->button(QDialogButtonBox::Cancel)->setText(QString::fromLocal8Bit("ȡ��"));

	connect(ui->loginBox,SIGNAL(accepted(void)),
		this,SLOT(onAccepted(void)));
	connect(ui->loginBox,SIGNAL(rejected(void)),
		this,SLOT(onRejected(void)));

}
LoginDialog::~LoginDialog(void){
	delete ui;
}

void LoginDialog::onAccepted(void)
{
	if (ui->cho_stu->isChecked() || ui->cho_admin->isChecked()) {
	SqliteDb *sqlite = SqliteDb::getInstance();

	if (QSqlDatabase* db = (QSqlDatabase*)sqlite->ConnectDB("qt")) {
		QString str;
		if (ui->cho_stu->isChecked()) {
			str = QString("select *from user where user_num = '%1';").arg(ui->m_user->text());
		}
		else {
			str = QString("select *from admin where admin_num = '%1';").arg(ui->m_user->text());
		}
		QSqlQuery query = db->exec(str);
		if (query.next()) {
			int id = query.value(0).toInt();
			this->hide();
			if (ui->cho_stu->isChecked()) {
				StudentDialog* stu_page = new StudentDialog();
				stu_page->onShow(id);
			}
			else {
				AdminWidget* ad_page = new AdminWidget();
				ad_page->maShow(id);
			}
		}
		else {
			QMessageBox msgBox(
				QMessageBox::Critical,
				"Error",
				QString::fromLocal8Bit("�û������������"),
				QMessageBox::Ok,
				this);
			msgBox.exec();
		}
		sqlite->DisConnectDB(db);
	}
	else {
		QMessageBox msgBox(
			QMessageBox::Critical,
			"Error",
			QString::fromLocal8Bit("�������ݿ����"),
			QMessageBox::Ok,
			this);
		msgBox.exec();
	}
	}
	else {
		QMessageBox msgBox(
			QMessageBox::Critical,
			"Error",
			QString::fromLocal8Bit("��ѡ���������"),
			QMessageBox::Ok,
			this);
		msgBox.exec();
	}

}

void LoginDialog::onRejected(void)
{
	QMessageBox msgBox(
		QMessageBox::Question,
		QString::fromLocal8Bit("��¼"),
		QString::fromLocal8Bit("�Ƿ�ȷ��Ҫȡ����¼?"),
		QMessageBox::Yes|QMessageBox::No,
		this);
	if(msgBox.exec() == QMessageBox::Yes){
		this->close();
	}
}

void LoginDialog::onShow(void) {
	this->show();
}