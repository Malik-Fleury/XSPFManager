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

    //void addData(QString key, QString data);
    //QString getDataFromKey(QString& key);
    //QMap<QString, QString>::key_iterator getConstBegin();
    //7QMap<QString, QString>::key_iterator getConstEnd();

private:
    QFileInfo fileInfo;
    //QMap<QString, QString>* dataMap;
};

#endif // TRACK_H
