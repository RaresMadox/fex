#include <QApplication>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

//----------------------------------------------------------------
int main(int argc,char *argv[]){

    QApplication app(argc,argv);

    QWidget *window = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(window);
    QLabel *label = new QLabel("Hello World!");
    label->setAlignment(Qt::AlignCenter);


    label->resize(400,200);
    window->setFixedSize(650,400);
    
    layout->addWidget(label,Qt::AlignCenter);
    
    window->show();
    return app.exec();
}
