#include "MaDialog.h"
#include <QDebug>
#include <QMessageBox>
MaDialog::MaDialog(): ui(new Ui::MaDialog) {
	ui->setupUi(this);
	ui->lineEdit_3->setValidator(new QIntValidator(this));
	connect(ui->tableWidget, SIGNAL(cellChanged(int, int)),
		this, SLOT(onRecorded(int, int)));
	connect(ui->m_updated, SIGNAL(clicked(void)),
		this, SLOT(onUpdated(void)));
	connect(ui->m_selected, SIGNAL(clicked(void)),
		this, SLOT(onSelected(void)));
	connect(ui->m_inserted, SIGNAL(clicked(void)),
		this, SLOT(onInserted(void)));
}

MaDialog::~MaDialog() {
	this->rec.clear();
	delete ui;
}

void MaDialog::onTable() {
	SqliteDb *sqlite = SqliteDb::getInstance();
	if (QSqlDatabase* db = (QSqlDatabase*)sqlite->ConnectDB("qt")) {

		ui->tableWidget->clearContents();
		//ui->m_name->setText(QString::fromLocal8Bit("学号："));
		QString str = QString("select count(*) from course;");	
		QSqlQuery query;
		query.exec(str);
		int coun = 0;
		if (query.next()) {
			coun = query.value(0).toInt();
		}

		query.clear();

		ui->tableWidget->setRowCount(coun);

		str = QString("select * from course;");
		query.exec(str);
		int i = 0;
		while(query.next()) {
			QTableWidgetItem *item0 = new QTableWidgetItem(query.value(0).toString());
			QTableWidgetItem *item1 = new QTableWidgetItem(query.value(1).toString());
			item0->setFlags(Qt::NoItemFlags);
			item1->setFlags(Qt::NoItemFlags);
			ui->tableWidget->setItem(i,0,new QTableWidgetItem(*item0));
			ui->tableWidget->setItem(i,1,new QTableWidgetItem(*item1));
			ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
			ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value(3).toString()));
			ui->tableWidget->setItem(i,4,new QTableWidgetItem(query.value(4).toString()));
			++i;
		}
		query.clear();
		this->rec.clear();
		
		sqlite->DisConnectDB(db);
	}
}

void MaDialog::onSelected() {
	ui->tableWidget->clearContents();
	SqliteDb *sqlite = SqliteDb::getInstance();
	QString str = QString("select * from course");
	if (QSqlDatabase* db = (QSqlDatabase*)sqlite->ConnectDB("qt")) {
		int flag = 0;
		
		str += QString(" where ");
		if (!ui->lineEdit->text().isEmpty()) {
			str += QString("course_num = '%1'").arg(ui->lineEdit->text());
			++flag;
		}

		if (!ui->lineEdit_2->text().isEmpty()) {
			if (flag >= 1) {
				str += QString(" and ");
			}
			str += QString("course_name = '%1'").arg(ui->lineEdit_2->text());
			++flag;
		}
		if (!ui->lineEdit_3->text().isEmpty()) {
			if (flag >= 1) {
				str += QString(" and ");
			}
			++flag;
			str += QString("course_credit = %1").arg(ui->lineEdit_3->text().toInt());
		}

		if (!ui->lineEdit_4->text().isEmpty()) {
			if (flag >= 1) {
				str += QString(" and ");
			}
			++flag;
			str += QString("course_term = '%1'").arg(ui->lineEdit_4->text());
		}
		if (flag == 0) {
			str.remove(" where");
		}
		str += QString(";");


		QSqlQuery query;
		query.exec(str);
		int i = 0;
		while(query.next()) {
			QTableWidgetItem *item0 = new QTableWidgetItem(query.value(0).toString());
			QTableWidgetItem *item1 = new QTableWidgetItem(query.value(1).toString());
			item0->setFlags(Qt::NoItemFlags);
			item1->setFlags(Qt::NoItemFlags);
			ui->tableWidget->setItem(i,0,new QTableWidgetItem(*item0));
			ui->tableWidget->setItem(i,1,new QTableWidgetItem(*item1));
			ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
			ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value(3).toString()));
			ui->tableWidget->setItem(i,4,new QTableWidgetItem(query.value(4).toString()));
			++i;
		}
		query.clear();
		this->show();
		this->rec.clear();
	}
}


void MaDialog::onRecorded(int a, int b) {
	this->rec.push_back(make_pair(a,b));
}

void MaDialog::onUpdated(){
	QString str;
	SqliteDb *sqlite = SqliteDb::getInstance();
	if (QSqlDatabase* db = (QSqlDatabase*)sqlite->ConnectDB("qt"))
	{
		bool flag = false;
		str = QString("select count(*) from course;");
		QSqlQuery query;
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
					str = QString("update course set course_name = '%1' where course_id = %2;").arg(m_change).arg(m_select);		
				}
				else if (iter->second == 3) {
					str = QString("update course set course_term = '%1' where course_id = %2;").arg(m_change).arg(m_select);	
				}
				else if (iter->second == 4) {
					int im_change = m_change.toInt();
					str = QString("update course set course_credit = %1 where course_id = %2;").arg(im_change).arg(m_select);	
				}
				flag = true;
			}
		}
		else {
			int temp = ui->tableWidget->rowCount() - 1;
			str = QString("insert into course values(%1,'%2','%3','%4',%5);").arg(ui->tableWidget->item(temp, 0)->text().toInt()).arg(ui->tableWidget->item(temp, 1)->text()).arg(ui->tableWidget->item(temp, 2)->text()).arg(ui->tableWidget->item(temp, 3)->text()).arg(ui->tableWidget->item(temp, 4)->text().toInt());
			flag = true;
		}
		this->rec.clear();
		if (query.exec(str) == true && flag == true) {
			QMessageBox message(QMessageBox::NoIcon, QString::fromLocal8Bit("学生管理"), QString::fromLocal8Bit("更新成功！")); 
			message.exec();
		}
	}
}

void MaDialog::onInserted() {
	//ui->tableWidget->setItem(iRow,2,new QTableWidgetItem(query.value(2).toString()));
	//ui->tableWidget->setItem(iRow,3,new QTableWidgetItem(query.value(3).toString()));
	//ui->tableWidget->setItem(iRow,4,new QTableWidgetItem(query.value(4).toString()));
	SqliteDb *sqlite = SqliteDb::getInstance();
	if (QSqlDatabase* db = (QSqlDatabase*)sqlite->ConnectDB("qt")) {
		int iRow = ui->tableWidget->rowCount();
		//ui->m_name->setText(QString::fromLocal8Bit("学号："));
		QString str = QString("select course_num from course where course_id = %1;").arg(iRow);
		QSqlQuery query;
		query.exec(str);
		int num = 0;
		if (query.next()) {
			num = query.value(0).toInt();
		}
		query.clear();
		ui->tableWidget->setRowCount(iRow + 1);
		QTableWidgetItem *item0 = new QTableWidgetItem(QString::number(iRow+1));
		QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(++num));
		item0->setFlags(Qt::NoItemFlags);
		item1->setFlags(Qt::NoItemFlags);
		ui->tableWidget->setItem(iRow,0,new QTableWidgetItem(*item0));
		ui->tableWidget->setItem(iRow,1,new QTableWidgetItem(*item1));
	}
}

void MaDialog::onShow() {
	onTable();
	this->show();
}