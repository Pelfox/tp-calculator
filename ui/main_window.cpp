#include "main_window.h"
#include "ui_main_window.h"

void MainWindow::connect_buttons() {
    for (int i = 0; i < 10; ++i) {
        const QString button_name = QString("btn%1").arg(i);
        const auto* button = this->findChild<QPushButton*>(button_name);

        if (!button) {
            qCritical() << "Button" << button_name << "not found";
        } else {
            connect(button, &QPushButton::clicked, this, &MainWindow::on_digit_clicked);
            qDebug() << "Button" << button_name << "connected";
        }
    }
}

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Calculator");

    this->connect_buttons();
    this->expression = QString();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_digit_clicked() {
    const auto button = qobject_cast<QPushButton*>(sender());
    if (!button) {
        qCritical() << "Received signal from an unknown sender";
        return;
    }

    const QVariant digit_variant = button->property("digit");
    if (digit_variant.isNull()) {
        qCritical() << "Received signal from a button without a digit property";
        return;
    }

    const int digit = digit_variant.value<int>();
    this->expression.append(QString::number(digit));
    this->ui->expression_text->setText(this->expression);
}

void MainWindow::on_btnAC_clicked() {
    this->expression.clear();
    this->ui->expression_text->clear();
}

void MainWindow::on_btnSign_clicked() {
    if (this->expression.startsWith("-")) {
        this->expression.remove(0, 1);
    } else {
        this->expression.prepend("-");
    }
    this->ui->expression_text->setText(this->expression);
}

void MainWindow::on_btnBackspace_clicked() {
    if (!this->expression.isEmpty()) {
        this->expression.chop(1);
        this->ui->expression_text->setText(this->expression);
    }
}
