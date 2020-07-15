#ifndef HISTORY_H
#define HISTORY_H

#include <QVector>
#include "structdep.h"

#include <QDebug>

class commit
{
public:
    commit();

    void del();
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
    ~History();

    void addCommit(commit& commit);
    void pullBack(QVector<department*>& deps);
    void returnBack(QVector<department*>& deps);
    uint16_t historyLength();
    uint16_t pulledLength();

private:
    QVector<commit> history;
    QVector<commit> pulled;

    void delPulled();
};

#endif // HISTORY_H
