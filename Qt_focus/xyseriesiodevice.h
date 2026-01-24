// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef XYSERIESIODEVICE_H
#define XYSERIESIODEVICE_H

#include <QIODevice>
#include <QList>
#include <QPointF>
#include<QFile>
#include <QtCharts/QXYSeries>

QT_FORWARD_DECLARE_CLASS(QXYSeries)

#define sampleCount0 1000//1000 samples per second
#define sampleCount1 5000//2000 samples per second

class XYSeriesIODevice : public QIODevice
{
    Q_OBJECT
public:

    explicit XYSeriesIODevice(QXYSeries* series, QObject* parent = nullptr);
    static const int sampleCount = sampleCount0;

    QFile* getAudioFile() {
        return m_audioFile;
    }
    void setAudioFile(QFile* file) {
        m_audioFile = file;
    }
protected:
    qint64 readData(char* data, qint64 maxSize) override;
    qint64 writeData(const char* data, qint64 maxSize) override;
   
private:
    QXYSeries* m_series = nullptr;
    QList<QPointF> m_buffer;

    QFile* m_audioFile=nullptr;

public:
    QByteArray readAudioData(); // 确保这个函数是 public

};
#endif // XYSERIESIODEVICE_H