#ifndef ABSTRACTREPTILE_H
#define ABSTRACTREPTILE_H

#include <QObject>
#include <QUrl>
#include <QRegExp>
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class AbstractReptile : public QObject
{
    Q_OBJECT
public:
    explicit AbstractReptile(QObject *parent = 0);
    AbstractReptile(QObject *parent,QUrl &initUrl,QRegExp & analysisData,QRegExp & analysisNextUrl);
    void setCurrentUrl(QUrl &url){this->currentUrl=url;}
    void setanalysisDataRegExp(QRegExp & regExp){this->analysisData=regExp;}
    void setanalysisNextUrlRegExp(QRegExp & regExp){this->analysisNextUrl=regExp;}
    ~AbstractReptile();
    //===========
    virtual void save();//保存，继承是若添加数据，需要重写
    virtual void load();//读取保存，继承是若添加数据，需要重写
    //----------------
    virtual void getData(){}
    virtual void getNextUrl(){}
    virtual bool finishWork(){return false;}
private:
    QUrl currentUrl;//当前网址
    QByteArray replyData;//当前请求收到的数据
    QMap<QString,int> allUrl;//所有请求过的网址（解析到的QString数据）
    QMap<QString,int> data;//解析到的数据数据
    QRegExp analysisData;//数据解析规则
    QRegExp analysisNextUrl;//爬取规则
    QNetworkAccessManager * manager;//用于请求网页

//==========================================
    //      发生错误时调用，返回true表示终止
    virtual bool replyError(){this->save(); return true;}
    virtual bool analysisDataError(){this->save(); return true;}
    virtual bool analysisNextUrlError(){this->save(); return true;}
    //========================================
signals:
    void workFinish(const QList<QString> & data);//爬取终止时报告获取的数据
    void updateState(const QString & Msg);//更新请求Url、解析数据时报告进度
    //===================================
    void requestError(const QString & msg);
    void getDataError(const QString & msg);
    void getNextUrlError(const QString & msg);
    void IOError(const QString & msg);

public slots:
    void work();
    void handleReply(QNetworkReply *reply);
};

#endif // ABSTRACTREPTILE_H
