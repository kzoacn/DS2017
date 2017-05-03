#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
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

void loginDialog::on_login_clicked()
{
    string id=ui->usr->text().toStdString();
    string pwd=ui->pwd->text().toStdString();
    if(rm->isUser(id,pwd)){
        accept();
    }else{
        QMessageBox::warning(this, QString::fromLocal8Bit("警告！"),
                           QString::fromLocal8Bit("用户名或密码错误！"),
                           QMessageBox::Yes);
    }
}

void loginDialog::on_reg_clicked()
{
    string id=ui->usr->text().toStdString();
    string pwd=ui->pwd->text().toStdString();
    if(rm->regiser(id,pwd,id)){
        QMessageBox::warning(this, QString::fromLocal8Bit("警告！"),
                           QString::fromLocal8Bit("注册成功！"),
                           QMessageBox::Yes);
    }else{
        QMessageBox::warning(this, QString::fromLocal8Bit("警告！"),
                           QString::fromLocal8Bit("用户名已使用"),
                           QMessageBox::Yes);
    }
}
