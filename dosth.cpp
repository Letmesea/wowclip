#include <dosth.h>

Dosth::Dosth(QWidget *parent)
    : QWidget(parent) {

//    stackedWidget = new QStackedWidget(this);

//    label = new QLabel(this);
////    label->setText(label->fontMetrics().elidedText(res, Qt::ElideRight, 180, Qt::TextSingleLine));
//    label->setFixedHeight(100);
////    label->setWordWrap(true);

//    label->setAttribute(Qt::WA_TranslucentBackground);
////    label->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

//    label->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
//    label->installEventFilter(this);



    lineEdit = new QTextEdit();
    lineEdit->setWordWrapMode(QTextOption::WrapAnywhere);
    lineEdit->setAttribute(Qt::WA_TranslucentBackground);
    lineEdit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    lineEdit->setFixedHeight(109);
//    lineEdit->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
//    stackedWidget->setStyleSheet("background-color:#F8F8FF;border-width: 3px;border-color: #E1FFFF; border-style: solid;");
    lineEdit->installEventFilter(this);
    lineEdit->setAcceptRichText(true);
    lineEdit->verticalScrollBar()->setStyleSheet("QScrollBar{width:20px;}");
//    stackedWidget->addWidget(label);
//    stackedWidget->addWidget(lineEdit);

//    stackedWidget->setCurrentWidget(lineEdit);

    hBoxLayout = new QHBoxLayout();
    hBoxLayout->setMargin(0);
    hBoxLayout->addWidget(lineEdit);

    vBoxLayout = new QVBoxLayout();
    vBoxLayout->setMargin(3);

    vBoxLayout->addLayout(hBoxLayout);
    setLayout(vBoxLayout);
}
void Dosth::setText(QString text_){
//    QFontMetrics fontWidth(label->font());//得到每个字符的宽度
//        QString elideNote = fontWidth.elidedText(text_, Qt::ElideRight, 150);

    lineEdit->setHtml(text_);
//    label->setText(text_);
    //    label->setText(label->fontMetrics().elidedText(res, Qt::ElideRight, 180, Qt::TextSingleLine));

}
bool Dosth::eventFilter(QObject * obj, QEvent * evt) {


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
