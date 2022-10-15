#ifndef HCOMMANDLINEPROCESSOR_H
#define HCOMMANDLINEPROCESSOR_H

#include <QObject>

class HCommandLineProcessor : public QObject
{
    Q_OBJECT
public:
    explicit HCommandLineProcessor(QObject *parent = nullptr);
private:
    void help();
    void wait5seconds();

    void wait4input();
    void dispatchCommand(const QString& command);

signals:
    void finished();
    void start();
    void stop();
public slots:
    void startup();
    void beginNextLoop();
};

#endif // HCOMMANDLINEPROCESSOR_H
