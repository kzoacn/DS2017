#include "logindialog.h"
#include "ui_logindialog.h"
#include "mainwindow.h"
#include "adminwindow.h"
#include <QMessageBox>
#include <QLineEdit>
using namespace sjtu;
loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
}

loginDialog::~loginDialog()
{
    delete ui;
}
void loginDialog::loadRM(shared_ptr<RailwayMinistry> _rm){
    rm=_rm;
}

string loginDialog::getID(){
    return ui->usr->text().toStdString();
}

bool loginDialog::isAdmin(){
    return ui->checkBox_2->isChecked();
}

void loginDialog::on_login_clicked()
{
    string id=ui->usr->text().toStdString();
    string pwd=ui->pwd->text().toStdString();
    if(rm->isUser(id,pwd)){
        if(ui->checkBox_2->isChecked()){
            if(rm->isAdmin(id)){
                accept();
            }else{
                QMessageBox::warning(this,tr("警告"),tr("你没有管理员权限"));
            }
        }else{
            accept();
        }
    }else{
        QMessageBox::warning(this, tr("警告！"),
                           tr("用户名或密码错误！"),
                           QMessageBox::Yes);
    }
}

void loginDialog::on_reg_clicked()
{
    string id=ui->usr->text().toStdString();
    string pwd=ui->pwd->text().toStdString();
    if(rm->regiser(id,pwd,id)){
        QMessageBox::information(this, tr("提示"),
                           tr("注册成功！"),
                           QMessageBox::Yes);
    }else{
        QMessageBox::warning(this, tr("警告！"),
                           tr("用户名已使用"),
                           QMessageBox::Yes);
    }
}

void loginDialog::on_checkBox_stateChanged(int arg1)
{
    if(ui->checkBox->isChecked())
        ui->pwd->setEchoMode(QLineEdit::Normal);
    else
        ui->pwd->setEchoMode(QLineEdit::Password);
}

void loginDialog::on_checkBox_2_stateChanged(int arg1)
{

}
