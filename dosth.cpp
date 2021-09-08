#include <dosth.h>

Dosth::Dosth(QWidget *parent)
    : QWidget(parent) {

    stackedWidget = new QStackedWidget(this);
    QString res = "hhhh来了来了";

    label = new QLabel(this);
//    label->setText(label->fontMetrics().elidedText(res, Qt::ElideRight, 180, Qt::TextSingleLine));
//    label->setMinimumHeight(200);
//    label->setWordWrap(true);

//    label->setAttribute(Qt::WA_TranslucentBackground);
//    label->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

//    label->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
//    label->installEventFilter(this);



    lineEdit = new QTextEdit();
    lineEdit->setHtml(lineEdit->fontMetrics().elidedText(res, Qt::ElideRight, 180, Qt::TextSingleLine));
    lineEdit->setWordWrapMode(QTextOption::WrapAnywhere);
    lineEdit->setAttribute(Qt::WA_TranslucentBackground);
    lineEdit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    lineEdit->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    lineEdit->installEventFilter(this);
    lineEdit->setAcceptRichText(true);

    stackedWidget->addWidget(label);
    stackedWidget->addWidget(lineEdit);

    stackedWidget->setCurrentWidget(lineEdit);

    hBoxLayout = new QHBoxLayout();
    hBoxLayout->setMargin(0);
    hBoxLayout->addWidget(stackedWidget);

    vBoxLayout = new QVBoxLayout();
    vBoxLayout->setMargin(3);

    vBoxLayout->addLayout(hBoxLayout);
    setLayout(vBoxLayout);
}
bool Dosth::eventFilter(QObject * obj, QEvent * evt) {

    if  (obj==lineEdit){
        if  (evt->type()==QEvent::MouseButtonDblClick){

        }
    }

//    if (obj == qb)
//    {
//        if (evt->type() == QEvent::MouseButtonDblClick)
//        {
//            lineEdit->setText(qb->toHtml());
//            stackedWidget->setCurrentIndex(1);
//            //ui.lineEdit->setFocus();
//        }
//    }
//    else if (obj == lineEdit)
//    {
//        if (evt->type() == QEvent::KeyPress)
//        {
//            QKeyEvent* keyevt = static_cast<QKeyEvent*>(evt);
//            if ((keyevt->key() == Qt::Key_Return) ||
//                (keyevt->key() == Qt::Key_Escape) ||(keyevt->key() == Qt::Key_Enter))
//            {
//                qb->setText(lineEdit->toPlainText());
//                stackedWidget->setCurrentIndex(0);
//            }
//        }
//        else if (evt->type() == QEvent::FocusOut)
//        {
//            qb->setText(lineEdit->toPlainText());
//            stackedWidget->setCurrentIndex(0);
//        }
//    }

    return QWidget::eventFilter(obj, evt);
}
