#ifndef IFRAMELISTENER_H
#define IFRAMELISTENER_H

class IFrameListener {
public:
    virtual ~IFrameListener() {}
    virtual void addChangeListener(IFrameListener* listener) = 0;
    virtual void removeChangeListener(IFrameListener* listener) = 0;

};

#endif // IFRAMELISTENER_H
