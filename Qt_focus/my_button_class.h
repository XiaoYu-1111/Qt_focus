#pragma once
#include <QPushButton>
//自定义按钮类型

class MyQPushButton : public QPushButton {
    Q_OBJECT

public:
    MyQPushButton(QPushButton* parent = nullptr) : QPushButton(parent) {
        setFixedSize(200, 800);
        setStyleSheet(style_mybutton);
    }
    QString style_mybutton = R"(QPushButton{font-size:20px;color:#0F1C2E;
                                background-color:#cee8ff;border-radius:5px;}
                                QPushButton:hover{background-color:#e0e0e0;}
                                QPushButton:pressed{padding-top:3px;padding-left:3px;})";
};
