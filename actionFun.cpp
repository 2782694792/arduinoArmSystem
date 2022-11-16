#include <applicationHeader.h>



/*
 * 判断下一行是否为空
*/
bool UpperMachine :: NextItemEmpty(QTableWidget *t, int x, int y)
{
    return t->item(x+1,y) == NULL || (t->item(x+1,y) && t->item(x+1,y)->text() == tr(""));
}

/*
 * 判断当前行是否为空
*/
bool UpperMachine :: CurrentItemEmpty(QTableWidget *t, int x, int y)
{
    return t->item(x,y) == NULL || (t->item(x,y) && t->item(x,y)->text() == tr(""));
}

/*
 * 判断是否选中行
*/
bool UpperMachine::selectRow()
{
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    if(items.empty())
        //        qDebug()<<"选中了某行";
        return false;
    return true;
}

/*
 * 首位获取
*/
QString UpperMachine :: readFirstAction()
{
    if(ui->tableWidget->selectedItems().count() != 0)
    {
        QString sendCommand;
        sendCommand
                .append("a" + QString("%1").arg(ui->tableWidget->item(0,0)->text(), 3, QLatin1Char('0')))
                .append("b" + QString("%1").arg(ui->tableWidget->item(0,1)->text(), 3, QLatin1Char('0')))
                .append("c" + QString("%1").arg(ui->tableWidget->item(0,2)->text(), 3, QLatin1Char('0')))
                .append("d" + QString("%1").arg(ui->tableWidget->item(0,3)->text(), 3, QLatin1Char('0')));
        return sendCommand;
    }
    else {
        QMessageBox::critical(this,"恢复首位","首位数据为空，无法获取数据！");
        return "";
    }
}

/*
 * 获取行数据
*/
QString UpperMachine :: readItems(int currentIndex)
{
    if(!CurrentItemEmpty(ui->tableWidget,0,0))
    {
        QString sendCommand;
        sendCommand
                .append("a" + QString("%1").arg(ui->tableWidget->item(currentIndex,0)->text(), 3, QLatin1Char('0')))
                .append("b" + QString("%1").arg(ui->tableWidget->item(currentIndex,1)->text(), 3, QLatin1Char('0')))
                .append("c" + QString("%1").arg(ui->tableWidget->item(currentIndex,2)->text(), 3, QLatin1Char('0')))
                .append("d" + QString("%1").arg(ui->tableWidget->item(currentIndex,3)->text(), 3, QLatin1Char('0')));
        return sendCommand;
    }
    else {
        QMessageBox::critical(this,"示教运行","数据为空，无法获取数据进行示教！");
        return "";
    }
}
