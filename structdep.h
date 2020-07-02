#ifndef STRUCTDEP_H
#define STRUCTDEP_H

#include <QVariant>
#include <QVector>
#include <stdio.h>

struct empl
{
    QString name, sal, func;
};

struct department
{
    QString name;//, num, midsal;
    QVector<empl*> empls;
    int num()
    {
        return empls.count();
    }
    int midsal()
    {
        int v = 0, n = 0;
        for (auto empl : empls)
        {
            v += empl->sal.toInt();
            ++n;
        }
        return v/n;
    }
};

#endif // STRUCTDEP_H
