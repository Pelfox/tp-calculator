#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum OperationType {
    UNKNOWN,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
};

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    void on_digit_clicked();
    void on_operation_button_clicked();

private slots:
    void on_btnDot_clicked();
    void on_btnBackspace_clicked();

    void on_btnAC_clicked();
    void on_btnSign_clicked();
    /* void on_btnPercent_clicked(); */

    void on_btnEqual_clicked();

private:
    Ui::MainWindow *ui;
    QString expression = QString();

    OperationType operation_type = UNKNOWN;
    QList<double> operation_data = {};

    void connect_digit_buttons();
    void connect_operation_buttons();
};

#endif // MAINWINDOW_H
