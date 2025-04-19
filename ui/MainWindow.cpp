#include "BasicPage.h"
#include "SettingsPage.h"

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    this->ui->setupUi(this);
    this->setWindowTitle("TP Calculator");

    this->ui->tabWidget->clear();
    this->ui->tabWidget->addTab(new BasicPage(this), "Калькулятор");
    this->ui->tabWidget->addTab(new SettingsPage(this), "Настройки");

    this->setCentralWidget(this->ui->tabWidget);
}

MainWindow::~MainWindow() {
    delete this->ui;
}
