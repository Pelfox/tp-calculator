#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    void on_digit_clicked();

private slots:
    void on_btnAC_clicked();
    void on_btnSign_clicked();
    void on_btnBackspace_clicked();

private:
    Ui::MainWindow *ui;
    QString expression;

    void connect_buttons();
};

#endif // MAINWINDOW_H
