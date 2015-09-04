#include "user.h"

User::User(QString n, QString d, unsigned p) : name(n), date(d), point(p)
{

}

bool User::operator <(User &b)
{
    if(point < b.point)
        return true;
    return false;
}
bool User::operator >(User &b)
{
    if(point > b.point)
        return true;
    return false;
}
bool User::operator <(User *b)
{
    if(point < b->point)
        return true;
    return false;
}
bool User::operator >(User *b)
{
    if(point > b->point)
        return true;
    return false;
}
User::User()
{

}
