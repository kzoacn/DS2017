#include "minewindow.h"
#include "ui_minewindow.h"

MineWindow::MineWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MineWindow)
{
    ui->setupUi(this);
}

MineWindow::~MineWindow()
{
    delete ui;
}
