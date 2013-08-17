#ifndef PLUGINSPROXYMODEL_HPP
#define PLUGINSPROXYMODEL_HPP

#include <QSortFilterProxyModel>

class QVariant;
class QAbstractTableModel;
class DataFilesModel;

class PluginsProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

    DataFilesModel *mSourceModel;

public:

    explicit PluginsProxyModel(QObject *parent = 0, DataFilesModel *model = 0);
    ~PluginsProxyModel();

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};

#endif // PLUGINSPROXYMODEL_HPP
