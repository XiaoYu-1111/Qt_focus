
//organized by: <Rain>
//date: 2024.12.6
#include "mywindows_class.h"

MySubWindow::MySubWindow(QWidget* parent) : QWidget(parent)

{
    setWindowTitle("User windows");
    setMinimumSize(600, 400);
    QString styleSheet = "QWidget{background-color: #1e293b;}";
    setStyleSheet(styleSheet);

    // 创建布局
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    // 初始化状态栏
    My_statusBar = new QStatusBar(this);
    My_statusBar->setMaximumHeight(20);
    My_statusBar->setSizeGripEnabled(false);
    layout->addWidget(My_statusBar, 0, Qt::AlignBottom);
    // 设置状态栏样式
    QString widget_statusbar = "font-size: 18px;background-color:#374357;"
        "color: #cee8ff;"
        "border-top-left-radius: 0px;"
        "border-top-right-radius: 0px;"
        "border-bottom-left-radius: 5px;"
        "border-bottom-right-radius:5px;"; // 深色
    My_statusBar->setStyleSheet(widget_statusbar);
    My_statusBar->showMessage("init status bar", 5000);

}

void MySubWindow::closeEvent(QCloseEvent* event) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "prompt", "Are you sure?",
        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        event->accept();
    }
    else {
        event->ignore();
    }
}

void MySubWindow::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event); // 避免未使用参数警告
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 启用反走样

    painter_grid(painter);
    painter_axis(painter);
    painter_circle(painter);
    painter_text(painter);
    //painter_bezier(painter);
    //painter_mc(painter);
    // 如果需要绘制圆圈
    if (drawCircle) {
        painter_mc(painter);
    }
}

void MySubWindow::mouseDoubleClickEvent(QMouseEvent* event) {
    // 记录鼠标双击的位置并设置绘制标志为 true
    doubleClickPosition = event->pos();
    drawCircle = true; // 标记需要绘制圆圈
    update(); // 请求重新绘制窗口
}
void MySubWindow::mouseMoveEvent(QMouseEvent* event) {

    // 鼠标移动时，如果需要绘制圆圈，则更新圆的位置
    if (drawCircle) {
        doubleClickPosition = event->pos();
        update(); // 请求重新绘制窗口
    }
}

void MySubWindow::painter_mc(QPainter& painter) {

    int radius = 50;  // 圆的半径
    painter.setPen(QPen(Qt::white, 2)); // 圆的颜色
    painter.drawEllipse(doubleClickPosition.x() - radius,
        doubleClickPosition.y() - radius,
        radius * 2, radius * 2); // 绘制圆圈
    //显示圆心坐标,相对窗口中心坐标

    QString text = "(" + QString::number(doubleClickPosition.x() - width() / 2) + "," + QString::number(-(doubleClickPosition.y() - height() / 2)) + ")";
    QFont font;
    font.setPointSize(15); // 设置字体大小
    painter.setFont(font); // 将字体应用到 QPainter
    painter.setPen(QPen(Qt::white, 2)); // 设置画笔颜色和宽度
    painter.drawText(doubleClickPosition.x() + 10, doubleClickPosition.y() + 10, text); // 绘制文字
    //drawCircle = false; // 标记不需要绘制圆圈
    My_statusBar->showMessage("R position: " + text, 5000);

}
//绘制其余图形
void MySubWindow::painter_bezier(QPainter& painter) {

    painter.setRenderHint(QPainter::Antialiasing); // 启用反走样

    // 获取窗口的中心坐标
    int centerX = width() / 2;
    int centerY = height() / 2;

    // 定义贝塞尔曲线的控制点
    QPointF p1(centerX - 200, centerY - 200);   // 起点
    QPointF p2(centerX + 0, centerY - (-100));   // 控制点
    QPointF p3(centerX + 200, centerY - 200);  // 终点

    // 创建 QPainterPath 对象
    QPainterPath path;
    path.moveTo(p1); // 移动到起点
    path.quadTo(p2, p3); // 绘制二次贝塞尔曲线

    // 绘制贝塞尔曲线
    painter.setPen(QPen(Qt::red, 2)); // 设置画笔颜色和宽度
    painter.drawPath(path); // 使用 drawPath 来绘制
}

