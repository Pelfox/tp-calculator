#include "ExpressionParser.h"

QString operationTypeToString(const ExpressionOperationType type) {
    switch (type) {
        case ExpressionOperationType::ADDITION:
            return "+";
        case ExpressionOperationType::SUBTRACTION:
            return "-";
        case ExpressionOperationType::MULTIPLICATION:
            return "*";
        case ExpressionOperationType::DIVISION:
            return "/";
        default:
            return "UNKNOWN";
    }
}

ExpressionOperationType operationTypeFromVariant(const int variant) {
    switch (variant) {
        case 0:
            return ExpressionOperationType::ADDITION;
        case 1:
            return ExpressionOperationType::SUBTRACTION;
        case 2:
            return ExpressionOperationType::MULTIPLICATION;
        case 3:
            return ExpressionOperationType::DIVISION;
        default:
            return ExpressionOperationType::UNKNOWN;
    }
}

void ExpressionParser::setRight(const double value) {
    this->right = QString::number(value);
}

void ExpressionParser::setLeft(const double value) {
    this->left = QString::number(value);
}

void ExpressionParser::clear(bool includeResult) {
    this->left.clear();
    this->right.clear();
    this->operationType = ExpressionOperationType::UNKNOWN;

    if (includeResult) {
        this->result = std::nullopt;
    }
}

QString ExpressionParser::removeLastSymbol() {
    QString value = this->left;
    if (this->operationType != ExpressionOperationType::UNKNOWN) {
        value = this->right;
    }

    if (value.isEmpty()) {
        this->result = std::nullopt;
        this->operationType = ExpressionOperationType::UNKNOWN;
        return "";
    }

    value.chop(1);
    if (this->operationType == ExpressionOperationType::UNKNOWN) {
        this->left = value;
    } else {
        this->right = value;
    }

    return value;
}

QString ExpressionParser::appendDot() {
    QString value = this->left;
    if (this->operationType != ExpressionOperationType::UNKNOWN) {
        value = this->right;
    }

    if (value.length() == 0) {
        value.append("0");
    }

    value.append(".");
    if (this->operationType == ExpressionOperationType::UNKNOWN) {
        this->left = value;
    } else {
        this->right = value;
    }

    return value;
}

void ExpressionParser::appendSymbol() {
    QString value = this->left;
    if (this->operationType != ExpressionOperationType::UNKNOWN) {
        value = this->right;
    }

    if (value.startsWith("-")) {
        value.remove(0, 1);
    } else {
        value.prepend("-");
    }

    if (this->operationType == ExpressionOperationType::UNKNOWN) {
        this->left = value;
    } else {
        this->right = value;
    }
}

QString ExpressionParser::appendDigit(const int digit) {
    if (this->operationType == ExpressionOperationType::UNKNOWN) {
        this->left.append(QString::number(digit));
        return this->left;
    }
    this->right.append(QString::number(digit));
    return this->right;
}

double ExpressionParser::calculate() {
    if (this->right.isEmpty()) {
        return this->left.toDouble();
    }

    const double leftValue = this->left.toDouble();
    const double rightValue = this->right.toDouble();
    double result;

    switch (this->operationType) {
        case ExpressionOperationType::ADDITION:
            result = leftValue + rightValue;
            break;
        case ExpressionOperationType::SUBTRACTION:
            result = leftValue - rightValue;
            break;
        case ExpressionOperationType::MULTIPLICATION:
            result = leftValue * rightValue;
            break;
        case ExpressionOperationType::DIVISION:
            if (rightValue == 0) {
                throw std::runtime_error("Division by zero");
            }
            result = leftValue / rightValue;
            break;
        default:
            return 0;
    }

    this->result = result;
    return result;
}

void ExpressionParser::setOperationFromVariant(const int variant) {
    this->operationType = operationTypeFromVariant(variant);
}

void ExpressionParser::setOperation(const ExpressionOperationType type) {
    this->operationType = type;
}

QString ExpressionParser::toString() const {
    QString result;
    if (!this->left.isEmpty()) {
        result.append(this->left);
    }
    if (this->operationType != ExpressionOperationType::UNKNOWN) {
        result.append(operationTypeToString(this->operationType));
    }
    if (!this->right.isEmpty()) {
        result.append(this->right);
    }
    if (this->result.has_value()) {
        if (!this->right.isEmpty() && !this->left.isEmpty()) {
            result.append(" = ");
        } else {
            result.append(QString::number(this->result.value()));
        }
    }
    return result;
}

