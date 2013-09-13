#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

class CustomTabStyle : public QProxyStyle
{
public:
    QSize sizeFromContents(ContentsType type, const QStyleOption *option,
                           const QSize &size, const QWidget *widget) const
    {
        QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
        if (type == QStyle::CT_TabBarTab)
            s.transpose();
        return s;
    }

    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {

        QProxyStyle::drawControl(element, option, painter, widget);
        if (element == CE_TabBarTabLabel)
        {
            if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option))
            {
                QStyleOptionTab opt(*tab);
                opt.shape = QTabBar::RoundedNorth;
                QProxyStyle::drawControl(element, &opt, painter, widget);
                return;
            }
        }
        QProxyStyle::drawControl(element, option, painter, widget);
    }
};



bool MainWindow::leftbarHide = false;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //populate and set the model
    QStringList packageList;
    packageList.append("Local Ads");
    packageList.append("South American Ads");
    packageList.append("German Ads");

    QStandardItemModel* packageIconStringModel = new QStandardItemModel(this);

    QIcon iconAddCopy;
    QPixmap iconW(":/res/icons/white/add_copies.png");
    QPixmap iconB(":/res/icons/black/add_copies.png");
    iconAddCopy.addPixmap(iconW,QIcon::Normal);
    iconAddCopy.addPixmap(iconB,QIcon::Selected);
    QStandardItem* item1 = new QStandardItem(iconAddCopy, "Add Copies");

    QIcon iconCampaigns;
    QPixmap iconCampaignsW(":/res/icons/white/campaigns.png");
    QPixmap iconCampaignsB(":/res/icons/black/campaigns.png");
    iconCampaigns.addPixmap(iconCampaignsW,QIcon::Normal);
    iconCampaigns.addPixmap(iconCampaignsB,QIcon::Selected);
    QStandardItem* item2 = new QStandardItem(iconCampaigns, "Campaigns");

    QIcon iconCate;
    QPixmap iconCateW(":/res/icons/white/categories.png");
    QPixmap iconCateB(":/res/icons/black/categories.png");
    iconCate.addPixmap(iconCateW,QIcon::Normal);
    iconCate.addPixmap(iconCateB,QIcon::Selected);
    QStandardItem* item3 = new QStandardItem(iconCate, "Categories");

    QIcon iconConfigure;
    QPixmap iconConfigureW(":/res/icons/white/config.png");
    QPixmap iconConfigureB(":/res/icons/black/config.png");
    iconConfigure.addPixmap(iconConfigureW,QIcon::Normal);
    iconConfigure.addPixmap(iconConfigureB,QIcon::Selected);
    QStandardItem* item4 = new QStandardItem(iconConfigure, "Configurations");

    //    QIcon iconCate;
    //    QPixmap iconCateW(":/res/icons/white/categories.png");
    //    QPixmap iconCateB(":/res/icons/black/categories.png");
    //    iconCate.addPixmap(iconCateW,QIcon::Normal);
    //    iconCate.addPixmap(iconCateB,QIcon::Selected);
    //    QStandardItem* item3 = new QStandardItem(iconCate, "Categories");



    packageIconStringModel->appendRow(item1);
    packageIconStringModel->appendRow(item2);
    packageIconStringModel->appendRow(item3);
    packageIconStringModel->appendRow(item4);

    tableModel = new TableModel(this);
    //    ui->itemTableView->setAlternatingRowColors(true);
    ui->itemFrame->setStyleSheet(".QFrame#itemFrame{background-color: rgba(51,55,60,80);}");
    ui->itemTableView->setStyleSheet("QHeaderView{background: rgba(109,94,95);color:white;} QTableCornerButton::section{background-color:rgba(51,55,60,0)}" \
                                     " QTableView#itemTableView{color: white;background-color: rgba(51,55,60,0);selection-color:black; selection-background-color:white;}");
    //    ui->itemTableView->setStyleSheet("background-color: rgba(51,55,60,80);");
    //    ui->itemTableView->setStyleSheet(" QTableView#itemTableView{background-color: rgba(51,55,60,80);} QFrame#itemFrame{background-color:red}");

    ui->itemEditWidget->setStyleSheet("QPushButton{background-color: rgba(30, 30, 30,200); color: white; font: 12pt}");
    ui->menuBar->setStyleSheet("QMenuBar{background-color:rgb(35,58,144); color: white; padding-top:10px;}   QMenu{font:12px}");

    ui->tabWidget->setStyle(new CustomTabStyle);
    packageModel = new QStringListModel(packageList,this);
    ui->moduleList->setModel(packageIconStringModel);
    ui->packageListView->setModel(packageModel);
    ui->itemTableView->setModel(tableModel);

    ui->packageListWidget->hide();
    ui->itemFrame->hide();
    ui->itemEditWidget->hide();
    ui->Wizard->hide();

    //apply assets
    setStyleSheet("MainWindow {background-image:url(:/res/images/blurred_background.png)};");
    QPixmap adminIcon(":/res/images/user_portrait.png");
    ui->serverName->setPixmap(adminIcon);
    ui->serverName->setFixedSize(adminIcon.size());


    //rightbar
    QPixmap networkHealth(":/res/images/network_health.png");
    ui->networkHealth->setIcon(networkHealth);
    ui->networkHealth->setIconSize(networkHealth.size());

    QPixmap networkBandwidth(":/res/images/network_bandwidth.png");
    ui->networkBandwidth->setIcon(networkBandwidth);
    ui->networkBandwidth->setIconSize(networkBandwidth.size());

    QPixmap networkUploaded(":/res/images/recently_uploaded.png");
    ui->networkUploaded->setIcon(networkUploaded);
    ui->networkUploaded->setIconSize(networkUploaded.size());

    QPixmap networkReported(":/res/images/recently_reported.png");
    ui->networkReported->setIcon(networkReported);
    ui->networkReported->setIconSize(networkReported.size());

    QPixmap networkAD(":/res/images/recently_created.png");
    ui->networkCreatedAD->setIcon(networkAD);
    ui->networkCreatedAD->setIconSize(networkAD.size());

    QPixmap networkStatus(":/res/images/network_status.png");
    ui->networkStatus->setIcon(networkStatus);
    ui->networkStatus->setIconSize(networkStatus.size());

    connect(ui->addItemButton, SIGNAL(clicked(bool)) , this, SLOT(test(bool)));
    connect(ui->networkHealth, SIGNAL(clicked()), this, SLOT(showNetworkHealthDialog()));
    connect(ui->moduleList, SIGNAL(clicked(QModelIndex)), this, SLOT(showPackageListWidget(QModelIndex)) );
    connect(ui->itemTableView,SIGNAL(clicked(QModelIndex)),ui->itemEditWidget, SLOT(show()));
    connect(ui->itemEdit,SIGNAL(clicked()), ui->Wizard, SLOT(show()));
    connect(ui->packageListView,SIGNAL(clicked(QModelIndex)), this, SLOT(selectPackageList(QModelIndex)));
    connect(ui->WizardCancelButton,SIGNAL(clicked()), ui->Wizard, SLOT(hide()));
    connect(ui->resetviewButton,SIGNAL(clicked()), this, SLOT(resetview()));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::test(bool value){
    qDebug() << "got value: " << value << endl;
}

