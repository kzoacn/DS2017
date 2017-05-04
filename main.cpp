#include "mainwindow.h"
#include "adminwindow.h"
#include "logindialog.h"
#include "testwindow.h"
#include "src/RailwayMinistry.hpp"
#include <QApplication>
#include <QDialog>
#include <QTextCodec>
#include <QStandardItemModel>
#include "src/User.hpp"
#include "src/Admin.hpp"
#include <QDebug>
using namespace sjtu;
int main(int argc, char *argv[])
{
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    shared_ptr<RailwayMinistry> rm(new RailwayMinistry());


    rm->readFromFile();


    loginDialog lgin;
    MainWindow userWindow;
    AdminWindow adminWindow;
    lgin.loadRM(rm);
    if(lgin.exec()==QDialog::Accepted){
        qDebug()<<QString::fromStdString(lgin.getID())<<endl;
        string id=lgin.getID();
        if(lgin.isAdmin()){
            adminWindow.load(id,rm);
            adminWindow.show();
        }else{
            userWindow.load(id,rm);
            userWindow.show();
        }
        return a.exec();
    }
    return 0;
}
