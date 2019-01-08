#include "include/commands/addtrackcommand.h"

/**
* AddTrackCommand
* Constructeur surchargé: composant graphique gérant la liste de lecture, la piste a ajouter, la ligne et un parent
*
* @param PlaylistTableWidget* playlistTable : Table qui s'occupe de gérer la liste de lecture
* @param Track& track: Média à ajouter
* @param int row: Ligne sur laquelle ajouter le média
* @param QUndoCommand* parent: Parent
*/
AddTrackCommand::AddTrackCommand(PlaylistTableWidget* playlistTable, Track& track, int row, QUndoCommand* parent): QUndoCommand(parent)
{
    this->playlistTable = playlistTable;
    this->track = track;
    this->row = row;
}

/**
* ~AddTrackCommand
* Destructeur par défaut
*/
AddTrackCommand::~AddTrackCommand()
{

}

/**
* undo
* Permet de revenir en arrière en retirant le média
*/
void AddTrackCommand::undo()
{
    playlistTable->removeTrack(row);
}

/**
* redo
* Permet de (re)faire l'ajout du média
*/
void AddTrackCommand::redo()
{
    playlistTable->addTrack(new Track(this->track), row);
}
