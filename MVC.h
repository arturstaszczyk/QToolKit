#ifndef MVC_H
#define MVC_H

#include <QObject>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#define MODEL_CLASS_BEGIN(ClassName) \
    class ClassName ## Model : public QObject { \
    public: \
        explicit ClassName ## Model (QObject* parent = nullptr) \
            : QObject(parent) {}

#define MODEL_CLASS_END };

#define CONTROLLER_CLASS_DEFINE_BEGIN(ClassName) \
    class ClassName ## Model; \
    class ClassName ## Controller : public QObject { \
    public: \
        explicit NavigationBarController(QQmlApplicationEngine& engine, QObject *parent = 0); \
    private: \
        ClassName ## Model* mModel;


#define CONTROLLER_CLASS_DEFINE_END };

#define CONTROLLER_CLASS_DEFINE(ClassName) \
    CONTROLLER_CLASS_DEFINE_BEGIN(ClassName) \
    CONTROLLER_CLASS_DEFINE_END

#define CONTROLLER_CLASS_DELCARE(ClassName, ModelProperty, ControllerProperty) \
    ClassName ## Controller::ClassName ## Controller(QQmlApplicationEngine& engine, \
        QObject *parent) \
        : QObject(parent) {\
        mModel = new ClassName ## Model(this); \
        engine.rootContext()->setContextProperty(ModelProperty, mModel); \
        engine.rootContext()->setContextProperty(ControllerProperty, this); \
    }


#endif // MVC_H
