#ifndef XSPFPLAYLIST_H
#define XSPFPLAYLIST_H

#include <QtWidgets>
#include "pugixml.hpp"

#include "include/data/playlist.h"

class Xspf
{
public:
    Xspf();
    Xspf(QString& filePath);
    ~Xspf();

    Playlist readPlaylist();
    void savePlaylist(QString filename, Playlist& playlist);

private:
    void open(QString& filePath);
    void close();

    QString getBaseUri();
    QList<Track*>* getTracks();

private:
    pugi::xml_document* doc;
};

#endif // XSPFPLAYLIST_H
