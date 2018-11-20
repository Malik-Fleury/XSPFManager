#include "include/window/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    setupMenuActions();
    setupPlaylistTable();

    path = "";
    playlist = nullptr;
}

MainWindow::~MainWindow()
{
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

void MainWindow::setupOtherEvents()
{
    //connect(this->playlistTableView, &QTableView::)
}

void MainWindow::setupPlaylistTable()
{
    this->playlistTable = new PlaylistTable(this);
    this->centralWidget()->layout()->addWidget(playlistTable);
}

void MainWindow::setupPlaylistTableModel()
{
    PlaylistModel* model = new PlaylistModel(this->playlist, this);
    this->playlistTable->setModel(model);
}

void MainWindow::newFile()
{
    this->freeMemoryPlaylist();
    this->playlist = new Playlist();
}

void MainWindow::open()
{
    QString fileToOpen = QFileDialog::getOpenFileName(this, "Open xspf playlist", QString(), "*.xspf");

    if(!fileToOpen.isEmpty())
    {
        xspf.open(fileToOpen);

        this->freeMemoryPlaylist();Wa
        this->playlist = xspf.readPlaylist();

        // Add the data of the playlist to the table
        setupPlaylistTableModel();
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
    xspf.savePlaylist(this->path, *playlist);
}

void MainWindow::saveAs()
{
    QString fileToSave = QFileDialog::getSaveFileName(this, "Save the xspf playlist", QString(), "*.xspf");

    if(!fileToSave.isEmpty())
    {
        this->path = fileToSave;
        this->save();
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

void MainWindow::freeMemoryPlaylist()
{
    if(this->playlist != nullptr)
    {
        delete playlist;
        playlist = nullptr;
    }
}

void MainWindow::dropEventHandler(QDropEvent* event)
{

}
