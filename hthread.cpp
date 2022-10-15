#include "hthread.h"
#include <QTime>
#include <QTimerEvent>
#include <iostream>
#include <QDebug>

using namespace std;

HThread::HThread(QObject *parent)
    :QThread(parent)
{

}

HThread::~HThread()
{
    qDebug()<<__func__;
}

void HThread::run()
{
    MyObject *obj = new MyObject;
    connect(this, SIGNAL(finished()), obj, SLOT(deleteLater()));
    emit objectCreated(obj);

    exec();
}

MyObject::MyObject(QObject *parent)
    :QObject(parent)
{

}

MyObject::~MyObject()
{
    qDebug()<<__func__;
}

void MyObject::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == _timerId)
    {
        qDebug()<<__func__<<QThread::currentThreadId();
        std::cout<<QTime::currentTime().toString("HHmmss.zzz").toStdString()<<endl;
    }
}

void MyObject::on_start()
{
    cout<<__func__<<"starting..."<<endl;
    _timerId = startTimer(1000);
}

void MyObject::on_stop()
{
    cout<<__func__<<endl;
    killTimer(_timerId);
}
