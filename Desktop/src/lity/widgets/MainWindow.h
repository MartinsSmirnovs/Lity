#pragma once

#include "FieldDescriptor.h"
#include "MainWindowManager.h"
#include <QAbstractButton>
#include <QMainWindow>
#include <lity/LityConfig.h>
#include <lity/LityLogic.h>


namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget* parent = nullptr );
    ~MainWindow();

public slots:
    void onButtonFieldClicked( QAbstractButton* button );
    void onButtonColorClicked( QAbstractButton* button );
    void onButtonBuildingClicked( QAbstractButton* button );
    void onOpenSettings();
    void onSettingsWindowClosed( int result );
    void displayBuildingSelectionMenu();
    void onFieldsUpdate( const FieldDescriptorList& descriptionList );

private:
    Ui::MainWindow* ui;

    QButtonGroup* groupFields;
    QButtonGroup* groupColors;
    QButtonGroup* groupBuildings;

    MainWindowManager manager;

    void setColor( QAbstractButton& button, RGB color ) const;

    void clearFields();

    void initializeFields();
    void initializeColorSelectionPanel();
    void initializeBuildingSelectionPanel();
};
