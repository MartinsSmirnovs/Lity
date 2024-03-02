#ifndef DYNAMICSETTINGS_H
#define DYNAMICSETTINGS_H

#include <QObject>
#include <QSettings>

class DynamicSettings : public QObject
{
    Q_OBJECT
public:
    DynamicSettings() = delete;
    void operator=( const DynamicSettings& ) = delete;
    static DynamicSettings* instance( const QString& directoryPath, QObject* parent = nullptr );
    static DynamicSettings* instance();
    virtual ~DynamicSettings();

    bool getAutomaticPayment() const;
    void setAutomaticPayment( bool automaticPayment );

private:
    static DynamicSettings* dynamicSettings;
    DynamicSettings( const QString& directoryPath, QObject* parent = nullptr );

    QSettings* settings = nullptr;

    bool automaticPayment = false;
};

#endif // DYNAMICSETTINGS_H
