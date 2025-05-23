#include "HistoryPage.h"

#include <QLabel>
#include <QFormLayout>

#include "ui_HistoryPage.h"

HistoryPage::HistoryPage(QWidget *parent) : QWidget(parent), ui(new Ui::HistoryPage),
                                              mainWindow(dynamic_cast<MainWindow *>(parent)) {
    this->ui->setupUi(this);
    this->renderHistory();
}

void HistoryPage::renderHistory() const {
    QWidget* scrollAreaContent = ui->historyList->widget();
    const QList<HistoryEntry> entries = mainWindow->database.getEntries();

    auto *newContent = new QWidget;

    auto *layout = new QFormLayout(scrollAreaContent);
    layout->setVerticalSpacing(20);

    for (const auto &entry : entries) {
        auto *entryLayout = new QFormLayout();
        entryLayout->setVerticalSpacing(5);
        entryLayout->setRowWrapPolicy(QFormLayout::WrapAllRows);

        auto *label = new QLabel(QString("%1%2").arg(entry.expression).arg(entry.result));
        entryLayout->addWidget(label);

        QDateTime entryTimestamp = QDateTime::fromString(entry.timestamp,"yyyy-MM-dd HH:mm:ss");
        entryTimestamp = entryTimestamp.addSecs(3 * 60 * 60);
        auto *date = new QLabel(QString("%1").arg(entryTimestamp.toString("dd.MM.yyyy, HH:mm:ss")));
        entryLayout->addWidget(date);

        layout->addRow(entryLayout);
    }

    newContent->setLayout(layout);
    ui->historyList->setWidget(newContent);
    ui->historyList->setWidgetResizable(true);
}

HistoryPage::~HistoryPage() {
    delete ui;
}
