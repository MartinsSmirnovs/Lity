#include "MainWindowManager.h"
#include "DynamicSettings.h"
#include "FieldDescriptor.h"
#include <QDebug>
#include <lity/Differ.h>


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
        automaticProcess(id);
    } else {
        manualProcess(id);
    }
}

void MainWindowManager::automaticProcess(int fieldId) {
    fieldsCurrent[fieldId] = currentType;

    // Return if there is no diff between readings
    if (Differ::equal(fieldsPrevious, fieldsCurrent)) {
        return;
    }

    Figure::AnimationList animations;
    try {
        animations = logic.process(fieldsPrevious, fieldsCurrent);
    } catch (std::exception& exception) {
        qDebug() << exception.what();
    }

    // STOPPED HERE! HAVE TO COPY PASTE CODE HERE FROM MAINWINDOW.CPP!!
}

void MainWindowManager::manualProcess(int fieldId) {
    FieldDescriptor fieldDescriptor;
    fieldDescriptor.id    = fieldId;
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
