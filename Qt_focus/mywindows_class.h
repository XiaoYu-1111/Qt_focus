#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QMessageBox>
#include <QCloseEvent>
#include <QPainter>
#include <QPainterPath>

class MySubWindow : public QWidget {
    Q_OBJECT

public:
    MySubWindow(QWidget* parent = nullptr);

private:
    QStatusBar* My_statusBar;
protected:
    void closeEvent(QCloseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override; // 重写鼠标双击事件
    void mouseMoveEvent(QMouseEvent* event) override;// 重写鼠标移动事件

private:
    void painter_axis(QPainter& painter);
    void painter_text(QPainter& painter);
    void painter_circle(QPainter& painter);
    void painter_bezier(QPainter& painter);
    void painter_mc(QPainter& painter);
    void painter_grid(QPainter& painter);

    QPoint doubleClickPosition;  // 保存双击位置
    bool drawCircle=false;              // 控制是否绘制圆圈
};
