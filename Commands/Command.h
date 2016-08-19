#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>

#define COMMAND_NAME(class) #class

class Command : public QObject
{
    Q_OBJECT
public:
    explicit Command(QString name, QObject *parent = 0)
        : QObject(parent)
        , mFinished(false)
        , mName(name) {}

    virtual~Command(){}

    virtual void execute() = 0;

    bool finished() const { return mFinished; }
    QString name() const { return mName; }

signals:
    void commandProgress(quint32 updateProgress);
    void commandFinished();

protected:
    // every derrived class must call finish (or use CommandFinisher)
    // to finish command exection
    void finish() { mFinished = true; emit commandFinished(); }

protected:
    bool mFinished;
    QString mName;

protected:
    class CommandFinisher
    {
    public:
        explicit CommandFinisher(Command* command)
            : mCommand(command) {}

        ~CommandFinisher()
        {
            mCommand->finish();
        }

    private:
        Command* mCommand;
    };
};

#endif // COMMAND_H
