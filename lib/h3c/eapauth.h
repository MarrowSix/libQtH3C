#ifndef EAPAUTH_H
#define EAPAUTH_H

#include "util/export.h"
#include "types/profile.h"
#include "types/eapmessage.h"
#include <QObject>
#include <QDataStream>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netinet/in.h>

namespace QH3C {

class QH3C_EXPORT EapAuth : public QObject
{
    Q_OBJECT
public:
    EapAuth(Profile&);
    ~EapAuth();
    void serveLoop();

private:
    void sendStart();
    void sendLogoff();
    void sendResponceId();
    void sendResponceMd5();

private signals:
    void socketCreateFailed();

private:
    Profile profile;
    int clientSocket;
    int interfaceIndex;
    unsigned char macAddress[6];
    struct ifreq tempIfreq;
    std::string versionInfo;
};

}

#endif
