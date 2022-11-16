#ifndef HOMESETTINGS_H
#define HOMESETTINGS_H

#include <mechanicalarm.h>
#include <applicationHeader.h>

void UpperMachine :: application_UISettings(void)
{
    mechanicalArm.setStartCheck(0);
    //    菜单栏背景色
    ui->menubar->setStyleSheet("background-color:rgb(195, 197, 198)");


    //    获取位置只读
    ui->textEdit_BArmObtain->setReadOnly(true);
    ui->textEdit_ClowObtain->setReadOnly(true);
    ui->textEdit_SArmObtain->setReadOnly(true);
    ui->textEdit_RevolvingStageObtain->setReadOnly(true);

    //    配置文本框事件过滤器
    ui->textEdit_ClowMin->installEventFilter(this);
    ui->textEdit_ClowMax->installEventFilter(this);
    ui->textEdit_SArmMin->installEventFilter(this);
    ui->textEdit_SArmMax->installEventFilter(this);
    ui->textEdit_BArmMin->installEventFilter(this);
    ui->textEdit_BArmMax->installEventFilter(this);
    ui->textEdit_RStageMin->installEventFilter(this);
    ui->textEdit_RStageMax->installEventFilter(this);


    //    配置按钮事件过滤器
    ui->pushButton_W->installEventFilter(this);
    ui->pushButton_A->installEventFilter(this);
    ui->pushButton_X->installEventFilter(this);
    ui->pushButton_D->installEventFilter(this);
    ui->pushButton_I->installEventFilter(this);
    ui->pushButton_J->installEventFilter(this);
    ui->pushButton_M->installEventFilter(this);
    ui->pushButton_L->installEventFilter(this);


    //    居中显示
    ui->textEdit_ClowObtain->setAlignment(Qt::AlignCenter);
    ui->textEdit_SArmObtain->setAlignment(Qt::AlignCenter);
    ui->textEdit_BArmObtain->setAlignment(Qt::AlignCenter);
    ui->textEdit_RevolvingStageObtain->setAlignment(Qt::AlignCenter);
    ui->textEdit_ClowMin->setAlignment(Qt::AlignCenter);
    ui->textEdit_ClowMax->setAlignment(Qt::AlignCenter);
    ui->textEdit_SArmMin->setAlignment(Qt::AlignCenter);
    ui->textEdit_SArmMax->setAlignment(Qt::AlignCenter);
    ui->textEdit_BArmMin->setAlignment(Qt::AlignCenter);
    ui->textEdit_BArmMax->setAlignment(Qt::AlignCenter);
    ui->textEdit_RStageMin->setAlignment(Qt::AlignCenter);
    ui->textEdit_RStageMax->setAlignment(Qt::AlignCenter);
    ui->textEdit_SendClow->setAlignment(Qt::AlignCenter);
    ui->textEdit_SendSArm->setAlignment(Qt::AlignCenter);
    ui->textEdit_SendBArm->setAlignment(Qt::AlignCenter);
    ui->textEdit_SendRStage->setAlignment(Qt::AlignCenter);



    ///设置表格
    //    设置列数：限定5列
    ui->tableWidget->setColumnCount(4);
    //    设置行数：限定10行
    ui->tableWidget->setRowCount(10);
    //    设置标题
    ui->tableWidget->setWindowTitle("示教表格");
    //    设置表头
    QStringList tableHeader;
    tableHeader << QString("爪头")  << QString("小臂")  << QString("大臂")  << QString("转台");
    ui->tableWidget->setHorizontalHeaderLabels(tableHeader);
    //    表头可视化
    ui->tableWidget->verticalHeader()->setVisible(true);
    ui->tableWidget->horizontalHeader()->setVisible(true);
    //    隐藏栅格
    //    ui->tableWidget->setShowGrid(false);

    //    设置可编辑
    //    ui->tableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //    设置表格选择方式：设置表格为整列选中
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //    选择目标方式
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //    设置选中颜色：粉色
    ui->tableWidget->setStyleSheet("selection-background-color:gray");
    //    设置水平滚动条
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //    设置垂直滚动条
    ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //    只能选中一行，不可多行
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //    去掉每行的行号
    //    QHeaderView *headerView = ui->tableWidget->verticalHeader();
    //    headerView->setHidden(true);

    //    获取单元格的内容
    //    QString strText = ui->tableWidget->item(1, 1)->text();
    //    输出单元格内容
    //    qDebug()<<"单元格内容："<<strText;


    //    设置按钮透明
    ui->pushButton_STEP->setFlat(1);
    //    ui->pushButton_STEP->setStyleSheet("outline: none");
    ui->pushButton_PAUSE->setFlat(1);
    //    ui->pushButton_PAUSE->setStyleSheet("outline: none");
    ui->pushButton_STOP->setFlat(1);
    //    ui->pushButton_STOP->setStyleSheet("outline: none");
    ui->pushButton_PLAY->setFlat(1);
    //    ui->pushButton_PLAY->setStyleSheet("outline: none");




    for(int rows=0;rows<ui->tableWidget->rowCount();rows++)
    {
        for(int columns=0;columns<ui->tableWidget->columnCount();columns++)
        {
            ui->tableWidget->setRowHeight(rows,30);
            ui->tableWidget->setColumnWidth(columns,100);
            //            //            居中显示
            //            ui->tableWidget->item(rows,columns)->setTextAlignment(Qt::AlignCenter);
            //            设置前景颜色
            //            ui->tableWidget->item(rows,columns)->setBackground(QColor(85,170,255));
            //            ui->tableWidget->item(rows,columns)->setTextColor();//设置文本颜色
            //            设置字体为黑体
            //            ui->tableWidget->item(rows,columns)->setFont(QFont("Helvetica"));
        }
    }


    //    文本框默认软限位
    ui->textEdit_ClowMin->setText(QString::number(mechanicalArm.getClowMin()));
    ui->textEdit_ClowMax->setText(QString::number(mechanicalArm.getClowMax()));
    ui->textEdit_SArmMin->setText(QString::number(mechanicalArm.getSArmMin()));
    ui->textEdit_SArmMax->setText(QString::number(mechanicalArm.getSArmMax()));
    ui->textEdit_BArmMin->setText(QString::number(mechanicalArm.getBArmMin()));
    ui->textEdit_BArmMax->setText(QString::number(mechanicalArm.getBArmMax()));
    ui->textEdit_RStageMin->setText(QString::number(mechanicalArm.getRStageMin()));
    ui->textEdit_RStageMax->setText(QString::number(mechanicalArm.getRStageMax()));

    mechanicalArm.setStartCheck(1);

    //    设置软限位默认值
    currentsoftlimitSettings();

    //    默认间隔时间
    ui->textEdit_timeOut->setText("2500");




}

//void UpperMachine :: controlsSettings(bool tf)
//{
//    if (upperSerial.getL_isOpen() == true) {

//    }
//    else
//    {

//    }
//    ui->pushButton_CloseSerial->setEnabled(1);
//    ui->pushButton_ReadLocation->setEnabled(1);
//    ui->pushButton_SwitchStatus->setEnabled(1);
//}


#endif // HOMESETTINGS_H
