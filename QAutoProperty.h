#ifndef QAUTOPROPERTY_H
#define QAUTOPROPERTY_H

#include <QList>
#include <QObject>
#include <QQmlListProperty>
//https://gist.github.com/Rolias/48d453a0490d36090193

#define AUTO_PROPERTY(TYPE, NAME) \
    Q_PROPERTY(TYPE NAME READ NAME WRITE NAME NOTIFY NAME ## Changed ) \
    public: \
       TYPE NAME() const { return a_ ## NAME ; } \
       void NAME(TYPE value) { \
          if (a_ ## NAME == value)  return; \
          a_ ## NAME = value; \
          emit NAME ## Changed(value); \
        } \
       Q_SIGNAL void NAME ## Changed(TYPE value);\
    private: \
       TYPE a_ ## NAME;

#define READONLY_PROPERTY(TYPE, NAME) \
    Q_PROPERTY(TYPE NAME READ NAME CONSTANT ) \
    public: \
       TYPE NAME() const { return a_ ## NAME ; } \
    private: \
       void NAME(TYPE value) {a_ ## NAME = value; } \
       TYPE a_ ## NAME;

#define LIST_PROPERTY(TYPE, NAME) \
    Q_PROPERTY(QQmlListProperty<TYPE> NAME READ NAME NOTIFY NAME ## Changed) \
    public: \
        QQmlListProperty<TYPE> NAME() { return QQmlListProperty<TYPE>(this, a_ ## NAME ## Raw); } \
        QList<TYPE*> NAME ## Raw() const { return a_ ## NAME ## Raw; } \
        void NAME ## Add(TYPE* value) { \
            a_ ## NAME ## Raw.append(value); \
            emit NAME ## Changed(QQmlListProperty<TYPE>(this, a_ ## NAME ## Raw)); \
        } \
        void NAME ## Clear() { \
            a_ ## NAME ## Raw.clear(); \
            emit NAME ## Changed(QQmlListProperty<TYPE>(this, a_ ## NAME ## Raw)); \
        } \
        void NAME(QList<TYPE*> value) { \
            a_ ## NAME ## Raw = value; \
            emit NAME ## Changed(QQmlListProperty<TYPE>(this, a_ ## NAME ## Raw)); \
        } \
        Q_SIGNAL void NAME ## Changed(QQmlListProperty<TYPE> value); \
    private: \
        QList<TYPE*> a_ ## NAME ## Raw;



#endif // QAUTOPROPERTY_H
