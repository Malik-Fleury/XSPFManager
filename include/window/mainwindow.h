#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

#include "ui_mainwindow.h"
#include "include/tools/xspf.h"
#include "include/widgets/table/playlisttablewidget.h"
#include "include/widgets/panelexport.h"

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
    void enableWidgets(bool enable);

    void newFile();
    void open();
    void save();
    void saveAs();

    void about();

    void freeMemoryPlaylist();

private slots:
    void dropEventHandler(QDropEvent* event);

private:
    PlaylistTableWidget* playlistTable;
    PanelExport* panelExport;

    Xspf xspf;
    QString path;
    Playlist* playlist;
};

#endif // MAINWINDOW_H
