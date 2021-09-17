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
#include <QScrollBar>

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
     //关闭按钮
     void on_closeButton_clicked();
     //显示主页
     void showHome();
     //系统托盘点击事件
     void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
};
class AnimatedScrollBar : public QScrollBar
{
    Q_OBJECT
    Q_PROPERTY(int expandedWidth READ expandedWidth WRITE setExpandedWidth)
public:
    AnimatedScrollBar(QWidget *parent = Q_NULLPTR);
    QSize sizeHint() const;
    int expandedWidth(){
        return _expandedWidth;
    }
    void setExpandedWidth(int val);

protected:
    bool event(QEvent *e);
private:
    QVariantAnimation *varAnima;
    int preferWidth = 15;
    int _expandedWidth = 22;
};
#endif // WOWCLIP_H
