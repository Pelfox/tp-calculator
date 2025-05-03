#ifndef SETTINGS_H
#define SETTINGS_H

#include <QFile>
#include <QSettings>

enum GeometryFunctionDisplayType {
    RADIANS,
    DEGREES,
};

class Settings {
public:
    Settings() = default;

    [[nodiscard]] GeometryFunctionDisplayType getGeometryFunctionDisplayType() const;

    void setGeometryFunctionDisplayType(GeometryFunctionDisplayType type);

    [[nodiscard]] int getPrecision() const;

    void setPrecision(int precision);

    QString getDBFile();

private:
    QSettings settings = QSettings("MIREA", "TP Calculator");
};

#endif //SETTINGS_H
