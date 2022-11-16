#include <applicationHeader.h>
#include <serialHeader.h>
#include <otherHeader.h>
#include <QFile>


/*
 * 检查软限位
*/
void UpperMachine::checkSoftLimit(int steerNum)
{
    if(mechanicalArm.getStartCheck()){
        //            聚焦更改文本框背景颜色
        //    QPalette in = QPalette(),out = QPalette();
        //    in.setColor(QPalette::Base,Qt::green);
        //    out.setColor(QPalette::Base,Qt::white);
        switch (steerNum) {
        case 1:
            //            爪头最小软限位
            checkSoftLimit_Clow(1);
            break;
        case 2:
            //            爪头最大软限位
            checkSoftLimit_Clow(2);
            break;
        case 3:
            //            小臂最小软限位
            checkSoftLimit_SArm(1);
            break;
        case 4:
            //            小臂最大软限位
            checkSoftLimit_SArm(2);
            break;
        case 5:
            //            大臂最小软限位
            checkSoftLimit_BArm(1);
            break;
        case 6:
            //            大臂最大软限位
            checkSoftLimit_BArm(2);
            break;
        case 7:
            //            转台最小软限位
            checkSoftLimit_RStage(1);
            break;
        case 8:
            //            转台最大软限位
            checkSoftLimit_RStage(2);
            break;
        default:
            currentsoftlimitSettings();
            break;
        }
    }
}


/*
 * 软限位读取
*/
void UpperMachine :: loadSoftLitmit()
{
    QStringList infoList;
    QFile file("./softlimit.txt");
    try {
        //        1、打开文件读写权限
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        //        2、文件流指向文本输出流
        QTextStream txtInput(&file);
        int i = 0;
        //        3、指向最后一个指针位置
        while (!txtInput.atEnd())
        {
            //            4、读取数据
            infoList.append(txtInput.readLine());
            QMessageBox::about(this,"文本流读取","\r开始文件写入 \n第 " +QString::number(i) +" 行："+infoList[i]);
            i++;
        }

        ui->textEdit_ClowMin->setText(infoList[0].split("=")[1].split(";")[0]);
        ui->textEdit_ClowMax->setText(infoList[1].split("=")[1].split(";")[0]);
        ui->textEdit_SArmMin->setText(infoList[2].split("=")[1].split(";")[0]);
        ui->textEdit_SArmMax->setText(infoList[3].split("=")[1].split(";")[0]);
        ui->textEdit_BArmMin->setText(infoList[4].split("=")[1].split(";")[0]);
        ui->textEdit_BArmMax->setText(infoList[5].split("=")[1].split(";")[0]);
        ui->textEdit_RStageMin->setText(infoList[6].split("=")[1].split(";")[0]);
        ui->textEdit_RStageMax->setText(infoList[7].split("=")[1].split(";")[0]);
        //    ui->textEdit_Sleep->setText( info[8].split('=')[1]);
    } catch (exception &ex_fileLoad) {
        QMessageBox::critical(this,"文件警告","文件打开或写入失败，原因："+QString(ex_fileLoad.what()));
    }
}

/*
 * 软限位写入
*/
void UpperMachine :: saveSoftLimit(void)
{
    QString txt = ("ClowMin=" + ui->textEdit_ClowMin->toPlainText() + ";\n" +
                   "ClowMax=" + ui->textEdit_ClowMax->toPlainText() + ";\n" +
                   "SmallArmMin=" + ui->textEdit_SArmMin->toPlainText() + ";\n" +
                   "SmallArmMax=" + ui->textEdit_SArmMax->toPlainText() + ";\n" +
                   "BigArmMin=" + ui->textEdit_BArmMin->toPlainText() + ";\n" +
                   "BigArmMax=" + ui->textEdit_BArmMax->toPlainText() + ";\n" +
                   "RevolvingStageMin=" + ui->textEdit_RStageMin->toPlainText() + ";\n" +
                   "RevolvingStageMax=" + ui->textEdit_RStageMax->toPlainText()  + ";");
    //            + "\r\n" +
    //            "Sleep=" + ui->textEdit_Sleep->toPlainText();
    QFile file("./softlimit.txt");
    try {
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        file.write(txt.toUtf8());
        QMessageBox::about(this,"文件打开成功","文件写入成功，内容：\n"+txt);
    } catch (exception &ex_fileWrite) {
        QMessageBox::about(this,"文件打开失败","文件写入失败，原因：\n"+QString(ex_fileWrite.what()));
    }
}

