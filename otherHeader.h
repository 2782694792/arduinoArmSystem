#ifndef OTHERHEADER_H
#define OTHERHEADER_H

#include <QString>


//休眠
void sleep_MS(int);
//加换行
QString strAddLine(QString);
//除去末尾
QString strDelLast(QByteArray);
//寻找状态编码
int findModelNum(QByteArray);
//查询状态信息
int findModelInfo(QByteArray);

#endif // OTHERHEADER_H
