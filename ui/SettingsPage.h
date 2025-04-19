#ifndef SETTINGS_PAGE_H
#define SETTINGS_PAGE_H

#include "MainWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class SettingsPage;
}
QT_END_NAMESPACE

class SettingsPage final : public QWidget {
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr);
    ~SettingsPage() override;

private slots:
    void onGeometryTypeDegreeToggled(bool checked) const;
    void onGeometryTypeRadiansToggled(bool checked) const;
    void onPrecisionChanged(int value) const;

private:
    Ui::SettingsPage *ui;
    MainWindow *mainWindow;
};

#endif //SETTINGS_PAGE_H
