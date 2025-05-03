#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

#include "Settings.h"
#include "history/HistoryDatabase.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    Settings settings;
    HistoryDatabase database;

private slots:
    void onTabChanged(int index);

private:
    Ui::MainWindow *ui;
};


#endif //MAIN_WINDOW_H
