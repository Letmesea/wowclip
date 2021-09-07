#include <dosth.h>

Dosth::Dosth(QWidget *parent)
    : QWidget(parent) {

    stackedWidget = new QStackedWidget(this);

    label = new QLabel(this);
    QString res = "hhhh来了来了";
    label->setText(label->fontMetrics().elidedText(res, Qt::ElideRight, 180, Qt::TextSingleLine));
label->setMinimumHeight(200);
label->setWordWrap(true);
//    label->setStyleSheet("background-color:white");
    label->setAttribute(Qt::WA_TranslucentBackground);
    label->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    lineEdit = new QTextEdit();

    label->setFocusPolicy(Qt::FocusPolicy::ClickFocus);

//    stackedWidget->setGeometry(0, 0, 100, 30);

    label->installEventFilter(this);
    lineEdit->installEventFilter(this);

    stackedWidget->addWidget(label);
    stackedWidget->addWidget(lineEdit);

    stackedWidget->setCurrentWidget(label);

    hBoxLayout = new QHBoxLayout();
    hBoxLayout->setMargin(0);
    hBoxLayout->addWidget(stackedWidget);

    vBoxLayout = new QVBoxLayout();
    vBoxLayout->setMargin(3);

    vBoxLayout->addLayout(hBoxLayout);
    setLayout(vBoxLayout);
}
bool Dosth::eventFilter(QObject * obj, QEvent * evt) {
    if (obj == label)
    {
        if (evt->type() == QEvent::MouseButtonDblClick)
        {
            lineEdit->setText(label->text());
            stackedWidget->setCurrentIndex(1);
            //ui.lineEdit->setFocus();
        }
    }
    else if (obj == lineEdit)
    {
        if (evt->type() == QEvent::KeyPress)
        {
            QKeyEvent* keyevt = static_cast<QKeyEvent*>(evt);
            if ((keyevt->key() == Qt::Key_Return) ||
                (keyevt->key() == Qt::Key_Escape) ||
                (keyevt->key() == Qt::Key_Enter))
            {
                label->setText(lineEdit->toPlainText());
                stackedWidget->setCurrentIndex(0);
            }
        }
        else if (evt->type() == QEvent::FocusOut)
        {
            label->setText(lineEdit->toPlainText());
            stackedWidget->setCurrentIndex(0);
        }
    }

    return QWidget::eventFilter(obj, evt);
}
