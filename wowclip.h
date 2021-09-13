#ifndef WOWCLIP_H
#define WOWCLIP_H

#include <QMainWindow>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QMouseEvent>
#include <QAction>
#include <QApplication>
#include <dosth.h>
#include <QClipboard>
#include <QListWidgetItem>

#include <QMimeData>
#include <QDir>
#include <QFile>
#include <cstring>
#include <QtNetwork/QtNetwork>
#include <QDesktopWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class WowClip; }
QT_END_NAMESPACE

class WowClip : public QMainWindow
{
    Q_OBJECT
public:
    WowClip(QWidget *parent = nullptr);
    ~WowClip();

private:
    Ui::WowClip *ui;
     const QClipboard *board = QApplication::clipboard();
     const QClipboard::Mode mode = QClipboard::Clipboard;
    //类型数据
     const QMimeData *mimeData ;
    //系统托盘图标与提示
    QSystemTrayIcon *system_tray = new QSystemTrayIcon(this);
    //系统托盘菜单
    QMenu *menu_tray = new QMenu(this);

    bool mMoveing;
    QPoint mMovePosition;
    int screen_center_x = 0;
    QString workdir =QCoreApplication::applicationDirPath()+"/dataTemp/";
    bool isShow = false;

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    QString dealImgUrl(const QString &str);
private slots:
     void hotKey_Ctrlq();
     void createSysTrayActions();
     void addItem();
     void listenClipChanged(QClipboard::Mode mode_);
     void on_listWidget_currentItemChanged(QListWidgetItem *current,
                                           QListWidgetItem *previous);
     void saveData(const QString &data);
     void slot_replyFinished(QNetworkReply* reply);
};
#endif // WOWCLIP_H
