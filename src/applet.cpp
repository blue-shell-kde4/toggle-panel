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
#include "applet.h"
#include "config/generalconfig.h"
#include "config/appearanceconfig.h"
#include "config/config.h"
#include "config/configpage.h"

// KDE
#include <Plasma/Containment>
#include <Plasma/View>
#include <Plasma/IconWidget>
#include <KConfigDialog>
#include <KLocale>
#include <KGlobal>

// Qt
#include <QtCore/QTimer>
#include <QtCore/QMetaObject>
#include <QtCore/QMetaMethod>
#include <QtGui/QGraphicsLinearLayout>


Applet::Applet(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args),
      m_config(new Config(this))
{

    m_timer = 0;
    m_icon = 0;
    m_clicked = false;
    m_containment = 0;

    KGlobal::locale()->insertCatalog("plasma-applet-paneltoggle");

}


Applet::~Applet()
{

    delete m_timer;
    writeConfig();
    delete m_config;

}


void Applet::loadConfig()
{

    KConfigGroup cfg = config();

    m_config->readConfig(&cfg);
    if (m_config->isFirstStart()) {
        setConfigurationRequired(true);
    }

}


void Applet::writeConfig()
{

    KConfigGroup cfg = config();

    m_config->writeConfig(&cfg);

}


void Applet::init()
{
    
    m_containment = containment();

    loadConfig();

    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Horizontal);
    m_icon = new Plasma::IconWidget(this);
    m_icon->setEnabled(false);
    m_icon->setIcon("arrow-up");
    layout->addItem(m_icon);
    setLayout(layout);

    connect(m_icon, SIGNAL(clicked()), this, SLOT(iconClicked()));
    connect(this, SIGNAL(activate()), this, SLOT(togglePanelMode()));

    // we need to wait for the containment + view
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(checkForPanel()));
    m_timer->setInterval(1000);
    m_timer->setSingleShot(false);
    m_timer->start();


    setStatus(Plasma::ActiveStatus);

}


void Applet::configChanged()
{

    setConfigurationRequired(false);

    // restore default
    m_clicked = true;
    togglePanelMode();

}


void Applet::iconClicked()
{

    togglePanelMode();

}


void Applet::ensurePanelIsVisible()
{

    if (containment() && containment()->view()) {
        containment()->view()->metaObject()->invokeMethod(containment()->view(), "unhide");
    }

}


void Applet::updateIcon()
{

    if (m_config->useCustomIcons()) {
        if (m_clicked) {
            m_icon->setIcon(m_config->getIcon(1));
        } else {
            m_icon->setIcon(m_config->getIcon(0));
        }
        return;
    } else if (m_config->useSVG()) {
        if (m_clicked) {
            m_icon->setSvg(m_config->getSVG(), m_config->getSVGElement(1));
        } else {
            m_icon->setSvg(m_config->getSVG(), m_config->getSVGElement(0));
        }
        return;
    }

    const bool hideOnNextClick = (m_clicked && m_config->getMode(0) == Config::AutoHideMode) ||
            (!m_clicked && m_config->getMode(1) == Config::AutoHideMode);
    QString icon;
    switch(location()) {
    case Plasma::LeftEdge:
        icon = hideOnNextClick ? "arrow-left" : "arrow-right";
        break;
    case Plasma::RightEdge:
        icon = hideOnNextClick ? "arrow-right" : "arrow-left";
        break;
    case Plasma::TopEdge:
        icon  = hideOnNextClick ? "arrow-up" : "arrow-down";
        break;
    case Plasma::BottomEdge:
        icon = hideOnNextClick ? "arrow-down" : "arrow-up";
        break;
    default:
        icon = hideOnNextClick ? "arrow-up" : "arrow-down";
        break;
    }
    m_icon->setIcon(icon);

}



int Applet::getDefaultModeFromRC() const {

    if (!containment() || !containment()->view()) {
        qDebug() << "null containment || view";
        return -1;
    }

    // TODO: Plasma-Netbook?
    KConfig cfg("plasma-desktoprc");
    KConfigGroup viewGroup(&cfg, "PlasmaViews");
    KConfigGroup idGroup(&viewGroup, QString::number(((Plasma::View*) containment()->view())->id()));

    return idGroup.readEntry("panelVisibility", -1);

}



void Applet::checkForPanel()
{

    if (!m_icon || !containment() || !containment()->view()) {
        qDebug() << "null icon, cont, view";
        return;
    }

    bool success = false;
    for (int i = 0; i < containment()->view()->metaObject()->methodCount(); i++) {
        if (QLatin1String(containment()->view()->metaObject()->method(i).signature()) ==
                QLatin1String("setVisibilityMode(PanelView::VisibilityMode)")) {
            success = true;
            break;
        }
    }

    if (!success) {
        m_icon->setEnabled(false);
        return;
    }

    delete m_timer;
    m_timer = 0;

    m_icon->setEnabled(true);
    // Restore default mode
    setPanelMode(m_config->getMode(0));

}


void Applet::constraintsEvent(Plasma::Constraints constraints)
{

    Plasma::Applet::constraintsEvent(constraints);
       
    if (constraints & Plasma::FormFactorConstraint) {
        // new containment ?
        if (m_containment != 0 && m_containment != containment()) {
            qDebug() << "new containment ...";

            m_containment = containment();
            m_icon->setEnabled(false);

            setConfigurationRequired(true);

            delete m_timer;
            m_timer = new QTimer(this);
            connect(m_timer, SIGNAL(timeout()), this, SLOT(checkForPanel()));
            m_timer->setInterval(1000);
            m_timer->setSingleShot(false);
            m_timer->start();
        }
    }

}


void Applet::setPanelMode(int mode)
{

    if (m_icon == 0 || !m_icon->isEnabled()) {
        return;
    }

    const bool success = containment()->view()->metaObject()->invokeMethod(containment()->view(),
                        "setVisibilityMode", QGenericArgument("PanelView::VisibilityMode", (void*) &mode));

    if (!success) {
        qDebug() << "failed to set mode: " << mode;
    }

    m_clicked = (mode == m_config->getMode(1));
    updateIcon();

    if (mode != (int) Config::AutoHideMode) {
        QTimer::singleShot(1500, this, SLOT(ensurePanelIsVisible()));
    }

}


void Applet::createConfigurationInterface(KConfigDialog *parent)
{

    setConfigurationRequired(false);

    m_configPageList.clear();

    m_configPageList << new AppearanceConfig(parent);
    m_configPageList << new GeneralConfig(parent);

    for (int i = m_configPageList.size()-1; i >= 0; --i) {
        ConfigPage *page = m_configPageList.at(i);
        page->init(m_config);
        parent->addPage(page, page->pageName(), page->pageIcon(), page->pageHeader());
        connect(page, SIGNAL(configChanged()), parent, SLOT(settingsModified()));
    }

    connect(parent, SIGNAL(applyClicked()), this, SLOT(configAccepted()));
    connect(parent, SIGNAL(okClicked()), this, SLOT(configAccepted()));

    parent->resize(300, 300);

}


void Applet::configAccepted()
{

    for (int i = m_configPageList.size()-1; i >= 0; --i) {
        m_configPageList.at(i)->apply(m_config);
    }

    configChanged();

}


void Applet::togglePanelMode()
{

    if (m_clicked) {
        setPanelMode(m_config->getMode(0));
    } else {
        setPanelMode(m_config->getMode(1));
    }

}


#include "applet.moc"
