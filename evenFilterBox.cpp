#include <applicationHeader.h>


void UpperMachine::groupbox2_eventFilter(QObject *object){
    if (object==ui->textEdit_ClowMin)
    {
        checkSoftLimit(1);
    }
    if (object==ui->textEdit_ClowMax)
    {
        checkSoftLimit(2);
    }
    if (object==ui->textEdit_SArmMin)
    {
        checkSoftLimit(3);
    }
    if (object==ui->textEdit_SArmMax)
    {
        checkSoftLimit(4);
    }
    if (object==ui->textEdit_BArmMin)
    {
        checkSoftLimit(5);
    }
    if (object==ui->textEdit_BArmMax)
    {
        checkSoftLimit(6);
    }
    if (object==ui->textEdit_RStageMin)
    {
        checkSoftLimit(7);
    }
    if (object==ui->textEdit_RStageMax)
    {
        checkSoftLimit(8);
    }
}

/*
 * 按键事件
*/
void UpperMachine::groupbox4_eventFilter(QObject *object){
    if (object == ui->pushButton_W) {
        //        qDebug() <<"W:爪头抓取";
        robotAction = RobotAction::CLOW_GRAB;
        key_SerialWrite("M2000");
    }
     if (object == ui->pushButton_A) {
        //        qDebug() <<"A:小臂内收";
        robotAction = RobotAction::SMALL_ARM_ADDUCTION;
        key_SerialWrite("M0100");
    }
    if (object == ui->pushButton_X) {
        //        qDebug() <<"X:爪头释放";
        robotAction = RobotAction::CLOW_RELEASE;
        key_SerialWrite("M1000");
    }
    if (object == ui->pushButton_D) {
        //        qDebug() <<"D:小臂外展";
        robotAction = RobotAction::SMALL_ARM_OUTREACH;
        key_SerialWrite("M0200");
    }
    if (object == ui->pushButton_I) {
        //        qDebug() <<"I:转台右转";
        robotAction = RobotAction::REVOLVING_STAGE_RIGHT;
        key_SerialWrite("M0002");
    }
    if (object == ui->pushButton_J) {
        //        qDebug() <<"J:大臂内收";
        robotAction = RobotAction::BIG_ARM_ADDUCTION;
        key_SerialWrite("M0010");
    }
    if (object == ui->pushButton_M) {
        //        qDebug() <<"M:转台左转";
        robotAction = RobotAction::REVOLVING_STAGE_LEFT;
        key_SerialWrite("M0001");
    }
    if (object == ui->pushButton_L) {
        //        qDebug() <<"L:大臂外展";
        robotAction = RobotAction::BIG_ARM_OUTREACH;
        key_SerialWrite("M0020");
    }
}
