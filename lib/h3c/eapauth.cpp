#include "eapauth.h"

QH3C::EapAuth::EapAuth(Profile &profile) :
    profile(profile)
{
    clientSocket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_PAE));
    if (clientSocket < 0) {
        emit this->socketCreateFailed();
    }

    /*
     * use the struct ifreq to get the device index
     */
    memset(&tempIfreq, 0, sizeof(tempIfreq));
    strncpy(tempIfreq.ifr_name, profile.ethInterface().c_str(),
            IFNAMSIZ-1);
    if ((ioctl(clientSocket, SIOCGIFINDEX, &tempIfreq)) < 0) {}
    interfaceIndex = tempIfreq.ifr_ifindex;

    /*
     * use the struct ifreq to get the device mac address
     */
    memset(&tempIfreq, 0, sizeof(tempIfreq));
    strncpy(tempIfreq.ifr_name, profile.ethInterface().c_str(),
            IFNAMSIZ-1);
    if ((ioctl(clientSocket, SIOCGIFHWADDR, &tempIfreq)) < 0) {}
//    strncpy(macAddress, tempIfreq.ifr_hwaddr.sa_data, ETH_ALEN);
    mempcpy(ethernetHeader.h_source, tempIfreq.ifr_hwaddr.sa_data, ETH_ALEN);
    ethernetHeader.h_proto = ETH_P_PAE;
    /*
     * Version Info, get by wireshark
     */
    versionInfo = VERSION_INFO;
}

QH3C::EapAuth::~EapAuth() {

}

void QH3C::EapAuth::serveLoop() {
    try {
        sendStart(PAE_GROUP_ADDR);
        while (true) {
            char *receive = nullptr;
            struct sockaddr saddr;
            int sdrlen = sizeof(saddr);
            ssize_t recvLen = 0;
            try {
                receive = new char[BUFFER_SIZE];
            } catch (std::exception &e) {
                qDebug() << "Allocate Failed " << e.what();
                exit(1);
            }
            recvLen = recvfrom(clientSocket, receive, BUFFER_SIZE, 0, &saddr, (socklen_t *)(&sdrlen));
            eapHandler(receive+sizeof(struct ethhdr), recvLen-sizeof(struct ethhdr));
        }
    } catch (...) {
        qDebug() << "Start EAP Authenticate Failed!";
    }

}

QByteArray QH3C::EapAuth::getEAPOL(int8_t type, std::string &payload) {
    QByteArray tempData;
    QDataStream eapolStream(tempData);
    eapolStream.setByteOrder(QDataStream::BigEndian);
    eapolStream.setVersion(QDataStream::Qt_5_9);

    eapolStream << EAPOL_VERSION << type << (int16_t)payload.size();
    eapolStream.writeRawData(payload.c_str(), payload.size());
    return tempData;
}

QByteArray QH3C::EapAuth::getEAP(int8_t code, int8_t identifer, std::string &data, int8_t type = 0) {
    QByteArray tempData;
    QDataStream eapStream(tempData);
    eapStream.setByteOrder(QDataStream::BigEndian);
    eapStream.setVersion(QDataStream::Qt_5_9);
    if (EAP_CODE_SUCCESS == code || EAP_CODE_SUCCESS == code) {
        eapStream << code << identifer << (int16_t)(2*sizeof(int8_t) + sizeof(int16_t));
    } else if (EAP_CODE_REQUEST == code || EAP_CODE_RESPONSE == code) {
        eapStream << code << identifer << (int16_t)(2*sizeof(int8_t) + sizeof(int16_t) + data.size()) << type;
        eapStream.writeRawData(data.c_str(), data.size());
    }
}

void QH3C::EapAuth::sendStart(const char* dest) {
    mempcpy(ethernetHeader.h_dest, dest, ETH_ALEN);

}

void QH3C::EapAuth::sendLogoff(int8_t id) {

}

void QH3C::EapAuth::sendResponceId(int8_t id) {

}

void QH3C::EapAuth::sendResponceMd5(int8_t id) {

}

void QH3C::EapAuth::socketCreateFailed() {

}

void QH3C::EapAuth::eapHandler(const char *packet, ssize_t len) {
    /*
     * the section of EAPOL header
     */
    int8_t eapolVersion = 0;
    int8_t eapolType = 0;
    uint16_t eapolLength = 0;
    /*
     * the basic section of EAP header
     */
    int8_t eapCode = 0;
    int8_t eapIdentifier = 0;
    int16_t eapLength = 0;
    QByteArray temp = QByteArray::fromRawData(packet, len);
    QDataStream eapIn(temp);

    eapIn >> eapolVersion >> eapolType >> eapolLength;
    eapIn >> eapCode >> eapIdentifier >> eapLength;
    if (EAPOL_PACKE != eapolType) {
        qDebug() << "Got Unknown EAPOL packet type " << eapolType;
    }

    if (EAP_CODE_SUCCESS == eapCode) {
        qDebug() << "Got EAP Success";
    } else if (EAP_CODE_FAILURE == eapCode) {
        qDebug() << "Got EAP Failure";
        exit(-1);
    } else if (EAP_CODE_RESPONSE == eapCode) {
        qDebug() << "Got Unknown EAP Response";
    } else if (EAP_CODE_REQUEST == eapCode) {
        int8_t eapType = 0;
        int eapLen = eapLength - sizeof(int8_t)*3 - sizeof(int16_t);
        char *eapTypeData = new char[eapLen];
        eapIn >> eapType;
        eapIn.readRawData(eapTypeData, eapLen);
        if (EAP_TYPE_ID == eapType) {
            qDebug() << "Got EAP Request for identity";
            sendResponceId(eapIdentifier);
        } else if (EAP_TYPE_MD5 == eapType) {
            qDebug() << "Got EAP Request for MD5-Challenge";
            sendResponceMd5(eapIdentifier);
        }
    }
}
