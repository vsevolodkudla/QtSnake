#ifndef USER_H
#define USER_H

#include <QString>
#include <QTime>

class User
{

public:
    User(QString n, QString d, unsigned p);
    User();
    bool operator <(User&);
    bool operator>(User&);
    bool operator <(User*);
    bool operator>(User*);
    QString name;
    QString date;
    long point;
};

#endif // USER_H
