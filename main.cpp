#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;

    // disable resizing for the window
    window.setWindowFlags(window.windowFlags() & ~Qt::WindowMinimizeButtonHint);
    window.setFixedSize(window.size());

    // set application icon
    QApplication::setWindowIcon(QIcon(":/icons/icon.png"));

    window.show();
    return QApplication::exec();
}
