#ifndef TRACK_H
#define TRACK_H

#include <QString>
#include <QMap>
#include <QList>
#include <QDebug>

class Track
{
public:
    Track();
    ~Track();

    void addData(QString key, QString data);
    void showDebugData();
    QString getDataFromKey(QString& key);

    QMap<QString, QString>::key_iterator getConstBegin();
    QMap<QString, QString>::key_iterator getConstEnd();

private:
    QMap<QString, QString>* dataMap;
};

#endif // TRACK_H
