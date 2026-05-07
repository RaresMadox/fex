#include "CustomApplication.h"
#include <QFile>
#include <QFileSystemWatcher>

CustomApplication* CustomApplication::_instance = nullptr;

CustomApplication::CustomApplication(int &argc, char **argv) : QApplication(argc, argv)
{

    if (_instance) {
            qFatal("Error: Only one instance of CustomApplication is allowed!");
    }
        _instance = this;

    applyStyleSheet();   // Aplicăm stilul inițial
    setupStyleWatcher(); // Pornim monitorizarea fișierului

}

void CustomApplication::applyStyleSheet() {
    QFile f(getStyleFilePath());
    if (f.open(QFile::ReadOnly)) {
        this->setStyleSheet(f.readAll());
        f.close();
        qDebug() << "StyleSheet reîncărcat cu succes.";
    }
}

void CustomApplication::setupStyleWatcher() {
    QString path = getStyleFilePath();

    if (!path.startsWith(":/")) {
        auto *watcher = new QFileSystemWatcher({path}, this);
        
        QObject::connect(watcher, &QFileSystemWatcher::fileChanged, this, [this, watcher, path](const QString &) {
            this->applyStyleSheet();
            
            if (!watcher->files().contains(path)) {
                watcher->addPath(path);
            }
        });
        
        qDebug() << "Monitorizare activată pentru:" << path;
    }
}

QString CustomApplication::getStyleFilePath() const {
    QString localPath = QString(SOURCE_DIR) + "/style.qss";
    if (QFile::exists(localPath)) {
        return localPath;
    }
    return QStringLiteral(":/style.qss");
}