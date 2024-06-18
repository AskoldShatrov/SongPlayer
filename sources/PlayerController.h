#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QMediaPlayer>
#include <QAbstractListModel>

class AudioInfo;

class PlayerController : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(bool playing READ playing NOTIFY playingChanged)
    Q_PROPERTY(AudioInfo* currentSong READ currentSong WRITE setCurrentSong NOTIFY currentSongChanged)
    Q_PROPERTY(qint64 position READ position NOTIFY positionChanged)
    Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)

public:
    enum Role {
        AudioTitleRole = Qt::UserRole + 1,
        AudioAuthorNameRole,
        AudioSourceRole,
        AudioImageSourceRole,
        AudioVideoSourceRole
    };

    explicit PlayerController(QObject *parent = nullptr);

    bool playing() const;
    qint64 position() const;
    qint64 duration() const;

    Q_INVOKABLE void switchToNextSong();

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    AudioInfo *currentSong() const;
    void setCurrentSong(AudioInfo *newCurrentSong);

public slots:
    void switchToPreviousSong();
    void playPause();
    void changeAudioSource(const QUrl &source);
    void addAudio(const QString& title,
                  const QString& authorName,
                  const QUrl& audioSource,
                  const QUrl& imageSource,
                  const QUrl& videoSource = QUrl());
    void removeAudio(int index);
    void switchToAudioByIndex(int index);
    void updatePosition(qint64 position);
    void updateDuration(qint64 duration);
    void setPosition(qint64 position);

signals:
    void playingChanged();
    void currentSongChanged();
    void positionChanged();
    void durationChanged();


private:
    bool m_playing = false;
    QMediaPlayer m_mediaPlayer;
    QList<AudioInfo*> m_audioList;
    AudioInfo *m_currentSong = nullptr;
};

#endif // PLAYERCONTROLLER_H
