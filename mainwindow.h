#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTimerEvent>
#include <requester.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onGetDataClick();

private:
    void init();
    void getData();
    void timerEvent(QTimerEvent *event);
    Requester          _requester;
    QStandardItemModel _model;
    float _minLat;
    float _maxLat;
    float _minLon;
    float _maxLon;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
