#include "profile.h"

QH3C::Profile::Profile()
{
}

QH3C::Profile::Profile(const QH3C::Profile &b) :
    d_id(b.d_id),
    d_pwd(b.d_pwd),
    d_eitf(b.d_eitf)
{
}

QH3C::Profile::Profile(QH3C::Profile &&b) :
    d_id(std::move(b.d_id)),
    d_pwd(std::move(b.d_pwd)),
    d_eitf(std::move(b.d_eitf))
{
}

QH3C::Profile::~Profile()
{
}

const std::string &QH3C::Profile::id() const
{
    return d_id;
}

const std::string &QH3C::Profile::password() const
{
    return d_pwd;
}

const std::string &QH3C::Profile::ethInterface() const
{
    return d_eitf;
}

void QH3C::Profile::setId(const std::string &id)
{
    d_id = id;
}

void QH3C::Profile::setPassword(const std::string &pwd)
{
    d_pwd = pwd;
}

void QH3C::Profile::setEith(const std::string &eitf)
{
    d_eitf = eitf;
}
