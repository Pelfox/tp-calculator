#ifndef HISTORYPAGE_H
#define HISTORYPAGE_H

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

    ~HistoryPage() override;

private:
    Ui::HistoryPage *ui;
    MainWindow* mainWindow;
};

#endif //HISTORYPAGE_H
