#ifndef RCWEBCAM_H
#define RCWEBCAM_H

#include <QObject>
#include <QCamera>
#include <QMediaCaptureSession>
#include <QVideoWidget>
#include <QDebug>

class RCWebcam : public QObject {
    Q_OBJECT

public:
    RCWebcam(QVideoWidget* videoWidget, QObject* parent = nullptr)
        : QObject(parent), m_videoWidget(videoWidget) {}

public slots:
    void run() {
        qDebug() << "Webcam operation started...";

        // Inicializa a câmera
        m_camera = new QCamera(this);
        m_captureSession.setCamera(m_camera);

        // Configura o widget de vídeo
        m_captureSession.setVideoOutput(m_videoWidget);

        // Inicia a câmera
        m_camera->start();

        qDebug() << "Webcam operation finished.";
        emit finished();  // Emitir o sinal finished ao terminar
    }

signals:
    void finished();

private:
    QVideoWidget* m_videoWidget;
    QCamera* m_camera;
    QMediaCaptureSession m_captureSession;
};

#endif // RCWEBCAM_H
