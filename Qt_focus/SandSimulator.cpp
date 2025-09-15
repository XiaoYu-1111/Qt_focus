#include "SandSimulator.h"
#include <QPainter>
#include <cstdlib>
#include<chrono>
#include <thread>
#include<qpushbutton.h>

SandSimulator::SandSimulator(QWidget* parent) : QWidget(parent) {

    QString styleSheet = "QWidget{background-color: #1e293b;}";
    setStyleSheet(styleSheet);
    // 创建布局
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    // 初始化状态栏
    Sand_statusBar = new QStatusBar(this);
    Sand_statusBar->setMaximumHeight(20);
    Sand_statusBar->setSizeGripEnabled(false);
    layout->addWidget(Sand_statusBar, 0, Qt::AlignBottom);
    // 设置状态栏样式
    QString widget_statusbar = "font-size: 18px;background-color:#374357;"
        "color: #cee8ff;"
        "border-top-left-radius: 0px;"
        "border-top-right-radius: 0px;"
        "border-bottom-left-radius: 5px;"
        "border-bottom-right-radius:5px;"; // 深色
    Sand_statusBar->setStyleSheet(widget_statusbar);
    Sand_statusBar->showMessage("init statusbar", 5000);

    QPushButton* button_clear = new QPushButton("Clear",this);
    //设置按钮位置100,100
    button_clear->setGeometry(100, 100, 100, 20);
    button_clear->setStyleSheet(widget_statusbar);
    //layout->addWidget(button_clear, 1, Qt::AlignBottom);

    connect(button_clear, &QPushButton::clicked, [=] {
		particles.clear();
        int number = particles.size();
        Sand_statusBar->showMessage(QString("all particles %1, Added 10 particles.").arg(number), 2000);
		update(); // 触发绘图事件
        });
}

void SandSimulator::paintEvent(QPaintEvent* event) {

	std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	);

    QPainter painter(this);
    QColor backgroundColor =Qt::green; // 新增颜色属性
    // 可以设置画笔颜色和宽度
    QPen pen(backgroundColor, 2); // 设置画笔颜色和宽度
    painter.setPen(pen);

    // 绘制矩形的边框
    int border = border_width; // 边界宽度
    painter.drawRect(border, border, width() - 2 * border, height() - 2 * border);
    // 绘制圆
    int circle1_radious = 20; // 圆的半径
    painter.drawEllipse(border - circle1_radious, border - circle1_radious, circle1_radious*2, circle1_radious * 2);
    // 设置画刷为无填充
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::NoPen);
	// 绘制粒子
    for (const auto& particle : particles) {
        painter.setBrush(particle.color); // 设置画刷为随机颜色
        //painter.setBrush(Qt::transparent); // 设置填充为透明以绘制空心
        //painter.setPen(particle.color); // 设置画笔为随机颜色的边框
        
        //中心位置需要减去半径的一半
        painter.drawEllipse(particle.position_x-particle.radius,
            particle.position_y-particle.radius ,
            particle.radius*2,
            particle.radius*2);
    }
    int number = particles.size();
    QString text = QString("Number of Particles: %1  FPS:%2 deltaTime:%3").arg(number).arg(FPS).arg(deltaTime);
    SandSimulator::painter_text(painter, text);
    Sand_statusBar->showMessage(QString("all particles %1, Added 10 particles.").arg(number), 2000);

	std::chrono::milliseconds current = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	);


	qDebug() << "paintEvent time:" << current.count() - now.count() << "ms";
	auto diff_time = current.count() - now.count();

    if (diff_time < frameTime) {
        std::this_thread::sleep_for(std::chrono::milliseconds(frameTime - diff_time));
		deltaTime = frameTime;
    }
    else {
		deltaTime = diff_time;
		qDebug() << "Warning: paintEvent took longer than the interval!"<<deltaTime;
    }

}

void SandSimulator::showEvent(QShowEvent* event) {
    showMaximized(); // 最大化窗口
    QWidget::showEvent(event);
    generateParticles();  // 在窗口显示时生成粒子
}

