#include "AdminWidget.h"
#include <QPushButton>
#include "MaDialog.h"
#include "ScDialog.h"

AdminWidget::AdminWidget():ui(new Ui::AdminWidget){
	ui->setupUi(this);
	connect(ui->m_User,SIGNAL(clicked()),this,SLOT(maUser()));
	connect(ui->m_Course,SIGNAL(clicked()),this,SLOT(maUser()));
	connect(ui->m_Grade,SIGNAL(clicked()),this,SLOT(maGrade()));
}

AdminWidget::~AdminWidget() {
	delete ui;
}

void AdminWidget::maUser() {
	MaDialog* ma_page = new MaDialog();
	ma_page->onShow();
}

void AdminWidget::maGrade() {
	ScDialog* scgrade = new ScDialog();
	scgrade->onShow();
}

void AdminWidget::maCourse() {
	MaDialog* ma_page = new MaDialog();
	ma_page->onShow();
}

void AdminWidget::maShow(int i) {
	this->adminid = i;
	this->show();
}