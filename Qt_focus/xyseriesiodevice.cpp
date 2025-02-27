// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "xyseriesiodevice.h"

XYSeriesIODevice::XYSeriesIODevice(QXYSeries* series, QObject* parent) :
    QIODevice(parent),
    m_series(series),
    m_audioFile(nullptr)//initialize to nullptr
{
}

qint64 XYSeriesIODevice::readData(char* data, qint64 maxSize)
{
    Q_UNUSED(data);
    Q_UNUSED(maxSize);
    return -1;
}

qint64 XYSeriesIODevice::writeData(const char* data, qint64 maxSize)
{
    static const int resolution = 4;

    if (m_buffer.isEmpty()) {// first write
        m_buffer.reserve(sampleCount);
        for (int i = 0; i < sampleCount; ++i)
            m_buffer.append(QPointF(i, 0));
    }
    //如果可用的样本数量小于 sampleCount
    // 将缓冲区中前面的样本 Y 值更新为后面的样本值
    // 以保持缓冲区域的平滑性。
    int start = 0;
    const int availableSamples = int(maxSize) / resolution;
    if (availableSamples < sampleCount) {
        start = sampleCount - availableSamples;
        for (int s = 0; s < start; ++s)
            m_buffer[s].setY(m_buffer.at(s + availableSamples).y());
    }
    //将数据写入缓冲区
    for (int s = start; s < sampleCount; ++s, data += resolution)
        m_buffer[s].setY(qreal(uchar(*data) - 128) / qreal(128));
    //将缓冲区中的数据更新到 QXYSeries 中
    m_series->replace(m_buffer);
            // 输出最新（最后一个）数值
            /*if (!m_buffer.isEmpty()) {
                qDebug() << "Latest value:" << m_buffer.last().y();
            }*/
    return (sampleCount - start) * resolution;
}

QByteArray XYSeriesIODevice::readAudioData() {
    QByteArray audioData;
    qDebug() << "Buffer size:" << m_buffer.size(); // 输出缓冲区的大小
    // 假设你的数据存储在某个缓冲区中，这里你可以将数据转化为 QByteArray
    // 这里的示例需要根据你的数据来源进行调整
    if (m_buffer.isEmpty()) { // first write
        m_buffer.reserve(sampleCount);
        for (int i = 0; i < sampleCount; ++i)
            m_buffer.append(QPointF(i, 0)); // 这里确保填充有效数据
    }

    for (const auto& point : m_buffer) {
        audioData.append(static_cast<char>(point.y() * 128 + 128)); // 示例转换
    }
    return audioData;
}