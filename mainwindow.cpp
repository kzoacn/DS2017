#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QString>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_search_clicked()
{
    QStandardItemModel  *model = new QStandardItemModel();
    model->setColumnCount(18);
    model->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("车次"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("起点"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("终点"));
    model->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("出发时间"));
    model->setHeaderData(4,Qt::Horizontal,QString::fromLocal8Bit("到达时间"));
    model->setHeaderData(5,Qt::Horizontal,QString::fromLocal8Bit("经过时间"));
    model->setHeaderData(6,Qt::Horizontal,QString::fromLocal8Bit("商务座"));
    /*model->setHeaderData(7,Qt::Horizontal,tr("特等座"));
    model->setHeaderData(8,Qt::Horizontal,tr("一等座"));
    model->setHeaderData(9,Qt::Horizontal,tr("二等座"));
    model->setHeaderData(10,Qt::Horizontal,tr("高级软卧"));
    model->setHeaderData(11,Qt::Horizontal,tr("软卧"));
    model->setHeaderData(12,Qt::Horizontal,tr("硬卧"));
    model->setHeaderData(13,Qt::Horizontal,tr("软座"));
    model->setHeaderData(14,Qt::Horizontal,tr("硬座"));
    model->setHeaderData(15,Qt::Horizontal,tr("无座"));
    model->setHeaderData(17,Qt::Horizontal,tr("其他"));*/
    for(int i=0;i<3;i++)
        for(int j=0;j<4;j++)
            model->setItem(i,j,new QStandardItem(QString('a'+(i^j))) );
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}
