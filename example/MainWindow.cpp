#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QAction>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	ui->widget->commandPaletteEngine()->addActionsFromMenu(ui->menuBar);
	ui->widget->commandPaletteEngine()->addFunctionForDynamicActions(
			[&](QString searchQuery) {
				QAction* action1 = new QAction( "DynamicEngine1: " + searchQuery, this );
				QAction* action2 = new QAction( "DynamicEngine1: " +searchQuery.toUpper(), this );
				QList<QAction*> result{ action1, action2};
				return result;
			}
		);
	ui->widget->commandPaletteEngine()->addFunctionForDynamicActions(
			[&](QString searchQuery) {
				QAction* action1 = new QAction( "DynamicEngine2: " +searchQuery, this );
				QList<QAction*> result{ action1};
				return result;
			}
		);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
	this->close();
}
