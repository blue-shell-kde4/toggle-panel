
// own
#include "config.h"

// KDE
#include <KConfigGroup>
#include <Plasma/Theme>


Config::Config(QObject *parent)
    : QObject(parent)
{

    m_configChanged = false;
    connect(this, SIGNAL(configChanged()), this, SLOT(configChangedSlot()));

}


Config::~Config()
{


}


Config::Mode Config::getMode(int i) const
{

    if (m_modes.size() > i) {
        return m_modes.at(i);
    }
    return Config::InvalidPanelMode;

}


QString Config::getIcon(int i) const
{

    if (m_icons.size() > i) {
        return m_icons.at(i);
    }
    return QString();

}


bool Config::useCustomIcons() const
{

    return m_useCustomIcons;

}


bool Config::useSVG() const
{

    return m_useSVG;

}


bool Config::isFirstStart() const
{

    return m_firstStart;

}


QString Config::getSVGElement(int i) const
{

    if (m_svgElements.size() > i) {
        return m_svgElements.at(i);
    }
    return QString();

}


QString Config::getSVG() const
{

    return m_SVG;

}


void Config::setMode(int i, const Config::Mode &mode)
{

    m_modes.insert(i, mode);
    emit configChanged();

}


void Config::setIcon(int i, const QString &icon)
{

    m_icons.insert(i, icon);
    emit configChanged();

}


void Config::setUseCustomIcons(bool useCustomIcons)
{

    m_useCustomIcons = useCustomIcons;
    emit configChanged();

}


void Config::setUseSVG(bool useSVG)
{

    m_useSVG = useSVG;
    emit configChanged();

}


void Config::setSVG(const QString &SVG)
{

    m_SVG = SVG;
    emit configChanged();

}


void Config::setSVGElement(int i, const QString &element)
{

    m_svgElements.insert(i, element);
    emit configChanged();

}


void Config::readConfig(const KConfigGroup *cfg)
{

    setMode(0, (Config::Mode) cfg->readEntry("Mode0", (int) Config::NormalPanelMode));
    setMode(1, (Config::Mode) cfg->readEntry("Mode1", (int) Config::HiddenMode));

    setIcon(0, cfg->readEntry("Icon0", QString()));
    setIcon(1, cfg->readEntry("Icon1", QString()));
    setUseCustomIcons(cfg->readEntry("UseCustomIcons", false));

    setUseSVG(cfg->readEntry("UseSVG", false));
    setSVG(cfg->readEntry("SVG", Plasma::Theme::defaultTheme()->imagePath("widgets/arrows")));
    setSVGElement(0, cfg->readEntry("SVGElement1", "down-arrow"));
    setSVGElement(1, cfg->readEntry("SVGElement2", "up-arrow"));

    m_firstStart = cfg->readEntry("FirstStart", true);
    m_configChanged = m_firstStart;

}


void Config::writeConfig(KConfigGroup *cfg)
{

    if (!m_configChanged) {
        return;
    }

    cfg->writeEntry("Mode0", (int) getMode(0));
    cfg->writeEntry("Mode1", (int) getMode(1));

    cfg->writeEntry("Icon0", getIcon(0));
    cfg->writeEntry("Icon1", getIcon(1));
    cfg->writeEntry("UseCustomIcons", useCustomIcons());

    cfg->writeEntry("UseSVG", useSVG());
    cfg->writeEntry("SVG", getSVG());
    cfg->writeEntry("SVGElement1", getSVGElement(0));
    cfg->writeEntry("SVGElement2", getSVGElement(1));

    cfg->writeEntry("FirstStart", false);

}


void Config::configChangedSlot()
{

    m_configChanged = true;

}


#include "config.moc"

