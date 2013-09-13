#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QtGui>

#include "tablemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void test(bool value);
    void showNetworkHealthDialog();
    void showPackageListWidget(QModelIndex index);
//    void showEditingWizard(QModelIndex index);
    void selectPackageList(QModelIndex index);
    void resetview();

private:
    Ui::MainWindow *ui;
    bool static leftbarHide;//TODO use a state machine if logic going big
    int const static move_offset = 200;
    int const static duration = 100;
    TableModel* tableModel;
    QStringListModel* packageModel;
    QStringListModel* moduleModel;
};

#endif // MAINWINDOW_H
