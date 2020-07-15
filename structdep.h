#ifndef STRUCTDEP_H
#define STRUCTDEP_H

#include <QVariant>
#include <QVector>

#include <QDebug>

//struct - это тот же class, у которого
//все члены public
//struct точно так же наследуются и т.п.,
//там те же правила - можно наследовать
//их хоть друг от друга, - это лишь вопрос
//стиля/вкусовщины

struct empl
{
    QString name, surname, midname, sal, func;
    QString fio()
    {
        QString fio = surname + ' ' + name + ' ' + midname;
        return fio;
    }
    empl& operator=(const empl& right);
    void del();
};

struct department
{
    QString name;
    QVector<empl*> empls;

    void newPtrEmplVector(const QVector<empl*>& v);
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
    void del();
};

bool operator==(const empl& left, const empl& right);
bool operator==(const department& left, const department& right);
bool operator==(const QVector<empl*>& left, const QVector<empl*>& right);

#endif // STRUCTDEP_H
