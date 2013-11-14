#ifndef CONFIGPAGE_H
#define CONFIGPAGE_H


// Qt
#include <QtGui/QWidget>


class Config;
class ConfigPage : public QWidget
{
    Q_OBJECT


public:
    ConfigPage(QWidget *parent = 0);
    ~ConfigPage();

    virtual QString pageName() const = 0;
    virtual QString pageHeader() const = 0;
    virtual QString pageIcon() const = 0;

    virtual void init(Config *cfg) = 0;
    virtual void apply(Config *cfg) = 0;


signals:
    void configChanged();


};


#endif // CONFIGPAGE_H
