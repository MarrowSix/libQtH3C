#ifndef EAPMESSAGE_H
#define EAPMESSAGE_H

#include "util/export.h"
#include <string>

namespace QH3C {

/*
 * Const Variable of eap protocol
 * Reference: <https://tools.ietf.org/html/rfc3748/>
 */
const char PAE_GROUP_ADDR[] = "\x01\x80\xc2\x00\x00\x03";
const char BROADCAST_ADDR[] = "\xff\xff\xff\xff\xff\xff";

/*
 * Reference: <https://fjkfwz.github.io/2014/12/04/H3C-inode-Linux/>
 * Or catch by Wireshark
 */
const int8_t EAPOL_VERSION = 1;
const int8_t EAPOL_PACKE = 0;

const int8_t EAPOL_TYPE_START = 1;
const int8_t EAPOL_TYPE_LOGOFF = 2;

/*
 * EAP Packet Type:
 * Request      Code Section of EAP is 1
 * Response     Code Section of EAP is 2
 * Success      Code Section of EAP is 3
 * Failure      Code Section of EAP is 4
 */
const int8_t EAP_CODE_REQUEST = 1;
const int8_t EAP_CODE_RESPONSE = 2;
const int8_t EAP_CODE_SUCCESS = 3;
const int8_t EAP_CODE_FAILURE = 4;

/*
 * EAP Packet Data Section Type:
 * Identity         1   represent to query target identity
 * MD5-Challenge    4   represent to MD5-Challenge include md5 code
 *                      in Type Data
 */
const int8_t EAP_TYPE_ID = 1;
const int8_t EAP_TYPE_MD5 = 4;

/*
 * For Unknown reason, have to split the \x07 and the char
 * in the back.
 * Otherwise, the '\x07b' will be parser as '{'.
 */
const std::string VERSION_INFO = std::string("\x06\x07")+std::string("bjQ7SE8BZ3MqHhs3clMregcDY3Y=")+std::string("\x20\x20");

/*
 * Receive Buffer Size
 */
const size_t BUFFER_SIZE = 1600;
const size_t ETHMINFRAME = 64;
const int MD5LEN = 16;

/*
 * Running Dir
 */
const char RUNNING_DIR[] = "/tmp";
const char LOCK_FILE[] = "qth3c.lock";
}

#endif
