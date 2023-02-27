#pragma once

#include <QAbstractButton>
#include <QMainWindow>
#include <lity/LityConfig.h>
#include <lity/LityLogic.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void onButtonFieldClicked(QAbstractButton* button);
    void onButtonColorClicked(QAbstractButton* button);
    void onButtonBuildingClicked(QAbstractButton* button);
    void onOpenSettings();
    void onSettingsWindowClosed(int result);
    void displayBuildingsMenu();

private:
    Ui::MainWindow* ui;

    FieldsRaw fieldsPrevious;
    FieldsRaw fieldsCurrent;

    LityLogic logic;

    QButtonGroup* groupFields;
    QButtonGroup* groupColors;
    QButtonGroup* groupBuildings;

    Field::Type currentType         = Field::black;
    Field::Building currentBuilding = Field::Building::levelNone;

    void setColor(QAbstractButton& button, RGB color) const;
    void setText(QAbstractButton& button, Field::Building building) const;

    void clearFields();

    void setupBuildingMenu();

    void automaticProcess(QAbstractButton& button);
    void manualProcess(QAbstractButton& button);
};
