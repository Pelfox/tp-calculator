#include "BasicPage.h"
#include "HistoryPage.h"
#include "SettingsPage.h"

#include "MainWindow.h"

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      settings(),
      database(settings.getDBFile()),
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

void MainWindow::onTabChanged(const int index) const {
    if (index == 1) {
        if (const auto *historyPage = dynamic_cast<HistoryPage *>(ui->tabWidget->widget(index))) {
            historyPage->renderHistory();
        }
    }
}

MainWindow::~MainWindow() {
    delete this->ui;
}
