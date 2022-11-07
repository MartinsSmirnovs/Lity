#include "MainWindow.h"
#include "logic/LityConfig.h"
#include "ui_MainWindow.h"
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget* parent)
: QMainWindow(parent),
  ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setWindowTitle("Lity Desktop");

    auto group = new QButtonGroup(this);
    group->setExclusive(false);

    for (int i = 0; i < sideSize; i++) {
        auto layout = new QHBoxLayout(this);

        for (int j = 0; j < sideSize; j++) {
            auto button = new QPushButton(this);
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            layout->addWidget(button);
            group->addButton(button);
            group->setId(button, i * sideSize + j);
        }

        ui->fieldsContainer->layout()->addItem(layout);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
