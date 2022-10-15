#ifndef HTHREAD_H
#define HTHREAD_H

#include <QThread>

class MyObject : public QObject
{
    Q_OBJECT
public:
    MyObject(QObject* parent = nullptr);
    virtual ~MyObject();

protected:
    void timerEvent(QTimerEvent *event) override;

public slots:
    void on_start();
    void on_stop();

private:
    int _timerId;
};

class HThread : public QThread
{
    Q_OBJECT
public:
    HThread(QObject* parent = nullptr);
    virtual ~HThread();

protected:
    void run() override;

signals:
    void objectCreated(MyObject*);
};

#endif // HTHREAD_H
