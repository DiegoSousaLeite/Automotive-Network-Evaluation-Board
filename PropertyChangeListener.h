#ifndef PROPERTYCHANGELISTENER_H
#define PROPERTYCHANGELISTENER_H

class PropertyChangeListener {
public:
    virtual ~PropertyChangeListener() {}
    virtual void propertyChanged(const QString &property, const QVariant &oldValue, const QVariant &newValue) = 0;
};


#endif // PROPERTYCHANGELISTENER_H
