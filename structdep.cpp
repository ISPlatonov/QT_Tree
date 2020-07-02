#include "structdep.h"

struct empls
{
    QVector<QString> names, sal, func;
};

struct department
{
    QString name, num, midsal;
    empls empls;
};
