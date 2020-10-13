/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * LXDE-Qt - a lightweight, Qt based, desktop toolset
 * https://lxqt.org/
 *
 * Copyright: 2015 LXQt team
 * Authors:
 *   zjesclean@gmail.com
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include "config.h"
#include "../src/settings.h"
#include "ui_config.h"

Config::Config(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::Config)
{
    m_ui->setupUi(this);

    Settings& set = Settings::instance();
    m_ui->iconSizeEdt->setValue(set.iconSize());
    m_ui->maxItemsEdt->setValue(set.maxDisplayApps());
    m_ui->maxLengthEdt->setValue(set.maxTextWidth());
    m_ui->filterDskChk->setChecked(set.filterCurrentDesktop());
    m_ui->filterScrChk->setChecked(set.filterCurrentScreen());

    m_ui->fontSizeEnabled->setChecked(set.customFontSizeEnabled());
    m_ui->fontSize->setValue(set.customFontSize() ? set.customFontSize() : qApp->font().pointSize());
    m_ui->fontSize->setEnabled(set.customFontSizeEnabled());

    connect(m_ui->iconSizeEdt, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int) {
        save();
    });
    connect(m_ui->maxItemsEdt, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int) {
        save();
    });
    connect(m_ui->maxLengthEdt, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int) {
        save();
    });
    connect(m_ui->fontSize, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int) {
        save();
    });

    connect(m_ui->filterDskChk, &QCheckBox::stateChanged, this, &Config::save);
    connect(m_ui->filterScrChk, &QCheckBox::stateChanged, this, &Config::save);
    connect(m_ui->fontSizeEnabled, &QCheckBox::stateChanged, [this](int state) {
        m_ui->fontSize->setEnabled(state);
        save();
    });
}

Config::~Config()
{
    delete m_ui;
}

void Config::save()
{
    Settings& set = Settings::instance();

    set.setIconSize(m_ui->iconSizeEdt->value());
    set.setDisplayApps(m_ui->maxItemsEdt->value());
    set.setMaxTextWidth(m_ui->maxLengthEdt->value());
    set.setFilterCurrentDesktop(m_ui->filterDskChk->isChecked());
    set.setFilterCurrentScreen(m_ui->filterScrChk->isChecked());
    set.setCustomFontSizeEnabled(m_ui->fontSizeEnabled->isChecked());
    set.setCustomFontSize(m_ui->fontSize->value());

    set.sync();
}
