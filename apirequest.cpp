//
// Created by Tofu on 25-8-3.
//

#include "apirequest.h"
#include "genauth.h"
#include "storage.h"

APIRequest api_request;
std::unique_ptr<QNetworkAccessManager> APIRequest::networkmanager;
std::optional<AuthInfoGenerator> generator;

void APIRequest::addAuthenInfo(QNetworkRequest& req)
{
    static const QString CLIENT_VERSION = "1222";
    static const QString PLATFORM = "ard";

    req.setRawHeader("CLIENT_VERSION", CLIENT_VERSION.toUtf8());
    req.setRawHeader("PLATFORM", PLATFORM.toUtf8());
    req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");

    if (!generator)
        generator = AuthInfoGenerator(storage.getToken().toStdString());

    auto [auth, salt, sign] = generator->generate();

    //stdstring 2 qstring
    if (!auth.empty())
        req.setRawHeader("Authorization", QString::fromStdString(auth).toUtf8());
    req.setRawHeader("salt", QString::fromStdString(salt).toUtf8());
    req.setRawHeader( "sign", QString::fromStdString(sign).toUtf8());
}

QNetworkReply* APIRequest::login(const QString& account, const QString& password)
{
    QNetworkRequest req(QUrl("https://api.llspace.com/api/1/users/sign_in"));

    addAuthenInfo(req);

    QString req_body = QString("account=%1&password=%2").arg(account, password);
    QByteArray req_body_bytes = req_body.toUtf8();

    return networkmanager->post(req, req_body_bytes);
}
