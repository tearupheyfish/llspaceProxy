//
// Created by Tofu on 2025/8/12.
//

#ifndef IISPACEPROXY_STORAGE_H
#define IISPACEPROXY_STORAGE_H

#include <qt6keychain/keychain.h>

inline class
{
    std::optional<QString> token{};
public:
    /// 如果token不存在则返回空
    QString getToken()
    {
        if (!token.has_value())
        {
            QKeychain::ReadPasswordJob readjob("read_token");
            readjob.setKey("pupupu.db.authentication_token");
            token = readjob.textData();
        }
        return *token;
    }
    void writeToken(const QString& token)
    {
        QKeychain::WritePasswordJob writejob("write_token");
        writejob.setKey("pupupu.db.authentication_token");
        writejob.setTextData(token);

        this->token = token;
    }
}storage;

#endif //IISPACEPROXY_STORAGE_H