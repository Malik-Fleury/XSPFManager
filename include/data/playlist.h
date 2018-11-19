#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QString>
#include <QList>
#include "include/data/track.h"

class Playlist
{
public:
    Playlist(QString baseUri, QList<Track*>* tracksList);
    ~Playlist();

    QDir getBaseUriDir();
    QString getBaseUri();
    Track* getTrack(int id);
    bool existsBaseUri();

    QList<Track*>::const_iterator getConstIterator();
    QList<Track*>::const_iterator getConstBegin();
    QList<Track*>::const_iterator getConstEnd();

private:
    void freeTrackMemory();

private:
    QDir baseUriDir;
    QList<Track*>* tracksList;
};

#endif // PLAYLIST_H
