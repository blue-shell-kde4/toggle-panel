#ifndef CONFIG_H
#define CONFIG_H

// QtCore
#include <QtCore/QObject>
#include <QtCore/QStringList>


class KConfigGroup;
class Config : public QObject
{
    Q_OBJECT


public:
    enum Mode {
        InvalidPanelMode = -1,
        NormalPanelMode = 0,
        AutoHideMode = 1,
        HiddenMode = 2,
        LetWindowsCoverMode = 3,
        WindowsGoBelowMode = 4
    };

    explicit Config(QObject *parent = 0);
    ~Config();

    Config::Mode getMode(int i) const;
    QString getIcon(int i) const;
    bool useCustomIcons() const;
    bool useSVG() const;
    bool isFirstStart() const;
    QString getSVGElement(int i) const;
    QString getSVG() const;

    void setMode(int i, const Config::Mode &mode);
    void setIcon(int i, const QString &icon);
    void setUseCustomIcons(bool useCustomIcons);
    void setUseSVG(bool useSVG);
    void setSVG(const QString &SVG);
    void setSVGElement(int i, const QString &element);

    void readConfig(const KConfigGroup *cfg);
    void writeConfig(KConfigGroup *cfg);


private:
    QStringList m_icons;
    QList<Config::Mode> m_modes;
    bool m_useCustomIcons;
    bool m_firstStart;
    bool m_configChanged;
    bool m_useSVG;
    QString m_SVG;
    QStringList m_svgElements;


private slots:
    void configChangedSlot();


signals:
    void configChanged();

    
};


#endif // CONFIG_H