/*
 * 复位
*/
void UpperMachine :: resetLocation()
{
    if (upperSerial.getL_isOpen()) {

        QByteArray command = QString(strAddLine("LEFT")).toUtf8();
        robotAction = RobotAction::RESET;
        //    try {
        upperSerialPort.write(command);
        qDebug() << "发送命令：" << command;
    }
    else {
        QMessageBox::warning(this,"切换状态","当前未连接，请进行设备连接！");
    }

    //        sleep_MS(50);
    //        if (upperSerial.getWriteSuccess() == true) {
    //            QMessageBox::about(this,"复位命令","复位成功！");
    //        }else {
    //            throw exception();
    //        }
    //    } catch (exception &ex_reset) {
    //        QMessageBox::critical(this,"复位命令","复位失败！"+ QString(ex_reset.what()));
    //        upperSerialPort.write(QString(strAddLine("UP")).toUtf8());
    //    }
}

/*
 * 手爪软限位
 */
void UpperMachine :: checkSoftLimit_Clow(int i){
    if(i == 1){
        //1、属于软限位默认范围
        //            1.1、设置最小值 >= 默认最小值
        if (ui->textEdit_ClowMin->toPlainText().toInt() < mechanicalArm.getClowMin()) {
            QMessageBox::critical(this,"手爪警告","手爪最小软限位  不能小于  默认最小软限位：须 ≥ " + QString::number(mechanicalArm.getClowMin()) + "°");
            i=0;
        }
        //            1.2、设置最小值 <= 设置最大值
        else if (ui->textEdit_ClowMin->toPlainText().toInt() > ui->textEdit_ClowMax->toPlainText().toInt() ) {
            QMessageBox::critical(this,"手爪警告","手爪最小软限位  不能大于  设置的最大软限位：须 ≤ " + QString::number(ui->textEdit_ClowMax->toPlainText().toInt()) + "°");
            i = 0;
        }
        if(i == 0)
            //        设置默认软限位
            ui->textEdit_ClowMin->setText(QString::number(mechanicalArm.getClowMin()));
        else
            mechanicalArm.setCurrent_CMin(QString::number(mechanicalArm.getClowMin()));
    }
    else{
        //            1.3、设置最大值 <= 默认最大值
        if (ui->textEdit_ClowMax->toPlainText().toInt() > mechanicalArm.getClowMax()) {
            QMessageBox::critical(this,"手爪警告","手爪最大软限位  不能大于  默认最大软限位：须 ≤ " + QString::number(mechanicalArm.getClowMax()) + "°");
            i=0;
        }
        //            1.4、设置最大值 >= 设置最小值
        else if (ui->textEdit_ClowMax->toPlainText().toInt() < ui->textEdit_ClowMin->toPlainText().toInt() ) {
            QMessageBox::critical(this,"手爪警告","手爪最大软限位  不能小于  设置的最小软限位：须 ≥ " + QString::number(ui->textEdit_ClowMin->toPlainText().toInt()) + "°");
            i=0;
        }
        if(i == 0)
            //        设置默认软限位
            ui->textEdit_ClowMax->setText(QString::number(mechanicalArm.getClowMax()));
        else
            mechanicalArm.setCurrent_CMax(QString::number(mechanicalArm.getClowMax()));
    }
}

