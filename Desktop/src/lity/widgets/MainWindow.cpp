#include "MainWindow.h"
#include "SettingsWindow.h"
#include "ui_MainWindow.h"
#include <QButtonGroup>

MainWindow::MainWindow(QWidget* parent)
: QMainWindow(parent),
  ui(new Ui::MainWindow),
  manager() {
    ui->setupUi(this);

    setWindowTitle("Lity Desktop");

    initializeFields();
    initializeColorSelectionPanel();
    initializeBuildingSelectionPanel();

    connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::onOpenSettings);

    connect(&manager, &MainWindowManager::updateFieldsEvent, this, &MainWindow::onFieldsUpdate);
}

void MainWindow::onFieldsUpdate(const FieldDescriptorList& descriptionList) {
    for (const auto& description : descriptionList) {
        const int id      = description.id;
        auto& buttonField = *groupFields->button(id);
        buttonField.setText(description.text);
        setColor(buttonField, description.color);
    }
}

void MainWindow::initializeColorSelectionPanel() {
    groupColors = new QButtonGroup(this);

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
}

void MainWindow::initializeFields() {
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

    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::clearFields);
    clearFields();
}

void MainWindow::clearFields() {
    manager.reset();

    const int buttonsCount = groupFields->buttons().size();
    for (int i = 0; i < buttonsCount; i++) {
        setColor(*groupFields->button(i), RGB(0, 0, 0));
        groupFields->button(i)->setText("");
    }
}

void MainWindow::onButtonColorClicked(QAbstractButton* button) {
    const auto type = static_cast<Field::Type>(groupColors->id(button));
    manager.setType(type);
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
    // const auto rawId     = groupFields->id(&button);
    // fieldsCurrent[rawId] = currentType;

    // // Return if there is no diff between readings
    // if (Differ::equal(fieldsPrevious, fieldsCurrent)) {
    //     return;
    // }

    // Figure::AnimationList animations;
    // try {
    //     animations = logic.process(fieldsPrevious, fieldsCurrent);
    // } catch (std::exception& exception) {
    //     qDebug() << exception.what();
    // }

    // for (const auto& animation : animations) {
    // const auto point = animation.second;
    // const auto id    = Converter::toId(point, sideSize);
    // auto& button     = *groupFields->button(id);

    // const auto& color = animation.first.getColor();

    // setColor(button, color);

    // // Update our local fields buffer so it would not get surprises
    // // on next read
    // fieldsCurrent[id] = toFieldType(color);
    // }

    // for (const auto& point : logic.getUpdatedPoints()) {
    // const auto id = Converter::toId(point, sideSize);
    // auto& button  = *groupFields->button(id);

    // const auto y = point.y;
    // const auto x = point.x;

    // const auto& field = logic.getFields()[y][x];
    // setText(button, field.getBuilding());
    // }

    // animations.clear();

    // fieldsPrevious = fieldsCurrent;
}

void MainWindow::onButtonFieldClicked(QAbstractButton* button) {
    const int id = groupFields->id(button);
    manager.buttonFieldClicked(id);
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

void MainWindow::onOpenSettings() {
    auto settingsWindow = new SettingsWindow(this);
    settingsWindow->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
    settingsWindow->show();
    connect(settingsWindow, &QDialog::finished, this, &MainWindow::onSettingsWindowClosed);
}

void MainWindow::onSettingsWindowClosed(int result) {
    if (result == QDialog::Accepted) {
        displayBuildingSelectionMenu();
        clearFields();
    }
}

void MainWindow::initializeBuildingSelectionPanel() {
    groupBuildings = new QButtonGroup(this);

    groupBuildings->addButton(ui->levelNone, static_cast<int>(Field::Building::levelNone));
    groupBuildings->addButton(ui->levelOne, static_cast<int>(Field::Building::levelFirst));
    groupBuildings->addButton(ui->levelTwo, static_cast<int>(Field::Building::levelSecond));
    groupBuildings->addButton(ui->levelThree, static_cast<int>(Field::Building::levelThird));

    connect(groupBuildings, qOverload<QAbstractButton*>(&QButtonGroup::buttonClicked), this, &MainWindow::onButtonBuildingClicked);

    displayBuildingSelectionMenu();
}

void MainWindow::onButtonBuildingClicked(QAbstractButton* button) {
    const auto building = static_cast<Field::Building>(groupBuildings->id(button));
    manager.setBuildingType(building);
}

void MainWindow::displayBuildingSelectionMenu() {
    if (manager.isAutomaticPaymentEnabled()) {
        ui->levelContainer->hide();
    } else {
        ui->levelContainer->show();
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
