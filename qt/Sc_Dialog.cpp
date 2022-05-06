#include "ScDialog.h"
#include <QDebug>
#include <QMessageBox>
ScDialog::ScDialog(): ui(new Ui::ScDialog) {

	ui->setupUi(this);
	ui->lineEdit->setValidator(new QIntValidator(this));
	ui->lineEdit_2->setValidator(new QIntValidator(this));
	connect(ui->tableWidget, SIGNAL(cellChanged(int, int)),
		this, SLOT(onRecorded(int, int)));
	connect(ui->m_updated, SIGNAL(clicked(void)),
		this, SLOT(onUpdated(void)));
	connect(ui->m_selected, SIGNAL(clicked(void)),
		this, SLOT(onSelected(void)));
	connect(ui->m_inserted, SIGNAL(clicked(void)),
		this, SLOT(onInserted(void)));
	connect(ui->tableWidget, SIGNAL(cellClicked(int,int)),
		this, SLOT(indRec(int, int)));
	connect(ui->m_deleted, SIGNAL(clicked(void)),
		this, SLOT(onDeleted(void)));
}

ScDialog::~ScDialog() {
	this->rec.clear();
	delete ui;
}

void ScDialog::onTable() {
	SqliteDb *sqlite = SqliteDb::getInstance();
	if (QSqlDatabase* db = (QSqlDatabase*)sqlite->ConnectDB("qt")) {
		ui->tableWidget->clearContents();
		//ui->m_name->setText(QString::fromLocal8Bit("学号："));
		QString str = QString("select count(*) from sc;");	
		QSqlQuery query;
		QSqlQuery query1;
		QSqlQuery query2;
		query.exec(str);
		int coun = 0;
		if (query.next()) {
			coun = query.value(0).toInt();
		}

		query.clear();

		ui->tableWidget->setRowCount(coun);

		str = QString("select * from sc;");
		query.exec(str);
		int i = 0;
		while(query.next()) {
			str = QString("select user_name from user where user_id = %1;").arg(query.value(0).toInt());
			query1.exec(str);
			query1.next();
			str = QString("select course_name from course where course_id = %1;").arg(query.value(1).toInt());
			query2.exec(str);
			query2.next();

			QTableWidgetItem *item0 = new QTableWidgetItem(query1.value(0).toString());
			QTableWidgetItem *item1 = new QTableWidgetItem(query2.value(0).toString());
			item0->setFlags(Qt::NoItemFlags);
			item1->setFlags(Qt::NoItemFlags);
			ui->tableWidget->setItem(i,0,new QTableWidgetItem(*item0));
			ui->tableWidget->setItem(i,1,new QTableWidgetItem(*item1));
			ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
			++i;
		}
		query.clear();
		this->rec.clear();
		ui->tableWidget->verticalHeader()->setHidden(true);

		sqlite->DisConnectDB(db);
	}    
}

void ScDialog::onSelected() {
	ui->tableWidget->clearContents();
	SqliteDb *sqlite = SqliteDb::getInstance();
	QString str = QString("select * from sc");
	if (QSqlDatabase* db = (QSqlDatabase*)sqlite->ConnectDB("qt")) {
		int flag = 0;

		str += QString(" where ");
		if (!ui->lineEdit->text().isEmpty()) {
			str += QString("sc_sid = %1").arg(ui->lineEdit->text().toInt());
			++flag;
		}

		if (!ui->lineEdit_2->text().isEmpty()) {
			if (flag >= 1) {
				str += QString(" and ");
			}
			str += QString("sc_cid = %1").arg(ui->lineEdit_2->text().toInt());
			++flag;
		}
		if (flag == 0) {
			str.remove(" where");
		}
		str += QString(";");

		QSqlQuery query;
		QSqlQuery query1;
		QSqlQuery query2;
		query.exec(str);
		int i = 0;
		while(query.next()) {
			str = QString("select user_name from user where user_id = %1;").arg(query.value(0).toInt());
			query1.exec(str);
			query1.next();
			str = QString("select course_name from course where course_id = %1;").arg(query.value(1).toInt());
			query2.exec(str);
			query2.next();

			QTableWidgetItem *item0 = new QTableWidgetItem(query1.value(0).toString());
			QTableWidgetItem *item1 = new QTableWidgetItem(query2.value(0).toString());
			item0->setFlags(Qt::NoItemFlags);
			item1->setFlags(Qt::NoItemFlags);
			ui->tableWidget->setItem(i,0,new QTableWidgetItem(*item0));
			ui->tableWidget->setItem(i,1,new QTableWidgetItem(*item1));
			ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
			++i;
		}
		ui->tableWidget->verticalHeader()->setHidden(true);
		query.clear();
		this->show();
		this->rec.clear();
	}
}


