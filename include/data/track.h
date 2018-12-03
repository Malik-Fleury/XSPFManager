#ifndef TRACK_H
#define TRACK_H

#include <QString>
#include <QMap>
#include <QList>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

class Track
{
public:
    Track(QString absoluteFilePath = "");
    Track(QString uriBase, QString relativePath);
    Track(Track& trackSource);
    virtual ~Track();

    QString getFilename();
    QString getAbsolutePath();
    QString getAbsoluteFilePath();
    QString getRelativeFilePath(QDir& absolutePathDir);

    void setAbsoluteFilePath(QString absoluteFilePath);

    static QString generateAbsolutePath(QString baseUri, QString relativePath);

private:
    QFileInfo fileInfo;
};

#endif // TRACK_H
