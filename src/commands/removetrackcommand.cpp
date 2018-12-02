#include "include/commands/removetrackcommand.h"

RemoveTrackCommand::RemoveTrackCommand(PlaylistTableWidget* playlistTable, Track& track, int row, QUndoCommand* parent): QUndoCommand(parent)
{
    this->playlistTable = playlistTable;
    this->track = new Track(track);
    this->row = row;
}

RemoveTrackCommand::~RemoveTrackCommand()
{
    if(this->track != nullptr)
    {
        delete this->track;
    }
}

void RemoveTrackCommand::undo()
{
    playlistTable->addTrack(track, row);
}

void RemoveTrackCommand::redo()
{
    playlistTable->removeTrack(row);
}
