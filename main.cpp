/**
 * @file main.cpp
 * @brief Application entry point.
 *
 * Responsibilities:
 *  1. Create the QApplication instance.
 *  2. Load and apply @c style.qss (with live-reload during development).
 *  3. Construct and show MainWindow.
 *
 * ### Stylesheet loading strategy
 * The CMake build injects the macro @c SOURCE_DIR pointing to the project
 * source root.  At startup the app tries to open @c SOURCE_DIR/style.qss
 * directly from the filesystem.  If it exists, a QFileSystemWatcher is
 * set up so that every time the file is saved the stylesheet is re-applied
 * without restarting the application — useful while tweaking colours.
 *
 * If the source file is not present (e.g. in a distributed build), the
 * embedded Qt resource @c :/style.qss is used instead.
 *
 * @note Some editors (VS Code, Kate) save files by deleting and recreating
 *       them, which causes the OS to remove the inotify watch.  The watcher
 *       callback re-adds the path after each change event to handle this.
 */

#include <QApplication>
#include "MainWindow.h"
#include "core/CustomApplication.h"



/**
 * @brief Application entry point.
 * @param argc Argument count passed by the OS.
 * @param argv Argument vector passed by the OS.
 * @return Exit code returned to the OS (0 on clean exit).
 */
int main(int argc, char *argv[]) {
    
    CustomApplication a(argc, argv);
        
    MainWindow w;
    w.show();

    return a.exec();
}
