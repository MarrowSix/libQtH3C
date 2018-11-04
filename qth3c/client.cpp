//
// Created by arshrow on 18-10-24.
//

#include <unistd.h>
#include "client.h"

Client::Client()
    : auth(nullptr)
{
}

Client::~Client() {
    delete auth;
}


bool Client::readConfig(const QString &file)
{
    QFile c(file);
    if (!c.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QDebug(QtMsgType::QtCriticalMsg).noquote() << "Can't open configuration file"
            << file;
        return false;
    }
    if (!c.isReadable()) {
        QDebug(QtMsgType::QtCriticalMsg).noquote()
            << "Configuration file" << file << "is not readable!";
        return false;
    }

    QJsonParseError error;
    QJsonDocument confJson = QJsonDocument::fromJson(c.readAll(), &error);
    c.close();
    QJsonObject confObj = confJson.object();
    if (error.error != QJsonParseError::NoError) {
        qCritical() << "Failed to parse configuration file:" << error.errorString();
        return false;
    }

    profile.setEith(confObj["ether_interface"].toString().toStdString());
    profile.setId(confObj["identify_id"].toString().toStdString());
    profile.setPassword(confObj["password"].toString().toStdString());
    profile.setDaemon(confObj["daemon"].toBool());

    return true;
}

void Client::setup(const QString &eitf,
                   const QString &id,
                   const QString &pwd,
                   const bool daemon)
{
    profile.setId(id.toStdString());
    profile.setPassword(pwd.toStdString());
    profile.setEith(eitf.toStdString());
    profile.setDaemon(daemon);
}

bool Client::start() {
    if (0 != getuid()) {
        QDebug(QtMsgType::QtInfoMsg).noquote() << "Permission Denied! Please try to use \"sudo\"";
        exit(-1);
    }
    auth = new QH3C::EapAuth(profile, QH3C::PAE_GROUP_ADDR);
    auth->serveLoop();
    return true;
}
