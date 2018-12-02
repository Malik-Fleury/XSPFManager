#ifndef REMOVETRACKCOMMAND_H
#define REMOVETRACKCOMMAND_H

#include <QUndoCommand>
#include "include/widgets/table/playlisttablewidget.h"
#include "include/data/track.h"

class RemoveTrackCommand : public QUndoCommand
{
public:
    RemoveTrackCommand(PlaylistTableWidget* playlistTable, Track& track, int row = -1, QUndoCommand* parent = 0);
    virtual ~RemoveTrackCommand();

    void undo() override;
    void redo() override;

private:
    PlaylistTableWidget* playlistTable;
    Track* track;
    int row;
};

#endif // REMOVETRACKCOMMAND_H
