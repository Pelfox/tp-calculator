#include "BasicPage.h"
#include "HistoryPage.h"
#include "SettingsPage.h"

#include "MainWindow.h"

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      settings(), // OK: settings default-constructed
      database(settings.getDBFile()), // now safe to use settings
      ui(new Ui::MainWindow) {
    this->ui->setupUi(this);
    this->setWindowTitle("TP Calculator");

    this->ui->tabWidget->clear();
    this->ui->tabWidget->addTab(new BasicPage(this), "Калькулятор");
    this->ui->tabWidget->addTab(new HistoryPage(this), "История");
    this->ui->tabWidget->addTab(new SettingsPage(this), "Настройки");

    this->setCentralWidget(this->ui->tabWidget);
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
}

void MainWindow::onTabChanged(int index) {
    if (index == 1) {
        HistoryPage *historyPage = dynamic_cast<HistoryPage *>(ui->tabWidget->widget(index));
        if (historyPage) {
            historyPage->renderHistory(); // Call a method to fetch and reload data
        }
    }
}

MainWindow::~MainWindow() {
    delete this->ui;
}
