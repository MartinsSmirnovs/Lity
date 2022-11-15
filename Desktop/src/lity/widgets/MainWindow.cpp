#include "MainWindow.h"
#include "DynamicSettings.h"
#include "SettingsWindow.h"
#include "ui_MainWindow.h"
#include <QButtonGroup>
#include <QDebug>
#include <lity/Converter.h>
#include <lity/Differ.h>

MainWindow::MainWindow(QWidget* parent)
: QMainWindow(parent),
  ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setWindowTitle("Lity Desktop");

    groupColors = new QButtonGroup(this);
    groupFields = new QButtonGroup(this);

    groupFields->setExclusive(false);

    const QSize buttonSize = QSize(60, 60);
    for (int i = 0; i < sideSize; i++) {
        for (int j = 0; j < sideSize; j++) {
            auto button = new QPushButton(this);
            button->setFixedSize(buttonSize);

            groupFields->addButton(button);
            groupFields->setId(button, i * sideSize + j);

            ui->fieldsContainer->addWidget(button, j, i);
        }
    }

    connect(groupFields, qOverload<QAbstractButton*>(&QButtonGroup::buttonClicked), this, &MainWindow::onButtonFieldClicked);

    groupColors->addButton(ui->radioBlack);
    groupColors->addButton(ui->radioBlue);
    groupColors->addButton(ui->radioGreen);
    groupColors->addButton(ui->radioPurple);
    groupColors->addButton(ui->radioRed);
    groupColors->addButton(ui->radioWhite);

    groupColors->setId(ui->radioBlack, Field::black);
    groupColors->setId(ui->radioBlue, Field::blue);
    groupColors->setId(ui->radioGreen, Field::green);
    groupColors->setId(ui->radioPurple, Field::purple);
    groupColors->setId(ui->radioRed, Field::red);
    groupColors->setId(ui->radioWhite, Field::white);

    connect(groupColors, qOverload<QAbstractButton*>(&QButtonGroup::buttonClicked), this, &MainWindow::onButtonColorClicked);

    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::clearFields);
    clearFields();

    connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::onOpenSettings);

    setupBuildingMenu();
}

void MainWindow::clearFields() {
    for (int i = 0; i < fieldsCount; i++) {
        setColor(*groupFields->button(i), RGB(0, 0, 0));
        setText(*groupFields->button(i), Field::Building::levelNone);
    }

    fieldsPrevious.fill(Field::none);
    fieldsCurrent = fieldsPrevious;

    logic = LityLogic();
}

void MainWindow::onButtonColorClicked(QAbstractButton* button) {
    currentType = static_cast<Field::Type>(groupColors->id(button));
}

Field::Type toFieldType(const RGB& color) {
    const auto red   = color.red;
    const auto green = color.green;
    const auto blue  = color.blue;

    if (red == 255 && green == 0 && blue == 0) {
        return Field::red;
    }

    if (red == 0 && green == 255 && blue == 0) {
        return Field::green;
    }

    if (red == 0 && green == 0 && blue == 255) {
        return Field::blue;
    }

    if (red == 255 && green == 0 && blue == 255) {
        return Field::purple;
    }

    if (red == 255 && green == 255 && blue == 255) {
        return Field::white;
    }

    return Field::black;
}

void MainWindow::automaticProcess(QAbstractButton& button) {
    const auto rawId     = groupFields->id(&button);
    fieldsCurrent[rawId] = currentType;

    // Return if there is no diff between readings
    if (Differ::equal(fieldsPrevious, fieldsCurrent)) {
        return;
    }

    LityLogic::AnimationList animations;
    try {
        animations = logic.process(fieldsPrevious, fieldsCurrent);
    } catch (std::exception& exception) {
        qDebug() << exception.what();
    }

    for (const auto& animation : animations) {
        const auto point = animation->getPoint();
        const auto id    = Converter::toId(point, sideSize);
        auto& button     = *groupFields->button(id);

        const auto& color = animation->getTarget();

        setColor(button, color);

        // Update our local fields buffer so it would not get surprises
        // on next read
        fieldsCurrent[id] = toFieldType(color);
    }

    for (const auto& point : logic.getUpdatedPoints()) {
        const auto id = Converter::toId(point, sideSize);
        auto& button  = *groupFields->button(id);

        const auto y = point.y;
        const auto x = point.x;

        const auto& field = logic.getFields()[y][x];
        setText(button, field.getBuilding());
    }

    animations.clear();

    fieldsPrevious = fieldsCurrent;
}

void MainWindow::manualProcess(QAbstractButton& button) {
    const auto buttonId = groupFields->id(&button);
    const auto& color   = Field::getColor(currentType);
    setColor(button, color);
    setText(button, currentBuilding);
}

void MainWindow::onButtonFieldClicked(QAbstractButton* button) {
    const auto settings    = DynamicSettings::instance();
    const bool isAutomatic = settings->getAutomaticPayment();

    if (isAutomatic) {
        automaticProcess(*button);
    } else {
        manualProcess(*button);
    }
}

QString toColorName(const RGB& color) {
    const auto red   = color.red;
    const auto green = color.green;
    const auto blue  = color.blue;

    if (red == 255 && green == 0 && blue == 0) {
        return "red";
    }

    if (red == 0 && green == 255 && blue == 0) {
        return "green";
    }

    if (red == 0 && green == 0 && blue == 255) {
        return "blue";
    }

    if (red == 255 && green == 0 && blue == 255) {
        return "purple";
    }

    if (red == 255 && green == 255 && blue == 255) {
        return "white";
    }

    return "black";
}

void MainWindow::setColor(QAbstractButton& button, RGB color) const {
    button.setStyleSheet("background-color:" + toColorName(color));
}

void MainWindow::setText(QAbstractButton& button, Field::Building building) const {
    QString buttonText;

    switch (building) {
        case Field::Building::levelNone: {
            buttonText = "";
        } break;
        case Field::Building::levelFirst: {
            buttonText = "I";
        } break;
        case Field::Building::levelSecond: {
            buttonText = "II";
        } break;
        case Field::Building::levelThird: {
            buttonText = "III";
        } break;
    }

    button.setText(buttonText);
}

void MainWindow::onOpenSettings() {
    auto settingsWindow = new SettingsWindow(this);
    settingsWindow->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
    settingsWindow->show();
    connect(settingsWindow, &QDialog::finished, this, &MainWindow::onSettingsWindowClosed);
}

void MainWindow::onSettingsWindowClosed(int result) {
    if (result == QDialog::Accepted) {
        displayBuildingsMenu();
        clearFields();
    }
}

void MainWindow::setupBuildingMenu() {
    groupBuildings = new QButtonGroup(this);

    groupBuildings->addButton(ui->levelNone, static_cast<int>(Field::Building::levelNone));
    groupBuildings->addButton(ui->levelOne, static_cast<int>(Field::Building::levelFirst));
    groupBuildings->addButton(ui->levelTwo, static_cast<int>(Field::Building::levelSecond));
    groupBuildings->addButton(ui->levelThree, static_cast<int>(Field::Building::levelThird));

    connect(groupBuildings, qOverload<QAbstractButton*>(&QButtonGroup::buttonClicked), this, &MainWindow::onButtonBuildingClicked);

    displayBuildingsMenu();
}

void MainWindow::onButtonBuildingClicked(QAbstractButton* button) {
    currentBuilding = static_cast<Field::Building>(groupBuildings->id(button));
}

void MainWindow::displayBuildingsMenu() {
    const auto settings = DynamicSettings::instance();

    if (settings->getAutomaticPayment()) {
        ui->levelContainer->hide();
    } else {
        ui->levelContainer->show();
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
