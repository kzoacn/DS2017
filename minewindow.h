#ifndef MINEWINDOW_H
#define MINEWINDOW_H
#include <QMainWindow>
#include "src/lib/shared_ptr.hpp"
#include "src/RailwayMinistry.hpp"
#include "src/User.hpp"
using namespace sjtu;
namespace Ui {
class MineWindow;
}

class MineWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MineWindow(QWidget *parent = 0);
    ~MineWindow();
    User user;
    void load(string id,shared_ptr<RailwayMinistry>_rm);

private slots:
    void on_queryTicket_clicked();

    void on_yes_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MineWindow *ui;
};

#endif // MINEWINDOW_H
