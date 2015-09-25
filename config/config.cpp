#include "config.h"
#include "ui_config.h"
#include "../src/settings.h"

Config::Config(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::Config)
{
    m_ui->setupUi(this);

    Settings & set = Settings::instance();
    m_ui->iconSizeEdt->setValue(set.iconSize());
    m_ui->maxItemsEdt->setValue(set.maxDisplayApps());
    m_ui->maxLengthEdt->setValue(set.maxTextWidth());
    m_ui->filterDskChk->setChecked(set.filterCurrentDesktop());
    m_ui->filterScrChk->setChecked(set.filterCurrentScreen());

    connect(m_ui->iconSizeEdt, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int){ save(); });
    connect(m_ui->maxItemsEdt, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int){ save(); });
    connect(m_ui->maxLengthEdt, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int){ save(); });

    connect(m_ui->filterDskChk, &QCheckBox::stateChanged, this, &Config::save);
    connect(m_ui->filterScrChk, &QCheckBox::stateChanged, this, &Config::save);
}

Config::~Config()
{
    delete m_ui;
}

void Config::save()
{
    Settings & set = Settings::instance();

    set.setIconSize(m_ui->iconSizeEdt->value());
    set.setDisplayApps(m_ui->maxItemsEdt->value());
    set.setMaxTextWidth(m_ui->maxLengthEdt->value());
    set.setFilterCurrentDesktop(m_ui->filterDskChk->isChecked());
    set.setFilterCurrentScreen(m_ui->filterScrChk->isChecked());

    set.sync();
}
