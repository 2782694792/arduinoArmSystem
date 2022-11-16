#include <applicationHeader.h>
#include <serialHeader.h>
#include <otherHeader.h>


/*
 * 设备连接--获取全称
*/
void UpperMachine::connectUM()
{
    if (upperSerial.getL_isOpen() == 1) {
        QMessageBox::about(this,"打开串口","当前串口已经打开,设备："+upperSerial.getDeviceName());
    }
    else{
        //获取设备全称，获取则说明连接成功   Arduino Uno (COM4)
        upperSerial.setDeviceName(GetDeviceFullName());
        /*Console.WriteLine("设备信息" + deviceFullName);*/
        if (upperSerial.getDeviceName().contains(upperSerial.getL_deviceFlag()))
        {
            try {
                upperSerialPort.setPortName(QString(upperSerial.getL_c_protName()));
                upperSerialPort.setBaudRate(upperSerial.getL_c_baudRate());
                //                upperSerialPort.setDataBits(upperSerial.getL_c_dataBits());
                //                upperSerialPort.setStopBits(upperSerial.getL_c_stopBits());
                //                upperSerialPort.setParity(upperSerial.getL_c_parity());
                upperSerialPort.setDataBits(QSerialPort::Data8);
                upperSerialPort.setStopBits(QSerialPort::OneStop);
                upperSerialPort.setParity(QSerialPort::NoParity);
                upperSerialPort.setFlowControl(QSerialPort::NoFlowControl);
                connect(&upperSerialPort, &QSerialPort::readyRead, this, &UpperMachine::serialPort_ReadAvailable);
                //            do {
                upperSerialPort.open(QIODevice::ReadWrite);
                //            } while ( upperSerialPort.open(QIODevice::ReadWrite) != true);

                //                QMessageBox *btn2 = new QMessageBox(QMessageBox::Information,QString("打开串口中"),QString("串口打开中，请稍后......"));
                //            sleep_MS(10);
                //            btn2->exec();
                QMessageBox::about(this,"打开串口","串口打开成功");
                upperSerial.setL_isOpen(1);
                upperSerial.setL_isOpen(upperSerialPort.isOpen());
                ui->label_deviceName->setText(upperSerial.getDeviceName());
                ui->label_connectInfo->setStyleSheet("color:green;");
                ui->label_connectInfo->setText("连接成功");
                ui->label_StatusInfo->setStyleSheet("color:black;");
                ui->label_StatusInfo->setText("默认状态");
                qDebug() << upperSerial.getL_isOpen() << "\\" <<  upperSerialPort.portName()
                         << "\\" << upperSerialPort.baudRate() << "\\" << upperSerialPort.dataBits()
                         << "\\" << upperSerialPort.stopBits()
                         << "\\RW:" << upperSerialPort.open(QIODevice::ReadWrite);
                //                sp.DataReceived += Sp_DataReceived;
                //                sp.Open();
                //探测一次当前状态
                //切换响应状态
                //            robotAction = RobotAction::UP;
                //发送数据
                //sp.Write("UP\n");

            } catch (exception ex_rw) {
                qDebug() << "打开串口失败" << QString(ex_rw.what());
                ui->label_deviceName->setText("设备配置有误");
                ui->label_connectInfo->setStyleSheet("color:red;");
                ui->label_connectInfo->setText("打开设备失败！");
            }
        }
        else
        {
            qDebug() << "打开串口失败，不存在类似设备名称";
            ui->label_deviceName->setText("不存在类似设备名称");
            ui->label_connectInfo->setStyleSheet("color:red;");
            ui->label_connectInfo->setText("连接设备失败！");
        }
    }
}



