#pragma once
#include <QApplication>
#include <QFile>
#include <QFileSystemWatcher>
#include <memory>

class App : public QApplication {
public:
    App(int &argc, char **argv);
    void applyStyleSheet();
    void applyStyleSheet(const QString &path);

private:
    void setupStyleWatcher();
    QString getStyleFilePath() const;
private:
    QString _styleSheetPath();
};
