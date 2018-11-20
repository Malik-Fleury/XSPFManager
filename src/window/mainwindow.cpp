#include "include/window/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    QString path = "playlist/WOA2018_base_relatif.xspf";
    Xspf xspf(path);
    Playlist playlist = xspf.readPlaylist();
    xspf.savePlaylist("./test.xspf", playlist);
}

MainWindow::~MainWindow()
{
}
