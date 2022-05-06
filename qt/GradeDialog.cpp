#include "GradeDialog.h"
#include <QPushButton>
#include <QDateTime>
#include "ChartDialog.h"

GradeDialog::GradeDialog(void):ui(new Ui::GradeDialog) {
	ui->setupUi(this);
	connect(ui->sel_term, SIGNAL(activated(int)),
		this, SLOT(onList(void)));
	connect(ui->sel_type, SIGNAL(activated(int)),
		this, SLOT(onTable(void)));
}

GradeDialog::~GradeDialog(void) {
	delete ui;
}

void GradeDialog::onView(void) {

}

void GradeDialog::onList(void) {
	QString selcourse = ui->sel_term->currentText();
	SqliteDb *sqlite = SqliteDb::getInstance();
	if (QSqlDatabase* db = (QSqlDatabase*)sqlite->ConnectDB("qt")) {
		ui->m_list->clear();
		//ui->m_name->setText(QString::fromLocal8Bit("学号："));

		QString str = QString("select course_id from course where course_term = '%1';").arg(selcourse);		
		QSqlQuery query;
		query.exec(str);
		vector<int> c_id;
		while(query.next()) {
			c_id.push_back(query.value(0).toInt());
		}
		query.clear();

		vector<float> sc_grade;
		vector<QString> sc_name;
		for (int i = 0; i < c_id.size(); ++i) {
			str = QString("SELECT sc_cid, sc_grade from sc where sc_cid = %1 and sc_sid = %2;").arg(c_id[i]).arg(this->s_id);
			query.exec(str);
			int sc_cid;
			if (query.next()) {
				sc_cid = query.value(0).toInt();
				sc_grade.push_back(query.value(1).toFloat());
				query.clear();
				str = QString("SELECT course_name from course where course_id = %1;").arg(sc_cid);
				query.exec(str);
				if (query.next()) {
					sc_name.push_back(query.value(0).toString());
					query.clear();
					if(sc_grade.size() != 0) {
						if (sc_grade.back() == 0){
							ui->m_list->addItem(sc_name.back());
						}
						else {
							ui->m_list->addItem(sc_name.back() + " " + QString::number(sc_grade.back()));
						}
					}
				}
			}
		}
		ui->m_list->adjustSize();
		sqlite->DisConnectDB(db);
		if (sc_grade.size() != 0) {
			ChartDialog *gradeview = new ChartDialog();
			gradeview->Paint(sc_name, sc_grade);
			gradeview->show();
		}
	}
}

void GradeDialog::onTable(void) {

}


void GradeDialog::onShow(int id) {
	this->s_id = id;
	this->show();
	SqliteDb *sqlite = SqliteDb::getInstance();

	if (QSqlDatabase* db = (QSqlDatabase*)sqlite->ConnectDB("qt")) {
		//ui->m_name->setText(QString::fromLocal8Bit("学号："));
		QString str = QString("select user_ad_date from user where user_id = %1;").arg(id);

		QSqlQuery query;
		QString s_date;
		query.exec(str);
		if(query.next()) {
			s_date = query.value(0).toString();
			s_date.chop(6);
			int bef_year = s_date.toInt();

			QDate cur_date = QDate::currentDate();
			int cur_year = cur_date.toString("yyyy").toInt();
			int cur_month = cur_date.toString("M").toInt();

			for (int i = bef_year; i < cur_year; ++i) {
				if (cur_year - bef_year > 4) {
					break;
				}
				if (i != bef_year) {
					ui->sel_term->addItem(QString::number(i)+QString::fromLocal8Bit("春季学期"));
				}
				ui->sel_term->addItem(QString::number(i)+QString::fromLocal8Bit("秋季学期"));
			}
			if (cur_month >= 8) {
				ui->sel_term->addItem(QString::number(cur_year)+QString::fromLocal8Bit("秋季学期"));
				ui->sel_term->addItem(QString::number(cur_year)+QString::fromLocal8Bit("春季学期"));
			}
			else if(cur_month >= 3) {
				ui->sel_term->addItem(QString::number(cur_year)+QString::fromLocal8Bit("春季学期"));
			}
			query.clear();
			sqlite->DisConnectDB(db);
		}
		onList();
	}
}

void GradeDialog::onInquired() {

}

void GradeDialog::onSelected() {

}

void GradeDialog::onQuited() {

}