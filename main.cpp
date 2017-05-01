#include "mainwindow.h"
#include "logindialog.h"
#include "testwindow.h"
#include "src/RailwayMinistry.hpp"
#include <QApplication>
#include <QDialog>
#include <QTextCodec>
#include <QStandardItemModel>
#include "src/User.hpp"
#include "src/Admin.hpp"
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
    lgin.show();
    MainWindow w;
    w.show();




    return a.exec();
}
