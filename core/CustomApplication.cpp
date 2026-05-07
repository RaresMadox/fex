#include "CustomApplication.h"
#include "utils/StandardFile.h"
#include <QFileSystemWatcher>
#include <memory>

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

CustomApplication::~CustomApplication() {}

void CustomApplication::applyStyleSheet() {
    auto f = std::make_unique<StandardFile>(getStyleFilePath().toStdString());
    if (f->open()) {
        this->setStyleSheet(QString::fromStdString(f->readAll()));
        qDebug() << "StyleSheet reîncărcat cu succes.";
    }
}

void CustomApplication::setupStyleWatcher() {
    QString path = getStyleFilePath();

    if (!path.isEmpty()) {
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
    if (StandardFile::exists(localPath.toStdString())) {
        return localPath;
    }
    return {};
}