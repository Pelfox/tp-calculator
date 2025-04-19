#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

enum GeometryFunctionDisplayType {
    RADIANS,
    DEGREES,
};

class Settings {
public:
    Settings() = default;

    GeometryFunctionDisplayType getGeometryFunctionDisplayType() const;
    void setGeometryFunctionDisplayType(GeometryFunctionDisplayType type);

    int getPrecision() const;
    void setPrecision(int precision);

private:
    QSettings settings = QSettings();
};

#endif //SETTINGS_H
