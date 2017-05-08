#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "minewindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "minewindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QString>
#include "src/RailwayMinistry.hpp"
#include "src/Station.hpp"
#include <QMessageBox>
#include "minewindow.h"
using namespace sjtu;
using std::to_string;

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}
void AdminWindow::load(string _id, shared_ptr<RailwayMinistry> _rm){
    admin=Admin(_id,_rm);
}

void AdminWindow::on_openCSV_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open CSV"), ".", tr("CSV Files(*.csv)"));
    if(path.length() == 0) {
               QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
     } else {
        ui->CSVPath->setText(path);
     }
}

void AdminWindow::on_load_clicked()
{
    admin.addTrainFromCSV(ui->CSVPath->text().toStdString());
    QMessageBox::information(NULL, tr("Path"), tr("Success!"));
}

void AdminWindow::on_open_log_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open Log"), ".", tr("Files(*.*)"));
    if(path.length() == 0) {
               QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
     } else {
        ui->log_path->setText(path);
     }
}

void AdminWindow::on_load_log_clicked()
{
    admin.addLogFromFile(ui->log_path->text().toStdString());
    QMessageBox::information(NULL, tr("Path"), tr("Success!"));
}

void AdminWindow::on_query_user_clicked()
{
    MineWindow *mine=new MineWindow(this);
    string id=ui->userid->text().toStdString();
    mine->load(id,admin.rw);
    mine->show();
}

void AdminWindow::on_export_log_clicked()
{
    QString path = QFileDialog::getSaveFileName(this,tr("选择导出文件"),".",tr("Log File (*.log)"));
    if(path.length() == 0) {
           QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
     } else {
        admin.exportLog(path.toStdString());
        QMessageBox::information(NULL, tr("Path"), tr("Success!"));
     }
}

