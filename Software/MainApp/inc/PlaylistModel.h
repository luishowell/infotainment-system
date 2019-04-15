/**
 * @file PlaylistModel.h
 * @author 
 * @brief Adapted from the Qt Media Player example https://doc.qt.io/qt-5/qtmultimedia-multimediawidgets-player-playlistmodel-h.html 
 * @version 0.1
 * @date 2019-04-15
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractItemModel>
#include <QScopedPointer>

class QMediaPlaylist;

/**
 * @brief model of playlist used by the QMediaPlayer
 * 
 */
class PlaylistModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum Column
    {
        Title = 0,
        ColumnCount
    };

    /**
     * @brief Construct a new Playlist Model object
     * 
     * @param parent 
     */
    explicit PlaylistModel(QObject *parent = nullptr);

    /**
     * @brief Destroy the Playlist Model object
     * 
     */
    ~PlaylistModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QMediaPlaylist *playlist() const;
    void setPlaylist(QMediaPlaylist *playlist);

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole) override;

private slots:
    void beginInsertItems(int start, int end);
    void endInsertItems();
    void beginRemoveItems(int start, int end);
    void endRemoveItems();
    void changeItems(int start, int end);

private:
    QScopedPointer<QMediaPlaylist> m_playlist;
    QMap<QModelIndex, QVariant> m_data;
};

#endif // PLAYLISTMODEL_H