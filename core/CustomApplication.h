#pragma once

#include <QApplication>
#include <QString>
#include <QFile>


class CustomApplication : public QApplication {
    Q_OBJECT
    public:
        CustomApplication(int &argc, char **argv);
        
        static CustomApplication* instance();

        void applyStyleSheet();     

    private:
        QString getStyleFilePath() const;   
        void setupStyleWatcher();
    private:
        QString _styleSheetPath;
        static CustomApplication* _instance;
};