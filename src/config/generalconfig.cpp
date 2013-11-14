/***************************************************************************
 *   Copyright (C) 2012-2013 by Kai Dombrowe <just89@gmx.de>               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

// own
#include "generalconfig.h"
#include "config.h"

// ui
#include "ui_generalconfig.h"

// KDE
#include <KConfigGroup>
#include <KLocale>


GeneralConfig::GeneralConfig(QWidget *parent)
    : ConfigPage(parent),
      ui(new Ui::GeneralConfig)
{

    ui->setupUi(this);

    ui->defaultModeCombo->addItem(i18n("Always visible"), Config::NormalPanelMode);
    ui->defaultModeCombo->addItem(i18n("Auto-hide"), Config::AutoHideMode);
    ui->defaultModeCombo->addItem(i18n("Windows can cover"), Config::LetWindowsCoverMode);
    ui->defaultModeCombo->addItem(i18n("Windows go below"), Config::WindowsGoBelowMode);

    ui->onClickCombo->addItem(i18n("Always visible"), Config::NormalPanelMode);
    ui->onClickCombo->addItem(i18n("Auto-hide"), Config::AutoHideMode);
    ui->onClickCombo->addItem(i18n("Windows can cover"), Config::LetWindowsCoverMode);
    ui->onClickCombo->addItem(i18n("Windows go below"), Config::WindowsGoBelowMode);

    connect(ui->defaultModeCombo, SIGNAL(currentIndexChanged(int)), this, SIGNAL(configChanged()));
    connect(ui->onClickCombo, SIGNAL(currentIndexChanged(int)), this, SIGNAL(configChanged()));

}


GeneralConfig::~GeneralConfig()
{

    delete ui;

}


QString GeneralConfig::pageName() const
{

    return i18n("General");

}


QString GeneralConfig::pageHeader() const
{

    return QString();

}


QString GeneralConfig::pageIcon() const
{

    return "configure";

}


void GeneralConfig::init(Config *cfg)
{

    ui->defaultModeCombo->setCurrentIndex(ui->defaultModeCombo->findData(cfg->getMode(0)));
    ui->onClickCombo->setCurrentIndex(ui->onClickCombo->findData(cfg->getMode(1)));

}


void GeneralConfig::apply(Config *cfg)
{

    cfg->setMode(0, (Config::Mode) ui->defaultModeCombo->itemData(ui->defaultModeCombo->currentIndex()).toInt());
    cfg->setMode(1, (Config::Mode) ui->onClickCombo->itemData(ui->onClickCombo->currentIndex()).toInt());

}


#include "generalconfig.moc"
