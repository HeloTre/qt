#include "StudentDialog.h"

StudentDialog::StudentDialog(void):ui(new Ui::StudentDialog){
	ui->setupUi(this);
	connect(ui->m_quited,SIGNAL(clicked(void)),
		this,SLOT(onQuited(void)));
	connect(ui->m_inquired,SIGNAL(clicked(void)),
		this,SLOT(onInquired(void)));
	connect(ui->m_selected,SIGNAL(clicked(void)),
		this,SLOT(onSelected(void)));
}

StudentDialog::~StudentDialog(void) {
	delete ui;
}

void StudentDialog::onSelected(void) {
	
}

void StudentDialog::onQuited(void) {
	this->close();
}

void StudentDialog::onInquired(void) {
	GradeDialog* gra_page = new GradeDialog();
	gra_page->onShow(this->ss_id);
}

void StudentDialog::onShow(int id) {
	this->ss_id = id;
	SqliteDb *sqlite = SqliteDb::getInstance();

	if (QSqlDatabase* db = (QSqlDatabase*)sqlite->ConnectDB("qt")) {

		//ui->m_name->setText(QString::fromLocal8Bit("学号："));


		QString str = QString("select *from user where user_id = %1;").arg(id);
		
		QSqlQuery query;
		
		query.exec(str);
		if(query.next()) {
			QString s_name = query.value(2).toString();
			QString s_num = query.value(1).toString();
			s_name = QString::fromLocal8Bit("姓名： ") + s_name;
			s_num = QString::fromLocal8Bit("学号： ") + s_num;

			ui->m_name->setText(s_name);
			ui->m_id->setText(s_num);
		}
		query.clear();


		str = QString("select *from sc where sc_sid = %1;").arg(id);
		query.exec(str);

		vector<int> s_id;
		while(query.next()){
			s_id.push_back(query.value(1).toInt());
		}
		query.clear();
		QString c_name;
		QString c_credit;
		for (int i = 0; i < s_id.size(); ++i) {
			str = QString("SELECT course_name, course_credit from course where course_id = %1;").arg(s_id[i]);
			query.exec(str);
			query.next();
			c_credit =  query.value(1).toString();
			c_name = query.value(0).toString();
			c_name = QString::fromLocal8Bit("课名: ") + c_name;
			c_credit = QString::fromLocal8Bit("学分：") + c_credit;
			ui->m_list->addItem(c_name + " " + c_credit);
			query.clear();
		}
		ui->m_list->adjustSize();
		sqlite->DisConnectDB(db);
	}

	this->show();
}