void ScDialog::onRecorded(int a, int b) {
	this->rec.push_back(make_pair(a,b));
}

void ScDialog::indRec(int a, int b) {
	this->inrec = a;
}
void ScDialog::onUpdated(){
	QString str;
	SqliteDb *sqlite = SqliteDb::getInstance();
	if (QSqlDatabase* db = (QSqlDatabase*)sqlite->ConnectDB("qt"))
	{
		str = QString("select count(*) from sc;");
		QSqlQuery query;
		QSqlQuery query1;
		QSqlQuery query2;
		bool flag = false;
		query.exec(str);

		int num = 0;
		if (query.next()) {
			num = query.value(0).toInt();
		}
		query.clear();
		if (ui->tableWidget->rowCount() == num) {
			for(auto iter=this->rec.begin(); iter!=this->rec.end(); iter++) {
				QString m_change = ui->tableWidget->item(iter->first, iter->second)->text();
				int m_select = ui->tableWidget->item(iter->first, 0)->text().toInt();
				if (iter->second == 2) {
					str = QString("select user_id from user where user_name = '%1';").arg(ui->tableWidget->item(iter->first, 0)->text());
					query1.exec(str);
					query1.next();
					str = QString("select course_id from course where course_name = '%1';").arg(ui->tableWidget->item(iter->first, 1)->text());
					query2.exec(str);
					query2.next();
					str = QString("update sc set sc_grade = %1 where sc_sid = %2 and sc_cid = %3;").arg(m_change.toFloat()).arg(query1.value(0).toInt()).arg(query2.value(0).toInt());
					flag = true;
				}
			}
		}
		else {
			int temp = ui->tableWidget->rowCount() - 1;
			str = QString("select user_id from user where user_name = '%1';").arg(ui->tableWidget->item(temp, 0)->text());
			query1.exec(str);
			query1.next();
			str = QString("select course_id from course where course_name = '%1';").arg(ui->tableWidget->item(temp, 1)->text());
			query2.exec(str);
			query2.next();
			str = QString("insert into sc values(%1,%2,%3);").arg(query1.value(0).toInt()).arg(query2.value(0).toInt()).arg(ui->tableWidget->item(temp, 2)->text().toFloat());
			flag = true;
		}
		ui->tableWidget->verticalHeader()->setHidden(true);
		this->rec.clear();
		if (query.exec(str) == true && flag == true) {
			QMessageBox message(QMessageBox::NoIcon, QString::fromLocal8Bit("成绩管理"), QString::fromLocal8Bit("更新成功！")); 
			message.exec();
		}
	}
}

void ScDialog::onInserted() {
	//ui->tableWidget->setItem(iRow,2,new QTableWidgetItem(query.value(2).toString()));
	//ui->tableWidget->setItem(iRow,3,new QTableWidgetItem(query.value(3).toString()));
	//ui->tableWidget->setItem(iRow,4,new QTableWidgetItem(query.value(4).toString()));
		int iRow = ui->tableWidget->rowCount();
		//ui->m_name->setText(QString::fromLocal8Bit("学号："));
		ui->tableWidget->setRowCount(iRow + 1);
}

void ScDialog::onDeleted() {
	QString str;
	SqliteDb *sqlite = SqliteDb::getInstance();
	if (QSqlDatabase* db = (QSqlDatabase*)sqlite->ConnectDB("qt"))
	{
		QSqlQuery query;
		QSqlQuery query1;
		QSqlQuery query2;
 		str = QString("select user_id from user where user_name = '%1';").arg(ui->tableWidget->item(this->inrec, 0)->text());
		query1.exec(str);
		query1.next();
		str = QString("select course_id from course where course_name = '%1';").arg(ui->tableWidget->item(this->inrec, 1)->text());
		query2.exec(str);
		query2.next();
		ui->tableWidget->removeRow(this->inrec);
		str = QString("delete from sc where sc_sid = %1 and sc_cid= %2;").arg(query1.value(0).toInt()).arg(query2.value(0).toInt());
		if (query.exec(str) == true) {
			QMessageBox message(QMessageBox::NoIcon, QString::fromLocal8Bit("成绩管理"), QString::fromLocal8Bit("删除成功！")); 
			message.exec();
		}
		sqlite->DisConnectDB(db);
	}
}

void ScDialog::onShow() {
	onTable();
	this->show();
}