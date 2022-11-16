#include <QDesktopServices>
#include <QTimer>
#include <applicationHeader.h>

#include <homesettings.h>
#include <otherHeader.h>
#include "enumHeader.h"

UpperMachine::UpperMachine(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UpperMachine)
{
    ui->setupUi(this);
    //    连接信号和槽：连接函数（指定类《控件》,信号，主体应用，槽函数）
    connect(ui->menubar,SIGNAL(triggered(QAction*)), this, SLOT(menuBar_Action(QAction*)));
    //    connect(&upperSerialPort, &QSerialPort::readyRead, this, &UpperMachine::serialPort_ReadAvailable);
    this->setWindowIcon(QIcon(".\\Image\\machine.png"));
    //    主程序界面
    application_UISettings();
    //    qDebug() << "进入主页";`

    //定时器实例化
    m_pTimer = new QTimer(this);
    //超时槽函数
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));

}

UpperMachine::~UpperMachine()
{
    delete ui;
}

/*
 * 接收串口读取的数据
 */
void UpperMachine::serialPort_ReadAvailable()
{
    readAvailableInfo();
}

/*
 * 获取当前位置
*/
void UpperMachine::on_pushButton_ReadLocation_clicked()
{
    readCurrentLocation();
}

/*
 * 关闭当前串口设备
*/
void UpperMachine::on_pushButton_CloseSerial_clicked()
{
    closeSerialDevice();
}

/*
 * 操纵状态切换
*/
void UpperMachine::on_pushButton_SwitchStatus_clicked()
{
    switchSteerStatus();
}

/*
 * 软限位
*/
bool UpperMachine::eventFilter(QObject *object, QEvent *event)
{
//    if (upperSerial.getL_isOpen()) {
        //    输入聚焦
        if (event->type()==QEvent::FocusOut){
            groupbox2_eventFilter(object);
        }
        //    鼠标按压
        if (event->type()==QEvent::MouseButtonPress){
            groupbox4_eventFilter(object);
        }
        if (event->type()==QEvent::MouseButtonRelease){
            key_SerialWrite("M0000");
        }



        return false;
//    }
//    else {
//        QMessageBox::warning(this,"添加动作","当前未连接，请进行设备连接！");
//        return false;
//    }
}

/*
 * 复位
*/
void UpperMachine::on_pushButton_Reset_clicked()
{
    resetLocation();
}

/*
 * 发送位置
*/
void UpperMachine::on_pushButton_SendLocation_clicked()
{
    sendLocation();
}

/*
 * 爪头抓取
 */
void UpperMachine::on_pushButton_W_clicked()
{
    groupbox4_eventFilter(ui->pushButton_W);
    //            qDebug() <<"W:爪头抓取";
    //    robotAction = RobotAction::CLOW_GRAB;
    //    key_SerialWrite("M2000");
}

void UpperMachine::on_pushButton_W_released()
{
    key_SerialWrite("M0000");
}

/*
 * 爪头释放
 */
void UpperMachine::on_pushButton_X_clicked()
{
    groupbox4_eventFilter(ui->pushButton_X);
}

void UpperMachine::on_pushButton_X_released()
{
    key_SerialWrite("M0000");
}

/*
 * 小臂外展
 */
void UpperMachine::on_pushButton_A_clicked()
{
    groupbox4_eventFilter(ui->pushButton_A);
}

void UpperMachine::on_pushButton_A_released()
{
    key_SerialWrite("M0000");
}

/*
 * 小臂内收
 */
void UpperMachine::on_pushButton_D_clicked()
{
    groupbox4_eventFilter(ui->pushButton_D);
}

void UpperMachine::on_pushButton_D_released()
{
    key_SerialWrite("M0000");
}

/*
 * 大臂外展
 */
void UpperMachine::on_pushButton_J_clicked()
{
    groupbox4_eventFilter(ui->pushButton_J);
}

void UpperMachine::on_pushButton_J_released()
{
    key_SerialWrite("M0000");
}

/*
 * 大臂内收
 */
void UpperMachine::on_pushButton_L_clicked()
{
    groupbox4_eventFilter(ui->pushButton_L);
}

void UpperMachine::on_pushButton_L_released()
{
    key_SerialWrite("M0000");
}


/*
 * 转台左移
 */
void UpperMachine::on_pushButton_I_clicked()
{
    groupbox4_eventFilter(ui->pushButton_I);
}

void UpperMachine::on_pushButton_I_released()
{
    key_SerialWrite("M0000");
}

/*
 * 转台右移
 */
void UpperMachine::on_pushButton_M_clicked()
{
    groupbox4_eventFilter(ui->pushButton_M);
}

void UpperMachine::on_pushButton_M_released()
{
    key_SerialWrite("M0000");
}

/*
 * 添加动作
*/
void UpperMachine::on_pushButton_AddAction_clicked()
{
    addAction();
}

/*
 * 删除动作
*/
void UpperMachine::on_pushButton_deleteAction_clicked()
{
    deleteAction();
}

/*
 * 清空轨迹
*/
void UpperMachine::on_pushButton_clearAction_clicked()
{
    clearAction();
}

/*
 * 恢复首位
*/
void UpperMachine::on_pushButton_FirstAction_clicked()
{
    firstAction();
}

/*
 * 示教启动
*/
void UpperMachine::on_pushButton_PLAY_clicked()
{
    playActions();
}

/*
 * 示教暂停
*/
void UpperMachine::on_pushButton_PAUSE_clicked()
{
    pauseActions();
}

/*
 * 示教停止
*/
void UpperMachine::on_pushButton_STOP_clicked()
{
    stopActions();
}

/*
 * 单步运行
*/
void UpperMachine::on_pushButton_STEP_clicked()
{
    stepActions();
}





//菜单栏Home回调槽函数
void UpperMachine::menuBar_Action(QAction* a)
{
    if(a->text() == "Home"){
        UpperMachine().show();
        qDebug("进入主页");
    }else if(a->text() == "Exit"){
        upperSerialPort.close();
        upperSerial.setL_isOpen(false);
        qDebug("退出程序");
        this->close();
    }else if (a->text() == "ConnectUM") {
        connectUM();
        qDebug("连接设备");
    }else if (a->text() == "Load") {
        loadSoftLitmit();
        qDebug("载入软限位");
    }else if (a->text() == "Save") {
        saveSoftLimit();
        qDebug("保存软限位");
    }else if (a->text() == "Tutorial") {
        //        openTutorial();
        QString qtManulFile = "F:\\机械臂\\0论文资料\\201835010349_郑烁彬_基于Qt技术的机械臂系统的设计与实现_定稿.pdf";
        QDesktopServices::openUrl(QUrl::fromLocalFile(qtManulFile));
        qDebug("打开教程");
    }



}


