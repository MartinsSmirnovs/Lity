#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private:
    Ui::MainWindow* ui;

    FieldsRaw fieldsPrevious;
    FieldsRaw fieldsCurrent;

    LityLogic logic;

    QButtonGroup* groupFields;
    QButtonGroup* groupColors;

    Field::Type currentType = Field::black;

    void setColor(QAbstractButton& button, RGB color) const;
    void setText(QAbstractButton& button, Field::Building building) const;

    void clearFields();
};

#endif // MAINWINDOW_H
