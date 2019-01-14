#ifndef MOVETRACKCOMMAND_H
#define MOVETRACKCOMMAND_H

#include <QUndoCommand>
#include "include/widgets/table/playlisttablewidget.h"

/**
* Classe de commande permettant de modifier la position du média dans la liste de lecture.
* Elle est utilisée dans le cas du undo/redo.
*
* @author	Malik Fleury
* @version	1
*/
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
