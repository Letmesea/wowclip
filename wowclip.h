#ifndef WOWCLIP_H
#define WOWCLIP_H

#include <QMainWindow>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QMouseEvent>

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
    QSystemTrayIcon *system_tray = new QSystemTrayIcon(this);
    QMenu *menu_tray = new QMenu(this);

    bool mMoveing;
    QPoint mMovePosition;
    int screen_center_x = 0;

    bool isShow = true;

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
private slots:
     void hotKey_Ctrlq();
};
#endif // WOWCLIP_H
