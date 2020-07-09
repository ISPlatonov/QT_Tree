#ifndef HISTORY_H
#define HISTORY_H

#include <QVector>
#include "structdep.h"

#include <QDebug>

class commit
{
public:
    commit();
    void setPrev(const department& prevDep);
    void setNew(const department& newDep);
    department* getPrev();
    department* getNew();
private:
    department* prevDep;
    department* newDep;
};

class History
{
public:
    History();

    void addCommit(commit& commit);
    void pullBack(QVector<department*>& deps);

private:
    QVector<commit> history;
};

#endif // HISTORY_H
