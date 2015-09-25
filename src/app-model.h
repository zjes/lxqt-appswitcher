#pragma once

#include <QPixmap>
#include <QAbstractListModel>

struct AppInfo
{
    WId     windowId;
    QString name;
    QPixmap pixmap;
};

namespace AppRole {
enum Role {
    Display = Qt::DisplayRole,
    Icon = Qt::UserRole + 1,
    Window = Qt::UserRole +2
};
}

class AppModel : public QAbstractListModel
{
    Q_OBJECT
public:
    AppModel(QObject *parent);
protected:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
private:
    void create();
    bool filter(WId window, bool byDesk, bool byScreen) const;
private:
    QList<AppInfo> m_list;
};
