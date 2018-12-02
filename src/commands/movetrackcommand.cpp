#include "include/commands/movetrackcommand.h"

MoveTrackCommand::MoveTrackCommand(PlaylistTableWidget* playlistTable, int rowFrom, int rowTo, QUndoCommand* parent): QUndoCommand(parent)
{
    this->playlistTable = playlistTable;
    this->rowFrom = rowFrom;
    this->rowTo = rowTo;
}

MoveTrackCommand::~MoveTrackCommand()
{

}

void MoveTrackCommand::undo()
{
    playlistTable->moveTrack(rowTo, rowFrom);
}

void MoveTrackCommand::redo()
{
    playlistTable->moveTrack(rowFrom, rowTo);
}
