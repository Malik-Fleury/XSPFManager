#include "include/data/playlist.h"

Playlist::Playlist(QString baseUri): baseUriDir(baseUri), tracksList()
{
}

Playlist::Playlist(Playlist& playlistSource)
{
    Playlist(playlistSource.baseUriDir.absolutePath());

    for(auto itrTrack = playlistSource.getConstBegin(); itrTrack != playlistSource.getConstEnd(); itrTrack++)
    {
        Track* track = (Track*)*itrTrack;
        this->tracksList.append(track);
    }
}

Playlist::~Playlist()
{
    freeTrackMemory();
}

QString Playlist::getBaseUri()
{
    return this->getBaseUriDir().path();
}

QDir Playlist::getBaseUriDir()
{
    return this->baseUriDir;
}

void Playlist::addTrack(Track* track)
{
    this->tracksList.append(track);
}

Track* Playlist::getTrack(int id)
{
    return tracksList.at(id);
}

void Playlist::removeTrack(Track* track)
{
    this->tracksList.removeOne(track);
}

int Playlist::getNumberOfTracks()
{
    return this->tracksList.size();
}

bool Playlist::existsBaseUri()
{
    return this->getBaseUri() != ".";
}

QList<Track*>::const_iterator Playlist::getConstBegin()
{
    return tracksList.constBegin();
}

QList<Track*>::const_iterator Playlist::getConstEnd()
{
    return tracksList.constEnd();
}

void Playlist::freeTrackMemory()
{
    while(!tracksList.empty())
    {
        Track* track =tracksList.takeLast();
        delete track;
    }
}
