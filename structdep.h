#ifndef STRUCTDEP_H
#define STRUCTDEP_H

#include <QVariant>
#include <QVector>

#include <QDebug>

struct empl
{
    QString name, surname, midname, sal, func;
    QString fio()
    {
        QString fio = surname + ' ' + name + ' ' + midname;
        return fio;
    }
    empl& operator=(const empl& right);
};

struct department
{
    QString name;
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
        if(!n)
            return 0;
        return v/n;
    }
    void clear()
    {
        empls.clear();
        name = "";
    }
    department& operator=(const department & right);
};

bool operator==(const empl& left, const empl& right);
bool operator==(const department& left, const department& right);

#endif // STRUCTDEP_H
