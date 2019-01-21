#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QtWidgets>
#include <QUndoStack>

#include "include/data/playlist.h"

class AddTrackCommand;
class MoveTrackCommand;
class RemoveTrackCommand;

/**
* Widget permettant d'afficher la liste de lecture sous forme d'une table.
*
* @author	Malik Fleury
* @version	1
*/
class PlaylistTableWidget : public QTableWidget
{
public:
    PlaylistTableWidget(QWidget* parent = 0);
    virtual ~PlaylistTableWidget();

    void fill(Playlist* playlist);

    void addTrack(Track* track, int position = -1);
    void removeSelectedTracks();
    void removeTrack(int row);
    void moveTrack(int rowFrom, int rowTo);

    void addRow(Track* track, int rowNumber = -1);
    QList<QTableWidgetItem*> takeRow(int row);
    void setRow(int row, const QList<QTableWidgetItem*>& rowItems);

public slots:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void changeEvent(QEvent* event) override;

    void undo();
    void redo();

    void updateOutputFields(QString playlistOutputFilePath);
    void sortColumn(int logicalIndex);
    void sortChanged(int logicalIndex, Qt::SortOrder order);


    void configureHeaders();
private:
    void configureTable();
    void setupFormats();
    void move(QDropEvent* event);
    void addTracksFromOutside(QDropEvent* event);
    void addTrackDragAndDrop(QFileInfo& fileInfo, int rowTo);

private:
    Playlist* playlist;
    QStringList listFormats;

    QUndoStack commandStack;
    QStack<int> undoNumberOfSteps;
    QStack<int> redoNumberOfSteps;
};

#include "include/commands/addtrackcommand.h"
#include "include/commands/movetrackcommand.h"
#include "include/commands/removetrackcommand.h"

#endif // PLAYLISTWIDGET_H
