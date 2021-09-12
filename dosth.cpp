#include <dosth.h>

Dosth::Dosth(QWidget *parent)
    : QWidget(parent) {

    stackedWidget = new QStackedWidget(this);
    QString res = "<html><body><p style=\"margin: 10px auto; padding: 0px; text-indent: 0px; color: rgb(0, 0, 0); font-family: &quot;Helvetica Neue&quot;, Helvetica, Verdana, Arial, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: left; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; background-color: rgb(255, 255, 255); text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;\">点击 Accept License Agreement 选择好版本进行下载，需要注册Oracle账户登陆下载！</p><p style=\"margin: 10px auto; padding: 0px; text-indent: 0px; color: rgb(0, 0, 0); font-family: &quot;Helvetica Neue&quot;, Helvetica, Verdana, Arial, sans-serif; font-size: 14px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: left; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; background-color: rgb(255, 255, 255); text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;\"><IMG alt=\"enter description here\"   src='://mlogo5' loading=\"lazy\" style=\"margin: 0px; padding: 0px; border: 0px; max-width: 700px; height: auto;\"><\/p><\/body><\/html>";

    label = new QLabel(this);
//    label->setText(label->fontMetrics().elidedText(res, Qt::ElideRight, 180, Qt::TextSingleLine));
//    label->setMinimumHeight(200);
//    label->setWordWrap(true);

//    label->setAttribute(Qt::WA_TranslucentBackground);
//    label->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

//    label->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
//    label->installEventFilter(this);



    lineEdit = new QTextEdit();
//    lineEdit->setHtml(lineEdit->fontMetrics().elidedText(res, Qt::ElideRight, 180, Qt::TextSingleLine));
//    lineEdit->setHtml(res);
    lineEdit->setWordWrapMode(QTextOption::WrapAnywhere);
    lineEdit->setAttribute(Qt::WA_TranslucentBackground);
    lineEdit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
//    lineEdit->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    stackedWidget->setStyleSheet("background-color:#F8F8FF;border-width: 3px;border-color: #E1FFFF; border-style: solid;");
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
void Dosth::setText(QString text_){
    lineEdit->setHtml(text_);
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
