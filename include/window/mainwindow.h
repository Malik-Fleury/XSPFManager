#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

#include "ui_mainwindow.h"
#include "include/tools/xspf.h"
#include "include/widgets/table/playlisttablewidget.h"
#include "include/widgets/panelexport.h"

/**
* Classe représentant la fenêtre principale de l'application
*
* @author	Malik Fleury
* @version	1
*/
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

    void loadLanguage(const QString& languageFile);
    void changeLanguage(QAction* action);

    void about();

    void freeMemoryPlaylist();

private slots:
    void dropEventHandler(QDropEvent* event);

private:
    QActionGroup* languagesActGroup;
    PlaylistTableWidget* playlistTable;
    PanelExport* panelExport;

    Xspf xspf;
    QString path;
    Playlist* playlist;

    const QString FRENCH_FILE = "xspfmanager_fr.qm";
    const QString ENGLISH_FILE = "xspfmanager_en.qm";
};

#endif // MAINWINDOW_H
