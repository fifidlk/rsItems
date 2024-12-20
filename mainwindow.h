#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void slot1();
    void slot2();
    void slot3();
    void slot4();
    void slot5();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *_scene;
};

#endif // MAINWINDOW_H
