#pragma once

#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "src/lib/shared_ptr.hpp"
#include "src/RailwayMinistry.hpp"
#include <QDialog>

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = 0);
    ~loginDialog();
    shared_ptr<RailwayMinistry>rm;
    void loadRM(shared_ptr<RailwayMinistry>_rm);
    string getID();
private slots:
    void on_login_clicked();

    void on_reg_clicked();

private:
    Ui::loginDialog *ui;
};

#endif // LOGINDIALOG_H
