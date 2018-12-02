#include "include/commands/addtrackcommand.h"

AddTrackCommand::AddTrackCommand(PlaylistTableWidget* playlistTable, Track& track, int row, QUndoCommand* parent): QUndoCommand(parent)
{
    this->playlistTable = playlistTable;
    this->track = track;
    this->row = row;
}

AddTrackCommand::~AddTrackCommand()
{

}

void AddTrackCommand::undo()
{
    playlistTable->removeTrack(row);
}

void AddTrackCommand::redo()
{
    playlistTable->addTrack(new Track(this->track), row);
}
