#ifndef ADDTRACKCOMMAND_H
#define ADDTRACKCOMMAND_H

#include <QtWidgets>
#include <QUndoCommand>
#include "include/data/track.h"
#include "include/widgets/table/playlisttablewidget.h"

/**
* Classe de commande permettant d'ajouter ou retirer un média de la liste de lecture.
* Elle est utilisée dans le cas du undo/redo.
*
* @author	Malik Fleury
* @version	1
*/
class AddTrackCommand : public QUndoCommand
{
public:
    AddTrackCommand(PlaylistTableWidget* playlistTable, Track& track, int row = -1, QUndoCommand* parent = 0);
    virtual ~AddTrackCommand();

    void undo() override;
    void redo() override;

private:
    PlaylistTableWidget* playlistTable;
    Track track;
    int row;
};

#endif // ADDTRACKCOMMAND_H
