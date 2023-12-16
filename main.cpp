#include "widget.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    Widget w;
    qDebug() << "加法";
    w.show();
    return a.exec(); //应用程序循环回进行消息监听
}
