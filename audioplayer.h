#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QStandardItemModel>

namespace Ui {
class AudioPlayer;
}

class AudioPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit AudioPlayer(QWidget *parent = nullptr);
    ~AudioPlayer();
    int volume() const;
    void setVolume(int);

private slots:
    void on_addbtn_clicked(); //Слот для добавления треков

private:
    Ui::AudioPlayer *ui;
    QStandardItemModel *playListModel; //для отображения плейлиста
    QMediaPlayer *player; //по названию все понятно
    QMediaPlaylist *playlist; //тут тоже
};

#endif // AUDIOPLAYER_H