void SandSimulator::generateParticles() {

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SandSimulator::updateParticles);
    timer->start(frameTime);  // 每100毫秒更新一次
}
//鼠标双击位置增加小球
void SandSimulator::mouseDoubleClickEvent(QMouseEvent* event) {
    int border = border_width; // 边界宽度
    int circleRadius = paricleRadius; // 圆的半径
    QPoint position = event->pos(); // 获取鼠标点击位置
    int mouseX = position.x();
    int mouseY = position.y();

    // 随机位置，范围[-10, 10]
    float randomX = mouseX + (rand() % 21 - 10);
    float particleY = mouseY + (rand() % 21 - 10);
    
    // 检查鼠标点击位置是否在边界内
    if (mouseX > border && mouseX < width() - border &&
        mouseY > border && mouseY < height() - border) {

        for (int i = 0; i < 10; ++i) { // 添加10个小球
            // 随机位置偏移
            //float randomX = mouseX + (rand() % 21 - 10);  // 随机范围[-10, 10]
            //float particleY = mouseY + (rand() % 21 - 10); // 随机范围[-10, 10]

            float randomX = mouseX ;  // 随机范围[-10, 10]
            float particleY = mouseY ; // 随机范围[-10, 10]

            particles.emplace_back(randomX, particleY); // 添加粒子到列表
            particles.back().radius = circleRadius; // 设置半径
            particles.back().mass = SandSimulator::pi * particles.back().radius * particles.back().radius; // 质量

            // 设置初始速度
            particles.back().velocityX = rand() % 21-10 ; // 随机水平速度[-10, 10]
            particles.back().velocityY = rand() % 21 - 10; // 随机垂直速度[-10, 10]
        }
        
        qDebug() << "Added 10 particles.";
        int number = particles.size();
        QString text = QString("Number of Particles: %1").arg(number);
        Sand_statusBar->showMessage(QString("all particles %1, Added 10 particles.").arg(number), 2000);
    }
    else {
        qDebug() << "mouseDoubleClickEvent out of border";
    }
    update(); // 触发绘图事件

}

void SandSimulator::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Space) {
        
        for (int i = 0; i < 10; ++i) { // 添加10个小球
            // 随机位置偏移
            //float randomX = mouseX + (rand() % 21 - 10);  // 随机范围[-10, 10]
            //float particleY = mouseY + (rand() % 21 - 10); // 随机范围[-10, 10]
            float randomX =width() / 2 + (rand() % 21 - 10);  // 随机范围[-10, 10]
            float particleY = height() / 2 + (rand() % 21 - 10); // 随机范围[-10, 10]

            particles.emplace_back(randomX, particleY); // 添加粒子到列表
            particles.back().radius = paricleRadius; // 设置半径
            particles.back().mass = SandSimulator::pi * particles.back().radius * particles.back().radius; // 质量

            // 设置初始速度
            particles.back().velocityX = rand() % 21 - 10; // 随机水平速度[-10, 10]
            particles.back().velocityY = rand() % 21 - 10; // 随机垂直速度[-10, 10]
        }

        qDebug() << "Added 10 particles.";
        int number = particles.size();
        QString text = QString("Number of Particles: %1").arg(number);
        Sand_statusBar->showMessage(QString("all particles %1, Added 10 particles.").arg(number), 2000);
        update(); // 触发绘图事件

       
    }

    if (event->key() == Qt::Key_Escape) {
    //清除所有粒子
    particles.clear();
    update(); // 触发绘图事件
        }

};

void SandSimulator::updateParticles() {
    int border = border_width; // 边界宽度

    // 只生成新粒子如果当前粒子数量少于最大数量
    if (particles.size() < particleCount) {
        float x = width() / 8 + rand() % 100;  // 固定在中间位置
        float y = border + 50; // 粒子生成在上部
        particles.emplace_back(x, y); // 添加粒子到列表
        particles.back().radius = paricleRadius; // 设置半径
        particles.back().mass = SandSimulator::pi * particles.back().radius * particles.back().radius; // 质量

        // 设置初始速度
        particles.back().velocityX = 1000; // 速度为1
        particles.back().velocityY = 200; // 速度为2
    }
    // 更新粒子位置和速度
    for (auto& particle : particles) {
        applyGravityAndDrag(particle);
        applyBoundaryCollision(particle, border);
    }
    // 检查粒子之间的碰撞
    checkP_PCollisions();
    update(); // 触发绘图事件
}

void SandSimulator::applyGravityAndDrag(SandParticle& particle) {
    const float applied_gravity = GRAVITY; // 假设重力为正向下
    const float applied_drag = DRAG; // 合适的阻力值

    // 施加重力，通常以负值来表示向下
	particle.velocityY += applied_gravity; // 应用重力

    // 更新位置
    particle.position_x += particle.velocityX* frameTime/1000;
    particle.position_y += particle.velocityY* frameTime/1000;

    // 施加阻力
    particle.velocityX = particle.velocityX * (1 - applied_drag); // 应用阻力
    particle.velocityY = particle.velocityY * (1 - applied_drag); // 应用阻力

    // 限制速度
    //limitSpeed(particle, MAX_SPEED); // 限制最大速度
}

