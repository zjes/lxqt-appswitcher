#pragma once

#include <QDialog>

namespace Ui
{ class Config; }

class Config : public QDialog
{
    Q_OBJECT
public:
    explicit Config(QWidget *parent = 0);
    virtual ~Config();
private:
    void save();
private:
    Ui::Config *m_ui;
};

