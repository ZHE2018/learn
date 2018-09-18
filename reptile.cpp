#include "reptile.h"

reptile::reptile()
{

}

reptile::~reptile()
{

}

QUrl reptile::captureToUrl(const QString &line, const QUrl &currenturl)
{
    QUrl url;
    QString s=line.section(QRegExp("\"[^\"]*\""),0);
    s.replace(QString("\""),QString(""));
    s=currenturl.url().section(QRegExp("http(s)?://[^/]*"),0)+s;
    url.setUrl(s);
    return url;
}

