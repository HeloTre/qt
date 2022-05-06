#include "ChartDialog.h"

ChartDialog::ChartDialog():ui(new Ui::ChartDialog){
	ui->setupUi(this);
	image = QImage(850, 480, QImage::Format_RGB32); //��ʼ����С
	QColor backColor = qRgb(255, 255, 255);  //������ɫ
	image.fill(backColor); //�Ի������
}

ChartDialog::~ChartDialog() {
	delete ui;
}

void ChartDialog::Paint(vector<QString> &cname,vector<float> &cgrade) {
	QPainter painter(&image);
	painter.setRenderHint(QPainter::Antialiasing, true);//���÷����ģʽ���ÿ�һ��


	double pointx = 60, pointy = 400;//ȷ��������������꣬���ﶨ��(35,280)
	double width = 800 - pointx, height = 360;//ȷ���������ȸ��߶� ���Ķ��廭��Ϊ600X300��������˶�����

	//���������� ������ԭ��(35��280)
	//painter.drawRect(5, 5, 600-10,320-10);//��Χ�ľ��Σ���(5,5)�𣬵�(590,290)��������Χ����5�ļ�϶��

	painter.drawLine(pointx,pointy,width+pointx,pointy);//������x���Ϊwidth
	painter.drawLine(pointx,pointy-height,pointx,pointy);//������y�߶�Ϊheight




	//������������ֵ����Сֵ��ƽ����

	QPen pen, penPoint;
	pen.setColor(Qt::black);
	pen.setWidth(2);
	penPoint.setColor(Qt::blue);
	penPoint.setWidth(5);
	double kx = width / (cgrade.size() - 1);
	double ky = height / 4;
	for(int i = 0; i < cgrade.size() - 1; ++i)
	{
		//����y���ǵ��ŵģ�����y������Ҫpointy-a[i]*ky ����kyΪ����ϵ��
		painter.setPen(pen);//��ɫ����������
		painter.drawLine(pointx + i * kx, pointy - cgrade[i] / 25.0 * ky, pointx + kx * (i + 1), pointy-cgrade[i+1] / 25.0 * ky);  //����
		painter.setPen(penPoint);//��ɫ�ıʣ����ڱ�Ǹ�����
		painter.drawPoint(pointx + kx * i, pointy - cgrade[i] / 25.0 * ky);  //����y����
		painter.drawText(pointx + kx * i, pointy - cgrade[i] / 25.0 * ky - 5,
			QString::number(cgrade[i])); 
	}
	painter.drawPoint(pointx + kx * (cgrade.size() - 1), pointy - cgrade[cgrade.size() -1 ] / 25.0 * ky);//�������һ����
	painter.drawText(pointx + kx * (cgrade.size() - 1), pointy - cgrade[cgrade.size() -1 ] / 25.0 * ky - 5,
		QString::number(cgrade.back())); 

	//����ƽ����
	//QPen penAve;
	//penAve.setColor(Qt::red);//ѡ���ɫ
	//penAve.setWidth(2);
	//penAve.setStyle(Qt::DotLine);//��������Ϊ����
	//painter.setPen(penAve);
	//painter.drawLine(pointx,pointy-78*ky,pointx+width,pointy-78*ky);



	//���ƿ̶���
	QPen penDegree;
	penDegree.setColor(Qt::black);
	penDegree.setWidth(2);
	painter.setPen(penDegree);
	//����x��̶���
	for(int i=0; i < cgrade.size(); ++i)
	{
		//ѡȡ���ʵ����꣬����һ�γ���Ϊ4��ֱ�ߣ����ڱ�ʾ�̶�
		painter.drawLine(pointx + i * kx,pointy,pointx + i * kx, pointy - 4);
		painter.drawText(pointx + i * kx - 12,
			pointy + 25, cname[i]);   //�����ֵ
	}
	//y��̶���
	double _maStep=(double) 50.0 / 4.0;//y��̶ȼ����������ֵ����ʾ
	for(int i = 0; i < 4; ++i)
	{
		//��Ҫ����ȷ��һ��λ�ã�Ȼ��һ���̶̵�ֱ�߱�ʾ�̶ȡ�
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