#pragma once
#include <QStyledItemDelegate>

class AppItemDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    AppItemDelegate(QObject *parent);
    void init();
protected:
    virtual void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
    int m_iconSize;
    int m_maxTextWidth = 0;
};