/*
 * 读取接收数据
*/
void UpperMachine :: readAvailableInfo()
{
    //接收设备返回的命令
    QString command_Recept;
    try {
        QByteArray buffer;
        //        arrayBuffer.clear();
        //    1、读取缓冲字节
        if (upperSerialPort.bytesAvailable()) {
            //    串口收到的数据并非连续的，需要进行缓存在进行解析
            //    从串口接收缓冲区中读取所有数据
            buffer = upperSerialPort.readAll();
            qDebug() << "已接收：" << buffer;
        }
        //    2、将字节加入自定义接收输入缓冲区列
        //        tempBuffer.append(buffer);
        arrayBuffer.append(buffer);
        qDebug() << "已存入：" << arrayBuffer << "——" + QString::number(arrayBuffer.count(),10);

        //        2.1、接收数据完整，执行指令
        if (arrayBuffer.contains("\n"))
        {
            //    3、解析当前操纵指令
            switch (robotAction) {
            /*
             * 获取当前坐标
             */
            case RobotAction::DOWN:
                //最小软限位    a:0,b:45,c:40,d:0\n     总共18个字节数
                //                if (tempBuffer.count() >= 18)
                if (arrayBuffer.count() >= 18)
                {
                    //除去换行符
                    command_Recept = QString(strDelLast(arrayBuffer));
                    //清空缓存
                    arrayBuffer.clear();
                    //执行命令
                    doDOWN(command_Recept);
                    qDebug() << "操纵指令" << RobotAction::DOWN << "执行成功！";
                    qDebug() << "++++++++++++++++++++++++++++++++++++++";
                    upperSerial.setWriteSuccess(1);
                }else{
                    qDebug() << "返回数据长度过低，数据有误，请检查主控制器指令处理与设备安全状态！";
                    upperSerial.setWriteSuccess(0);
                }
                break;
                /*
              * 状态切换
              */
            case RobotAction::UP:
                if (arrayBuffer.count() == 27)
                {
                    int modelNum = findModelNum(arrayBuffer);
                    qDebug() << "状态编码：" << modelNum;
                    //                    isBlueLight = modelNum == 0? true:false;
                    int switchContinue = findModelInfo(arrayBuffer);
                    if (switchContinue == 1) {
                        arrayBuffer.clear();
                        //    切换状态
                        robotAction = RobotAction::UP;
                        //    写入切换指令
                        upperSerialPort.write(QString(strAddLine("UP")).toUtf8());
                    }
                    else {
                        QString info = QString(strDelLast(arrayBuffer)).split("模式")[1].right(4);
                        qDebug() << "切换后的状态：" << info;
                        arrayBuffer.clear();
                        ui->label_StatusInfo->setText(info);
                        QMessageBox::about(this,"切换命令","状态："  + info + "切换成功！");
                        upperSerial.setWriteSuccess(1);
                    }
                }
                else{
                    qDebug() << "获取信息有误！" << arrayBuffer;
                    upperSerial.setWriteSuccess(0);
                }
                break;
            case RobotAction::RESET:
                //                qDebug() << arrayBuffer.count() << isBlueLight;
                //                if (arrayBuffer.count() == 8 && isBlueLight == true)
                if (arrayBuffer.count() == 8 )
                {
                    qDebug() << "复位成功！";
                    QMessageBox::about(this,"复位命令","复位成功！");
                    arrayBuffer.clear();
                    upperSerial.setWriteSuccess(1);
                }
                else
                    QMessageBox::critical(this,"复位命令","复位失败！");
                upperSerial.setWriteSuccess(0);
                break;
            case RobotAction::ADD_ACTION:
                if (arrayBuffer.count() >= 18)
                {
                    //除去末尾符   \r\n
                    command_Recept = QString(strDelLast(arrayBuffer));
                    arrayBuffer.clear();
                    //                    执行命令，单单获取不进行坐标设置
                    //                    doDOWN(command_Recept);
                    addUMAction(command_Recept);
                }
                else {
                    upperSerial.setWriteSuccess(0);
                }
                break;
            default:
                //                tempBuffer.clear();
                //                arrayBuffer.clear();
                //                upperSerial.setWriteSuccess(false);
                break;
            }
        }
        else {
            qDebug() << "数据不完整（元数据以换行符号结束）";
        }
    } catch (exception &ex) {
        qDebug() << ex.what();
        QMessageBox::critical(this, "串口返回数据解析异常", QString(ex.what()));
    }
}



/*
 * 获取设备全称、查询可用串口
*/
QString UpperMachine :: GetDeviceFullName()
{
    upperSerialPort.reset();
    upperSerialPort.close();
    upperSerial.setL_isOpen(false);
    //        ui->textEdit_Receipt->append("查询可用串口中......");
    qDebug("查询可用串口中......");
    sleep_MS(50);
    int i = QSerialPortInfo::availablePorts().count() , j = i;
    //    通过QSerialPortInfo类进行遍历，查找可用串口设备
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QString infoMain = info.portName() + ":" + info.description();
        i--;
        QMessageBox::StandardButton btn;
        if (info.isBusy()) {
            QMessageBox::question(this, "可用串口提示", infoMain + "被占用！寻找下一串口？", QMessageBox::Yes|QMessageBox::No);
        }
        else{
            if (info.description().contains(upperSerial.getL_deviceFlag())) {
                btn = QMessageBox::information(this,"匹配信息","相似设备匹配到一台："+infoMain+"!\n匹配成功！",QMessageBox::Yes);
                upperSerial.setL_c_protName(info.portName());
                qDebug() << "相似设备匹配到一台：" << j - i << "、"  << infoMain;
                return info.description();
            }
            else {
                qDebug() << "未找到指定匹配串口设备: " << upperSerial.getL_deviceFlag();
                btn = QMessageBox::question(this,"未匹配到相似设备："+upperSerial.getL_deviceFlag()+"!\n匹配失败！", "串口"+ infoMain + "不匹配！继续查询?",QMessageBox::Yes|QMessageBox::No);
            }
        }
        if (btn == QMessageBox::Yes) {
            if (i != 0) {
                qDebug() <<  j - i << "、"  << infoMain;
                continue;
            }else{
                qDebug() <<  j - i << "、"  << infoMain;
                QMessageBox :: information(this,"搜索提示","结束可用串口设备搜索！",QMessageBox::Ok);
                break;
            }
        }else {
            QMessageBox :: information(this,"搜索提示","结束可用串口设备搜索！",QMessageBox::Ok);
            break;
        }
    }
    return "";
}



/*
 * 添加动作记录
*/
void UpperMachine :: addAction_Location(int add_row,int add_column)
{
    ui->tableWidget->setItem(add_row,add_column + 0,new QTableWidgetItem(mechanicalArm.getClowLocation()));
    ui->tableWidget->setItem(add_row,add_column + 1,new QTableWidgetItem(mechanicalArm.getSmallArmLocation()));
    ui->tableWidget->setItem(add_row,add_column + 2,new QTableWidgetItem(mechanicalArm.getBigArmLocation()));
    ui->tableWidget->setItem(add_row,add_column + 3,new QTableWidgetItem(mechanicalArm.getRevolvingStageLocation()));
    qDebug() << "添加成功！";
    upperSerial.setWriteSuccess(1);
    QMessageBox::about(this,"添加动作","动作: 添加成功！");
    actionCount ++;
}

