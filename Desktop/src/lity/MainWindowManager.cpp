#include "MainWindowManager.h"
#include "DynamicSettings.h"
#include "FieldDescriptor.h"

MainWindowManager::MainWindowManager(QObject* parent)
: QObject(parent) {
}

void MainWindowManager::reset() {
    fieldsPrevious.fill(Field::none);
    fieldsCurrent = fieldsPrevious;

    logic = LityLogic();
}

bool MainWindowManager::isAutomaticPaymentEnabled() const {
    const auto settings = DynamicSettings::instance();
    return settings->getAutomaticPayment();
}

void MainWindowManager::setBuildingType(Field::Building type) {
    currentBuilding = type;
}

void MainWindowManager::setType(Field::Type type) {
    currentType = type;
}

void MainWindowManager::buttonFieldClicked(int id) {
    const auto settings    = DynamicSettings::instance();
    const bool isAutomatic = settings->getAutomaticPayment();

    if (isAutomatic) {
        // automaticProcess(*button);
    } else {
        manualProcess(id);
    }
}

void MainWindowManager::manualProcess(int buttonId) {
    FieldDescriptor fieldDescriptor;
    fieldDescriptor.id    = buttonId;
    fieldDescriptor.text  = getCurrentBuildingText();
    fieldDescriptor.color = Field::getColor(currentType);

    emit updateFieldsEvent({ fieldDescriptor });
}

QString MainWindowManager::getCurrentBuildingText() const {
    switch (currentBuilding) {
        case Field::Building::levelFirst: {
            return "I";
        } break;
        case Field::Building::levelSecond: {
            return "II";
        } break;
        case Field::Building::levelThird: {
            return "III";
        } break;
        default:
            return "";
            break;
    }
}
