//
// Created by Tofu on 2025/8/27.
//

#ifndef IISPACEPROXY_AUTHINFOGENERATE_H
#define IISPACEPROXY_AUTHINFOGENERATE_H

#include <string>

class AuthInfoGenerator
{
private:
    std::string token;
    static const std::string magic;
public:
    explicit
    AuthInfoGenerator(const std::string& token);

    std::tuple<std::string, std::string, std::string> generate();

    void updateToken(std::string newtoken);
};

#endif //IISPACEPROXY_AUTHINFOGENERATE_H