void AdminWindow::on_pushButton_11_clicked()
{
    QStandardItemModel  *model = new QStandardItemModel();
    model->setColumnCount(16);
    model->setHeaderData(0,Qt::Horizontal,tr("车次"));
    model->setHeaderData(1,Qt::Horizontal,tr("起点"));
    model->setHeaderData(2,Qt::Horizontal,tr("终点"));
    model->setHeaderData(3,Qt::Horizontal,tr("出发时间"));
    model->setHeaderData(4,Qt::Horizontal,tr("到达时间"));
    model->setHeaderData(5,Qt::Horizontal,tr("经过时间"));
    model->setHeaderData(6,Qt::Horizontal,tr("二等座"));
    model->setHeaderData(7,Qt::Horizontal,tr("一等座"));
    model->setHeaderData(8,Qt::Horizontal,tr("商务座"));
    model->setHeaderData(9,Qt::Horizontal,tr("特等座"));
    model->setHeaderData(10,Qt::Horizontal,tr("无座"));
    model->setHeaderData(11,Qt::Horizontal,tr("软座"));
    model->setHeaderData(12,Qt::Horizontal,tr("硬座"));
    model->setHeaderData(13,Qt::Horizontal,tr("高级软卧"));
    model->setHeaderData(14,Qt::Horizontal,tr("软卧下"));
    model->setHeaderData(15,Qt::Horizontal,tr("硬卧下"));
    Station a,b;
    a=Station(ui->start->text().toStdString());
    b=Station(ui->target->text().toStdString());
    Date date(ui->dateEdit->date());
    //date=Date::fromDay(ui->date->text().toStdString());
    vector<Train>trains=admin.getTrainByST(a,b,date);
    for(int i=0;i<trains.size();i++){
        model->setItem(i,0,new QStandardItem(QString::fromStdString(trains[i].getID())));
        model->setItem(i,1,new QStandardItem(QString::fromStdString(a.getName())));
        model->setItem(i,2,new QStandardItem(QString::fromStdString(b.getName())));
        model->setItem(i,3,new QStandardItem(QString::fromStdString(trains[i].getTime(date,a).to_string())));
        model->setItem(i,4,new QStandardItem(QString::fromStdString(trains[i].getTime(date,b).to_string())));
        model->setItem(i,5,new QStandardItem(QString::fromStdString(to_string((trains[i].getTime(date,b)-trains[i].getTime(date,a))))));
        for(int l=0;l<10;l++){
            if(trains[i].getCost(a,b,Ticket::toLevel(l))==0)
                model->setItem(i,6+l,new QStandardItem("-"));
            else
                model->setItem(i,6+l,new QStandardItem(QString::fromStdString(to_string((trains[i].getCost(a,b,Ticket::toLevel(l)))))));
        }
    }
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void AdminWindow::on_train_query_2_clicked()
{
    QStandardItemModel  *model = new QStandardItemModel();
    model->setColumnCount(13);
    model->setHeaderData(0,Qt::Horizontal,tr("站点"));
    model->setHeaderData(1,Qt::Horizontal,tr("时间"));
    model->setHeaderData(2,Qt::Horizontal,tr("二等座"));
    model->setHeaderData(3,Qt::Horizontal,tr("一等座"));
    model->setHeaderData(4,Qt::Horizontal,tr("商务座"));
    model->setHeaderData(5,Qt::Horizontal,tr("特等座"));
    model->setHeaderData(6,Qt::Horizontal,tr("无座"));
    model->setHeaderData(7,Qt::Horizontal,tr("软座"));
    model->setHeaderData(8,Qt::Horizontal,tr("硬座"));
    model->setHeaderData(9,Qt::Horizontal,tr("高级软卧"));
    model->setHeaderData(10,Qt::Horizontal,tr("软卧下"));
    model->setHeaderData(11,Qt::Horizontal,tr("硬卧下"));
    Train train=admin.getTrainByID(ui->train_number->text().toStdString());
    Date date(ui->dateEdit->date());
    //date=Date::fromDay(ui->date->text().toStdString());

    for(int i=0;i<train.getWay().size();i++){
        Station a=train.getWay()[i];
        model->setItem(i,0,new QStandardItem(QString::fromStdString(a.getName())));
        model->setItem(i,1,new QStandardItem(QString::fromStdString(train.getTime(date,a).to_string())));
        for(int l=0;l<10;l++){
            if(train.getCost(train.getStart(),a,Ticket::toLevel(l))==0)
                model->setItem(i,2+l,new QStandardItem("-"));
            else
                model->setItem(i,2+l,new QStandardItem(QString::fromStdString(to_string((train.getCost(train.getStart(),a,Ticket::toLevel(l)))))));
        }
    }

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void AdminWindow::on_pushButton_9_clicked()
{
    MineWindow *mine=new MineWindow(this);
    mine->load(admin.id,admin.rw);
    mine->show();
}

void AdminWindow::on_pushButton_3_clicked()
{
    string id=ui->train_number->text().toStdString();
    if(!admin.existTrain(id)){
        QMessageBox::warning(NULL,tr("提示"),tr("没有该车次"));
        return ;
    }
    if(admin.removeTrain(id))
        QMessageBox::information(NULL,tr("提示"),tr("删除成功"));
    else
        QMessageBox::warning(NULL,tr("提示"),tr("删除失败..."));
}

void AdminWindow::on_pushButton_5_clicked()
{
    Date date(ui->dateEdit->date());
    string trainid=ui->train_number->text().toStdString();
    if(!admin.existTrain(trainid)){
        QMessageBox::warning(NULL,tr("提示"),tr("没有该车次"));
        return ;
    }
    if(!admin.hasSold(trainid,date)){
        QMessageBox::warning(NULL,tr("提示"),tr("车次已有票售出，不可更改！"));
        return ;
    }
    if(admin.canSell(trainid,date)){
        admin.endSale(trainid,date);
        QMessageBox::information(NULL,tr("提示"),tr("已停止发售"));
    }else{
        admin.startSale(trainid,date);
        QMessageBox::information(NULL,tr("提示"),tr("已开始发售"));
    }
}
