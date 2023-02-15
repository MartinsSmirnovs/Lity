#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QAbstractButton>
#include <QDialog>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog {
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget* parent = nullptr);
    ~SettingsWindow();

private slots:
    void saveInput(QAbstractButton* clickedButton);


private:
    Ui::SettingsWindow* ui;
};

#endif // SETTINGSWINDOW_H
