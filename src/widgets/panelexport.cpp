#include "include/widgets/panelexport.h"
#include "ui_panelexport.h"

PanelExport::PanelExport(QWidget *parent) :
    QWidget(parent)
{
    this->setupUi(this);
    this->setupActions();
}

PanelExport::~PanelExport()
{
}

PlaylistModel* PanelExport::getPlaylistModel()
{
    return model;
}

void PanelExport::setPlaylistModel(PlaylistModel* playlistModel)
{
    model = playlistModel;
}

void PanelExport::setupActions()
{
    connect(buttonChooseOutputFile, &QPushButton::pressed, this, &PanelExport::chooseOutputFile);
    connect(buttonExport, &QPushButton::pressed, this, &PanelExport::exportFiles);
}

void PanelExport::chooseOutputFile()
{
    QString outputFilePath = QFileDialog::getSaveFileName(this, "Save the xspf playlist", QString(), "*.xspf");

    if(!outputFilePath.isEmpty())
    {
        this->lineEditOutputFile->setText(outputFilePath);
    }
}

void PanelExport::exportFiles()
{
    QFileInfo outputFileInfo(lineEditOutputFile->text());
    Playlist* playlist = model->getPlaylist();
    QProgressDialog progressBarDialog("Copying files...", "Cancel",0, 100, this);
    progressBarDialog.setWindowModality(Qt::WindowModal);

    progressBarDialog.show();

    if(!this->lineEditUri->text().isEmpty())
    {
        QString newUri = this->lineEditUri->text();
        playlist->setBaseUri(newUri);
    }

    int i = 0;
    for(auto itr = playlist->getConstBegin(); itr != playlist->getConstEnd(); itr++)
    {
        Track* track = (Track*)*itr;
        QString newAbsoluteFilePath = outputFileInfo.absolutePath() + QDir::separator() + track->getFilename();
        QFile::copy(track->getAbsoluteFilePath(), newAbsoluteFilePath);
        progressBarDialog.setValue(i++);
    }

    Xspf xspf;
    xspf.savePlaylist(outputFileInfo.absoluteFilePath(), *playlist);

    QMessageBox::information(this, "Copy", "Copy process is done.",
                             QMessageBox::Ok);
}
