#include <applicationHeader.h>



//获取当前坐标
void UpperMachine :: doDOWN(QString command)
{
    setLocation(command);

    //显示爪子坐标
    ui->textEdit_ClowObtain->setText(mechanicalArm.getClowLocation());

    //显示小臂坐标
    ui->textEdit_SArmObtain->setText(mechanicalArm.getSmallArmLocation());

    //显示大臂坐标
    ui->textEdit_BArmObtain->setText(mechanicalArm.getBigArmLocation());

    //显示转台坐标
    ui->textEdit_RevolvingStageObtain->setText(mechanicalArm.getRevolvingStageLocation());
}

//定义获取的位置
void UpperMachine :: setLocation(QString command)
{

    //指令例子 a:12,b:119,c:45,d:70\r\n   a:爪子 b:小臂 c:大臂 d:转台
    /*字符串进行按“，“分隔成多个元素结果，存入字符串数组*/
    QStringList elem = command.split(',');
    //    qDebug() << "转换后的字符一维列表：" << elem;

    //设置爪子
    mechanicalArm.setClowLocation(elem[0].split(':')[1]);

    //设置小臂
    mechanicalArm.setSmallArmLocation(elem[1].split(':')[1]);

    //设置大臂
    mechanicalArm.setBigArmLocation(elem[2].split(':')[1]);

    //设置转台
    mechanicalArm.setRevolvingStageLocation(elem[3].split(':')[1]);
}
