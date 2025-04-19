#include <QCheckBox>
#include "Settings.h"

#include "SettingsPage.h"
#include "ui_SettingsPage.h"

void initializeSettings(const Settings &settings, const Ui::SettingsPage *ui) {
    // geometry function display type
    if (settings.getGeometryFunctionDisplayType() == DEGREES) {
        ui->geometryTypeDegree->setChecked(true);
    } else {
        ui->geometryTypeRadians->setChecked(true);
    }

    // precision
    const int precision = settings.getPrecision();
    ui->precisionInput->setValue(precision);
}

SettingsPage::SettingsPage(QWidget *parent) : QWidget(parent), ui(new Ui::SettingsPage),
                                              mainWindow(dynamic_cast<MainWindow *>(parent)) {
    this->ui->setupUi(this);
    initializeSettings(this->mainWindow->settings, this->ui);

    connect(this->ui->geometryTypeDegree, &QCheckBox::toggled, this, &SettingsPage::onGeometryTypeDegreeToggled);
    connect(this->ui->geometryTypeRadians, &QCheckBox::toggled, this, &SettingsPage::onGeometryTypeRadiansToggled);
    connect(this->ui->precisionInput, &QSpinBox::valueChanged, this, &SettingsPage::onPrecisionChanged);
}

SettingsPage::~SettingsPage() {
    delete this->ui;
}

void SettingsPage::onGeometryTypeDegreeToggled(const bool checked) const {
    if (checked) {
        this->mainWindow->settings.setGeometryFunctionDisplayType(DEGREES);
    }
}

void SettingsPage::onGeometryTypeRadiansToggled(const bool checked) const {
    if (checked) {
        this->mainWindow->settings.setGeometryFunctionDisplayType(RADIANS);
    }
}

void SettingsPage::onPrecisionChanged(const int value) const {
    this->mainWindow->settings.setPrecision(value);
}
