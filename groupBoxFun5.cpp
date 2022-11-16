#include <applicationHeader.h>
#include <otherHeader.h>
#include <QTimer>

/*
 * 添加动作
*/
void UpperMachine :: addAction()
{
    if (upperSerial.getL_isOpen()) {
        robotAction = RobotAction::ADD_ACTION;
        //    发送指定指令
        upperSerialPort.write(QString(strAddLine("DOWN")).toUtf8());
    }
    else {
        QMessageBox::warning(this,"添加动作","当前未连接，请进行设备连接！");
    }
}

/*
 * 添加机械臂动作
*/
void UpperMachine::addUMAction(QString command)
{
    setLocation(command);
    QString msg = "";
    //判断当前位置是否安全
    if (mechanicalArm.getClowLocation().toInt() < mechanicalArm.getCurrent_CMin().toInt() || mechanicalArm.getClowLocation().toInt() > mechanicalArm.getCurrent_CMax().toInt()) {
        msg += "爪头超出设置范围,";
        //        qDebug() << mechanicalArm.getClowLocation().toInt() << "_" << mechanicalArm.getCurrent_CMin() << "_" << mechanicalArm.getCurrent_CMax();
    }
    if (mechanicalArm.getSmallArmLocation().toInt() < mechanicalArm.getCurrent_SAMin().toInt() || mechanicalArm.getSmallArmLocation().toInt() > mechanicalArm.getCurrent_SAMax().toInt()) {
        msg += "小臂超出设置范围,";
    }
    if (mechanicalArm.getBigArmLocation().toInt() < mechanicalArm.getCurrent_BAMin().toInt() || mechanicalArm.getBigArmLocation().toInt() > mechanicalArm.getCurrent_BAMax().toInt()) {
        msg += "大臂超出设置范围,";
    }
    if (mechanicalArm.getRevolvingStageLocation().toInt() < mechanicalArm.getCurrent_RSMin().toInt() || mechanicalArm.getRevolvingStageLocation().toInt() > mechanicalArm.getCurrent_RSMax().toInt()) {
        msg += "转台超出设置范围,";
    }

    if (msg != "")
    {
        QMessageBox::critical(this,"添加动作",msg + "添加失败！");
        return;
    }

    //    ListViewItem lvi = new ListViewItem(new string[] {
    //        actionIndex.ToString(),
    //        robot.ClowLocation.ToString(),
    //        robot.SmallArmLocation.ToString(),
    //        robot.BigArmLocation.ToString(),
    //        robot.RevolvingStageLocation.ToString()
    //    });
    //        qDebug() << "：：" << ui->tableWidget->item() << "——" << ui->tableWidget->columnCount();

    int add_row = 0,add_column = 0;
    int add_index = -1;
    QModelIndex current_index = ui->tableWidget->currentIndex();
    qDebug() << "添加前：" << current_index.row();

    //    以首个单元格作为标记
    if ( ui->tableWidget->item(0,0) == NULL )
    {
        addAction_Location(add_row,add_column);
    }
    else
    {
        if(NextItemEmpty(ui->tableWidget,current_index.row(),current_index.column())
                && !CurrentItemEmpty(ui->tableWidget,current_index.row(),current_index.column())){
            qDebug() << "添加前：" << current_index.row();
            add_index = current_index.row()+1;
            addAction_Location(add_index,add_column);
            //            ui->tableWidget->select
            //            tableWidget->setCurrentItem(NULL);
            //                for(int j = 0;j < 4;j++){
            //                    ui->tableWidget->item(current_index.row(), j)->setFlags(Qt::NoItemFlags);
            //                }
            //            key_SerialWrite("DOWN");
            //            ui->tableWidget->;
            //            qDebug() <<  ui->tableWidget->currentIndex();
            //            取消选中行
            ui->tableWidget->clearSelection();
            //                更换选中行，确保只可添加一次
        }
        else{
            QMessageBox::critical(this,"添加动作","不可空行或重复添加，请重新选择添加的位置");
            return;
        }
    }
    //        int index = lstAction.SelectedItems[0].Index;
    //        lstAction.Items.Insert(index + 1, lvi);
    //        lstAction.SelectedItems[0].Selected = false;
}

