#include "SettingsWindow.h"
#include "DynamicSettings.h"
#include "ui_SettingsWindow.h"

SettingsWindow::SettingsWindow(QWidget* parent)
: QDialog(parent),
  ui(new Ui::SettingsWindow) {
    ui->setupUi(this);

    setWindowTitle("Settings");

    const auto settings = DynamicSettings::instance();
    ui->autoPaymentCheckBox->setChecked(settings->getAutomaticPayment());

    connect(ui->buttonBox, &QDialogButtonBox::clicked, this, &SettingsWindow::saveInput);

    adjustSize();
}

void SettingsWindow::saveInput(QAbstractButton* clickedButton) {
    const auto buttonRole = ui->buttonBox->standardButton(clickedButton);

    if (buttonRole == QDialogButtonBox::Ok) {
        auto settings                   = DynamicSettings::instance();
        const bool isAutoPaymentChecked = ui->autoPaymentCheckBox->isChecked();
        settings->setAutomaticPayment(isAutoPaymentChecked);
        setResult(Accepted);
    } else {
        setResult(Rejected);
    }
}

SettingsWindow::~SettingsWindow() {
    delete ui;
}
