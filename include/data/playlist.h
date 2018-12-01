#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QString>
#include <QList>
#include "include/data/track.h"

class Playlist
{
public:
    Playlist(QString baseUri = "");
    Playlist(Playlist& playlistSource);
    virtual ~Playlist();

    QDir getBaseUriDir();
    QString getBaseUri();
    void setBaseUri(QString baseUri);
    void addTrack(Track* track);
    Track* getTrack(int id);
    void removeTrack(Track* track);
    void removeTrack(int id);
    int getNumberOfTracks();
    bool existsBaseUri();
    void move(int from, int to);

    QList<Track*>::const_iterator getConstIterator();
    QList<Track*>::const_iterator getConstBegin();
    QList<Track*>::const_iterator getConstEnd();

private:
    void freeTrackMemory();

private:
    QDir baseUriDir;
    QList<Track*> tracksList;
};

#endif // PLAYLIST_H
