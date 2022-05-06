#include "qt.h"
#include "LoginDialog.h"
#include "GradeDialog.h"
#include "StudentDialog.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{

	QApplication a(argc, argv);
	
	LoginDialog login_page;
	StudentDialog student_page;
	GradeDialog grade_page;

	login_page.show();

	//if (void* db = sqlite->ConnectDB("qt")) {
	//	QString m_user = ui->m_user->text();
	//	QString m_user = ui->m_us->text();
	//	login_page.ui->m_user->text() = "0221123095";
	//	str = QString("select count(*) from user where user_num = '%1';").arg(login_page.ui->m_user->text());
	//	QSqlQuery query = db->exec(str);

		//if (sel_Data.size() != 0) {
		//	qDebug() << "not null";
		//}
		//else {
		//	qDebug() << "null";
		//}
		//for (vector<vector<QVariant>>::iterator it = sel_Data.begin(); it != sel_Data.end(); ++it){
		//	for (int i = 0; i < (*it).size(); ++i){
		//		qDebug() << (*it)[i];
		//	}
		//}
		


		//sqlite->DisConnectDB(db);
	return a.exec();
}
