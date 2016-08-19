#include "CommandRecycler.h"

#include <QDebug>

#include "QToolKit/Commons.h"

CommandRecycler CommandRecycler::sInstance;

CommandRecycler::CommandRecycler(QObject *parent)
    : QObject(parent)
    , mRecyclerTimer(nullptr)
{
}

void CommandRecycler::setUpdateTime(std::chrono::milliseconds recyclerRefreshRate)
{
    SAFE_DELETE(mRecyclerTimer);

    mRecyclerTimer = new QTimer();
    mRecyclerTimer->setParent(this);
    mRecyclerTimer->setInterval(recyclerRefreshRate.count());
    mRecyclerTimer->setSingleShot(false);
    connect(mRecyclerTimer, SIGNAL(timeout()), this, SLOT(recycleCommands()));
    mRecyclerTimer->start();
}

void CommandRecycler::executeAndDispose(Command *command)
{
    mCommandsContainer.append(command);
    qDebug() << "Starting " << command->name();
    command->execute();
}

void CommandRecycler::recycleCommands()
{
    static Command* cmd;
    static QList<Command*> garbage;

    cmd = nullptr;
    garbage.clear();

    foreach(cmd, mCommandsContainer)
    {
        if(cmd->finished())
            garbage.append(cmd);
    }

    foreach(cmd, garbage)
    {
        mCommandsContainer.removeOne(cmd);
        qDebug() << "Finishing " << cmd->name();
        delete cmd;
    }

    garbage.clear();
}
