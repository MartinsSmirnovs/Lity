#include "MainWindow.h"
#include "logic/Converter.h"
#include "logic/Differ.h"
#include "ui_MainWindow.h"
#include <QButtonGroup>
#include <QDebug>
#include <QHBoxLayout>
#include <QMetaMethod>
#include <QObject>

MainWindow::MainWindow(QWidget* parent)
: QMainWindow(parent),
  ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setWindowTitle("Lity Desktop");

    groupColors = new QButtonGroup(this);
    groupFields = new QButtonGroup(this);

    groupFields->setExclusive(false);

    for (int i = 0; i < sideSize; i++) {
        auto layout = new QHBoxLayout(this);
        layout->setSpacing(2);

        for (int j = 0; j < sideSize; j++) {
            auto button = new QPushButton(this);
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            layout->addWidget(button);
            groupFields->addButton(button);
            groupFields->setId(button, i * sideSize + j);
        }

        ui->fieldsContainer->layout()->addItem(layout);
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
}

void MainWindow::clearFields() {
    for (int i = 0; i < fieldsCount; i++) {
        setColor(*groupFields->button(i), RGB(0, 0, 0));
    }

    fieldsPrevious.fill(Field::none);
    fieldsCurrent = fieldsPrevious;
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

void MainWindow::onButtonFieldClicked(QAbstractButton* button) {
    const auto rawId = groupFields->id(button);

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
        fieldsCurrent[id] = toFieldType(color);
    }
    animations.clear();

    fieldsPrevious = fieldsCurrent;
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

MainWindow::~MainWindow() {
    delete ui;
}
