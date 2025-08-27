#include "space.h"
#include "./ui_space.h"
#include "storage.h"
#include "apirequest.h"

#include <QJsonObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QShortcut>

Space::Space(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::Space) {
    ui->setupUi(this);
    ui->token_input->hide();

    auto* left = new QShortcut(QKeySequence(Qt::Key_Left), this);
    left->setContext(Qt::WidgetShortcut);
    connect(left, &QShortcut::activated, this, [=]() {

    });

    auto* right = new QShortcut(QKeySequence(Qt::Key_Right), this);
    left->setContext(Qt::WidgetShortcut);
    connect(right, &QShortcut::activated, this, [=]() {

    });
}

Space::~Space() {
    delete ui;
}

void Space::on_login_button_clicked() {
    if (! storage.getToken().isEmpty())
    {
        return;
    }

    const QString &account = ui->account_input->text();
    const QString &password = ui->password_input->text();

    auto reply = api_request.login(account, password);


    connect(reply, &QNetworkReply::finished, this, [=]() {
        QByteArray responseData;
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            qDebug() << "Response:" << responseData;
            // 处理成功响应逻辑
            // ui->resp->setText(responseData);
            responseData = reply->readAll();
        } else {
            qDebug() << "Error:" << reply->errorString();
            // 处理错误逻辑
            // ui->resp->setText(reply->errorString());
        }
        reply->deleteLater();

        // 解析 JSON
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData, &parseError);
        if (parseError.error != QJsonParseError::NoError) {
            qWarning() << "JSON parse error:" << parseError.errorString();
            return;
        }

        if (!jsonDoc.isObject()) {
            qWarning() << "Expected JSON object";
            return;
        }

        QJsonObject rootObj = jsonDoc.object();

        // 检查 code == 0
        int code = rootObj.value("code").toInt(-1);
        if (code != 0) {
            qWarning() << "Server returned error code:" << code;
            return;
        }

        // 获取 user.authentication_token
        QJsonObject userObj = rootObj.value("user").toObject();
        QString authToken = userObj.value("authentication_token").toString();

        storage.writeToken(authToken);
    });
}