/*
 * 删除动作
*/
void UpperMachine :: deleteAction()
{
    if (ui->tableWidget->selectedItems().count() == 0 ) {
        QMessageBox::information(this,"删除动作","请先选中行再进行删除操作！");
        qDebug() << "删除失败，选中行：" << ui->tableWidget->currentRow();
        return;
    }
    else
    {
        //        qDebug() << "删除前：" << ui->tableWidget->currentRow();
        //        ui->tableWidget->removeRow(ui->tableWidget->currentRow());
        if(selectRow())
        {
            QMessageBox::StandardButton btn = QMessageBox::question(this,"删除动作","确认删除当前选中行：第"+ QString::number(ui->tableWidget->currentRow()+1) +"行的动作记录",QMessageBox::Yes|QMessageBox::No);
            if (btn == QMessageBox::Yes) {
                //  1.1 重新排列
                //                1、获取当前索引
                //                2、取往下行数据内容
                //                3、取往上行数据内容
                //                4、合并数据内容
                //                5、清空所有数据
                //                6、重新赋值
                //  1.2 删除行
                ui->tableWidget->removeRow(ui->tableWidget->currentRow());
                qDebug() << "删除动作记录：" << ui->tableWidget->currentRow();
                //  1.2.1 补充行数
                int row = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(row);
            }
            //            else
            //            {
            //                return;
            //            }
        }
        else{
            QMessageBox::critical(this,"删除动作","请先选中非空行，再进行删除操作！");
            return;
        }
    }
}

/*
 * 清空动作
*/
void UpperMachine :: clearAction()
{
    QMessageBox::StandardButton btn = QMessageBox::question(this,"清空轨迹","确认清空当前所有动作记录",QMessageBox::Yes|QMessageBox::No);
    if (btn == QMessageBox::Yes) {
        ui->tableWidget->clearContents();
    }
}

/*
 * 恢复首位
*/
void UpperMachine :: firstAction()
{
    QByteArray command = QString(strAddLine(readFirstAction())).toUtf8();
    qDebug() << "恢复首位：" << command;
    upperSerialPort.write(command);
    QMessageBox::about(this,"恢复首位","恢复首位：" + command + "成功！");
}

/*
 * 示教启动
*/
void UpperMachine::playActions()
{
    if(!CurrentItemEmpty(ui->tableWidget,0,0))
    {
        playStatus = PlayStatus::PLAY;

        //    m_pTimer->start(1000);      // 1秒
        m_pTimer->start(ui->textEdit_timeOut->toPlainText().toInt());
    }
    else {
        QMessageBox::critical(this,"示教运行","数据为空，无法获取数据进行示教！");
        return;
    }
}

/*
 * 示教暂停
*/
void UpperMachine::pauseActions()
{
    if(!CurrentItemEmpty(ui->tableWidget,0,0))
    {
        if(m_pTimer->isActive() && playStatus == PlayStatus :: PLAY){
            playStatus = PlayStatus::PAUSE;
            m_pTimer->stop();
            ui->tableWidget->setFocus();
            //        选中当前行
            ui->tableWidget->setCurrentCell(playIndex,QItemSelectionModel::Select);
        }
        else {
            QMessageBox::information(this,"示教暂停","当前不存在示教活动");
        }
    }
    else {
        QMessageBox::critical(this,"示教运行","数据为空，无法获取数据进行示教！");
        return ;
    }
}

/*
 * 示教停止
*/
void UpperMachine::stopActions()
{
    if(!CurrentItemEmpty(ui->tableWidget,0,0))
    {
        if(m_pTimer->isActive() && playStatus == PlayStatus :: PLAY){
            playIndex = 0;
            playStatus = PlayStatus::STOP;
            m_pTimer->stop();
            ui->tableWidget->setFocus();
            //        选中当前行
            ui->tableWidget->setCurrentCell(playIndex,QItemSelectionModel::Select);
        }
        else {
            QMessageBox::information(this,"示教停止","当前不存在示教活动");
        }
    }
    else {
        QMessageBox::critical(this,"示教运行","数据为空，无法获取数据进行示教！");
        return ;
    }
}

/*
 * 单步运行
*/
void UpperMachine::stepActions()
{
    if(!CurrentItemEmpty(ui->tableWidget,0,0))
    {
        if(!m_pTimer->isActive() && (playStatus == PlayStatus :: PAUSE || playStatus == PlayStatus::STOP)){
            if (playIndex >= actionCount) {
                playIndex = 0;
            }
            else {
                ui->tableWidget->setFocus();
                //        选中当前行
                ui->tableWidget->setCurrentCell(playIndex,QItemSelectionModel::Select);
                QByteArray command = QString(strAddLine(readItems(playIndex))).toUtf8();
                qDebug()<<"单步运行，当前索引："  << playIndex;
                upperSerialPort.write(command);
                playIndex ++;
                //            超出范围跳转并停止
                //            m_pTimer->stop();
            }
            qDebug() << "当前行：" << ui->tableWidget->currentItem();
        }
        else {
            QMessageBox::information(this,"单步运行","示教活动正在运行或当前不存在示教活动");
        }
    }
    else {
        QMessageBox::critical(this,"示教运行","数据为空，无法获取数据进行示教！");
        return;
    }
}
