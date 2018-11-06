#include "include/window/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    setupMenuActions();
    setupPlaylistTable();

    xspf = nullptr;
    path = "";
}

MainWindow::~MainWindow()
{
    // Delete the Xspf
    if(xspf != nullptr)
    {
        delete xspf;
    }
}

void MainWindow::setupMenuActions()
{
    // File
    connect(menuFileNew, &QAction::triggered, this, &MainWindow::newFile);
    connect(menuFileOpen, &QAction::triggered, this, &MainWindow::open);
    connect(menuFileSave, &QAction::triggered, this, &MainWindow::save);
    connect(menuFileSaveAs, &QAction::triggered, this, &MainWindow::saveAs);
    connect(menuFileQuit, &QAction::triggered, this, &QApplication::quit);

    // Edit
    connect(menuEditUndo, &QAction::triggered, this, &MainWindow::undo);
    connect(menuEditRedo, &QAction::triggered, this, &MainWindow::redo);

    // Language
    // Not available now

    // Help
    connect(menuHelpAbout, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::setupPlaylistTable()
{
    PlaylistModel* model = new PlaylistModel(this);
    this->playlistTableView->setModel(model);

    this->playlistTableView->horizontalHeader()->setSectionsMovable(true);
    this->playlistTableView->verticalHeader()->setSectionsMovable(true);

    this->playlistTableView->verticalHeader()->setDragDropMode(QAbstractItemView::InternalMove);
    this->playlistTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MainWindow::newFile()
{
    xspf = new Xspf();
}

void MainWindow::open()
{
    QString fileToOpen = QFileDialog::getOpenFileName(this, "Open xspf playlist", QString(), "*.xspf");

    if(!fileToOpen.isEmpty())
    {
        xspf = new Xspf(fileToOpen);
        Playlist playlist = xspf->readPlaylist();

        // Add the data of the playlist to the table
    }
}

void MainWindow::save()
{
    // If the path is not already set, we ask to the user where to save
    if(this->path.isEmpty())
    {
        this->saveAs();
    }

    // Save the XSPF (need table)
    //xspf->savePlaylist(this->path, /*playlist to save*/);
}

void MainWindow::saveAs()
{
    QString fileToSave = QFileDialog::getSaveFileName(this, "Save the xspf playlist", QString(), "*.xspf");

    if(!fileToSave.isEmpty())
    {
        this->path = fileToSave;
    }
}

void MainWindow::undo()
{
}

void MainWindow::redo()
{
}

void MainWindow::about()
{
    QMessageBox::about(this, "XSPF-Manager", "Auteur: Malik Fleury \nVersion: 1");
}
