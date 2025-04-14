#pragma once
#include<QString>

class stylesheet_QT {//样式类,导入h文件，实例化后，即可使用~

public:
    /// <ok
    QString Menu = "color:#cee8ff;background-color:#1f2b3e;font-size:20px;";

    QString button_style_0 = R"(QPushButton{font-size:20px;color:#0F1C2E;
                                background-color:#cee8ff;border-radius:5px;}
                                QPushButton:hover{background-color:#e0e0e0;}
                                QPushButton:pressed{padding-top:3px;padding-left:3px;})";
    //GREEN
    QString button_style_max = R"(QPushButton{font-size:10px;color: rgb(0, 255, 0);
                                background-color: rgb(0, 255, 0);border-radius:10px;}
                                QPushButton:hover{background-color:#71c4ef;}
                                QPushButton:pressed{padding-top:3px;padding-left:3px;})";
    //YELLOW
    QString button_style_min = R"(QPushButton{font-size:10px;color:rgb(255, 128, 0);
                                background-color:rgb(255, 128, 0);border-radius:10px;}
                                QPushButton:hover{background-color:#71c4ef;}
                                QPushButton:pressed{padding-top:3px;padding-left:3px;})";
    //RED
    QString button_style_close = R"(QPushButton{font-size:10px;color:rgb(255, 0, 0);
                                background-color:rgb(255, 0, 0);border-radius:10px;}
                                QPushButton:hover{background-color:#71c4ef;}
                                QPushButton:pressed{padding-top:3px;padding-left:3px;})";
    QString label_title = R"(QLabel{color:#cee8ff;font-size:20px;font-style: normal; font-weight: bold;}
                            QLabel:hover{color:#b6ccd8;})";//主标签

    QString widget_upper = R"(QWidget{color:#3D5A80;background-color:#374357;font-size:20px;font-style: normal; font-weight: bold;}
                            QWidget:hover{color:#b6ccd8;})";//主标签

    QString label_main = R"(QLabel{color:#cee8ff;font-size:80px;font-style: normal; font-weight: bold;}
                            QLabel:hover{color:#e0e0e0;})";//主标签

    QString label_main2 = R"(QLabel{color:#71c4ef;font-size:30px;font-style: italic; font-weight: bold;}
                            QLabel:hover{color:#b6ccd8;})";//主标签

    QString task_test = R"(QTextEdit{color:#cee8ff;font-size:30px;font-style: italic; font-weight: bold;
                            background-color:#374357;border-radius:5px;}
                           QTextEdit:hover{color:#b6ccd8;})";//主标签

    QString style_spinbox = "font-size: 25px; color: black; font-weight: bold; background-color: #71c4ef;";//主标签
    /// 窗口颜色

    QString widget_gray1 = "background-color: #1e293b;color:#cee8ff;";//深色
    QString widget_uicenter =
        "background-color: #1e293b;"
        "color: #cee8ff;"
        "border-top-left-radius: 5px;"
        "border-top-right-radius: 5px;"
        "border-bottom-left-radius: 0px;"
        "border-bottom-right-radius: 0px;";; // 深色整理

    QString widget_statusbar ="font-size: 25px;background-color:#374357;"
        "color: #cee8ff;"
        "border-top-left-radius: 0px;"
        "border-top-right-radius: 0px;"
        "border-bottom-left-radius: 5px;"
        "border-bottom-right-radius:5px;"; // 深色整理
    //QString dock_widget = "background-color:#1e293b;color:#cbd5e1;QDockWidget{ border: 20px; }";
    /// <ok
    QString dock_widget = "QDockWidget { background-color:#3c556d; border: 5px; }"
        "QDockWidget::title { background-color: #374357; color: #0F1C2E; }" // 设置标题栏背景色和文字颜色
        "QDockWidget::title:hover { background-color: #cee8ff; }" // 悬停时背景色
        "QDockWidget::close-button { image:url(float_icon.png); }" // 自定义关闭按钮图标
        "QDockWidget::float-button { image: url(float_icon.png); }"; // 自定义浮动按钮图标

    /// <ok
    QString Tab_widget = "QTabWidget::pane { border: 0 solid #ccc; }" // 标签页面板的边框
        "QTabBar::tab { background: lightgray; padding: 8px;font-size: 20px;margin: 0px;border-radius:5px;}" // 标签的背景, 内边距和外边距
        "QTabBar::tab:selected { background: none; color: white; }" // 选中标签的背景和字体颜色
        "QTabBar::tab:hover { background: rgba(255, 255, 255, 0.2); }" // 鼠标悬停时标签的背景颜色
        "QTabBar::tab:!selected { background: none; color: black; }"; // 未选中标签的背景和字体颜色

    /// <ok
    QString dock_textEdit = "color:#cbd5e1;background-color: #1e293b;font-size:15px;border: 2px solid #1e293b;";

    QString style_bar = "QProgressBar {"
        "border: 2px solid #1e293b;"
        "border-radius: 10px;"
        "text-align: center;"
        "font:30px;"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #334155, stop:1 #71c4ef);"
        "}"
        "QProgressBar::chunk {"
        "background-color: #71c4ef;"
        "border-radius: 10px;"
        "width: 1px;" // 设置进度条块的宽度
        "}";

    QString label_dot = R"(QLabel{color:rgb(255, 128, 0);font-size:80px;font-style: normal; font-weight: bold;}
                            QLabel:hover{color:#e6fbe3;})";//主标签
    QString label_tab = R"(QLabel{color:#cee8ff;font-size:25px;font-style: normal; font-weight: bold;}
                            QLabel:hover{color:rgb(255, 128, 0);})";//主标签

    QString label_fontawesome = R"(QLabel{color:#cee8ff;font-size:30px;font-style: normal; font-weight: bold;}
                            QLabel:hover{color:rgb(255, 128, 0);})";//fontawesomeicons.h

    QString button_fontawesome = R"(QPushButton{font-size:30px;color:#cee8ff;
                                background-color:#0F1C2E;border-radius:5px;}
                                QPushButton:hover{background-color:#e0e0e0;}
                                QPushButton:pressed{padding-top:3px;padding-left:3px;})";
};
