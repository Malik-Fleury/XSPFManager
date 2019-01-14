#ifndef TRACK_H
#define TRACK_H

#include <QString>
#include <QMap>
#include <QList>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

/**
* Classe représentant un média
*
* @author	Malik Fleury
* @version	1
*/
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

    QString getOutputRelativeFilePath();
    void setOutputRelativeFilePath(QString outputRelFilePath);

    static QString generateAbsolutePath(QString baseUri, QString relativePath);

private:
    QFileInfo fileInfo;
    QFileInfo fileOutput;
};

#endif // TRACK_H
