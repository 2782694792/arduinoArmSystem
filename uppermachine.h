#ifndef UPPERMACHINE_H
#define UPPERMACHINE_H

#include <QMainWindow>
#include <QString>
#include <QKeyEvent>
#include <QTableWidget>
#include "enumHeader.h"
#include "upperserial.h"
#include "mechanicalarm.h"

//#include <QStandardItem>
//#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class UpperMachine; }
using namespace std;
QT_END_NAMESPACE

class UpperMachine : public QMainWindow
{
    Q_OBJECT

public:
    /*
     * 主程序----------------------------------
    */
    Ui::UpperMachine *ui;
    explicit UpperMachine(QWidget *parent = nullptr);
    ~UpperMachine();

    /*
     * 类实例-----------------------------------------------------------------------------------------------------
    */
    //    串口通讯
    QSerialPort upperSerialPort;
    //    串口实体类
    UpperSerial upperSerial;
    //    机械臂实体类
    MechanicalArm mechanicalArm;
    //    表格视图
    //    QStandardItemModel *standItemModel;

    //    创建子类
    //    class upperserial1 : public UpperSerial{};

    //    定时器
    QTimer *m_pTimer;


    /*
     * 机械臂参数-----------------------------------------------------------------------------------------------------
    */
    //    蓝灯：手动模式
    bool isBlueLight = false;
    //    示教保留文件工程名称
    string projectName = "";
    //    机械臂动作指令集
    RobotAction robotAction;
    //    枚举宏定义
    Q_ENUM(RobotAction);
    /*
     * 定义包装枚举
        Q_DECLARE_FLAGS(robotAction,RobotAction);
        //    注册枚举元对象
        Q_FLAG(robotAction);
        QMetaEnum qRobotAction = QMetaEnum::fromType<UpperMachine::robotAction>();
    */
    //    播放状态
    PlayStatus playStatus;
    Q_ENUM(PlayStatus);


    /*
     * 运行方法-----------------------------------------------------------------------------------------------------
    */
    ///主页程序
    //      主程序界面设置
    void application_UISettings();

    ///0、串口方法
    //    0.1、进行设备连接
    void connectUM();
    //    0.2、获取设备全称、查询可用串口
    QString GetDeviceFullName();
    //    0.3、读取接收数据
    void readAvailableInfo();

    ///1、groupbox1
    //    1.1、读取当前位置
    void readCurrentLocation();
    //    1.1.1、获取当前坐标
    void doDOWN(QString);
    void setLocation(QString);
    //    1.2、关闭当前串口设备
    void closeSerialDevice();
    //    1.3、切换操纵状态
    void switchSteerStatus();

    ///2、groupbox2
    void groupbox2_eventFilter(QObject *object);
    //    2.0、当前软限位设置
    void currentsoftlimitSettings();
    //    2.1、软限位控制
    void checkSoftLimit(int);
    void checkSoftLimit_Clow(int);
    void checkSoftLimit_SArm(int);
    void checkSoftLimit_BArm(int);
    void checkSoftLimit_RStage(int);
    //    2.2、保留软限位文件
    void saveSoftLimit();
    //    2.3、读取软限位文件
    void loadSoftLitmit();
    //    2.4、复位
    void resetLocation();

    ///3、groupbox3
    //    3、发送位置
    void sendLocation();

    ///4、groupbox4
    void groupbox4_eventFilter(QObject *object);
    //    4.0、按键串口写入函数
    void key_SerialWrite(QString);
    //    4.1、手柄爪头抓取
    void handle_Clow_Grab();
    //    4.2、手柄爪头释放
    void handle_Clow_Release();
    //    4.3、手柄小臂外展
    void handle_SArm_OutReach();
    //    4.4、手柄小臂内收
    void handle_SArm_Adduction();
    //    4.5、手柄大臂外展
    void handle_BArm_OutReach();
    //    4.6、手柄大臂臂内收
    void handle_BArm_Adduction();
    //    4.7、手柄转台左转
    void handle_RStage_Left();
    //    4.7、手柄转台左右转
    void handle_RStage_Right();

