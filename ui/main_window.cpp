#include "main_window.h"
#include "ui_main_window.h"

#include <QMessageBox>

void MainWindow::connect_digit_buttons() {
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

void MainWindow::connect_operation_buttons() {
    const std::vector operations = { QString("Divide"), QString("Multiply"), QString("Minus"), QString("Plus") };
    for (QString operation : operations) {
        const auto* button = this->findChild<QPushButton*>(QString("btn%1").arg(operation));
        if (!button) {
            qCritical() << "Button" << operation << "not found";
        } else {
            connect(button, &QPushButton::clicked, this, &MainWindow::on_operation_button_clicked);
        }
    }
}


MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Calculator");

    this->connect_digit_buttons();
    this->connect_operation_buttons();
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

void MainWindow::on_operation_button_clicked() {
    const auto button = qobject_cast<QPushButton*>(sender());
    if (!button) {
        qCritical() << "Received signal from an unknown sender";
        return;
    }

    const QVariant type_variant = button->property("type");
    if (type_variant.isNull()) {
        qCritical() << "Received signal from a button without a type property";
        return;
    }

    this->operation_data.append(this->expression.toDouble());
    this->ui->last_result->setText(this->expression);
    this->expression.clear();

    switch (type_variant.toInt()) {
        case 0: {
            this->operation_type = ADDITION;
            this->expression.append("+");
            break;
        }
        case 1: {
            this->operation_type = SUBTRACTION;
            this->expression.append("-");
            break;
        }
        case 2: {
            this->operation_type = MULTIPLICATION;
            this->expression.append("*");
            break;
        }
        case 3: {
            this->operation_type = DIVISION;
            this->expression.append("/");
            break;
        }
        default: {
            qCritical() << "Unknown operation type" << type_variant.toInt();
            break;
        }
    }

    this->ui->last_result->setText(this->ui->last_result->text().append(this->expression));
    this->ui->expression_text->setText(this->expression);
}

void MainWindow::on_btnDot_clicked() {
    if (this->expression.isEmpty() || (!this->expression[0].isDigit() && this->expression.length() > 1 && !this->expression[1].isDigit())) {
        this->expression.append(QString::number(0));
    }
    this->expression.append(QString("."));
    this->ui->expression_text->setText(this->expression);
}

void MainWindow::on_btnBackspace_clicked() {
    if (!this->expression.isEmpty() && (this->expression[this->expression.length() - 1].isDigit() || this->expression[this->expression.length() - 1] == '.')) {
        this->expression.chop(1);
        this->ui->expression_text->setText(this->expression);
    }
}

void MainWindow::on_btnAC_clicked() {
    if (this->ui->expression_text->text().isEmpty()) {
        this->ui->last_result->clear();
    }
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

void MainWindow::on_btnEqual_clicked() {
    if (this->expression.isEmpty() || this->operation_data.isEmpty() || this->operation_type == UNKNOWN) {
        return;
    }

    this->operation_data.append(this->expression.removeAt(0).toDouble());
    this->expression.clear();

    double result = 0;
    switch (this->operation_type) {
        case ADDITION: {
            result = this->operation_data[0] + this->operation_data[1];
            break;
        }
        case SUBTRACTION: {
            result = this->operation_data[0] - this->operation_data[1];
            break;
        }
        case MULTIPLICATION: {
            result = this->operation_data[0] * this->operation_data[1];
            break;
        }
        case DIVISION: {
            if (this->operation_data[1] == 0) {
                QMessageBox::warning(this->parentWidget(), "Ошибка", "Деление на ноль невозможно.");
                return;
            }
            result = this->operation_data[0] / this->operation_data[1];
            break;
        }
        default: {
            qCritical() << "Unknown operation type" << this->operation_type;
            break;
        }
    }

    this->expression.clear();
    this->ui->last_result->setText(this->ui->last_result->text().append(QString::number(this->operation_data[1])).append(" = "));
    this->ui->expression_text->setText(QString::number(result));

    this->operation_data.clear();
    this->operation_type = UNKNOWN;
}
