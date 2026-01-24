#pragma once

#ifndef SANDSIMULATOR_H
#define SANDSIMULATOR_H
#include <QWidget>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QTimer>
#include <vector>
#include <cmath>
#include <QRandomGenerator> // 需要包含这个头文件
#include <QVector2D>
#include <QMouseEvent>

// 表示沙粒的类
class SandParticle {
public:
    // 粒子的位置
    float position_x, position_y;
    // 粒子的速度
    float velocityX, velocityY;

    float mass; // 质量
    QColor color; // 新增颜色属性
    float radius; // 新增半径属性
    float accelerationX; // 新增加速度属性
    float accelerationY; // 新增加速度属性
    SandParticle(float x, float y,float m=1.0f, float radius =50.0f) :
        position_x(x), position_y(y), 
        velocityX(0.0f), velocityY(0.0f),
        mass(m),radius(radius),
        accelerationX(0.0f), accelerationY(0.0f)  // 为加速度初始化
    {
        // 为粒子随机生成颜色
        int lowerBound = 100;
        color.setRgb(QRandomGenerator::global()->bounded(lowerBound,256),
            QRandomGenerator::global()->bounded(lowerBound,256),
            QRandomGenerator::global()->bounded(lowerBound,256));
    }
};

// 沙子模拟器类
class SandSimulator : public QWidget {
    Q_OBJECT

public:
    // 构造函数
    explicit SandSimulator(QWidget* parent = nullptr);

public:
    const float GRAVITY = 1.0f; // 重力加速度
    const float DRAG = 0.01f; // 摩擦力系数
    const float MAX_SPEED = 10.0f; // 最大速度
    const float pi = 3.1415926; // 圆周率
    int border_width = 50; // 边界宽度

    int particleCount = 200; // 粒子数量
    int paricleRadius = 10; // 粒子半径

    int FPS = 50;  // 帧率
    int frameTime = 1000 / FPS;  // 间隔时间
	int deltaTime = 0; // 上次更新时间

protected:
    // 绘图事件处理
    void paintEvent(QPaintEvent* event) override;
    void showEvent(QShowEvent* event)override;
    void mouseDoubleClickEvent(QMouseEvent* event)override;
    void keyPressEvent(QKeyEvent* event)override;


private:
    QStatusBar* Sand_statusBar;
private:
    std::vector<SandParticle> particles; // 存储沙粒
    QTimer* timer; // 定时器
    void updateParticles(); // 更新粒子状态
    void applyGravityAndDrag(SandParticle& particle); // 应用重力和阻力
    
    void generateParticles();
    void applyBoundaryCollision(SandParticle& particle, int border);

    void checkP_PCollisions();
    bool isParticleAtBoundary(size_t index);
    void applyDamping(SandParticle& particle, float damping);
    void limitSpeed(SandParticle& particle, float maxSpeed);
    void painter_text(QPainter& painter, QString& text);

    void clearParticles() {
        particles.clear(); update();
	} // 清除所有粒子

};


#endif // SANDSIMULATOR_H