/*
 *  小臂软限位
*/
void UpperMachine :: checkSoftLimit_SArm(int i){
    if(i == 1){
        //1、属于软限位默认范围内
        //            1.1、设置最小值 >= 默认最小值
        if (ui->textEdit_SArmMin->toPlainText().toInt() < mechanicalArm.getSArmMin()) {
            QMessageBox::critical(this," 小臂警告"," 小臂最小软限位  不能小于  默认最小软限位：须 ≥ " + QString::number(mechanicalArm.getSArmMin()) + "°");
            i=0;
        }
        //            1.2、设置最小值 <= 设置最大值
        else if (ui->textEdit_SArmMin->toPlainText().toInt() > ui->textEdit_SArmMax->toPlainText().toInt() ) {
            QMessageBox::critical(this," 小臂警告"," 小臂最小软限位  不能大于  设置的最大软限位：须 ≤ " + QString::number(ui->textEdit_SArmMax->toPlainText().toInt()) + "°");
            i=0;
        }
        if(i == 0)
            //        设置默认软限位
            ui->textEdit_SArmMin->setText(QString::number(mechanicalArm.getSArmMin()));
        else
            mechanicalArm.setCurrent_SAMin(QString::number(mechanicalArm.getSArmMin()));
    }
    else{
        //            1.3、设置最大值 <= 默认最大值
        if (ui->textEdit_SArmMax->toPlainText().toInt() > mechanicalArm.getSArmMax()) {
            QMessageBox::critical(this," 小臂警告"," 小臂最大软限位  不能大于  默认最大软限位：须 ≤ " + QString::number(mechanicalArm.getSArmMax()) + "°");
            i=0;
        }
        //            1.4、设置最大值 >= 设置最小值
        else if (ui->textEdit_SArmMax->toPlainText().toInt() < ui->textEdit_SArmMin->toPlainText().toInt() ) {
            QMessageBox::critical(this," 小臂警告"," 小臂最大软限位  不能小于  设置的最小软限位：须 ≥ " + QString::number(ui->textEdit_SArmMin->toPlainText().toInt()) + "°");
            i=0;
        }
        if(i == 0)
            //        设置默认软限位
            ui->textEdit_SArmMax->setText(QString::number(mechanicalArm.getSArmMax()));
        else
            mechanicalArm.setCurrent_SAMax(QString::number(mechanicalArm.getSArmMax()));
    }
}

/*
 * 大臂软限位
*/
void UpperMachine :: checkSoftLimit_BArm(int i){
    if(i == 1){
        //1、属于软限位默认范围内
        //            1.1、设置最小值 >= 默认最小值
        if (ui->textEdit_BArmMin->toPlainText().toInt() < mechanicalArm.getBArmMin()) {
            QMessageBox::critical(this,"大臂警告","大臂最小软限位  不能小于  默认最小软限位：须 ≥ " + QString::number(mechanicalArm.getBArmMin()) + "°");
            i=0;
        }
        //            1.2、设置最小值 <= 设置最大值
        else if (ui->textEdit_BArmMin->toPlainText().toInt() > ui->textEdit_BArmMax->toPlainText().toInt() ) {
            QMessageBox::critical(this,"大臂警告","大臂最小软限位  不能大于  设置的最大软限位：须 ≤ " + QString::number(ui->textEdit_BArmMax->toPlainText().toInt()) + "°");
            i=0;
        }
        if(i == 0)
            //        设置默认软限位
            ui->textEdit_BArmMin->setText(QString::number(mechanicalArm.getBArmMin()));
        else
            mechanicalArm.setCurrent_BAMin(QString::number(mechanicalArm.getBArmMin()));
    }
    else{
        //            1.3、设置最大值 <= 默认最大值
        if (ui->textEdit_BArmMax->toPlainText().toInt() > mechanicalArm.getBArmMax()) {
            QMessageBox::critical(this,"大臂警告","大臂最大软限位  不能大于  默认最大软限位：须 ≤ " + QString::number(mechanicalArm.getBArmMax()) + "°");
            i=0;
        }
        //            1.4、设置最大值 >= 设置最小值
        else if (ui->textEdit_BArmMax->toPlainText().toInt() < ui->textEdit_BArmMin->toPlainText().toInt() ) {
            QMessageBox::critical(this,"大臂警告","大臂最大软限位  不能小于  设置的最小软限位：须 ≥ " + QString::number(ui->textEdit_BArmMin->toPlainText().toInt()) + "°");
            i=0;
        }
        if(i == 0)
            //        设置默认软限位
            ui->textEdit_BArmMax->setText(QString::number(mechanicalArm.getBArmMax()));
        else
            mechanicalArm.setCurrent_BAMax(QString::number(mechanicalArm.getBArmMax()));
    }
}


