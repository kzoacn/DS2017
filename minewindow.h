#ifndef MINEWINDOW_H
#define MINEWINDOW_H

#include <QMainWindow>

namespace Ui {
class MineWindow;
}

class MineWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MineWindow(QWidget *parent = 0);
    ~MineWindow();

private:
    Ui::MineWindow *ui;
};

#endif // MINEWINDOW_H
