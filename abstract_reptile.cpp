#include "abstract_reptile.h"
#include <QFile>
#include <QTextStream>


AbstractReptile::AbstractReptile(QObject *parent) : QObject(parent)
{
    manager= new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(handleReply(QNetworkReply*));
    this->load();
}

AbstractReptile::~AbstractReptile()
{
    delete this->manager;
}

void AbstractReptile::save()
{
    QFile file("temp.data");
    if(file.open(QFile::WriteOnly|QFile::Text))
    {
        QTextStream out(&file);
        out<<this->currentUrl.toString()<<"\r\n";
        out<<this->analysisData.pattern()<<"\r\n";
        out<<this->analysisNextUrl.pattern()<<"\r\n";
        for(auto i:this->allUrl.keys())
        {
            out<<i<<"\r\n";
        }
        out<<"\r\n";
        for(auto i:this->data.keys())
        {
            out<<i<<"\r\n";
        }
    }
    else
    {
        emit IOError(QString("Write file error: open fall."));
    }
    file.close();
}

void AbstractReptile::load()
{
    QFile file("temp.data");
    if(!file.exists())
        return;
    if(file.open(QFile::ReadOnly|QFile::Text))
    {
        QTextStream in(&file);
        QString line=in.readLine();
        this->currentUrl.setUrl(line);
        line=in.readLine();
        this->analysisData.setPattern(line);
        line=in.readLine();
        this->analysisNextUrl.setPattern(line);
        line=in.readLine();
        while(line!=QString(""))
        {
            allUrl.insert(line,1);
        }
        line=in.readLine();
        while(!in.atEnd())
        {
            data.insert(line,1);
        }
    }
    else
    {
        emit IOError(QString("Read file error: open fall."));
    }
    file.close();
}

void AbstractReptile::handleReply(QNetworkReply *reply)
{
    if(reply->error()!=QNetworkReply::NoError)//请求错误
    {
        emit requestError(QString("reply error:")+reply->errorString());
        if(this->replyError())
        {
            return;
        }
    }
}

void AbstractReptile::work()
{
    if(this->currentUrl.isEmpty())//Url无效，错误
    {
        emit getNextUrlError(QString("init Url is empty"));
        if(this->analysisNextUrlError())
        {
            return;
        }
    }
    this->manager->get(QNetworkRequest(this->currentUrl));
}

AbstractReptile::AbstractReptile(QObject *parent, QUrl &initUrl, QRegExp &analysisData, QRegExp &analysisNextUrl):QObject(parent)
{
    this->currentUrl=initUrl;
    this->analysisData=analysisData;
    this->analysisNextUrl=analysisNextUrl;
}
