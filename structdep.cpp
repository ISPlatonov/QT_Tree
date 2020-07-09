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
    return (left.name == right.name && left.empls == right.empls);
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
    this->empls = right.empls;

    return *this;
}
