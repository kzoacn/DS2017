#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "src/lib/shared_ptr.hpp"
#include "src/RailwayMinistry.hpp"
#include "src/User.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    User user;
    void load(string id,shared_ptr<RailwayMinistry>_rm);
private slots:
    void on_search_clicked();


    void on_train_query_clicked();


    void on_buy_clicked();


    void on_mine_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
