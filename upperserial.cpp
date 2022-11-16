#include "upperserial.h"

UpperSerial::UpperSerial()
{
}

UpperSerial::~UpperSerial()
{

}

bool UpperSerial::getL_isOpen() const
{
    return l_isOpen;
}

void UpperSerial::setL_isOpen(bool value)
{
    l_isOpen = value;
}

string UpperSerial::getL_devicePattern() const
{
    return l_devicePattern;
}

void UpperSerial::setL_devicePattern(const string &value)
{
    l_devicePattern = value;
}

int UpperSerial::getL_c_baudRate() const
{
    return l_c_baudRate;
}

int UpperSerial::getL_c_dataBits() const
{
    return l_c_dataBits;
}

int UpperSerial::getL_c_stopBits() const
{
    return l_c_stopBits;
}

string UpperSerial::getConnectInfo() const
{
    return connectInfo;
}

void UpperSerial::setConnectInfo(const string &value)
{
    connectInfo = value;
}

QString UpperSerial::getL_deviceFlag() const
{
    return l_deviceFlag;
}

void UpperSerial::setL_deviceFlag(const QString &value)
{
    l_deviceFlag = value;
}

QString UpperSerial::getDeviceName() const
{
    return deviceName;
}

void UpperSerial::setDeviceName(const QString &value)
{
    deviceName = value;
}

QString UpperSerial::getL_c_protName() const
{
    return l_c_protName;
}

void UpperSerial::setL_c_protName(const QString &value)
{
    l_c_protName = value;
}

int UpperSerial::getL_c_flowControl() const
{
    return l_c_flowControl;
}

bool UpperSerial::getWriteSuccess() const
{
    return writeSuccess;
}

void UpperSerial::setWriteSuccess(bool value)
{
    writeSuccess = value;
}

int UpperSerial::getL_c_parity() const
{
    return l_c_parity;
}
