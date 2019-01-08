#include "include/commands/movetrackcommand.h"

/**
* MoveTrackCommand
* Constructeur surchargé: composant graphique gérant la liste de lecture, la ligne de départ, la ligne d'arrivée et un parent
*
* @param PlaylistTableWidget* playlistTable : Table qui s'occupe de gérer la liste de lecture
* @param int rowFrom: Ligne qui va être déplacée
* @param int rowTo: Ligne où est déplacée le média
* @param QUndoCommand* parent: Parent
*/
MoveTrackCommand::MoveTrackCommand(PlaylistTableWidget* playlistTable, int rowFrom, int rowTo, QUndoCommand* parent): QUndoCommand(parent)
{
    this->playlistTable = playlistTable;
    this->rowFrom = rowFrom;
    this->rowTo = rowTo;
}

/**
* ~MoveTrackCommand
* Destructeur par défaut
*/
MoveTrackCommand::~MoveTrackCommand()
{

}


/**
* undo
* Permet de revenir en arrière et de déplacer le média à sa position précédente
*/
void MoveTrackCommand::undo()
{
    playlistTable->moveTrack(rowTo, rowFrom);
}

/**
* redo
* Permet de (re)faire un déplacement d'un média
*/
void MoveTrackCommand::redo()
{
    playlistTable->moveTrack(rowFrom, rowTo);
}
