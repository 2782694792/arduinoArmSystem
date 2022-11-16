#ifndef MECHANICALARM_H
#define MECHANICALARM_H
#include <QString>

//机械臂类
class MechanicalArm
{

public:
    MechanicalArm();
    ~MechanicalArm();

    int startCheck = 0;

    //手爪位置
    QString ClowLocation;
    //    手爪软限位
    const int ClowMin=0,ClowMax=180;
    //    当前软限位
    QString current_CMin = QString(ClowMin),current_CMax  = QString(ClowMax);

    //小臂位置
    QString SmallArmLocation;
    //    手爪软限位
    const int SArmMin= 45 ,SArmMax= 105 ;
    //    当前软限位
    QString current_SAMin  = QString(SArmMin),current_SAMax  = QString(SArmMax);

    //大臂位置
    QString BigArmLocation;
    //    手爪软限位
    const  int BArmMin= 40 ,BArmMax= 135 ;
    //    当前软限位
    QString current_BAMin  = QString(BArmMin),current_BAMax  = QString(BArmMax);

    //转台
    QString RevolvingStageLocation;
    //    手爪软限位
    const int RStageMin= 0 ,RStageMax= 180 ;
    //    当前软限位
    QString current_RSMin  = QString(RStageMin),current_RSMax  = QString(RStageMax);



    int getClowMin() const;
    int getClowMax() const;
    int getSArmMax() const;
    int getSArmMin() const;
    int getBArmMin() const;
    int getBArmMax() const;
    int getRStageMax() const;
    int getRStageMin() const;
    QString getClowLocation() const;
    void setClowLocation(const QString &value);
    QString getSmallArmLocation() const;
    void setSmallArmLocation(const QString &value);
    QString getBigArmLocation() const;
    void setBigArmLocation(const QString &value);
    QString getRevolvingStageLocation() const;
    void setRevolvingStageLocation(const QString &value);
    int getStartCheck() const;
    void setStartCheck(int value);
    QString getCurrent_CMin() const;
    void setCurrent_CMin(const QString &value);
    QString getCurrent_CMax() const;
    void setCurrent_CMax(const QString &value);
    QString getCurrent_SAMax() const;
    void setCurrent_SAMax(const QString &value);
    QString getCurrent_BAMax() const;
    void setCurrent_BAMax(const QString &value);
    QString getCurrent_RSMax() const;
    void setCurrent_RSMax(const QString &value);
    QString getCurrent_RSMin() const;
    void setCurrent_RSMin(const QString &value);
    QString getCurrent_BAMin() const;
    void setCurrent_BAMin(const QString &value);
    QString getCurrent_SAMin() const;
    void setCurrent_SAMin(const QString &value);
    int getIndex_mark() const;
    void setIndex_mark(int value);
    int getPlayIndex() const;
    void setPlayIndex(int value);
};

#endif // MECHANICALARM_H
