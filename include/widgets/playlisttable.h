#ifndef PLAYLISTTABLE_H
#define PLAYLISTTABLE_H

#include <QtWidgets>

class PlaylistTable : public QTableView
{
public:
    PlaylistTable(QWidget* parent = 0);
    virtual ~PlaylistTable();

    void addTrack(QString absoluteFilePath);
    void removeTrack();

public slots:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private:
    void setupTable();
    void setupFormats();

private:
    QStringList listFormats;
};

#endif // PLAYLISTTABLE_H
