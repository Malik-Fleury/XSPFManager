#ifndef PLAYLISTTABLE_H
#define PLAYLISTTABLE_H

#include <QtWidgets>

class PlaylistTable : public QTableView
{
public:
    PlaylistTable(QWidget* parent = 0);
    virtual ~PlaylistTable();

public slots:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private:
    void setupTable();

};

#endif // PLAYLISTTABLE_H
