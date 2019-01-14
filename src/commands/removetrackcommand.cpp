#include "include/commands/removetrackcommand.h"

/**
* RemoveTrackCommand
* Constructeur surchargé: composant graphique gérant la liste de lecture, la piste a ajouter, la ligne et un parent
*
* @param PlaylistTableWidget* playlistTable : Table qui s'occupe de gérer la liste de lecture
* @param Track& track: Média à retirer
* @param int row: Ligne du média à retirer
* @param QUndoCommand* parent: Parent
*/
RemoveTrackCommand::RemoveTrackCommand(PlaylistTableWidget* playlistTable, Track& track, int row, QUndoCommand* parent): QUndoCommand(parent)
{
    this->playlistTable = playlistTable;
    this->track = new Track(track);
    this->row = row;
}

/**
* RemoveTrackCommand
* Destructeur par défaut
*/
RemoveTrackCommand::~RemoveTrackCommand()
{
    if(this->track != nullptr)
    {
        delete this->track;
    }
}

/**
* undo
* Permet de revenir en arrière et ajoutant le média retiré
*/
void RemoveTrackCommand::undo()
{
    playlistTable->addTrack(track, row);
}

/**
 * redo
 * Permet de (re)faire une suppression d'un média
 */
void RemoveTrackCommand::redo()
{
    playlistTable->removeTrack(row);
}
