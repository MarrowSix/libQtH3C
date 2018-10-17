#include <net/if.h>
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
    for (int i=0; i<ETH_ALEN; i++) {
        macAddress[i] = tempIfreq.ifr_hwaddr.sa_data[i];
    }

    /*
     * Version Info, get by wireshark
     */
    versionInfo = VERSION_INFO;
}

QH3C::EapAuth::~EapAuth() {

}

void QH3C::EapAuth::serveLoop() {

}

void QH3C::EapAuth::sendStart() {

}

void QH3C::EapAuth::sendLogoff() {

}

void QH3C::EapAuth::sendResponceId() {

}

void QH3C::EapAuth::sendResponceMd5() {

}

void QH3C::EapAuth::socketCreateFailed() {

}
