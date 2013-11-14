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
#include "appearanceconfig.h"
#include "ui_appearanceconfig.h"

// ui
#include "config.h"



AppearanceConfig::AppearanceConfig(QWidget *parent)
    : ConfigPage(parent),
    ui(new Ui::AppearanceConfig)
{

    ui->setupUi(this);

    connect(ui->defaultIconButton, SIGNAL(iconChanged(QString)), this, SIGNAL(configChanged()));
    connect(ui->clickedIconButton, SIGNAL(iconChanged(QString)), this, SIGNAL(configChanged()));
    connect(ui->defaultIconsRadio, SIGNAL(toggled(bool)), this, SIGNAL(configChanged()));
    connect(ui->customIconsRadio, SIGNAL(toggled(bool)), this, SIGNAL(configChanged()));
    connect(ui->svgIconsRadio, SIGNAL(toggled(bool)), this, SIGNAL(configChanged()));
    connect(ui->svgRequester, SIGNAL(textChanged(QString)), this, SIGNAL(configChanged()));
    connect(ui->element1Edit, SIGNAL(textChanged(QString)), this, SIGNAL(configChanged()));
    connect(ui->element2Edit, SIGNAL(textChanged(QString)), this, SIGNAL(configChanged()));

}


AppearanceConfig::~AppearanceConfig()
{

    delete ui;

}


QString AppearanceConfig::pageName() const
{

    return i18n("Appearance");

}


QString AppearanceConfig::pageHeader() const
{

    return QString();

}


QString AppearanceConfig::pageIcon() const
{

    return "applications-graphics";

}


void AppearanceConfig::init(Config *cfg)
{

    ui->defaultIconButton->setIcon(cfg->getIcon(0));
    ui->clickedIconButton->setIcon(cfg->getIcon(1));
    ui->defaultIconsRadio->setChecked((!cfg->useCustomIcons() && !cfg->useSVG()));
    ui->svgIconsRadio->setChecked(cfg->useSVG());
    ui->customIconsRadio->setChecked(cfg->useCustomIcons());
    ui->svgRequester->setText(cfg->getSVG());
    ui->element1Edit->setText(cfg->getSVGElement(0));
    ui->element2Edit->setText(cfg->getSVGElement(1));

}


void AppearanceConfig::apply(Config *cfg)
{

    cfg->setIcon(0, ui->defaultIconButton->icon());
    cfg->setIcon(1, ui->clickedIconButton->icon());
    cfg->setUseCustomIcons(ui->customIconsRadio->isChecked());
    cfg->setUseSVG(ui->svgIconsRadio->isChecked());
    cfg->setSVGElement(0, ui->element1Edit->text());
    cfg->setSVGElement(1, ui->element2Edit->text());
    cfg->setSVG(ui->svgRequester->text());

}


#include "appearanceconfig.moc"


