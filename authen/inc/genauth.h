//
// Created by Tofu on 2025/8/27.
//

#ifndef IISPACEPROXY_AUTHINFOGENERATE_H
#define IISPACEPROXY_AUTHINFOGENERATE_H

#if defined(_WIN32) || defined(_WIN64)
    #ifdef EXPORT_AUTHEN
        #define AUTHEN_API __declspec(dllexport)
    #else
        #define AUTHEN_API __declspec(dllimport)
    #endif
#elif defined(__APPLE__)//todo: check useful or not
    #ifdef EXPORT_AUTHEN
        #define AUTHEN_API __attribute__((visibility("default")))
    #else
        #define AUTHEN_API
    #endif
#endif

#include <string>

class AUTHEN_API AuthInfoGenerator
{
private:
    std::string token;
public:
    explicit
    AuthInfoGenerator(const std::string& token);

    std::tuple<std::string, std::string, std::string> generate();

    void updateToken(std::string newtoken);
};

#endif //IISPACEPROXY_AUTHINFOGENERATE_H