#ifndef UPPERSERIAL_H
#define UPPERSERIAL_H
#include <QSerialPort>
#include <QString>

using namespace std;

class UpperSerial
{
public:
    UpperSerial();
    ~UpperSerial();

    bool getL_isOpen() const;
    void setL_isOpen(bool value);

    string getL_devicePattern() const;
    void setL_devicePattern(const string &value);

    int getL_c_baudRate() const;

    int getL_c_dataBits() const;

    int getL_c_stopBits() const;

    int getL_c_parity() const;

    string getConnectInfo() const;
    void setConnectInfo(const string &value);

    QString getL_deviceFlag() const;
    void setL_deviceFlag(const QString &value);

    QString getDeviceName() const;
    void setDeviceName(const QString &value);

    QString getL_c_protName() const;
    void setL_c_protName(const QString &value);


    int getL_c_flowControl() const;

    bool getWriteSuccess() const;
    void setWriteSuccess(bool value);

private:
    //设备串口名称正则表达式
    string l_devicePattern = "Arduino Uno (.*)";

    //设备全名称标志
    QString l_deviceFlag = "Arduino Uno";

    //    设备全名称
    QString deviceName = "";

    //正则表达式
    QRegExp l_reg();

    //串口号
    QString l_c_protName = "";

    //波特率
    //    const int l_c_baudRate = 57600;
    const int l_c_baudRate = QSerialPort::Baud57600;

    //数据位
    //    const int l_c_dataBits = 8;
    const int l_c_dataBits = QSerialPort::Data8;

    //停止位
    //    const int l_c_stopBits = 1;
    const int l_c_stopBits = QSerialPort::OneStop;

    //    校验位
    const int l_c_parity = QSerialPort::NoParity;

    //    流控制
    const int l_c_flowControl = QSerialPort::NoFlowControl;


    //串口是否已经打开
    bool l_isOpen = false;

    //    连接信息
    string connectInfo = "设备未连接";

    //    接收状态
    bool writeSuccess = false;

};



#endif // UPPERSERIAL_H
