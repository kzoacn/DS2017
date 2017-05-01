#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "src/lib/shared_ptr.hpp"
//#include "src/RailwayMinistry.hpp"
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
private:
    Ui::loginDialog *ui;
};

#endif // LOGINDIALOG_H
