#ifndef BASICPAGE_H
#define BASICPAGE_H

#include "MainWindow.h"
#include "core/ExpressionParser.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class BasicPage;
}

QT_END_NAMESPACE

enum OperationType {
    UNKNOWN,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
};

class BasicPage final : public QWidget {
    Q_OBJECT

public:
    explicit BasicPage(QWidget *parent = nullptr);

    ~BasicPage() override;

public slots:
    void onDigitClicked();

    void onOperationButtonClicked();

private slots:
    void on_btnDot_clicked();

    void on_btnBackspace_clicked();

    void on_btnAC_clicked();

    void on_btnSign_clicked();

    /* void on_btnPercent_clicked(); */

    void on_btnEqual_clicked();

private:
    Ui::BasicPage *ui;
    MainWindow *mainWindow;

    ExpressionParser expressionParser;

    void connectDigitButtons();

    void connectOperationButtons();
};

#endif // BASICPAGE_H
