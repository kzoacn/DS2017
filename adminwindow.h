﻿#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include "src/lib/shared_ptr.hpp"
#include "src/RailwayMinistry.hpp"
#include "src/Admin.hpp"
#include <QMainWindow>

using namespace sjtu;
namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = 0);
    ~AdminWindow();
    Admin admin;
    void load(string id,shared_ptr<RailwayMinistry>_rm);
private slots:
    void on_openCSV_clicked();

    void on_load_clicked();

private:
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
