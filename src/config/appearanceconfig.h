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

#ifndef APPEARANCECONFIG_H
#define APPEARANCECONFIG_H


// own
#include "configpage.h"


namespace Ui {
class AppearanceConfig;
}


class KConfigGroup;
class AppearanceConfig : public ConfigPage
{
    Q_OBJECT
    

public:
    explicit AppearanceConfig(QWidget *parent = 0);
    ~AppearanceConfig();
    

    virtual QString pageName() const;
    virtual QString pageHeader() const;
    virtual QString pageIcon() const;

    virtual void init(Config *cfg);
    virtual void apply(Config *cfg);


private:
    Ui::AppearanceConfig *ui;


};


#endif // APPEARANCECONFIG_H
