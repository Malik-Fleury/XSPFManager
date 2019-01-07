#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QString>
#include <QList>
#include "include/data/track.h"
#include "include/widgets/table/comparators.h"

enum Sorting
{
    FILENAME = 0,
    ABSOLUTE_FILE_PATH = 1,
    RELATIVE_FILE_PATH = 2
};

class Playlist
{
public:
    Playlist(QString baseUri = "");
    Playlist(Playlist& playlistSource);
    virtual ~Playlist();

    QDir getBaseUriDir();
    QString getBaseUri();
    void setBaseUri(QString baseUri);
    void addTrack(Track* track, int position = -1);
    Track* getTrack(int id);
    void removeTrack(Track* track);
    void removeTrack(int id);
    int getNumberOfTracks();
    bool existsBaseUri();
    void move(int from, int to);
    void sort(Sorting sorting);

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
