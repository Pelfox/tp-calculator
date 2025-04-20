#ifndef EXPRESSIONPARSER_H
#define EXPRESSIONPARSER_H

#include <QString>
#include <optional>

#include "Settings.h"

enum class ExpressionOperationType {
    UNKNOWN, // -1
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,

    // trigonometric functions
    SIN,
    COS,
    TAN,
    COTAN,
    SEC,
    COSEC,
};

class ExpressionParser {
public:
    explicit ExpressionParser(Settings &settings) : settings(settings) {
    }

    void setRight(double value);

    void setLeft(double value);

    void clear(bool includeResult = true);

    QString removeLastSymbol();

    QString appendDot();

    void appendSymbol();

    QString appendDigit(double digit);

    double calculate();

    void setOperationFromVariant(int variant);

    void setOperation(ExpressionOperationType type);

    [[nodiscard]] QString toString() const;

private:
    Settings &settings;
    QString left = QString();
    QString right = QString();
    std::optional<double> result = std::nullopt;
    ExpressionOperationType operationType = ExpressionOperationType::UNKNOWN;
};

#endif //EXPRESSIONPARSER_H
