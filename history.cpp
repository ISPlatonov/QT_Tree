#include "history.h"

History::History()
{

}

void History::addCommit(commit& commit)
{
    history.push_back(commit);
    qDebug() << history.length();
    qDebug() << commit.getNew()->name << commit.getPrev()->name;
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

    history.removeLast();
}

commit::commit()
{
    newDep = new department;
    prevDep = new department;
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
