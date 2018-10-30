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

    QString getBaseUri();
    Track* getTrack(int id);

    QList<Track*>::const_iterator getConstIterator();
    QList<Track*>::const_iterator getConstBegin();
    QList<Track*>::const_iterator getConstEnd();

private:
    void freeTrackMemory();

private:
    QString baseUri;
    QList<Track*>* tracksList;
};

#endif // PLAYLIST_H
