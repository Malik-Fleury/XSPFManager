#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "include/widgets/playlisttable.h"
#include "include/widgets/panelexport.h"
#include "ui_mainwindow.h"
#include "include/tools/xspf.h"
#include "include/data/playlistmodel.h"

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void setupMenuActions();
    void setupOtherEvents();
    void setupPlaylistTable();
    void setupPanelExport();
    void setupPlaylistTableModel();

    void newFile();
    void open();
    void save();
    void saveAs();

    void undo();
    void redo();

    void about();

    void freeMemoryPlaylist();

private slots:
    void dropEventHandler(QDropEvent* event);

private:
    PlaylistTable* playlistTable;
    PanelExport* panelExport;

    Xspf xspf;
    QString path;
    Playlist* playlist;
};

#endif // MAINWINDOW_H
