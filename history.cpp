#include "history.h"

void History::addCommit(commit& commit)
{
    pulled.clear();
    history.push_back(commit);
    qDebug() << history.length();
    //qDebug() << commit.getNew()->name << commit.getPrev()->name;
}

void History::pullBack(QVector<department*>& deps)
{
    auto lastCommit = history.last();
    if (lastCommit.getPrev()->name == "")
    {
        qDebug() << "adding";
        for (uint16_t i = 0; i < deps.length(); ++i)
            if (*deps[i] == *lastCommit.getNew())
            {
                qDebug() << deps.length();
                deps.remove(i);
                qDebug() << deps.length();
            }
    }

    else if (lastCommit.getNew()->name == "")
    {
        qDebug() << "deleting";
        deps.push_back(lastCommit.getPrev());
    }

    else
    {
        qDebug() << "changing" << lastCommit.getNew()->empls.length() << lastCommit.getPrev()->empls.length();
        for (uint16_t i = 0; i < deps.length(); ++i)
            if (*deps[i] == *lastCommit.getNew())
            {
                qDebug() << deps[i]->empls.length();
                *deps[i] = *lastCommit.getPrev();
                qDebug() << deps[i]->empls.length();
            }
    }
    pulled.push_back(lastCommit);
    history.removeLast();
}

void History::returnBack(QVector<department *> &deps)
{
    auto lastCommit = pulled.last();
    if (lastCommit.getPrev()->name == "")
    {
        //qDebug() << "adding";
        deps.push_back(lastCommit.getNew());
    }

    else if (lastCommit.getNew()->name == "")
    {
        //qDebug() << "deleting";
        for (uint16_t i = 0; i < deps.length(); ++i)
            if (*deps[i] == *lastCommit.getPrev())
            {
                //qDebug() << deps.length();
                deps.remove(i);
                //qDebug() << deps.length();
            }
    }

    else
    {
        //qDebug() << "changing" << lastCommit.getNew()->empls.length() << lastCommit.getPrev()->empls.length();
        for (uint16_t i = 0; i < deps.length(); ++i)
            if (*deps[i] == *lastCommit.getPrev())
            {
                //qDebug() << deps[i]->empls.length();
                *deps[i] = *lastCommit.getNew();
                //qDebug() << deps[i]->empls.length();
            }
    }
    history.push_back(lastCommit);
    pulled.removeLast();
}

commit::commit()
{
    newDep = new department;
    prevDep = new department;
}

void commit::del()
{
    this->newDep->del();
    this->prevDep->del();
    delete this;
}

department* commit::getNew()
{
    return this->newDep;
}

department* commit::getPrev()
{
    return this->prevDep;
}

void commit::setNew(const department& newDep)
{
    *this->newDep = newDep;
}

void commit::setPrev(const department& prevDep)
{
    *this->prevDep = prevDep;
}

uint16_t History::historyLength()
{
    return history.length();
}

uint16_t History::pulledLength()
{
    return pulled.length();
}

History::History()
{

}

History::~History()
{
    for (auto commit : history)
        commit.del();
    for (auto commit : pulled)
        commit.del();
    //delete  this;
}

void History::delPulled()
{
    for (auto commit : pulled)
        commit.del();
}
