#pragma once

#include "FieldDescriptor.h"
#include <QObject>
#include <lity/LityLogic.h>


class MainWindowManager : public QObject {
    Q_OBJECT

public:
    explicit MainWindowManager(QObject* parent = nullptr);
    void buttonFieldClicked(int id);
    void setBuildingType(Field::Building type);
    void setType(Field::Type type);
    bool isAutomaticPaymentEnabled() const;
    void reset();

signals:
    void updateFieldsEvent(const FieldDescriptorsList& descriptionList);

private:
    LityLogic logic;

    FieldsRaw fieldsPrevious;
    FieldsRaw fieldsCurrent;

    Field::Type currentType         = Field::black;
    Field::Building currentBuilding = Field::Building::levelNone;

    void manualProcess(int buttonId);
    QString getCurrentBuildingText() const;
};
