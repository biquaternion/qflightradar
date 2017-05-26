#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QSettings>
#include <QVector>

static const QVector<QString> __fields = {QString("id"),      // mode-s code
                                          QString("lat"),     // latitude,  deg
                                          QString("lon"),     // longitude, deg
                                          QString("track"),   // angle between N and course (throw East), deg
                                          QString("alt"),     // calibrated altitude, ft
                                          QString("speed"),   // ground speed, knots
                                          QString("f_06"),    // unrecognized/squawk???
                                          QString("radar"),   // radar
                                          QString("type"),    // type (aircraft)
                                          QString("registr"), // registration
                                          QString("f_10"),    // looks like a timestamp
                                          QString("src"),     // departure airport
                                          QString("dst"),     // arrival airport
                                          QString("flight"),  // flight header
                                          QString("f_14"),
                                          QString("f_15"),
                                          QString("callsign"),// call sign
                                          QString("f_17")
                                         };

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    init();
    this->startTimer(1000);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::init() {
    QSettings settings(":/config.ini", QSettings::IniFormat);
    settings.beginGroup("margins");
    _minLat = settings.value("minlat", 56.29f).toFloat();
    _maxLat = settings.value("maxlat", 55.13f).toFloat();
    _minLon = settings.value("minlon", 36.83f).toFloat();
    _maxLon = settings.value("maxlon", 38.63f).toFloat();

    ui->tableView->setModel(&_model);

    _requester.initRequester("data-live.flightradar24.com", 80, 0);
    connect(ui->pbGET, &QPushButton::clicked,
            this, &MainWindow::onGetDataClick);
}

void MainWindow::getData() {
    auto funcSuccess = [this] (const QJsonObject &obj) {
        _model.clear();
        int c = 0;
        for (auto it = __fields.begin();
             it != __fields.end();
             ++it) {
            _model.setHorizontalHeaderItem(c, new QStandardItem(*it));
            c++; // 11
        }
        foreach (auto val, obj) {
            if (val.isArray()) {
                QVariantList list = val.toArray().toVariantList();
                QList<QStandardItem*> stItemList;
                foreach (auto entry, list) {
                    if(entry.canConvert(QMetaType::QString)) {
                        stItemList.append(new QStandardItem(entry.toString()));
                    }
                }
                _model.appendRow(stItemList);
            }
        }
    };
    auto funcError   = [] (const QJsonObject &obj) {
        qDebug() << "=\t=\t=\terror\t=\t=\t=";
        qDebug() << obj;
    };
//bounds=56.29,55.13,36.83,38.63 - Moscow region
    QString apiStr("zones/fcgi/feed.js?bounds=%1,%2,%3,%4");
    QString params = apiStr.
            arg(QString::number(_minLat)).
            arg(QString::number(_maxLat)).
            arg(QString::number(_minLon)).
            arg(QString::number(_maxLon));

    qDebug() << params;
    _requester.sendRequest(params,
                    funcSuccess,
                    funcError,
                    Requester::Type::GET);

}

void MainWindow::onGetDataClick() {
    getData();
}

void MainWindow::timerEvent(QTimerEvent *event) {
    getData();
}
