#include "MainWindowManager.h"
#include "DynamicSettings.h"
#include "FieldDescriptor.h"
#include <QDebug>
#include <lity/Converter.h>
#include <lity/Differ.h>
#include <lity/LityLogic.h>

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

    FieldDescriptorList fieldsDescriptors;
    for (const auto& animationPoint : animations) {
        const auto& point = animationPoint.second;
        const auto& field = logic.getFieldAt(point);

        FieldDescriptor descriptor;
        descriptor.color = field.getColor();
        descriptor.id    = Converter::toId(point, sideSize);
        descriptor.text  = getBuildingText(field.getBuilding());

        fieldsDescriptors.push_back(descriptor);

        fieldsCurrent[descriptor.id] = field.getType();
    }

    emit updateFieldsEvent(fieldsDescriptors);

    // On next move the figure gets moved to another field and previous
    // field becomes none
    fieldsCurrent[fieldId] = Field::Type::none;

    fieldsPrevious = fieldsCurrent;
}

void MainWindowManager::manualProcess(int fieldId) {
    FieldDescriptor fieldDescriptor;
    fieldDescriptor.id    = fieldId;
    fieldDescriptor.text  = getCurrentBuildingText();
    fieldDescriptor.color = Field::getColor(currentType);

    emit updateFieldsEvent({ fieldDescriptor });
}

QString MainWindowManager::getBuildingText(Field::Building building) const {
    switch (building) {
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

QString MainWindowManager::getCurrentBuildingText() const {
    return getBuildingText(currentBuilding);
}
