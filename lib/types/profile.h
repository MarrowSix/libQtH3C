#ifndef PROFILE_H
#define PROFILE_H

#include "util/export.h"
#include <string>
#include <cstdint>

namespace QH3C {

class QH3C_EXPORT Profile {
public:
    Profile();
    Profile(const Profile&);
    Profile(Profile&&);
    ~Profile();

    const std::string& id() const;
    const std::string& password() const;
    const std::string& ethInterface() const;
    const bool isDaemon() const;

    void setId(const std::string& id);
    void setPassword(const std::string& pwd);
    void setEith(const std::string& eitf);
    void setDaemon(const bool& daemon);

private:
    std::string d_id;
    std::string d_pwd;
    std::string d_eitf;
    bool d_daemon;
};

}

#endif
