#include <QWidget>
#include <applicationHeader.h>
#include <otherHeader.h>
#include <QThread>

/*
 * 键盘按下事件
 */
void UpperMachine::keyPressEvent(QKeyEvent * event)
{
    if(upperSerial.getL_isOpen()) {

        // 单个按键
        switch (event->key())
        {
        //    W键
        case Qt::Key_W:
            //        qDebug() <<"W:爪头抓取";
            robotAction = RobotAction::CLOW_GRAB;
            key_SerialWrite("M2000");
            break;
            //     A键
        case Qt::Key_A:
            //        qDebug() <<"A:小臂内收";
            robotAction = RobotAction::SMALL_ARM_ADDUCTION;
            key_SerialWrite("M0100");
            break;
            //     X键
        case Qt::Key_X:
            //        qDebug() <<"X:爪头释放";
            robotAction = RobotAction::CLOW_RELEASE;
            key_SerialWrite("M1000");
            break;
            //     D键
        case Qt::Key_D:
            //        qDebug() <<"D:小臂外展";
            robotAction = RobotAction::SMALL_ARM_OUTREACH;
            key_SerialWrite("M0200");
            break;
            //     I键
        case Qt::Key_I:
            //        qDebug() <<"I:转台右转";
            robotAction = RobotAction::REVOLVING_STAGE_RIGHT;
            key_SerialWrite("M0002");
            break;
            //     J键
        case Qt::Key_J:
            //        qDebug() <<"J:大臂内收";
            robotAction = RobotAction::BIG_ARM_ADDUCTION;
            key_SerialWrite("M0010");
            break;
            //     M键
        case Qt::Key_M:
            //        qDebug() <<"M:转台左转";
            robotAction = RobotAction::REVOLVING_STAGE_LEFT;
            key_SerialWrite("M0001");
            break;
            //     L键
        case Qt::Key_L:
            //        qDebug() <<"L:大臂外展";
            robotAction = RobotAction::BIG_ARM_OUTREACH;
            key_SerialWrite("M0020");
            break;
        default:
            break;
        }

        // 两键组合
        if(event->modifiers() == Qt::ControlModifier) {
            if(event->key() == Qt::Key_R){
                //                Ctrl+R =》 复位
                robotAction = RobotAction::RESET;
                key_SerialWrite("LEFT");
            }
        }
        if(event->modifiers() == Qt::ControlModifier) {
            if(event->key() == Qt::Key_Q){
                //                Ctrl+Q =》 关闭连接
                closeSerialDevice();
            }
        }
        if(event->modifiers() == Qt::ControlModifier) {
            if(event->key() == Qt::Key_U){
                //                Ctrl+U  =》 切换状态
                switchSteerStatus();
            }
        }
        if(event->modifiers() == Qt::ControlModifier) {
            if(event->key() == Qt::Key_L){
                //                Ctrl+L  =》 连接串口
                connectUM();
            }
        }

        //    // 三键组合Shift + Ctrl + A的实现
        //    if (event->modifiers() == (Qt::ShiftModifier | Qt::ControlModifier) && event->key() == Qt::Key_A) {
        //        qDebug() << "CTRL + Shift + A";
        //    }

    }
    else{
        QMessageBox::critical(NULL,"串口异常","请先打开串口！");
        upperSerial.setL_isOpen(0);
    }
}

/*
 * 键盘释放事件
*/
void UpperMachine::keyReleaseEvent(QKeyEvent *event)
{
    // 键释放
    switch (event->key()) {
    case Qt::Key_W:
    case Qt::Key_A:
    case Qt::Key_X:
    case Qt::Key_D:
    case Qt::Key_I:
    case Qt::Key_J:
    case Qt::Key_M:
    case Qt::Key_L:
    case Qt::Key_Enter:
    case Qt::Key_Tab:
    case Qt::Key_Delete:
    case Qt::Key_R:
        key_SerialWrite("M0000");//发送数据
        //    actionCount = 0;
        //        qDebug() << ">> 舵机停下";
        break;
    default:
        break;
    }

}

void UpperMachine :: key_SerialWrite(QString keyValue)
{
    upperSerialPort.write(QString(strAddLine(keyValue)).toUtf8());
    //    QThread::sleep(1);
}

