#include <QDebug>
#include <QPainter>
#include <QApplication>
#include "app-model.h"
#include "app-itemdelegate.h"
#include "settings.h"

AppItemDelegate::AppItemDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{
}

void AppItemDelegate::init()
{
    m_iconSize = Settings::instance().iconSize();
    m_maxTextWidth = Settings::instance().maxTextWidth();
}

void AppItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    QStyle *style = option.widget ? option.widget->style() : QApplication::style();
    style->drawControl(QStyle::CE_ItemViewItem, &option, painter, option.widget);

    QPixmap img = index.model()->data(index, AppRole::Icon).value<QPixmap>();

    painter->drawPixmap(option.rect.left()+2, option.rect.top()+2, m_iconSize, m_iconSize, img);

    QString text = index.model()->data(index, AppRole::Display).toString();
    if (text.length() > m_maxTextWidth){
        text = text.left(m_maxTextWidth)+"...";
    }

    painter->setFont(option.font);

    painter->drawText(
        QRectF(option.rect.left()+m_iconSize+5, option.rect.top()+2, option.rect.width()-m_iconSize-5, m_iconSize),
        Qt::AlignLeft | Qt::AlignVCenter | Qt::TextSingleLine,
        text
    );
}

QSize AppItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QFontMetrics m(option.font);
    QString text = index.model()->data(index, AppRole::Display).toString();

    if (text.length() > m_maxTextWidth){
        text = text.left(m_maxTextWidth)+"...";
    }

    return QSize(m_iconSize + 10 + m.width(text), m_iconSize+4);
}

