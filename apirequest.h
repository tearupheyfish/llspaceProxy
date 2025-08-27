//
// Created by Tofu on 25-8-3.
//

#ifndef APIREQUEST_H
#define APIREQUEST_H

#include <QtNetwork/QNetworkAccessManager>
class APIRequest {
    static std::unique_ptr<QNetworkAccessManager> networkmanager;
    void addAuthenInfo(QNetworkRequest& req);
public:
    QNetworkReply* login(const QString& account, const QString& password);
    QNetworkReply* initArd();
};
extern APIRequest api_request;
#endif //APIREQUEST_H
