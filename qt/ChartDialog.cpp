#include "ChartDialog.h"

ChartDialog::ChartDialog():ui(new Ui::ChartDialog){
	ui->setupUi(this);
	image = QImage(850, 480, QImage::Format_RGB32); //初始化大小
	QColor backColor = qRgb(255, 255, 255);  //背景颜色
	image.fill(backColor); //对画布填充
}

ChartDialog::~ChartDialog() {
	delete ui;
}

void ChartDialog::Paint(vector<QString> &cname,vector<float> &cgrade) {
	QPainter painter(&image);
	painter.setRenderHint(QPainter::Antialiasing, true);//设置反锯齿模式，好看一点


	double pointx = 60, pointy = 400;//确定坐标轴起点坐标，这里定义(35,280)
	double width = 800 - pointx, height = 360;//确定坐标轴宽度跟高度 上文定义画布为600X300，宽高依此而定。

	//绘制坐标轴 坐标轴原点(35，280)
	//painter.drawRect(5, 5, 600-10,320-10);//外围的矩形，从(5,5)起，到(590,290)结束，周围留了5的间隙。

	painter.drawLine(pointx,pointy,width+pointx,pointy);//坐标轴x宽度为width
	painter.drawLine(pointx,pointy-height,pointx,pointy);//坐标轴y高度为height




	//获得数据中最大值和最小值、平均数

	QPen pen, penPoint;
	pen.setColor(Qt::black);
	pen.setWidth(2);
	penPoint.setColor(Qt::blue);
	penPoint.setWidth(5);
	double kx = width / (cgrade.size() - 1);
	double ky = height / 4;
	for(int i = 0; i < cgrade.size() - 1; ++i)
	{
		//由于y轴是倒着的，所以y轴坐标要pointy-a[i]*ky 其中ky为比例系数
		painter.setPen(pen);//黑色笔用于连线
		painter.drawLine(pointx + i * kx, pointy - cgrade[i] / 25.0 * ky, pointx + kx * (i + 1), pointy-cgrade[i+1] / 25.0 * ky);  //连线
		painter.setPen(penPoint);//蓝色的笔，用于标记各个点
		painter.drawPoint(pointx + kx * i, pointy - cgrade[i] / 25.0 * ky);  //计算y坐标
		painter.drawText(pointx + kx * i, pointy - cgrade[i] / 25.0 * ky - 5,
			QString::number(cgrade[i])); 
	}
	painter.drawPoint(pointx + kx * (cgrade.size() - 1), pointy - cgrade[cgrade.size() -1 ] / 25.0 * ky);//绘制最后一个点
	painter.drawText(pointx + kx * (cgrade.size() - 1), pointy - cgrade[cgrade.size() -1 ] / 25.0 * ky - 5,
		QString::number(cgrade.back())); 

	//绘制平均线
	//QPen penAve;
	//penAve.setColor(Qt::red);//选择红色
	//penAve.setWidth(2);
	//penAve.setStyle(Qt::DotLine);//线条类型为虚线
	//painter.setPen(penAve);
	//painter.drawLine(pointx,pointy-78*ky,pointx+width,pointy-78*ky);



	//绘制刻度线
	QPen penDegree;
	penDegree.setColor(Qt::black);
	penDegree.setWidth(2);
	painter.setPen(penDegree);
	//画上x轴刻度线
	for(int i=0; i < cgrade.size(); ++i)
	{
		//选取合适的坐标，绘制一段长度为4的直线，用于表示刻度
		painter.drawLine(pointx + i * kx,pointy,pointx + i * kx, pointy - 4);
		painter.drawText(pointx + i * kx - 12,
			pointy + 25, cname[i]);   //给点标值
	}
	//y轴刻度线
	double _maStep=(double) 50.0 / 4.0;//y轴刻度间隔需根据最大值来表示
	for(int i = 0; i < 4; ++i)
	{
		//主要就是确定一个位置，然后画一条短短的直线表示刻度。
		painter.drawLine(pointx, pointy - (i + 1) * ky,
			pointx + 4, pointy - (i + 1) * ky);
		if (i == 0) {
			painter.drawText(pointx - 50, pointy - (i + 0.85) * ky,
				QString::number(50));
		}
		else {
			painter.drawText(pointx - 50, pointy - (i + 0.85) * ky,
				QString::number((double)(_maStep*(i+1))+50)); 
		}
	}
}