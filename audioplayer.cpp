#include "audioplayer.h"
#include "ui_audioplayer.h"
#include "QFileDialog" //работа с диалоговым окном
#include "QDir" //работа с директориями

int AudioPlayer::volume() const{
    return ui->horizontalSlider->value();
}
void AudioPlayer::setVolume(int volume){
    player->setVolume(volume);
}

AudioPlayer::AudioPlayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AudioPlayer)
{


    ui->setupUi(this);
    playListModel=new QStandardItemModel(this);
    ui->playlistView->setModel(playListModel);
    playListModel->setHorizontalHeaderLabels(QStringList() <<tr("Track")
                                             << tr("File Path"));
    ui->playlistView->hideColumn(1);
    ui->playlistView->verticalHeader()->setVisible(false);
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playlistView->horizontalHeader()->setStretchLastSection(true);

    player=new QMediaPlayer(this);
    playlist=new QMediaPlaylist(this);
    player->setPlaylist(playlist);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);


    connect(ui->previousbtn,&QToolButton::clicked,playlist,&QMediaPlaylist::previous);
    connect(ui->nextbtn,&QToolButton::clicked,playlist,&QMediaPlaylist::next);
    connect(ui->playbtn,&QToolButton::clicked,player,&QMediaPlayer::play);
    connect(ui->stopbtn,&QToolButton::clicked,player,&QMediaPlayer::stop);
    connect(ui->pausebtn,&QToolButton::clicked,player,&QMediaPlayer::pause);

    connect(ui->playlistView, &QTableView::doubleClicked, [this](const QModelIndex &index){
            playlist->setCurrentIndex(index.row());
        });

    connect(playlist, &QMediaPlaylist::currentIndexChanged, [this](int index){
            ui->currentTrack->setText(playListModel->data(playListModel->index(index, 0)).toString());
        });


    ui->horizontalSlider->setRange(0,100);
    ui->horizontalSlider->setValue(25);
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SIGNAL(volumeChanged(int))); // Does nothing
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), player, SLOT(setVolume(int)));

}

AudioPlayer::~AudioPlayer()
{
    delete ui;
    delete player;
    delete playlist;
    delete playListModel;
}


void AudioPlayer::on_addbtn_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this,
                                                          tr("Open files"),
                                                          QString(),
                                                          tr("Audio Files (*.mp3)"));
    foreach (QString filePath, files) {
            QList<QStandardItem *> items;
            items.append(new QStandardItem(QDir(filePath).dirName()));
            items.append(new QStandardItem(filePath));
            playListModel->appendRow(items);
            playlist->addMedia(QUrl(filePath));
        }
}