void MySubWindow::painter_axis(QPainter& painter) {

    painter.setRenderHint(QPainter::Antialiasing); // 启用反走样
    // 获取窗口的中心坐标
    int centerX = width() / 2;
    int centerY = height() / 2;

    // 设置线条宽度和颜色
    painter.setPen(QPen(Qt::white, 2)); // 白色画笔，宽度为2

    // 绘制水平坐标轴（正向右）
    int offset = 0; // 坐标轴箭头的偏移量
    painter.drawLine(0 + offset, centerY, width() - offset, centerY); // 水平坐标轴

    // 绘制垂直坐标轴（正向上）
    painter.drawLine(centerX, 0 + offset, centerX, height() - offset); // 垂直坐标轴

    // 绘制坐标轴箭头（可选）
    painter.drawLine(width() - 10, centerY - 5, width(), centerY); // 水平箭头
    painter.drawLine(width() - 10, centerY + 5, width(), centerY);
    painter.drawLine(centerX - 5, 10, centerX, 0); // 垂直箭头
    painter.drawLine(centerX + 5, 10, centerX, 0);

}

void MySubWindow::painter_text(QPainter& painter) {
    // 获取窗口的中心坐标
    int centerX = width() / 2;
    int centerY = height() / 2;
    // 绘制文字
    QFont font;
    int fontSize = 25;
    font.setPointSize(fontSize); // 设置字体大小
    painter.setFont(font); // 将字体应用到 QPainter
    painter.setPen(QPen(QColor(255, 100, 70), 2)); // 设置画笔颜色和宽度
    QString text = "Drawing Table";
    QRect textRect = painter.boundingRect(0, 0, 0, 0, Qt::AlignCenter, text);
    // 计算文本中心位置
    int x = centerX - textRect.width() / 2; // x 坐标
    int y = fontSize * 2 - textRect.height() / 2; // y 坐标
    painter.drawText(x-width()/2+textRect.width()/2,  y, text); // 绘制文字
}

void MySubWindow::painter_circle(QPainter& painter) {


    // 获取窗口的中心坐标
    int centerX = width() / 2;
    int centerY = height() / 2;
    // 绘制圆圈
    int radius = 100; // 圆的半径
    painter.setPen(QPen(QColor(255, 100, 70), 5)); // 设置画笔颜色和宽度
    painter.drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2); // 绘制圆圈
    
    update();
    return;
};

void MySubWindow::painter_grid(QPainter& painter) {
// 获取窗口的中心坐标
    int centerX = width() / 2;
    int centerY = height() / 2;
    // 绘制网格
    int gridSize = 50; // 网格的大小
    int gridCount = 10; // 网格的数量
    // 绘制网格线
    painter.setPen(QPen(Qt::gray, 1)); // 设置网格线颜色和宽度
    for (int i = -gridCount / 2; i <= gridCount / 2; i++) {
        int x = centerX + i * gridSize; // 计算当前网格线的 x 坐标
        painter.drawLine(x, 0, x, height()); // 绘制垂直网格线

        int y = centerY + i * gridSize; // 计算当前网格线的 y 坐标
        painter.drawLine(0, y, width(), y); // 绘制水平网格线
    }

    // 绘制边界矩形
    painter.setPen(QPen(QColor(255, 100, 70), 2)); // 设置边界的颜色和宽度
    int boundaryOffset = (gridCount / 2) * gridSize; // 边界的偏移量
    painter.drawRect(centerX - boundaryOffset, centerY - boundaryOffset,
        boundaryOffset * 2, boundaryOffset * 2); // 绘制边界矩形

}

