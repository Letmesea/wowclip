#ifndef DOSTH_H
#define DOSTH_H

#include <QWidget>
#include <QLabel>

#include <QLineEdit>
#include <QTextEdit>
#include <QObject>
#include <QStackedWidget>

#include <qevent.h>
#include <QPointer>
#include<QHBoxLayout>
#include<QTextBrowser>
#include <QDebug>
/**
 * @brief 可编辑的项
 */
class Dosth:public QWidget{
    Q_OBJECT
public:
    Dosth(QWidget *parent = nullptr);
protected:
    bool eventFilter(QObject * obj, QEvent * e);
private:
    QPointer<QStackedWidget> stackedWidget;
        QPointer<QLabel> label;
//        QPointer<QTextBrowser> qb;
        QPointer<QTextEdit> lineEdit;
        //水平
        QHBoxLayout *hBoxLayout;
        QHBoxLayout *hBoxLayout2;
        //垂直
        QVBoxLayout *vBoxLayout;
};

#endif // DOSTH_H
