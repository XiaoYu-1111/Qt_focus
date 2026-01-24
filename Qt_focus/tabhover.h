#pragma once
#include <QEvent>
#include <QLabel>
#include <QTabWidget>
#include <QVBoxLayout>
///建立一个标签类，用于悬停切换tab

class HoverLabel : public QLabel {
    Q_OBJECT
public:
	// 构造函数
    HoverLabel(int index, QTabWidget* tabWidget, QWidget* parent = nullptr)
        : QLabel(parent), m_index(index)  ,m_tabWidget(tabWidget) {
    // 设置标签样式
    setStyleSheet(label_tab);
    }
protected:
    bool event(QEvent* event) override {
        if (event->type() == QEvent::HoverEnter) {
            // 鼠标悬停时切换 tab
            out_index(); 
            // 设置标签样式
            setStyleSheet(label_tab);
        }
        else if (event->type() == QEvent::HoverLeave) {
            // 设置标签样式
            setStyleSheet(label_tab);
        }
		
        return QLabel::event(event);
    }
private:
    int m_index; // 对应的 tab 索引
    QTabWidget* m_tabWidget; // 传入的 QTabWidget
    QString label_tab = R"(QLabel{color:#cee8ff;font-size:25px;font-style: normal; font-weight: bold;}
                            QLabel:hover{color:rgb(255, 128, 0);})";//主标签
   int out_index() {
	   qDebug() << "out_index" << m_index;
       if (m_tabWidget) {
           m_tabWidget->setCurrentIndex(m_index);
       }
       return m_index;
    }
};
