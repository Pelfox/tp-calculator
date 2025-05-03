#include "BasicPage.h"
#include "ui_BasicPage.h"

#include <QMessageBox>

// TODO: move out this code to a separate function
void BasicPage::connectDigitButtons() {
    for (int i = 0; i < 11; ++i) {
        const QString buttonName = QString("btn%1").arg(i);
        const auto *button = this->findChild<QPushButton *>(buttonName);

        if (!button) {
            qCritical() << "Button" << buttonName << "not found";
        } else {
            connect(button, &QPushButton::clicked, this, &BasicPage::onDigitClicked);
        }
    }
}

void BasicPage::connectOperationButtons() {
    const std::vector operations = {
        QString("Divide"), QString("Multiply"), QString("Minus"), QString("Plus"),
        QString("Sin"), QString("Cos"), QString("Tan"), QString("Cotan"),
        QString("Sec"), QString("Csc"),
    };
    for (const QString &operation: operations) {
        const auto *button = this->findChild<QPushButton *>(QString("btn%1").arg(operation));
        if (!button) {
            qCritical() << "Button" << operation << "not found";
        } else {
            connect(button, &QPushButton::clicked, this, &BasicPage::onOperationButtonClicked);
        }
    }
}

BasicPage::BasicPage(QWidget *parent): QWidget(parent), ui(new Ui::BasicPage),
                                       mainWindow(dynamic_cast<MainWindow *>(parent)),
                                       expressionParser(mainWindow->settings) {
    ui->setupUi(this);
    this->connectDigitButtons();
    this->connectOperationButtons();
}

BasicPage::~BasicPage() {
    delete this->ui;
}

void BasicPage::onDigitClicked() {
    const auto button = qobject_cast<QPushButton *>(sender());
    if (!button) {
        qCritical() << "Received signal from an unknown sender";
        return;
    }

    const QVariant digitVariant = button->property("digit");
    if (digitVariant.isNull()) {
        qCritical() << "Received signal from a button without a digit property";
        return;
    }

    auto digit = digitVariant.value<double>();
    if (digit == 10) {
        digit = M_PI;
    }

    const QString part = this->expressionParser.appendDigit(digit);
    this->ui->expression_text->setText(part);
}

void BasicPage::onOperationButtonClicked() {
    const auto button = qobject_cast<QPushButton *>(sender());
    if (!button) {
        qCritical() << "Received signal from an unknown sender";
        return;
    }

    const QVariant typeVariant = button->property("type");
    if (typeVariant.isNull()) {
        qCritical() << "Received signal from a button without a type property";
        return;
    }

    this->expressionParser.setOperationFromVariant(typeVariant.toInt());
    this->ui->last_result->setText(this->expressionParser.toString());
    this->ui->expression_text->clear();
}

void BasicPage::on_btnDot_clicked() {
    const QString value = this->expressionParser.appendDot();
    this->ui->expression_text->setText(value);
}

void BasicPage::on_btnBackspace_clicked() {
    const QString expression = this->expressionParser.removeLastSymbol();
    this->ui->expression_text->setText(expression);
}

void BasicPage::on_btnAC_clicked() {
    if (this->ui->expression_text->text().isEmpty()) {
        this->ui->last_result->clear();
    } else {
        this->expressionParser.clear();
        this->ui->expression_text->clear();
    }
}

void BasicPage::on_btnSign_clicked() {
    this->expressionParser.appendSymbol();
    this->ui->expression_text->setText(this->expressionParser.toString());
}

void BasicPage::on_btnEqual_clicked() {
    try {
        const double result = this->expressionParser.calculate();
        this->ui->expression_text->setText(QString::number(result, 'f', this->mainWindow->settings.getPrecision()));
        this->ui->last_result->setText(this->expressionParser.toString());

        this->expressionParser.clear();
        this->expressionParser.setLeft(result);

        this->mainWindow->database.addEntry(HistoryEntry(this->ui->last_result->text(), result, ""));
    } catch (const std::exception &_) {
        QMessageBox::critical(this->parentWidget(), "Ошибка вычислений", "Деление на 0 запрещено.");
    }
}
