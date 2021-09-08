#include "wowclip.h"
#include "ui_wowclip.h"

WowClip::WowClip(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WowClip)
{

    ui->setupUi(this);
    connect(board, SIGNAL(changed(QClipboard::Mode)),
           this, SLOT(listenClipChanged()));
    setWindowFlags(
                Qt::Tool|
                Qt::NoDropShadowWindowHint
                |Qt::WindowStaysOnTopHint
                |Qt::WindowTitleHint
                |Qt::WindowSystemMenuHint
                |Qt::WindowCloseButtonHint
                |Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

//    setWindowOpacity(0.85);
    if(!QSystemTrayIcon::isSystemTrayAvailable())
        return;
    createSysTrayActions();
    system_tray ->setToolTip(tr("WowClip 1.0"));
    system_tray ->setIcon(QIcon("://mlogo5"));
    system_tray->setContextMenu(menu_tray);

    system_tray->show();

//    addItem();
//    system_tray->showMessage(tr("wowclip"),QString(tr("wowclip已启动")));
}
void WowClip::listenClipChanged(){

}
void WowClip:: addItem(){
    Dosth *widget = new Dosth(this);
    QListWidgetItem *item_ui = new QListWidgetItem("",ui->listWidget);
    ui->listWidget->addItem(item_ui);
    ui->listWidget->setItemWidget(item_ui, widget);
    item_ui->setSizeHint(QSize(widget->width(),widget->height()));
};
/**
创建系统托盘菜单动作*/
void WowClip::createSysTrayActions()
{

    QAction *action_quit = new QAction(this);

    action_quit->setIcon(QIcon("://out"));

    action_quit->setText(tr("退出"));

    menu_tray->addAction(action_quit);

    connect(action_quit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
}
void WowClip:: hotKey_Ctrlq( ){
    if  (isShow){
        this->hide();
        isShow = false;
    }else{
        this->show();
        isShow = true;
    }
    emit ;
}


WowClip::~WowClip()
{
    delete ui;
}
void WowClip::mousePressEvent(QMouseEvent *event)
{
    mMoveing = true;
    mMovePosition = event->globalPos() - pos();
    event->accept();
}

void WowClip::mouseMoveEvent(QMouseEvent *event)
{
    if (mMoveing && (event->buttons() && Qt::LeftButton)
            && (event->globalPos()-mMovePosition).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos()-mMovePosition);
        mMovePosition = event->globalPos() - pos();
    }
    event->accept();
}

void WowClip::mouseReleaseEvent(QMouseEvent *event)
{
    mMoveing = false;
}
