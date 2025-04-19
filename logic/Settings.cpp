#include "Settings.h"

#include <QSettings>

const QString GEOMETRY_FUNCTION_DISPLAY_TYPE_KEY = "geometryFunctionDisplayType";
const QString PRECISION_KEY = "precision";

GeometryFunctionDisplayType Settings::getGeometryFunctionDisplayType() const {
    const int value = this->settings.value(GEOMETRY_FUNCTION_DISPLAY_TYPE_KEY, 0).toInt();
    if (value == 0) {
        return RADIANS;
    }
    if (value == 1) {
        return DEGREES;
    }
    qCritical() << "Unknown geometry function display type" << value;
    return RADIANS;
}

void Settings::setGeometryFunctionDisplayType(const GeometryFunctionDisplayType type) {
    this->settings.setValue(GEOMETRY_FUNCTION_DISPLAY_TYPE_KEY, type);
}

int Settings::getPrecision() const {
    return this->settings.value(PRECISION_KEY, 2).toInt();
}

void Settings::setPrecision(const int precision) {
    this->settings.setValue(PRECISION_KEY, precision);
}