    ///groupBox5
    //    5.1、添加动作
    void addAction();
    void addUMAction(QString);
    //    5.2、添加、判断记录
    void addAction_Location(int add_row, int add_column);
    bool NextItemEmpty(QTableWidget *t, int x, int y);
    bool CurrentItemEmpty(QTableWidget *t, int x, int y);
    //    5.3、删除动作
    void deleteAction();
    bool selectRow();
    //    5.4、清空轨迹
    void clearAction();
    //    5.5、恢复首位
    void firstAction();
    QString readFirstAction();

    //    5.6、示教启动
    void playActions();
    //    5.7、示教暂停
    void pauseActions();
    QString readItems(int);
    //    5.8、示教停止
    void stopActions();
    //    5.9、单步运行
    void stepActions();


private:
    //    当前按下的是那个键
    //    label currLabel = null;
    //    指令序列索引
    const int actionIndex = 1;
    //    播放索引
    int playIndex = 0;
    //    接收输入缓冲区列表
    QList<QByteArray> tempBuffer;
    //    接收输入缓冲区字节数组
    QByteArray arrayBuffer;
    //    机械臂操纵状态提醒
    //    FrmWarning frmWarning;
    //    动作添加次数
    int actionCount = -1;

private slots:
    ///菜单栏
    //    菜单栏监听回调
    void menuBar_Action(QAction *a);
    //    接收串口读取的数据
    void serialPort_ReadAvailable();
    ///groupbox1
    //    读取位置
    void on_pushButton_ReadLocation_clicked();
    //    关闭当前串口和设备
    void on_pushButton_CloseSerial_clicked();
    //    操纵状态切换
    void on_pushButton_SwitchStatus_clicked();
    ///groupbox2
    //    软限位
    bool eventFilter(QObject *object,QEvent *event) ;
    //    复位
    void on_pushButton_Reset_clicked();
    ///groupbox3
    //    发送位置
    void on_pushButton_SendLocation_clicked();
    ///groupbox4
    //    爪头抓取
    void on_pushButton_W_clicked();
    void on_pushButton_W_released();
    //    爪头释放
    void on_pushButton_X_clicked();
    void on_pushButton_X_released();
    //    小臂外展
    void on_pushButton_A_clicked();
    void on_pushButton_A_released();
    //    小臂内收
    void on_pushButton_D_clicked();
    void on_pushButton_D_released();
    //    转台左移
    void on_pushButton_I_clicked();
    void on_pushButton_I_released();
    //    转台右移
    void on_pushButton_M_clicked();
    void on_pushButton_M_released();
    //    大臂外展
    void on_pushButton_J_clicked();
    void on_pushButton_J_released();
    //    大臂内收
    void on_pushButton_L_clicked();
    void on_pushButton_L_released();
    ///groupbox5
    //    超时处理函数
    void handleTimeout();
    //    添加动作
    void on_pushButton_AddAction_clicked();
    //    删除动作
    void on_pushButton_deleteAction_clicked();
    //    清空轨迹
    void on_pushButton_clearAction_clicked();
    //    恢复首位
    void on_pushButton_FirstAction_clicked();
    //    示教启动
    void on_pushButton_PLAY_clicked();
    //    示教停止
    void on_pushButton_STOP_clicked();
    //    示教暂停
    void on_pushButton_PAUSE_clicked();
    //    示教单步运行
    void on_pushButton_STEP_clicked();

protected:
    //    保护类，作用为其对象，不能访问，只能由内部类或派生类访问
    //    键盘按键按压事件
    void keyPressEvent(QKeyEvent *);
    //    键盘按键放松事件
    void keyReleaseEvent(QKeyEvent *);

};
#endif // UPPERMACHINE_H
