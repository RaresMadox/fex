#include "MainWindow.hpp"
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)    
{       
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QLabel* label = new QLabel("Hello World!");
    label->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->addWidget(label);
}
