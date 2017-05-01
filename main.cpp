#include "mainwindow.h"
#include "logindialog.h"
#include "testwindow.h"
#include "src/RailwayMinistry.hpp"
#include <QApplication>
#include <QDialog>
#include <QTextCodec>
#include <QStandardItemModel>
int main(int argc, char *argv[])
{
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    loginDialog lgin;
    lgin.show();
    RailwayMinistry rm;
    rm.writeToFile();




    return a.exec();
}
