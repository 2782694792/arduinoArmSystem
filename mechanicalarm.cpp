#include "mechanicalarm.h"

//机械臂类
MechanicalArm::MechanicalArm()
{

}

MechanicalArm::~MechanicalArm()
{

}

QString MechanicalArm::getCurrent_SAMin() const
{
    return current_SAMin;
}

void MechanicalArm::setCurrent_SAMin(const QString &value)
{
    current_SAMin = value;
}

QString MechanicalArm::getCurrent_BAMin() const
{
    return current_BAMin;
}

void MechanicalArm::setCurrent_BAMin(const QString &value)
{
    current_BAMin = value;
}

QString MechanicalArm::getCurrent_RSMin() const
{
    return current_RSMin;
}

void MechanicalArm::setCurrent_RSMin(const QString &value)
{
    current_RSMin = value;
}

QString MechanicalArm::getCurrent_RSMax() const
{
    return current_RSMax;
}

void MechanicalArm::setCurrent_RSMax(const QString &value)
{
    current_RSMax = value;
}

QString MechanicalArm::getCurrent_BAMax() const
{
    return current_BAMax;
}

void MechanicalArm::setCurrent_BAMax(const QString &value)
{
    current_BAMax = value;
}

QString MechanicalArm::getCurrent_SAMax() const
{
    return current_SAMax;
}

void MechanicalArm::setCurrent_SAMax(const QString &value)
{
    current_SAMax = value;
}

QString MechanicalArm::getCurrent_CMax() const
{
    return current_CMax;
}

void MechanicalArm::setCurrent_CMax(const QString &value)
{
    current_CMax = value;
}

QString MechanicalArm::getCurrent_CMin() const
{
    return current_CMin;
}

void MechanicalArm::setCurrent_CMin(const QString &value)
{
    current_CMin = value;
}

int MechanicalArm::getStartCheck() const
{
    return startCheck;
}

void MechanicalArm::setStartCheck(int value)
{
    startCheck = value;
}


QString MechanicalArm::getRevolvingStageLocation() const
{
    return RevolvingStageLocation;
}

void MechanicalArm::setRevolvingStageLocation(const QString &value)
{
    RevolvingStageLocation = value;
}

QString MechanicalArm::getBigArmLocation() const
{
    return BigArmLocation;
}

void MechanicalArm::setBigArmLocation(const QString &value)
{
    BigArmLocation = value;
}

QString MechanicalArm::getSmallArmLocation() const
{
    return SmallArmLocation;
}

void MechanicalArm::setSmallArmLocation(const QString &value)
{
    SmallArmLocation = value;
}

QString MechanicalArm::getClowLocation() const
{
    return ClowLocation;
}

void MechanicalArm::setClowLocation(const QString &value)
{
    ClowLocation = value;
}

int MechanicalArm::getRStageMin() const
{
    return RStageMin;
}

int MechanicalArm::getRStageMax() const
{
    return RStageMax;
}

int MechanicalArm::getBArmMax() const
{
    return BArmMax;
}

int MechanicalArm::getBArmMin() const
{
    return BArmMin;
}

int MechanicalArm::getSArmMin() const
{
    return SArmMin;
}

int MechanicalArm::getSArmMax() const
{
    return SArmMax;
}

int MechanicalArm::getClowMax() const
{
    return ClowMax;
}

int MechanicalArm::getClowMin() const
{
    return ClowMin;
}
