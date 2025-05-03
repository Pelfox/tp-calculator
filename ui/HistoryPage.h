#ifndef HISTORYPAGE_H
#define HISTORYPAGE_H

#include <QWidget>

#include "MainWindow.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class HistoryPage;
}

QT_END_NAMESPACE

class HistoryPage : public QWidget {
    Q_OBJECT

public:
    explicit HistoryPage(QWidget *parent = nullptr);

    void renderHistory() const;
    void addHistoryEntry(const HistoryEntry &entry);

    ~HistoryPage() override;

private:
    Ui::HistoryPage *ui;
    MainWindow* mainWindow;
};

#endif //HISTORYPAGE_H
