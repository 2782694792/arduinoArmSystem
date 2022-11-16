#include "uppermachine.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    主程序类
    UpperMachine upperMachine;    
    upperMachine.setWindowTitle("上位机349");
    upperMachine.show();
    QMessageBox::aboutQt(NULL, "QtAbout");
    return a.exec();

}
