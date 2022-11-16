#include <applicationHeader.h>
#include <QTimer>
#include <otherHeader.h>


/*
 * 计时器超时处理
*/
void UpperMachine::handleTimeout()
{
    if (playStatus == PlayStatus::PLAY) {
        qDebug()<<"示教启动，当前索引："  << playIndex;
        ui->tableWidget->setFocus();
        //        选中当前行
        ui->tableWidget->setCurrentCell(playIndex,QItemSelectionModel::Select);
        qDebug() << "当前行：" << ui->tableWidget->currentItem();
        //        发送指令
        QByteArray command = QString(strAddLine(readItems(playIndex))).toUtf8();
        //        qDebug() << "恢复首位：" << command;
        upperSerialPort.write(command);
        qDebug() << command;
        //    QMessageBox::about(this,"恢复首位","命令：" + command + "发送成功！");
        playIndex ++;
        if (playIndex >= actionCount) {
            playIndex = 0;
        }
    }
}
