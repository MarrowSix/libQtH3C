//
// Created by arshrow on 18-10-24.
//

#ifndef QTH3C_CLIENT_H
#define QTH3C_CLIENT_H

#include <QtH3C>

class Client
{
public:
    Client();
    ~Client();
    bool readConfig(const QString&);
    void setup(const QString &eitf,
               const QString &id,
               const QString &pwd,
               const bool daemon);
    bool start();

private:
    QH3C::Profile profile;
    QH3C::EapAuth *auth;
};


#endif //QTH3C_CLIENT_H
