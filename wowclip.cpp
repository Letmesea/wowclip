#include "wowclip.h"
#include "ui_wowclip.h"

WowClip::WowClip(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WowClip)
{

    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint|Qt::WindowSystemMenuHint|
                   Qt::WindowCloseButtonHint|Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

//    setWindowOpacity(0.9);
    if(!QSystemTrayIcon::isSystemTrayAvailable())
        return;
    system_tray ->setToolTip(tr("WowClip 1.0"));
    system_tray ->setIcon(QIcon("://logo"));
    system_tray->setContextMenu(menu_tray);

    system_tray->show();
    system_tray->showMessage(tr("wowclip"),
                             QString(tr("wowclip已启动")));
//    setWindowFlags(Qt::Tool);
//    this->hide();
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
