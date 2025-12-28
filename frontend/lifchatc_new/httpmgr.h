#ifndef HTTPMGR_H
#define HTTPMGR_H
#include "singleton.h"
#include <QString>
#include <QUrl>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>
#include <QJsonDocument>

// 使用单例模式的HTTP管理器
class HttpMgr : public QObject, public Singleton<HttpMgr>,public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT
public:
    ~HttpMgr();
    void PostHttpReq(QUrl url,QJsonObject json,ReqId req_id,Modules mod);
private:
    // 网络访问管理器实例
    QNetworkAccessManager m_networkManager;
    HttpMgr();
    // 友元声明，允许Singleton访问私有构造函数
    friend class Singleton<HttpMgr>;

private slots:
    void slot_http_finish(ReqId id,QString res,ErrorCodes err,Modules mod);
signals:
    void sig_http_finish(ReqId id,QString res,ErrorCodes err,Modules mod);
    void sig_reg_mod_finish(ReqId id,QString res ,ErrorCodes err);

};

#endif // HTTPMGR_H
