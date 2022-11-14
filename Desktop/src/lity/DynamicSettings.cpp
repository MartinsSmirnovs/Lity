#include "DynamicSettings.h"

DynamicSettings* DynamicSettings::dynamicSettings = nullptr;

DynamicSettings::DynamicSettings(const QString& directoryPath, QObject* parent)
: QObject(parent) {
    settings         = new QSettings(directoryPath, QSettings::IniFormat, this);
    automaticPayment = settings->value("Automatic_Payment", false).toBool();
}

bool DynamicSettings::getAutomaticPayment() const {
    return automaticPayment;
}

void DynamicSettings::setAutomaticPayment(bool automaticPayment) {
    this->automaticPayment = automaticPayment;
    settings->setValue("Automatic_Payment", automaticPayment);
}

DynamicSettings* DynamicSettings::instance(const QString& directoryPath, QObject* parent) {
    if (!dynamicSettings) {
        dynamicSettings = new DynamicSettings(directoryPath, parent);
    }
    return dynamicSettings;
}

DynamicSettings* DynamicSettings::instance() {
    return dynamicSettings;
}

DynamicSettings::~DynamicSettings() {
    dynamicSettings = nullptr;
}
