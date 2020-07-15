#include "structdep.h"

bool operator==(const empl& left, const empl& right)
{
    return (left.sal == right.sal &&
            left.func == right.func &&
            left.name == right.name &&
            left.surname == right.surname &&
            left.midname == right.midname);
}

bool operator==(const department& left, const department& right)
{
    //qDebug() << left.name << right.name;

    if (left.name != right.name)
        return 0;

    if (left.empls.length() != right.empls.length())
        return 0;
    for (uint16_t i = 0; i < left.empls.length(); ++i)
    {
        if (left.empls[i]->fio() != right.empls[i]->fio() ||
                left.empls[i]->sal != right.empls[i]->sal ||
                left.empls[i]->func != right.empls[i]->func)
        {
            return 0;
        }
    }
    return 1;

    //return (left.name == right.name && &left.empls == &right.empls);
}

empl& empl::operator=(const empl& right)
{
    this->name = right.name;
    this->surname = right.surname;
    this->midname = right.midname;
    this->sal = right.sal;
    this->func = right.func;

    return *this;
}

department& department::operator=(const department& right)
{
    this->name = right.name;
    //this->empls = right.empls;
    this->newPtrEmplVector(right.empls);

    return *this;
}

/*department::~department()
{
    name.~QString();
    empls.~QVector();
}*/

/*QVector<empl*>& operator=(const QVector<empl*>& right)
{
    for (auto empl : right)
    {
        this->
    }
}*/

void department::newPtrEmplVector(const QVector<empl*>& v)
{
    this->empls.clear();
    for (auto emplPtr : v)
    {
        this->empls.push_back(new empl);
        *this->empls.last() = *emplPtr;
    }
}

//have to be overloaded
/*bool operator==(const QVector<empl*>& left, const QVector<empl*>& right)
{
    if (left.length() != right.length())
        return 0;
    for (uint16_t i = 0; i < left.length(); ++i)
    {
        if (left[i]->fio() != right[i]->fio() || left[i]->sal != right[i]->sal || left[i]->func != right[i]->func)
        {
            for (auto empl : left)
                qDebug() << empl->fio() << empl->sal << empl->func;
            for (auto empl : right)
                qDebug() << empl->fio() << empl->sal << empl->func;
            return 0;
        }
    }
    qDebug() << "eqv!!!";
    return 1;
}*/

void empl::del()
{
    name.~QString();
    surname.~QString();
    midname.~QString();
    sal.~QString();
    func.~QString();
    delete this;
}

void department::del()
{
    name.~QString();
    for (auto empl : empls)
        empl->del();
    delete this;
}