void SandSimulator::checkP_PCollisions() {
    for (size_t i = 0; i < particles.size(); ++i) {
        for (size_t j = i + 1; j < particles.size(); ++j) {
            float dx = particles[j].position_x - particles[i].position_x;
            float dy = particles[j].position_y - particles[i].position_y;
            float distanceSquared = dx * dx + dy * dy;
            float radiusSum = particles[i].radius + particles[j].radius;

            if (distanceSquared < radiusSum * radiusSum) { // 检测到碰撞
                float distance = std::sqrt(distanceSquared);
                float overlap = radiusSum - distance; // 计算重叠量

                // 计算法向量
                float nx = dx / distance; // 法向量x
                float ny = dy / distance; // 法向量y

                // 计算相对速度并更新速度
                float relativeVelocityX = particles[i].velocityX - particles[j].velocityX;
                float relativeVelocityY = particles[i].velocityY - particles[j].velocityY;

                float coeffRestitution = 0.9f; // 恢复系数
                float impulse = 2 * (relativeVelocityX * nx + relativeVelocityY * ny) / (particles[i].mass + particles[j].mass);

                particles[i].velocityX -= impulse * particles[j].mass * nx * coeffRestitution; // 更新粒子i速度
                particles[i].velocityY -= impulse * particles[j].mass * ny * coeffRestitution; // 更新粒子i速度
                particles[j].velocityX += impulse * particles[i].mass * nx * coeffRestitution; // 更新粒子j速度
                particles[j].velocityY += impulse * particles[i].mass * ny * coeffRestitution; // 更新粒子j速度

                // 更新位置的修正方式
                float massSum = particles[i].mass + particles[j].mass;
                float correctionI = (overlap * (particles[j].mass / massSum)); // 只需修正一边
                float correctionJ = overlap - correctionI; // 另一边的修正量


                //particles[i].position_x -= correctionI * nx; // 粒子i的位置修正
                //particles[i].position_y -= correctionI * ny;

                //particles[j].position_x += correctionJ * nx; // 粒子j的位置修正
                //particles[j].position_y += correctionJ * ny;

                // 只对不在边界的粒子进行位置修正
                if (!isParticleAtBoundary(i)) {
                    particles[i].position_x -= correctionI * nx; // 粒子i的位置修正
                    particles[i].position_y -= correctionI * ny;
                }

                if (!isParticleAtBoundary(j)) {
                    particles[j].position_x += correctionJ * nx; // 粒子j的位置修正
                    particles[j].position_y += correctionJ * ny;
                }
            }
        }
    }
}

bool SandSimulator::isParticleAtBoundary(size_t index) {
    int border = border_width; // 边界宽度
    return (particles[index].position_x - particles[index].radius <= border ||
        particles[index].position_x + particles[index].radius >= width() - border ||
        particles[index].position_y - particles[index].radius <= border ||
        particles[index].position_y + particles[index].radius >= height() - border);
}
//应用边界碰撞
void SandSimulator::applyBoundaryCollision(SandParticle& particle, int border) {
    // 左边界
    if (particle.position_x - particle.radius < border) {
        particle.position_x = border + particle.radius; // 修正位置
        particle.velocityX *= -1; // 反弹
    }
    // 右边界
    if (particle.position_x + particle.radius > width() - border) {
        particle.position_x = width() - border - particle.radius; // 修正位置
        particle.velocityX *= -1; // 反弹
    }
    // 上边界
    if (particle.position_y - particle.radius < border) {
        particle.position_y = border + particle.radius; // 修正位置
        particle.velocityY *= -1; // 反弹
    }
    // 下边界
    if (particle.position_y + particle.radius > height() - border) {
        particle.position_y = height() - border - particle.radius; // 修正位置
        particle.velocityY *= -1; // 反弹
    }
}
// 应用阻尼
void SandSimulator::applyDamping(SandParticle& particle, float damping) {
    particle.velocityX *= damping;
    particle.velocityY *= damping;
}
// 限制速度
void SandSimulator::limitSpeed(SandParticle& particle, float maxSpeed) {
    float speedSquared = particle.velocityX * particle.velocityX + particle.velocityY * particle.velocityY;
    if (speedSquared > maxSpeed * maxSpeed) {
        float speed = std::sqrt(speedSquared);
        particle.velocityX = particle.velocityX / speed * maxSpeed;
        particle.velocityY = particle.velocityY / speed * maxSpeed;
    }
}

void SandSimulator::painter_text(QPainter& painter,QString& text) {
    // 获取窗口的中心坐标
    int centerX = width() / 2;
    int centerY = height() / 2;
    // 绘制文字
    QFont font;
    int fontSize = 25;
    font.setPointSize(fontSize); // 设置字体大小
    painter.setFont(font); // 将字体应用到 QPainter
    painter.setPen(QPen(QColor(255, 100, 70), 2)); // 设置画笔颜色和宽度
   
    QRect textRect = painter.boundingRect(0, 0, 0, 0, Qt::AlignCenter, text);
    // 计算文本中心位置
    int x = centerX - textRect.width() / 2; // x 坐标
    int y = fontSize * 2 - textRect.height() / 2; // y 坐标
    painter.drawText(x - width() / 2 + textRect.width() / 2, y, text); // 绘制文字
}
