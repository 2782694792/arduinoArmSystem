#include <QCoreApplication>
#include <QString>
#include <QTime>
#include <QDebug>
#include <QMessageBox>

/*
 * 添加换行
*/
QString strAddLine(QString str)
{
    return str+"\n";
}


/*
 * 去除末尾
*/
QString strDelLast(QByteArray command)
{
    return command.replace("\r\n","");
}



/*
 * 自定义延时
*/
void sleep_MS(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 50);
}



/*
 * 查询状态编码
 */
int findModelNum(QByteArray arrayBuffer)
{
    QString command = QString(strDelLast(arrayBuffer));
    QStringList arrayList = command.split("式");
    return arrayList[1].left(1).toInt();
}



/*
 * 查询状态信息
*/
int findModelInfo(QByteArray arrayBuffer)
{
    qDebug() << "当前操纵状态：" << QString(arrayBuffer);
    QString command = QString(strDelLast(arrayBuffer));
    QStringList arrayList = command.split("模式");
    QMessageBox::StandardButton btn = QMessageBox::question(NULL,"操纵状态",arrayList[1].right(6)+"，继续切换？",QMessageBox::Yes|QMessageBox::No);
    if (btn == QMessageBox::Yes) {
        return 1;
    }
    else
    {
        return 0;
    }
}


