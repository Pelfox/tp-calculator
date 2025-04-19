#ifndef EXPRESSIONPARSER_H
#define EXPRESSIONPARSER_H

#include <QString>
#include <optional>

enum class ExpressionOperationType {
    UNKNOWN,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
};

class ExpressionParser {
public:
    ExpressionParser() = default;

    void setRight(double value);
    void setLeft(double value);

    void clear(bool includeResult = true);
    QString removeLastSymbol();

    QString appendDot();
    void appendSymbol();
    QString appendDigit(int digit);

    double calculate();

    void setOperationFromVariant(int variant);
    void setOperation(ExpressionOperationType type);

    [[nodiscard]] QString toString() const;

private:
    QString left = QString();
    QString right = QString();
    std::optional<double> result = std::nullopt;
    ExpressionOperationType operationType = ExpressionOperationType::UNKNOWN;
};

#endif //EXPRESSIONPARSER_H
