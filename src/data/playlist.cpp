#include "include/data/playlist.h"

/**
* Playlist
* Constructeur surchargé: URI de base
*
* @param QString baseURI : URI de base (par défaut : "")
*/
Playlist::Playlist(QString baseUri): baseUriDir(baseUri), tracksList()
{
}

/**
* Playlist
* Constructeur de copie (superficielle)
*
* @param Playlist& playlistSource : liste de lecture source à copier
*/
Playlist::Playlist(Playlist& playlistSource)
{
    Playlist(playlistSource.baseUriDir.absolutePath());

    for(auto itrTrack = playlistSource.getConstBegin(); itrTrack != playlistSource.getConstEnd(); itrTrack++)
    {
        Track* track = (Track*)*itrTrack;
        this->tracksList.append(track);
    }
}

/**
* ~Playlist
* Destructeur par défaut: supprime les médias
*/
Playlist::~Playlist()
{
    freeTrackMemory();
}

/**
* getBaseUri
* Description of the function
*
* @return Retourne une QString représentant l'URI de base
*/
QString Playlist::getBaseUri()
{
    return this->getBaseUriDir().path();
}

/**
* getBaseUri
* Description of the function
*
* @return Retourne un QDir représentant l'URI de base
*/
QDir Playlist::getBaseUriDir()
{
    return this->baseUriDir;
}

/**
* setBaseUri
* Permet de modifier l'URI de base
*
* @param QString baseUri : URI de base
*/
void Playlist::setBaseUri(QString baseUri)
{
    this->baseUriDir.setPath(baseUri);
}

/**
* addTrack
* Permet d'ajouter un média dans la liste de lectue
*
* @param Track* track : média à ajouter
* @param int position : position dans la liste de lecture (par défaut : à la fin)
*/
void Playlist::addTrack(Track* track, int position)
{
    if(position < 0)
    {
        this->tracksList.append(track);
    }
    else
    {
        this->tracksList.insert(position, track);
    }
}

/**
* getTrack
* Permet d'obtenir un média à une position spécifique
*
* @param int position : position dans la liste de lecture
* @return média correspondant
*/
Track* Playlist::getTrack(int position)
{
    return tracksList.at(position);
}

/**
* removeTrack
* Permet de retirer un média de la liste de lecture
*
* @param Track* track : média à supprimer
*/
void Playlist::removeTrack(Track* track)
{
    this->tracksList.removeOne(track);
}

/**
* removeTrack
* Permet de retirer un média de la liste de lecture
*
* @param int position : position du média à supprimer
*/
void Playlist::removeTrack(int position)
{
    Track* track = tracksList.at(position);
    delete track;

    this->tracksList.removeAt(position);
}

/**
* getNumberOfTracks
* Permet d'obtenir le nombre de média dans la liste de lecture
*
* @return Nombre de médias dans la liste de lecture
*/
int Playlist::getNumberOfTracks()
{
    return this->tracksList.size();
}

/**
* existsBaseUri
* Permet de vérifier si une URI de base existe
*
* @return Vrai si une URI de base est existant, faux autrement
*/
bool Playlist::existsBaseUri()
{
    return this->getBaseUri() != "." && this->getBaseUri() != "";
}

/**
* move
* Permet de déplacer un média
*
* @param int from : position du média à déplacer
* @param int to : position où déplacer le média
*/
void Playlist::move(int from, int to)
{
    this->tracksList.move(from, to);
}

void Playlist::sort(Sorting sorting, bool descending)
{
    switch(sorting)
    {
        case FILENAME:
            if(!descending)
            {
                std::sort(tracksList.begin(), tracksList.end(), Comparators::compareFilename);
            }
            else
            {
                std::sort(tracksList.begin(), tracksList.end(), Comparators::compareFilenameDescending);
            }
            break;
        case ABSOLUTE_FILE_PATH:
            if(!descending)
            {
                std::sort(tracksList.begin(), tracksList.end(), Comparators::compareAbsolutePath);
            }
            else
            {
                std::sort(tracksList.begin(), tracksList.end(), Comparators::compareAbsolutePathDescending);
            }
            break;
        case OUTPUT_ABSOLUTE_FILE_PATH:
            if(!descending)
            {
                std::sort(tracksList.begin(), tracksList.end(), Comparators::compareAbsoluteOutputPath);
            }
            else
            {
                std::sort(tracksList.begin(), tracksList.end(), Comparators::compareAbsoluteOutputPathDescending);
            }
            break;
        case OUTPUT_RELATIVE_FILE_PATH:
            if(!descending)
            {
                std::sort(tracksList.begin(), tracksList.end(), Comparators::compareRelativeOutputPath);
            }
            else
            {
                std::sort(tracksList.begin(), tracksList.end(), Comparators::compareRelativeOutputPathDescending);
            }
            break;
    }
}

/**
* getConstBegin
* Permet d'obtenir l'itérateur de début de liste
*
* @return Itérateur de début de liste
*/
QList<Track*>::const_iterator Playlist::getConstBegin()
{
    return tracksList.constBegin();
}

/**
* getConstEnd
* Permet d'obtenir l'itérateur de fin de liste
*
* @return Itérateur de fin de liste
*/
QList<Track*>::const_iterator Playlist::getConstEnd()
{
    return tracksList.constEnd();
}

/**
* freeTrackMemory
* Permet de libérer les médias de la liste
*/
void Playlist::freeTrackMemory()
{
    while(!tracksList.empty())
    {
        Track* track =tracksList.takeLast();
        delete track;
    }
}
