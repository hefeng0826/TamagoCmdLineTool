#include "hcommandlineprocessor.h"
#include <iostream>
#include <QTimer>

using namespace std;
HCommandLineProcessor::HCommandLineProcessor(QObject *parent) : QObject(parent)
{

}

void HCommandLineProcessor::help()
{
    cout<<"TamagoCmdLineTool Help"<<endl;
}

void HCommandLineProcessor::wait5seconds()
{
    cout<<"waitting 5 seconds..."<<endl;
    QTimer::singleShot(5000, this, SLOT(beginNextLoop()));
}

void HCommandLineProcessor::wait4input()
{
    cout<<"Tamago waitting input..."<<endl;
    string command;
    cin >> command;

    dispatchCommand(QString(command.c_str()));
}

void HCommandLineProcessor::dispatchCommand(const QString &command)
{
    if(command == "quit")
    {
        emit finished();
        return;
    }
    else if(command == "help")
    {
        help();
    }
    else if(command == "wait")
    {
        wait5seconds();
        return;
    }
    else if(command == "start")
    {
        emit start();
    }
    else if(command == "pause")
    {
        emit stop();
    }
    else
    {
        cout<<"Wrong command! Press any key contine..."<<endl;
        char c;
        cin>>c;
    }
    QTimer::singleShot(0, this, SLOT(beginNextLoop()));
}

void HCommandLineProcessor::startup()
{
    cout<<"TamagoCmdLineTool version 1.0"<<endl;
    QTimer::singleShot(0, this, SLOT(beginNextLoop()));
}

void HCommandLineProcessor::beginNextLoop()
{
    wait4input();
}
