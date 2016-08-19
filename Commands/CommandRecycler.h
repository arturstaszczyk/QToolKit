#ifndef COMMANDRECYCLER_H
#define COMMANDRECYCLER_H

#include <chrono>

#include <QTimer>
#include <QObject>

#include <Commands/Command.h>

class CommandRecycler : public QObject
{
    Q_OBJECT
public:

    static CommandRecycler& instance() { return sInstance; }

    void setUpdateTime(std::chrono::milliseconds recyclerRefreshRate);
    void executeAndDispose(Command* command);

private slots:
    void recycleCommands();

private:
    QTimer* mRecyclerTimer;
    QList<Command*> mCommandsContainer;


    explicit CommandRecycler(QObject *parent = 0);
    Q_DISABLE_COPY(CommandRecycler)

    static CommandRecycler sInstance;
};

#endif // COMMANDRECYCLER_H
