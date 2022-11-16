#include <applicationHeader.h>
#include <serialHeader.h>

#include <otherHeader.h>

/*
 * 发送位置
*/
void UpperMachine :: sendLocation()
{
    if (upperSerial.getL_isOpen()) {
        currentsoftlimitSettings();

        QString sendCommand;
        if (ui->textEdit_SendClow->toPlainText().trimmed().size() <= 0
                || ui->textEdit_SendClow->toPlainText().toInt() < mechanicalArm.getCurrent_CMin().toInt() || ui->textEdit_SendClow->toPlainText().toInt() > mechanicalArm.getCurrent_CMax().toInt()) {
            QMessageBox::critical(this,"发送位置","爪头角度超出当前软限位(" + mechanicalArm.getCurrent_CMin() + "-" + mechanicalArm.getCurrent_CMax() + ")，请重新设置！");
            ui->textEdit_SendClow->setText(mechanicalArm.getClowLocation());
            //        ui->textEdit_SendClow->setText("45");
        }
        else if (ui->textEdit_SendSArm->toPlainText().trimmed().size() <= 0
                 || ui->textEdit_SendSArm->toPlainText().toInt() < mechanicalArm.getCurrent_SAMin().toInt() || ui->textEdit_SendSArm->toPlainText().toInt() > mechanicalArm.getCurrent_SAMax().toInt()) {
            QMessageBox::critical(this,"发送位置","小臂角度超出当前软限位(" + mechanicalArm.getCurrent_SAMin() + "-" +  mechanicalArm.getCurrent_SAMax() + ")，请重新设置！");
            ui->textEdit_SendSArm->setText(mechanicalArm.getSmallArmLocation());
            //        ui->textEdit_SendSArm->setText("45");
        }
        else if (ui->textEdit_SendBArm->toPlainText().trimmed().size() <= 0
                 || ui->textEdit_SendBArm->toPlainText().toInt() < mechanicalArm.getCurrent_BAMin().toInt() || ui->textEdit_SendBArm->toPlainText().toInt() > mechanicalArm.getCurrent_BAMax().toInt()) {
            QMessageBox::critical(this,"发送位置","大臂角度超出当前软限位(" + mechanicalArm.getCurrent_BAMin() + "-" +  mechanicalArm.getCurrent_BAMax() + ")，请重新设置！");
            ui->textEdit_SendBArm->setText(mechanicalArm.getBigArmLocation());
            //        ui->textEdit_SendBArm->setText("45");
        }
        else if (ui->textEdit_SendRStage->toPlainText().trimmed().size() <= 0
                 || ui->textEdit_SendRStage->toPlainText().toInt() < mechanicalArm.getCurrent_RSMin().toInt()  || ui->textEdit_SendRStage->toPlainText().toInt() > mechanicalArm.getCurrent_RSMax().toInt() ) {
            QMessageBox::critical(this,"发送位置","转台角度超出当前软限位(" + mechanicalArm.getCurrent_RSMin() + "-" +  mechanicalArm.getCurrent_RSMax() + ")，请重新设置！");
            ui->textEdit_SendRStage->setText(mechanicalArm.getRevolvingStageLocation());
            //        ui->textEdit_SendRStage->setText("45");
        }
        else{
            QString clowSend = ui->textEdit_SendClow->toPlainText();
            QString sArmSend = ui->textEdit_SendSArm->toPlainText();
            QString bArmSend = ui->textEdit_SendBArm->toPlainText();
            QString rStageSend = ui->textEdit_SendRStage->toPlainText();
            sendCommand
                    .append("a" + QString("%1").arg(clowSend, 3, QLatin1Char('0')))
                    .append("b" + QString("%1").arg(sArmSend, 3, QLatin1Char('0')))
                    .append("c" + QString("%1").arg(bArmSend, 3, QLatin1Char('0')))
                    .append("d" + QString("%1").arg(rStageSend, 3, QLatin1Char('0')));
            QByteArray command = QString(strAddLine(sendCommand)).toUtf8();
            qDebug() << "发送命令：" << command;
            upperSerialPort.write(command);
            QMessageBox::about(this,"发送命令","命令：" + command + "发送成功！");
        }

        }
        else {
            QMessageBox::warning(this,"切换状态","当前未连接，请进行设备连接！");
        }
}
