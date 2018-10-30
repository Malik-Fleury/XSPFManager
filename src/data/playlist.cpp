#include "include/data/playlist.h"

Playlist::Playlist(QString baseUri, QList<Track*>* tracksList)
{
    this->baseUri = baseUri;
    this->tracksList = tracksList;
}

Playlist::~Playlist()
{
    freeTrackMemory();
    delete tracksList;
}



QString Playlist::getBaseUri()
{
    return this->baseUri;
}

Track* Playlist::getTrack(int id)
{
    return tracksList->at(id);
}

QList<Track*>::const_iterator Playlist::getConstBegin()
{
    return tracksList->constBegin();
}

QList<Track*>::const_iterator Playlist::getConstEnd()
{
    return tracksList->constEnd();
}

void Playlist::freeTrackMemory()
{
    for(int i = 0; i < tracksList->size(); i++)
    {
        Track* track = tracksList->at(i);
        delete track;
    }
}
