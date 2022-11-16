#include <applicationHeader.h>
#include <serialHeader.h>
#include <otherHeader.h>



/*获取当前位置*/
void UpperMachine::readCurrentLocation()
{
    if (upperSerial.getL_isOpen()) {
        //    清空缓存
        //    tempBuffer.clear();
        arrayBuffer.clear();
        //    1、设置当前指令为读取当前坐标
        robotAction = RobotAction::DOWN;
        qDebug() << "++++++++++++++++++++++++++++++++++++++";
        qDebug() << "执行当前指令：" << UpperMachine::robotAction;
        //    2、判断串口设备是否可读写
        if (upperSerial.getL_isOpen())
        {
            try{
                //            3、打开串口元对象所指向的串口设备
                //            upperSerialPort.open(QIODevice::ReadWrite);
                //            upperSerial.setL_isOpen(upperSerialPort.isOpen());
                try
                {
                    //                4、发送指定指令
                    upperSerialPort.write(QString(strAddLine("DOWN")).toUtf8());
                    //                upperSerialPort.write("DOWN\n");
                    qDebug() << "UTF8发送:" << strAddLine("DOWN").toUtf8();
                }
                catch (exception ex_write)
                {
                    QMessageBox::critical(this, "发送指令异常",  ex_write.what());
                }
            }
            catch (exception ex_open)
            {
                QMessageBox::critical(this, "串口设备异常", ex_open.what());
            }
        }
        else
        {
            QMessageBox::warning(this,"获取位置","串口不可读写，请重新打开串口或更换串口号");
            return;
        }

    }
    else {
        QMessageBox::warning(this,"获取位置","当前未连接，请进行设备连接！");
    }
}


/*
 * 关闭当前串口设备
*/
void UpperMachine :: closeSerialDevice()
{
    if(upperSerial.getL_isOpen() == 1){
        upperSerialPort.close();
        upperSerialPort.setPortName("");
        upperSerialPort.setBaudRate(QSerialPort::UnknownBaud);
        upperSerialPort.setDataBits(QSerialPort::UnknownDataBits);
        upperSerialPort.setStopBits(QSerialPort::UnknownStopBits);
        upperSerialPort.setFlowControl(QSerialPort::UnknownFlowControl);
        upperSerialPort.setParity(QSerialPort::UnknownParity);

        upperSerial.setL_c_protName("");
        upperSerial.setDeviceName("");

        ui->label_deviceName->setStyleSheet("color:red;");
        ui->label_deviceName->setText("设备已关闭");
        ui->label_connectInfo->setStyleSheet("color:red;");
        ui->label_connectInfo->setText("请进行连接");
        ui->label_StatusInfo->setStyleSheet("color:red;");
        ui->label_StatusInfo->setText("无法获取状态");

        ui->textEdit_BArmObtain->setText("");
        ui->textEdit_ClowObtain->setText("");
        ui->textEdit_SArmObtain->setText("");
        ui->textEdit_RevolvingStageObtain->setText("");

        arrayBuffer.clear();
        tempBuffer.clear();

        upperSerial.setL_isOpen(0);
        upperSerial.setWriteSuccess(0);

        QMessageBox::about(this,"关闭串口","串口连接已关闭");
    }
    else {
        QMessageBox::information(this,"关闭串口","当前未连接，请进行设备连接！");
    }
}


/*
 * 切换操纵状态
*/
void UpperMachine :: switchSteerStatus()
{
    if (upperSerial.getL_isOpen()) {
        //    切换状态
        robotAction = RobotAction::UP;
        //    写入切换指令
        upperSerialPort.write(QString(strAddLine("UP")).toUtf8());
    }
    else {
        QMessageBox::warning(this,"切换状态","当前未连接，请进行设备连接！");
    }
}

