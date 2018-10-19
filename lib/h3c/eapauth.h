#ifndef EAPAUTH_H
#define EAPAUTH_H

#include "util/export.h"
#include "types/profile.h"
#include "types/eapmessage.h"
#include <QObject>
#include <QtCore>
#include <QDataStream>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <exception>

namespace QH3C {

class QH3C_EXPORT EapAuth : public QObject
{
    Q_OBJECT
public:
    EapAuth(Profile&);
    ~EapAuth();
    void serveLoop();

private:
    QByteArray getEAPOL(int8_t, std::string&);
    QByteArray getEAP(int8_t, int8_t, std::string&, int8_t);
    void sendStart(const char*);
    void sendLogoff(int8_t);
    void sendResponceId(int8_t);
    void sendResponceMd5(int8_t);
    void eapHandler(const char *, ssize_t);

private signals:
    void socketCreateFailed();

private:
    Profile profile;
    int clientSocket;
    int interfaceIndex;
    char macAddress[6];
    struct ifreq tempIfreq;
    struct ethhdr ethernetHeader;
    std::string versionInfo;
};

}

#endif
