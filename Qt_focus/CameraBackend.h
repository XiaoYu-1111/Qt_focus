#ifndef CAMERABACKEND_H
#define CAMERABACKEND_H

#include <QObject>
#include <QCamera>
#include <QImageCapture>
#include <QMediaDevices>
#include <QVideoWidget>
#include <QMediaCaptureSession>
#include <QDebug>

class CameraBackend : public QObject
{
    Q_OBJECT
public:
    explicit CameraBackend(QObject* parent = nullptr) : QObject(parent) {
        // 初始化摄像头和图像捕获对象
        camera = new QCamera();
        imageCapture = new QImageCapture();
        videoWidget = new QVideoWidget;//视频窗口
        captureSession = new QMediaCaptureSession();//媒体捕获会话
        captureSession->setImageCapture(imageCapture);//设置图像捕获

    }
    Q_INVOKABLE void openCamera() {
        camera->start(); // 启动摄像头
        captureImage(); // 拍照
    }
    void captureImage() {
        captureSession->setCamera(camera);
        imageCapture->capture(); // 拍照
        int captureId = imageCapture->capture();
        qDebug() << "Capture ID:" << captureId;
    }

private:
    QCamera* camera;          // 摄像头对象
    QImageCapture* imageCapture; // 图像捕获对象
    QVideoWidget* videoWidget;
	QMediaCaptureSession* captureSession;// 媒体捕获会话
};

#endif // CAMERABACKEND_H
