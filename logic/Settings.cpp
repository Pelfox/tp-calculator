#include "Settings.h"

#include <QDir>
#include <QSettings>
#include <QTemporaryFile>

const QString GEOMETRY_FUNCTION_DISPLAY_TYPE_KEY = "geometryFunctionDisplayType";
const QString PRECISION_KEY = "precision";
const QString DB_FILE_KEY = "dbFile";

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

QString Settings::getDBFile() {
    if (this->settings.contains(DB_FILE_KEY)) {
        qDebug() << "DB file already exists";
        auto* file = new QFile(this->settings.value(DB_FILE_KEY).toString());
        if (file->exists()) {
            qDebug() << "DB file exists" << file->fileName();
            return this->settings.value(DB_FILE_KEY).toString();
        }
        qWarning() << "DB file does not exist, creating a new one";
        delete file;
    }


    const auto path = QDir::cleanPath(QDir::currentPath() + QDir::separator() + "calculator.db");
    qDebug() << "Creating new DB file" << path;

    this->settings.setValue(DB_FILE_KEY, path);
    const auto file = new QFile(path);
    if (!file->exists()) {
        file->open(QIODevice::ReadWrite);
        file->close();
    }

    return path;
}
