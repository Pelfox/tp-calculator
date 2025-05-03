#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.setWindowFlags(window.windowFlags() & ~Qt::WindowMinimizeButtonHint);
    window.setFixedSize(window.size());
    window.show();
    return QApplication::exec();
}
