#include <QCoreApplication>
#include "hcommandlineprocessor.h"
#include "hthread.h"
#include <QTimer>
#include <iostream>
#include <QDebug>

void on_objectCreated(MyObject*);
void on_threadStarted();

HCommandLineProcessor* cmd_processor;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cmd_processor = new HCommandLineProcessor(&a);

    QObject::connect(cmd_processor, SIGNAL(finished()), &a, SLOT(quit()));

    QTimer::singleShot(0, cmd_processor, SLOT(startup()));

    HThread *thread = new HThread;

    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    QObject::connect(thread, &HThread::objectCreated, on_objectCreated);
    QObject::connect(thread, &HThread::started, on_threadStarted);

    thread->start();
    qDebug()<<QThread::currentThreadId();
    std::cout<<"starting up..."<<std::endl;
    return a.exec();
}

void on_objectCreated(MyObject* obj)
{
    std::cout<<__func__<<std::endl;
    QObject::connect(cmd_processor, SIGNAL(start()), obj, SLOT(on_start()));
    QObject::connect(cmd_processor, SIGNAL(stop()), obj, SLOT(on_stop()));
}

void on_threadStarted()
{
    std::cout<<"Thread Started"<<std::endl;
}