/*
     * 转台软限位
     */
void UpperMachine :: checkSoftLimit_RStage(int i){
    if(i == 1){
        //1、属于软限位默认范围内
        //            1.1、设置最小值 >= 默认最小值
        if (ui->textEdit_RStageMin->toPlainText().toInt() < mechanicalArm.getRStageMin()) {
            QMessageBox::critical(this,"转台警告","转台最小软限位  不能小于  默认最小软限位：须 ≥ " + QString::number(mechanicalArm.getRStageMin()) + "°");
            i=0;
        }
        //            1.2、设置最小值 <= 设置最大值
        else if (ui->textEdit_RStageMin->toPlainText().toInt() > ui->textEdit_RStageMax->toPlainText().toInt() ) {
            QMessageBox::critical(this,"转台警告","转台最小软限位  不能大于  设置的最大软限位：须 ≤ " + QString::number(ui->textEdit_RStageMax->toPlainText().toInt()) + "°");
            i=0;
        }
        if(i == 0)
            //        设置默认软限位
            ui->textEdit_RStageMin->setText(QString::number(mechanicalArm.getRStageMin()));
        else
            mechanicalArm.setCurrent_RSMin(QString::number(mechanicalArm.getRStageMin()));
    }
    else{
        //            1.3、设置最大值 <= 默认最大值
        if (ui->textEdit_RStageMax->toPlainText().toInt() > mechanicalArm.getRStageMax()) {
            QMessageBox::critical(this,"转台警告","转台最大软限位  不能大于  默认最大软限位：须 ≤ " + QString::number(mechanicalArm.getRStageMax()) + "°");
            i=0;
        }
        //            1.4、设置最大值 >= 设置最小值
        else if (ui->textEdit_RStageMax->toPlainText().toInt() < ui->textEdit_RStageMin->toPlainText().toInt() ) {
            QMessageBox::critical(this,"转台警告","转台最大软限位  不能小于  设置的最小软限位：须 ≥ " + QString::number(ui->textEdit_RStageMin->toPlainText().toInt()) + "°");
            i=0;
        }
        if(i == 0)
            //        设置默认软限位
            ui->textEdit_RStageMax->setText(QString::number(mechanicalArm.getRStageMax()));
        else
            mechanicalArm.setCurrent_RSMax(QString::number(mechanicalArm.getRStageMax()));
    }
}


/*
 * 当前软限位
*/
void UpperMachine :: currentsoftlimitSettings()
{
    mechanicalArm.setCurrent_CMin(ui->textEdit_ClowMin->toPlainText());
    mechanicalArm.setCurrent_CMax(ui->textEdit_ClowMax->toPlainText());

    mechanicalArm.setCurrent_SAMin(ui->textEdit_SArmMin->toPlainText());
    mechanicalArm.setCurrent_SAMax(ui->textEdit_SArmMax->toPlainText());

    mechanicalArm.setCurrent_BAMin(ui->textEdit_BArmMin->toPlainText());
    mechanicalArm.setCurrent_BAMax(ui->textEdit_BArmMax->toPlainText());

    mechanicalArm.setCurrent_RSMin(ui->textEdit_RStageMin->toPlainText());
    mechanicalArm.setCurrent_RSMax(ui->textEdit_RStageMax->toPlainText());
}

