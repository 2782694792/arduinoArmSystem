#ifndef GROUPBOXFUNCTION_H
#define GROUPBOXFUNCTION_H

//    动作指令集
enum RobotAction
{
    UP = 1,
    DOWN,                                 //读取当前坐标
    RESET,                                 //复位
    ADD_ACTION,                       //添加动作
    REMOVE,                             //删除动作
    REVOLVING_STAGE_LEFT,               //转台左转
    REVOLVING_STAGE_RIGHT,            //转台右转
    SMALL_ARM_OUTREACH,             //小臂外展
    SMALL_ARM_ADDUCTION,           //小臂内收
    BIG_ARM_OUTREACH,               //大臂外展
    BIG_ARM_ADDUCTION,             //大臂内收
    CLOW_GRAB,                          //爪头抓取
    CLOW_RELEASE                    //爪头释放
};

//示教状态指令集
enum PlayStatus
{
    PLAY = 1,   //播放
    PAUSE,     //暂停
    STOP       //停止
};





#endif // GROUPBOXFUNCTION_H