void MainWindow::showNetworkHealthDialog(){
    qDebug() << "got it" << endl;
    QDialog d;
    d.setWindowTitle("NewworkHealth");
    d.exec();
}

void MainWindow::showPackageListWidget(QModelIndex index){
    this->ui->packageListWidget->show();
    //TODO change model by the index;
}

void MainWindow::selectPackageList(QModelIndex index){
    if(!leftbarHide){
        ui->itemFrame->show();
        //todo move module and package widget left;
        QPropertyAnimation* animationItemFrame = new QPropertyAnimation(ui->adminWidget, "geometry");
        animationItemFrame->setDuration(duration);
        animationItemFrame->setEndValue(QRect(ui->adminWidget->geometry().x() - move_offset,
                                              ui->adminWidget->geometry().y(), ui->adminWidget->geometry().width(), ui->adminWidget->geometry().height()));
        QPropertyAnimation* animationPackageFrame = new QPropertyAnimation(ui->packageListWidget, "geometry");
        animationPackageFrame->setDuration(duration);
        animationPackageFrame->setEndValue(QRect(ui->packageListWidget->geometry().x() - move_offset,
                                                 ui->packageListWidget->geometry().y(), ui->packageListWidget->geometry().width(), ui->packageListWidget->geometry().height()));
        animationItemFrame->start();
        animationPackageFrame->start();
        leftbarHide = true;
    }
}


void MainWindow::resetview(){
    //move module and package widget right, and hide itemTableview(as well as all its editor)
    if(leftbarHide){
        ui->itemFrame->hide();
        //layout hack, css will give layout color, the main item tableview, edit groupbox, and item tablview should be in same widget
        ui->itemEditWidget->hide();
        ui->Wizard->hide();
        QPropertyAnimation* animationItemFrame = new QPropertyAnimation(ui->adminWidget, "geometry");
        animationItemFrame->setDuration(duration);
        animationItemFrame->setEndValue(QRect(ui->adminWidget->geometry().x() + move_offset,
                                              ui->adminWidget->geometry().y(), ui->adminWidget->geometry().width(), ui->adminWidget->geometry().height()));
        QPropertyAnimation* animationPackageFrame = new QPropertyAnimation(ui->packageListWidget, "geometry");
        animationPackageFrame->setDuration(duration);
        animationPackageFrame->setEndValue(QRect(ui->packageListWidget->geometry().x() + move_offset,
                                                 ui->packageListWidget->geometry().y(), ui->packageListWidget->geometry().width(), ui->packageListWidget->geometry().height()));
        animationItemFrame->start();
        animationPackageFrame->start();
        leftbarHide = false;
    }

}
