#include "App.hpp"
#include "StandardFile.hpp"
App::App(int &argc, char **argv)
    : QApplication(argc, argv)
{
    applyStyleSheet();
    setupStyleWatcher();
}

void App::applyStyleSheet()
{
  auto f = std::make_unique<StandardFile>(getStyleFilePath().toStdString());
    if (f->open()) {
        this->setStyleSheet(QString::fromStdString(f->readAll()));
        qDebug() << "StyleSheet reîncărcat cu succes.";
    }
}

void App::applyStyleSheet(const QString &path)
{
    auto f = std::make_unique<StandardFile>(getStyleFilePath().toStdString());
    if (f->open()) {
        this->setStyleSheet(QString::fromStdString(f->readAll()));
        qDebug() << "StyleSheet reîncărcat cu succes.";
    }
}

QString App::getStyleFilePath() const {
   QString localPath = QString(SOURCE_DIR) + "/src/style.qss";
    if (StandardFile::exists(localPath.toStdString())) {
        return localPath;
    }
    return {};
}

void App::setupStyleWatcher() {
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
