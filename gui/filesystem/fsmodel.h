#ifndef STDMODEL_H
#define STDMODEL_H

#include <QStandardItemModel>
#include "fbxapi.h"
class FSModel : public QStandardItemModel
{
    Q_OBJECT
public:
    enum FileInfoRole {
        PathRole = Qt::UserRole+1,
        MimeTypeRole,
        IsDirRole,
        SizeRole,
        ModifiedRole,
        IndexRole,
        IsLinkRole,
        IsHiddenRole,
        FolderCountRole,
        FileCountRole
    };


    explicit FSModel(FbxAPI * fbx, QObject *parent = 0);
    void fetchMore(const QModelIndex &parent);
    bool canFetchMore(const QModelIndex &parent) const;
    bool hasChildren(const QModelIndex &parent) const;



    static QString sizeHuman(double size);
    QByteArray currentPath(const QModelIndex& index);

    //    Qt::ItemFlags flags(const QModelIndex &index) const;


signals:
    //Quand ca telecharge, on disable la vue, pour eviter des erreurs
    void enableChanged(bool enable);

public slots:
    void init();
    void dataReceived(const QList<FileInfo>& list);
    void mkdir(const QString& name, const QModelIndex& parent);
    void remove(const QModelIndexList& indexes);
    void upload(const QString& filename, const QModelIndex& parent);
    void download(const QString& destination, const QModelIndex& index);
    void refresh(const QModelIndex& parent = QModelIndex());
    void clear();

protected slots:
    void refreshCurrentIndex();
    void itemToBeRenamed(QStandardItem * item);


private:
    FbxAPI * mFbx;
    QModelIndex mCurrentIndex;
    bool mIsLoading;
    bool mRemTest;
    QMap<QNetworkReply*, QModelIndex> mReplyIndexes;
    QList<QModelIndex> mRemoveList;

};






#endif // STDMODEL_H
