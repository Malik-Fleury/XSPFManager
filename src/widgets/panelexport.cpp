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

    Playlist* playlist = playlistModel->getPlaylist();
    if(playlist->existsBaseUri())
    {
        this->checkBoxUri->setChecked(true);
        this->lineEditUri->setEnabled(true);
        this->lineEditUri->setText(playlist->getBaseUri());
    }
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
    int count = this->model->getPlaylist()->getNumberOfTracks();
    QFileInfo outputFileInfo(lineEditOutputFile->text());
    Playlist* playlist = model->getPlaylist();
    QProgressDialog progressBarDialog("Copying files...", "Cancel",0, count-1, this);
    progressBarDialog.setWindowModality(Qt::WindowModal);

    progressBarDialog.show();

    if(this->checkBoxUri->isChecked())
    {
        QString newUri = this->lineEditUri->text();
        playlist->setBaseUri(newUri);
    }
    else
    {
        playlist->setBaseUri("");
    }

    int i = 0;
    for(auto itr = playlist->getConstBegin(); itr != playlist->getConstEnd(); itr++)
    {
        Track* track = (Track*)*itr;
        QString newAbsoluteFilePath = outputFileInfo.absolutePath() + "/" + track->getFilename();
        QFile::copy(track->getAbsoluteFilePath(), newAbsoluteFilePath);
        progressBarDialog.setValue(i++);
    }

    Xspf xspf;
    xspf.savePlaylist(outputFileInfo.absoluteFilePath(), *playlist);

    QMessageBox::information(this, "Copy", "Copy process is done.",
                             QMessageBox::Ok);
}
