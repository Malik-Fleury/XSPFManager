#ifndef MOVETRACKCOMMAND_H
#define MOVETRACKCOMMAND_H

#include <QUndoCommand>
#include "include/widgets/table/playlisttablewidget.h"

class MoveTrackCommand : public QUndoCommand
{
public:
    MoveTrackCommand(PlaylistTableWidget* playlistTable, int rowFrom, int rowTo, QUndoCommand* parent = 0);
    virtual ~MoveTrackCommand();

    void undo() override;
    void redo() override;

private:
    PlaylistTableWidget* playlistTable;
    int rowFrom;
    int rowTo;
};

#endif // MOVETRACKCOMMAND_H
