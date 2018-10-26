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
    EapAuth();
    EapAuth(Profile&, const char*);
    ~EapAuth();
    void serveLoop();

private:
    void getEthrIndex(int sock);
    const char* getEthrMacAddress(int sock);
    QByteArray getEAPOL(int8_t, const QByteArray&);
    QByteArray getEAP(int8_t, int8_t, const QByteArray&, int8_t);
    ssize_t sendStart(const char*);
    void daemonlize();
    void sendLogoff(int8_t);
    void sendResponceId(int8_t);
    void sendResponceMd5(int8_t, QByteArray&);
    void eapHandler(const char *, ssize_t);

signals:
    void socketCreateFailed();

private:
    Profile profile;
    int clientSocket;
    int interfaceIndex;
    QByteArray temp;
    struct ifreq tempIfreq;
    struct ethhdr ethernetHeader;
    struct sockaddr_ll sadr_ll;
    std::string versionInfo;
};

}

#endif
