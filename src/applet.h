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
#ifndef APPLET_HEADER
#define APPLET_HEADER

// KDE
#include <Plasma/Applet>


namespace Plasma {
class IconWidget;
}

class Config;
class ConfigPage;
class AppearanceConfig;
class GeneralConfig;
class QTimer;
class Applet : public Plasma::Applet
{
    Q_OBJECT
    
    
public:
    Applet(QObject *parent, const QVariantList &args);
    ~Applet();

    void init();


public slots:
    virtual void configChanged();


private:
    QTimer *m_timer;
    Plasma::IconWidget *m_icon;
    bool m_clicked;
    Config *m_config;
    QList<ConfigPage*> m_configPageList;
    QObject *m_containment;

    int getDefaultModeFromRC() const;

    void updateIcon();
    void loadConfig();
    void writeConfig();
    void setPanelMode(int mode);


private slots:
    void checkForPanel();
    void iconClicked();
    void ensurePanelIsVisible();
    void createConfigurationInterface(KConfigDialog *parent);
    void configAccepted();
    void togglePanelMode();


protected:
    void constraintsEvent(Plasma::Constraints constraints);


};
 

K_EXPORT_PLASMA_APPLET(paneltoggleapplet, Applet)


#endif
