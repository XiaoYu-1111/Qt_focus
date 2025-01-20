#include "Qt_focus.h"
#include "style.h"

#pragma execution_character_set("utf-8")
///该指令仅支持VS环境;若在其他IDE环境下编译,请注释掉该行;设置中文编码可用;
//文件高级保存选项中设置为utf-8编码,以便支持中文注释;
Qt_focus::Qt_focus(QWidget *parent)
    : QMainWindow(parent)
{
#pragma region //start ui
    ui.setupUi(this);
    stylesheet_QT style;
this->setWindowTitle("RAIN_Focus_1.0");
this->setWindowIcon(QIcon(":/Qt_focus/ico/xiaoyu_base.png"));
this->setStyleSheet(style.widget_uicenter);
this->setContentsMargins(0,0,0,0);
this->setContextMenuPolicy(Qt::DefaultContextMenu);

initialSize = this->size();

#pragma endregion

#pragma region //main window
//ui.centralWidget->setMinimumSize(800, 500);
ui.centralWidget->setStyleSheet(style.widget_gray1);
    ui.mainToolBar->setMinimumHeight(30);
    ui.mainToolBar->setMaximumHeight(50);
    ui.mainToolBar->hide();//隐藏工具栏
        ui.statusBar->setMinimumHeight(30);
        ui.statusBar->setMaximumHeight(60);
        ui.statusBar->setStyleSheet(style.widget_statusbar);
        //ui.statusBar->hide();
QVBoxLayout* main_layout = new QVBoxLayout(ui.centralWidget);
main_layout->setContentsMargins(0, 0, 0, 0);

#pragma region//无边框设计显示upper window

bool is_borderless = 1;
widget_upper = new QWidget();//upper窗口

//#include <QGraphicsDropShadowEffect>
// 创建阴影效果
QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect();
shadowEffect->setBlurRadius(10); // 阴影模糊半径
shadowEffect->setOffset(0, 0); // 阴影偏移
shadowEffect->setColor(QColor(30,41,59, 255)); // 阴影颜色，带透明度
// 将阴影效果应用到上层窗口
//widget_upper->setGraphicsEffect(shadowEffect);
ui.centralWidget->setGraphicsEffect(shadowEffect);

if (is_borderless) {

this->setWindowFlags(Qt::FramelessWindowHint);//无边框
this->setAttribute(Qt::WA_TranslucentBackground);//背景透明

    //widget_upper = new QWidget();//upper窗口
    QHBoxLayout* layout_upper = new QHBoxLayout(widget_upper);
    widget_upper->setStyleSheet(style.widget_upper);
    main_layout->addWidget(widget_upper);
    layout_upper->setContentsMargins(0, 2, 0, 2);
    layout_upper->setSpacing(20);
    widget_upper->installEventFilter(this);
    ui.statusBar->installEventFilter(this);

    QLabel* label_title = new QLabel("    RAIN Focus 1.0");
    label_title->setStyleSheet(style.label_title);
    label_title->setAlignment(Qt::AlignVCenter | Qt::AlignLeft); // 设置文本上下居中，左对齐
    layout_upper->addWidget(label_title);
    layout_upper->addStretch();

    QFrame* line_upper = new QFrame();
    //line_upper->setFrameShape(QFrame::VLine);
    line_upper->setFrameShadow(QFrame::Raised);
    layout_upper->addWidget(line_upper);
    layout_upper->addStretch();
    QHBoxLayout* layout_line_upper = new QHBoxLayout(line_upper);
    layout_line_upper->setContentsMargins(0, 5, 30, 5);//(int left, int top, int right, int bottom)
    layout_line_upper->setSpacing(20);
    layout_upper->addWidget(line_upper);

    int button_w = 20;
    int button_h = 20;
    button_max = new QPushButton();
    button_max->setIcon(QIcon(":/Qt_focus/ico/max.png"));
    button_max->setFixedSize(button_w, button_h);
    button_max->setStyleSheet(style.button_style_max);
    button_max->setToolTip("Maximize");
    layout_line_upper->addWidget(button_max, 0, Qt::AlignRight);

    button_min = new QPushButton();
    button_min->setIcon(QIcon(":/Qt_focus/ico/min.png"));
    button_min->setFixedSize(button_w, button_h);
    button_min->setStyleSheet(style.button_style_min);
    button_min->setToolTip("Minimize");
    layout_line_upper->addWidget(button_min, 0, Qt::AlignRight);

    button_close = new QPushButton();
    button_close->setIcon(QIcon(":/Qt_focus/ico/close.png"));
    button_close->setFixedSize(button_w, button_h);
    button_close->setStyleSheet(style.button_style_close);
    button_close->setToolTip("Close");
    layout_line_upper->addWidget(button_close, 0, Qt::AlignRight);
    // 连接信号与槽
    connect(button_max, SIGNAL(clicked()), this, SLOT(maximizeRestore()));
    connect(button_min, SIGNAL(clicked()), this, SLOT(showMinimized()));
    connect(button_close, SIGNAL(clicked()), this, SLOT(close()));
}
else {
    widget_upper->hide();
}
#pragma endregion

    QWidget* widget_mid = new QWidget();//中窗口
    QHBoxLayout* layout_mid = new QHBoxLayout(widget_mid);
    layout_mid->setContentsMargins(0, 0, 0, 0);
    main_layout->addWidget(widget_mid);

    stackedWidget1 = new QTabWidget();//tab窗口
    stackedWidget1->setStyleSheet(style.Tab_widget);
    stackedWidget1->setContentsMargins(0, 0, 0, 0);

    QWidget* widget_left = new QWidget();
    widget_left->setMinimumWidth(20);

    QWidget* widget_right = new QWidget();
    widget_right->setMinimumWidth(20);

    layout_mid->addWidget(widget_left, Qt::AlignLeft);
    layout_mid->addWidget(stackedWidget1,Qt::AlignCenter);//中间窗口添加tab窗口
    layout_mid->addWidget(widget_right, Qt::AlignRight);

    Widget_page_home = new QWidget();
    Widget_page0 = new QWidget();//添加新页面
    Widget_page1 = new QWidget();
    Widget_page2 = new QWidget();
    Widget_page3 = new QWidget();
    Widget_page4 = new QWidget();


    //stackedWidget1->addTab(Widget_page0, QIcon(":/Qt_focus/ico/focus.png"), "&Rain Focus");//通过标签页的形式添加
    stackedWidget1->addTab(Widget_page_home, QIcon(":/Qt_focus/ico/homes.png"), "&");
    stackedWidget1->addTab(Widget_page0, QIcon(":/Qt_focus/ico/focus.png"), "&");//通过标签页的形式添加
    stackedWidget1->addTab(Widget_page1, QIcon(":/Qt_focus/ico/tasks.png"), "&");
    stackedWidget1->addTab(Widget_page2, QIcon(":/Qt_focus/ico/links.png"), "&");
    stackedWidget1->addTab(Widget_page3, QIcon(":/Qt_focus/ico/probe.png"), "&");
    
    stackedWidget1->tabBar()->setIconSize(QSize(50,50)); // 设置图标大小为32x32
#pragma endregion

#pragma region //page_home

    page3_layout_grid = new QVBoxLayout(Widget_page_home);
    page3_layout_grid->setContentsMargins(0, 0, 0, 0);

    QLabel* label_main = new QLabel();
    //QString page0_String1 = "Focus Time<br>Rain";
    QString widget_gray0 = "Home";
    QString widget_gray00 = "<span style='color:#94a3b8;font-size: 15pt;font-weight: normal;font-style:normal'>"
        "Software Developer<br>"
        "Based on Qt&Cpp Designed by Rain!"
        "</span>";
    QString combinedText0 = widget_gray0 + "<br>" + widget_gray00;
    label_main->setStyleSheet(style.label_main);
    label_main->setText(QString("<html>%1</html>").arg(combinedText0));
    label_main->setMinimumSize(400, 300);
    label_main->setAlignment(Qt::AlignCenter);

    page3_layout_grid->addWidget(label_main, Qt::AlignVCenter | Qt::AlignHCenter);

    QLCDNumber* lcd_number = new QLCDNumber();
    lcd_number->setDigitCount(8);
    lcd_number->setSegmentStyle(QLCDNumber::Flat);
    lcd_number->setFixedSize(200, 100);
    
    page3_layout_grid->addWidget(lcd_number, 1, Qt::AlignBottom | Qt::AlignRight);

    // 初始化定时器
    QTimer* timer_main = new QTimer(this);
    connect(timer_main, &QTimer::timeout, this, [=]() {
// 更新时间的槽函数
        QTime currentTime = QTime::currentTime();
        lcd_number->display(currentTime.toString("hh:mm:ss")); // 显示小时和分钟});
        auto generator = QRandomGenerator::global();
        int lowerBound = 150;
        int red = generator->bounded(lowerBound, 256);    // 生成 0-255 之间的随机红色值
        int green = generator->bounded(lowerBound, 256);  // 生成 0-255 之间的随机绿色值
        int blue = generator->bounded(lowerBound, 256);   // 生成 0-255 之间的随机蓝色值
        // 创建随机颜色字符串
        QString color = QString("rgb(%1, %2, %3)").arg(red).arg(green).arg(blue);
        QString styleSheet = QString("color: %1 ").arg(color);
        //lcd_number->setStyleSheet(styleSheet);
        });
    timer_main->start(1000); // 每秒更新一次

#pragma endregion

#pragma region //page0_Focus
    page0_layout_grid = new QGridLayout(Widget_page0);
    Widget_page0->setContentsMargins(0, 0, 0, 0);
    page0_layout_grid->setContentsMargins(0, 0, 0, 0);

    label_text_time = new QLabel;
    label_text_time->installEventFilter(this);
    //QString page0_String1 = "Focus Time<br>Rain";
    QString page0_String1 = "Focus Time";
    QString page0_String2 = "<span style='color:#94a3b8;font-size: 15pt;font-weight: normal;font-style:normal'>"
        "Software Developer<br>"
        "Based on Qt&Cpp Designed by Rain!"
        "</span>";
    //QString combinedText = page0_String1 + "<br>" + page0_String2;
    QString combinedText = page0_String1 + "<br>" ;
    label_text_time->setStyleSheet(style.label_main);
    label_text_time->setText(QString("<html>%1</html>").arg(combinedText));
    label_text_time->setMinimumSize(400, 300);
    label_text_time->setAlignment(Qt::AlignCenter);


    RoundProgressBar* round_progress_bar = new RoundProgressBar();//设置圆形进度条
    round_progress_bar->setValue(20);
    round_progress_bar->setFixedSize(100, 100);
    round_progress_bar->setOutlinePenWidth(0);
    round_progress_bar->setBaseCircleVisible(true);
    //round_progress_bar->setBarStyle(RoundProgressBar::BarStyle::StyleLine);
    round_progress_bar->setBarStyle(RoundProgressBar::BarStyle::StyleDonut);
   
    progress_bar = new QProgressBar();//设置进度条
    progress_bar->setMinimumSize(800, 50);
    progress_bar->setWindowTitle("Qt_segy_process::myst progress");
    progress_bar->setStyleSheet(style.style_bar);
    progress_bar->setRange(0, 100); // 设置范围

    button_set_focus = new QPushButton("Set Focus");//设置按钮
    button_set_focus->setStyleSheet(style.button_style_0);
    button_set_focus->setFixedSize(200, 40);
    //button_set_focus->move(200, 200);//设置按钮位置
   
    button_focus_reset = new QPushButton("Start");//重置按钮
    button_focus_reset->setStyleSheet(style.button_style_0);
    button_focus_reset->setFixedSize(200, 40);

    button_focus_pause= new QPushButton("Pause");//暂停按钮
    button_focus_pause->setStyleSheet(style.button_style_0);
    button_focus_pause->setFixedSize(200, 40);

    page0_layout_grid->addWidget(label_text_time, 0, 0, 1, 3, Qt::AlignTop | Qt::AlignCenter);
    //page0_layout_grid->addWidget(round_progress_bar, 1, 1, 1, 1, Qt::AlignCenter);
    page0_layout_grid->addWidget(button_set_focus, 2, 0, 1, 1, Qt::AlignBottom | Qt::AlignCenter);
    page0_layout_grid->addWidget(button_focus_reset,2, 1, 1, 1, Qt::AlignBottom | Qt::AlignCenter);
    page0_layout_grid->addWidget(button_focus_pause, 2, 2, 1, 1, Qt::AlignBottom | Qt::AlignCenter);
    //2, 1, 1, 1
    QLabel* label_addStretch = new QLabel();
    page0_layout_grid->addWidget(label_addStretch, 4, 1, 1, 1, Qt::AlignBottom | Qt::AlignCenter);
    connect(button_set_focus, SIGNAL(clicked()), this, SLOT(set_lable_time()));
    connect(button_focus_reset, SIGNAL(clicked()), this, SLOT(reset_lable_time()));
    connect(button_focus_pause, SIGNAL(clicked()), this, SLOT(Pause_focus_time()));

    Focus_time = 1500; // 设置倒计时初始为1800秒/30分钟
    Focus_time2 = 3600;

#pragma endregion

#pragma region //page1Task list

    page1_layout_grid = new QVBoxLayout(Widget_page1);
    page1_layout_grid->setContentsMargins(0, 0, 0, 0);

    label_task_title = new QLabel;
    //QString page0_String1 = "Focus Time<br>Rain";
    QString label_tasks2_title = "Task list";
    label_task_title->setText(QString("<html>%1</html>").arg(label_tasks2_title));
    label_task_title->setStyleSheet(style.label_main);
    label_task_title->setAlignment(Qt::AlignCenter);
    page1_layout_grid->addWidget(label_task_title, 0, Qt::AlignTop | Qt::AlignCenter);

    QtextEdit_tasks = new QTextEdit;
    QtextEdit_tasks->setReadOnly(false);
    QtextEdit_tasks->setStyleSheet(style.task_test);
    QtextEdit_tasks->setFixedSize(800, 50);
    QtextEdit_tasks->setHtml("<b>What's your task today?</b>"); // 设置初始HTML文字
    page1_layout_grid->addWidget(QtextEdit_tasks,0,Qt::AlignCenter);

    QPushButton *add_task = new QPushButton("Add Task");
    add_task->setStyleSheet(style.button_style_0);
    add_task->setFixedSize(200, 40);
   
    QPushButton* clear_task = new QPushButton("Clear Task");
    clear_task->setStyleSheet(style.button_style_0);
    clear_task->setFixedSize(200, 40);
    
    QWidget* task_container = new QWidget();
    task_container->setStyleSheet(style.widget_gray1);
    QVBoxLayout* task_layout = new QVBoxLayout(task_container);
    task_layout->setContentsMargins(0, 0, 0, 0);
    task_layout->addWidget(QtextEdit_tasks);
    page1_layout_grid->addWidget(task_container, 0, Qt::AlignBottom | Qt::AlignCenter);

    // 创建一个横向布局
    QWidget* taskWidget = new QWidget();
    QHBoxLayout* buttonLayout = new QHBoxLayout(taskWidget);
    buttonLayout->addWidget(add_task);
    buttonLayout->addWidget(clear_task);
    page1_layout_grid->addWidget(taskWidget, 1, Qt::AlignBottom | Qt::AlignCenter);

    connect(add_task, &QPushButton::clicked, this, [=]()  {
        if (taskCount < 10) {
            QTextEdit* newTextEdit = new QTextEdit;
            stylesheet_QT style;
            newTextEdit->setReadOnly(false);

            // 创建随机颜色字符串
            QString color = randonColor();

            QString task_test = QString(R"(QTextEdit{color:%1;font-size:30px;font-style: italic; font-weight: bold;
                            background-color:#374357;border-radius:5px;}
                           QTextEdit:hover{color:#b6ccd8;})").arg(color);;//主标签
            newTextEdit->setStyleSheet(task_test); // 只应用随机颜色
            newTextEdit->setFixedSize(800, 50);
            // 添加序号到初始HTML文字中
            QString htmlContent = QString("<b>%1. What should I do today?</b>").arg(taskCount );
            newTextEdit->setHtml(htmlContent); // 设置初始HTML文字
            // 确保 label_task_title 只被添加一次
            if (taskCount == 0) {
                page1_layout_grid->addWidget(label_task_title, 0, Qt::AlignTop | Qt::AlignCenter);
                page1_layout_grid->addWidget(task_container, 0, Qt::AlignBottom | Qt::AlignCenter);
            }
            task_layout->addWidget(newTextEdit, taskCount,Qt::AlignCenter);
            page1_layout_grid->addWidget(taskWidget, 1, Qt::AlignBottom | Qt::AlignCenter);
            taskCount += 1;
            ui.statusBar->showMessage(QString("Task %1 has added!").arg(QString::number(taskCount)));
        }
        else {
            QMessageBox::warning(this, "Warning", "You can only add up to 10 tasks!");
        }
        });
    connect(clear_task, &QPushButton::clicked, this, [=]() {

        if (taskCount >= 1) {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "prompt!", " Clear task!",
                QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                QLayoutItem* item;
                while ((item = task_layout->takeAt(0)) != 0) {
                    if (item->widget()) {
                        // 检查 widget 类型，只有当是 QTextEdit 时才删除
                        if (qobject_cast<QTextEdit*>(item->widget())) {
                            delete item->widget();
                        }
                    }
                    delete item;
                    taskCount = 0;//清空任务数量
                    ui.statusBar->showMessage("Clear task successfully!", 2000);
                }
            }
            else {
                ui.statusBar->showMessage("Clear task canceled!");
                return;
            }
        }});

#pragma endregion

#pragma region //page2Link list

    page2_layout_grid = new QVBoxLayout(Widget_page2);
    page2_layout_grid->setContentsMargins(0, 0, 0, 0);

    QLabel*label_task_title2 = new QLabel;
    //QString page0_String1 = "Focus Time<br>Rain";
    QString label_tasks2_title2 = "Link list";

    label_task_title2->setText(QString("<html>%1</html>").arg(label_tasks2_title2));
    label_task_title2->setStyleSheet(style.label_main);
    label_task_title2->setAlignment(Qt::AlignCenter);

    QPushButton *label_link1 = new QPushButton();
    label_link1->setFixedSize(600, 50);
    label_link1->setText("https://qwerty.liumingye.cn/");

    QPushButton* label_link2 = new QPushButton();
    label_link2->setFixedSize(600, 50);
    label_link2->setText("https://www.bilibili.com/");

    QFrame* line_frame = new QFrame();
    QHBoxLayout* lineLayout = new QHBoxLayout(line_frame);
    line_frame->setFrameShape(QFrame::HLine);
    line_frame->setFrameShadow(QFrame::Sunken);

    QTextEdit* TextEdit_search = new QTextEdit();
    
    
    QString color = randonColor();

    QString task_test = QString(R"(QTextEdit{color:%1;font-size:30px;font-style: normal; font-weight: bold;
                            background-color:#374357;border-radius:5px;}
                           QTextEdit:hover{color:#b6ccd8;})").arg(color);;//主标签
    TextEdit_search->setStyleSheet(task_test); // 只应用随机颜色
    TextEdit_search->setFixedSize(400, 50);

    QPushButton* button_search = new MyQPushButton();//自定义按钮
    button_search->setText("Search");
    lineLayout->addWidget(TextEdit_search,  Qt::AlignCenter);
    lineLayout->addWidget(button_search,  Qt::AlignRight);

    QString button_style_link = QString(R"(QPushButton{font-size:30px;color:#B7C4CF;
                                background-color:#57687c;border-radius:5px;}
                                QPushButton:hover{background-color:#71c4ef;}
                                QPushButton:pressed{padding-top:3px;padding-left:3px;})");
    label_link1->setStyleSheet(button_style_link);
    label_link2->setStyleSheet(button_style_link);

    page2_layout_grid->addWidget(label_task_title2, 0, Qt::AlignTop | Qt::AlignCenter);
    page2_layout_grid->addWidget(label_link1, 0, Qt::AlignCenter|Qt::AlignTop);
    page2_layout_grid->addWidget(label_link2, 0, Qt::AlignCenter | Qt::AlignTop);
    page2_layout_grid->addStretch(20);
    page2_layout_grid->addWidget(line_frame, 0, Qt::AlignCenter |Qt::AlignTop);
    page2_layout_grid->addStretch(80);

    connect(label_link1, &QPushButton::clicked, this, [=]() {
            QDesktopServices::openUrl(QUrl(label_link1->text()));
        });
    connect(label_link2, &QPushButton::clicked, this, [=]() {
        QDesktopServices::openUrl(QUrl(label_link2->text()));
        });

    connect(button_search, &QPushButton::clicked, this, [=]() {
        QDesktopServices::openUrl(QUrl("https://www.baidu.com/s?wd="+TextEdit_search->toPlainText()));
        });

#pragma endregion

#pragma region //page3Probe

    page3_layout_grid = new QVBoxLayout(Widget_page3);
    page3_layout_grid->setContentsMargins(0, 0, 0, 0);

    QLabel*label_probe_title = new QLabel;
    //QString page0_String1 = "Focus Time<br>Rain";
    QString label_probe_title_text = "Probe";
    label_probe_title->setText(QString("<html>%1</html>").arg(label_probe_title_text));
    label_probe_title->setMaximumHeight(100);
    label_probe_title->setStyleSheet(style.label_main);

    QPushButton* button_probe = new MyQPushButton();
    button_probe->setText("start monitor");

    //QPushButton* pauseButton = new MyQPushButton();
    pauseButton = new MyQPushButton();
    pauseButton->setText("pause");
    

    /*QPushButton* resumeButton = new MyQPushButton();
    resumeButton->setText("resume");*/

    QFrame* frame_audio = new QFrame();
    QHBoxLayout* lineLayout_frame = new QHBoxLayout(frame_audio);
    lineLayout_frame->addWidget(button_probe);
    lineLayout_frame->addWidget(pauseButton);
    //lineLayout_frame->addWidget(resumeButton);

    page3_layout_grid->addWidget(label_probe_title, 0, Qt::AlignTop | Qt::AlignCenter);
    page3_layout_grid->addWidget(frame_audio, 0, Qt::AlignCenter | Qt::AlignTop);

    connect(button_probe, &QPushButton::clicked, this, [=]() {
        Draw_audio_sensor();
        page3_layout_grid->addWidget(widget_audio,0,  Qt::AlignTop);
        });

    connect(pauseButton, &QPushButton::clicked, this, [=]() {

        if (audio_isPause==false) {
            pauseAudio();
            pauseButton->setText("resume");
            //获取按钮当前的样式
            QString styleSheet = pauseButton->styleSheet();
            styleSheet+="QPushButton{background-color:#7FFF00;}";//绿色
            pauseButton->setStyleSheet(styleSheet);
        }
        else {
            resumeAudio();
            pauseButton->setText("pause");
            //获取按钮当前的样式
            QString styleSheet = pauseButton->styleSheet();
            styleSheet += "QPushButton{background-color:#FF6347;}";//红色
            pauseButton->setStyleSheet(styleSheet);
        }
        audio_isPause = !audio_isPause;
        });

    //connect(resumeButton, &QPushButton::clicked, this, [=]() {
    //    resumeAudio();
    //    });

#pragma endregion
}

Qt_focus::~Qt_focus()//析构函数
{}

#pragma region//计时部分

void Qt_focus::set_lable_time() {

    if (widget_settime_show == true) {
        if (!widget_settime) {
            stylesheet_QT style;
            widget_settime = new QWidget();
            widget_settime->setWindowIcon(QIcon(":/Qt_focus/ico/focus.png"));
            widget_settime->setStyleSheet(style.widget_gray1);
            QGridLayout* layout_page0 = new QGridLayout(widget_settime);
            layout_page0->setContentsMargins(0, 0, 0, 0);
            widget_settime->setMinimumSize(400, 300);

            QLabel* label_time = new QLabel;
            label_time->setText("Focus Time:");
            label_time->setStyleSheet(style.label_main2);
            label_time->setAlignment(Qt::AlignCenter);

            QSpinBox* spin_box = new QSpinBox;
            spin_box->setRange(1, 300);
            spin_box->setValue(20);
            spin_box->setStyleSheet(style.style_spinbox);
            spin_box->setFixedSize(200, 40);

            QLabel* label_time2 = new QLabel;
            label_time2->setText("minutes");
            label_time2->setStyleSheet(style.label_main2);
            label_time2->setAlignment(Qt::AlignCenter);

            QPushButton* button_start_time = new QPushButton("Start Time");
            button_start_time->setFixedSize(200, 40);
            button_start_time->setStyleSheet(style.button_style_0);

            layout_page0->addWidget(label_time, 0, 0, Qt::AlignCenter);
            layout_page0->addWidget(spin_box, 1, 0, Qt::AlignCenter);
            layout_page0->addWidget(label_time2, 1, 1, Qt::AlignCenter);
            layout_page0->addWidget(button_start_time, 2, 0, Qt::AlignCenter);

            connect(button_start_time, &QPushButton::clicked, this, [=]() {
                reset_lable_time();
                });

            connect(spin_box, &QSpinBox::valueChanged,  this, [=]() {

                Focus_time = spin_box->value() * 60; // 设置倒计时初始为1800秒/30分钟
                ui.statusBar->showMessage("Focus time has set " + QString::number(Focus_time / 60) + " minutes!", 5000);
                label_text_time->setText(QString::number(Focus_time / 60) + " minutes!"); // 更新显示的时间
                //reset_lable_time();
                });
            widget_settime->show();
        }
        else {
            widget_settime->show();
        }
    }
    else {
        widget_settime->hide();
    }
    widget_settime_show=!widget_settime_show;
}

void Qt_focus::start_lable_time() {

    QApplication::processEvents();

    remainingTime = Focus_time;
    progress_Value = remainingTime;

    timer = new QTimer(this); // 初始化计时器并指定父对象
    connect(timer, &QTimer::timeout, [=] {
        updateCountdown();
        });
    timer->start(1000); // 每秒触发一次
    updateCountdown(); // 初始化显示
    page0_layout_grid->addWidget(progress_bar, 3, 0,1,3, Qt::AlignCenter);

    //showMaximized();
}

void Qt_focus::updateCountdown() {// 计时器槽函数
   
    if (remainingTime >= 0) {
        int hours = remainingTime / 3600;       // 计算小时
        int minutes = (remainingTime % 3600) / 60; // 计算分钟
        int seconds = remainingTime % 60;       // 计算秒
        int ms=remainingTime%1000;
        
        //QString timeString = QString("%1:%2:%3:%4")
        //    .arg(hours, 2, 10, QChar('0'))    // 补零
        //    .arg(minutes, 2, 10, QChar('0'))
        //    .arg(seconds, 2, 10, QChar('0'))
        //    .arg(hours, 2, 10, QChar('0'));

        QString timeString = QString("%1:%2:%3")
            .arg(hours, 2, 10, QChar('0'))    // 补零
            .arg(minutes, 2, 10, QChar('0'))
            .arg(seconds, 2, 10, QChar('0'));

        label_text_time->setText(timeString); // 更新显示的时间
        // 生成随机颜色
        auto generator = QRandomGenerator::global();
        int red = generator->bounded(200, 256);    // 生成 0-255 之间的随机红色值
        int green = generator->bounded(200, 256);  // 生成 0-255 之间的随机绿色值
        int blue = generator->bounded(255, 256);   // 生成 0-255 之间的随机蓝色值
        // 创建随机颜色字符串
        QString color = QString("rgb(%1, %2, %3)").arg(red).arg(green).arg(blue);

        //更改字体大小
        int font_size = 80;
        int width_init=initialSize.width();
        int Widget_current = Widget_page0->geometry().width();

        float scale = (float)Widget_current / (float)width_init;
        int scaled_font_size = (int)(font_size*scale)*0.8;
        
        QString style_current = label_text_time->styleSheet();
        QString add_style = QString(R"(QLabel{color:%1;font-size:%2px;})").arg(color).arg(scaled_font_size);
        
        label_text_time->setStyleSheet(style_current + add_style);// 应用随机颜色
        // 计算进度条值
        if (progress_Value > 0) {
            progress_bar->setValue((progress_Value - remainingTime) * 100 / progress_Value); // 计算进度条值
        }
        else {
            progress_bar->setValue(0); // 防止除零错误
        }
        remainingTime-=1; // 递减剩余时间

        //QDateTime currentTime = QDateTime::currentDateTime();
        //QString time_now = currentTime.toString("hh:mm:ss");
        //QString style_current_time = ui.statusBar->styleSheet();
        //QString add_style_time = QString(R"(color:%1;)").arg(color);
        //ui.statusBar->setStyleSheet(style_current_time + add_style_time);// 应用随机颜色

        //ui.statusBar->showMessage("System time: " + time_now); // 更新时间显示
        ////qDebug() << "pos:" << QCursor::pos();
    }
    else {
        timer->stop(); // 如果倒计时结束，停止计时器
        label_text_time->setText(QString::number(5) + " min rest!"); // 更新显示的时间
    }
}

void Qt_focus::reset_lable_time() {

    if (is_focus_start==false) {
        // 停止当前计时器
        if (timer) {
            timer->stop();
        }
        remainingTime = Focus_time;
        start_lable_time();
        button_focus_reset->setText("Reset");
        //stackedWidget1->tabBar()->hide();
    }
    /*else {
        stackedWidget1->tabBar()->show();
    }*/
   
    /*is_focus_start = !is_focus_start;*/
}

void Qt_focus::Pause_focus_time() {

    if (timer) {
        if (is_focus_pause == false)
        {
            // 停止当前计时器

            timer->stop();

            ui.statusBar->showMessage("Focus time has paused!");
            button_focus_pause->setText("Resume");
        }
        else {
            timer->start(1000); // 重新开始计时
            button_focus_pause->setText("Pause");
            ui.statusBar->showMessage("Focus time has resumed!");
        }
        is_focus_pause = !is_focus_pause;
    }
}

QString Qt_focus::getSystemTime() {

    /// 这里可以根据您的需求来定义当前时刻
    QDateTime currentTime = QDateTime::currentDateTime();
    QString timeString = currentTime.toString("mm:ss");
    label_text_time->setText(timeString);
    return timeString;
}

#pragma endregion

#pragma region//右键菜单
void Qt_focus::Main_page_Rmenu()
{
    Rclick_Menu = new QMenu(this);
    QAction* pAc1 = new QAction("Hide TabBar");
    QAction* pAc2 = new QAction("initialSize");
    QAction* pAc3 = new QAction("Fouse Model");

    QAction* pAc5 = new QAction("Painter Window");
    QAction* pAc6 = new QAction("SandParticle");

    QAction* Menu_exe = new QAction("EXE");

    Rclick_Menu->addAction(pAc1);
    Rclick_Menu->addAction(pAc2);
    Rclick_Menu->addAction(pAc3);

    Rclick_Menu->addAction(pAc5);
    Rclick_Menu->addAction(pAc6);
    Rclick_Menu->addAction(Menu_exe);

    QMenu* myMenu = new QMenu(this);//一号菜单
    QAction* option1Action1 = new QAction("Pysider6_timer", this);//一号菜单action
    QAction* option1Action2 = new QAction("virtual keyboard", this);//一号菜单action
    QAction* option1Action3 = new QAction("exe3", this);//一号菜单action
    myMenu->addAction(option1Action1);
    myMenu->addAction(option1Action2);
    myMenu->addAction(option1Action3);

    Menu_exe->setMenu(myMenu);

    connect(pAc1, &QAction::triggered, [=] {
        if (stackedWidget1->tabBar()->isVisible()) {
            stackedWidget1->tabBar()->hide();
            pAc1->setText("Show TabBar");
            //this->setWindowFlags(Qt::FramelessWindowHint);//无边框
            //this->show(); // 确保窗口更新
        }
        else {
            //this->setWindowFlags(Qt::Window | Qt::WindowTitleHint); // 恢复为带边框
            //this->show(); // 确保窗口更新
            stackedWidget1->tabBar()->show();
            pAc1->setText("Hide TabBar");
        }
        });

    connect(pAc2, &QAction::triggered, [=] {
        //QMessageBox::information(this, "title", "ac2");
        //showNormal();  // 恢复窗口
        
        QScreen* screen = QGuiApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();
        int x = (screenGeometry.width() - this->width()) / 2;
        int y = (screenGeometry.height() - this->height()) / 2;
        move(x, y);
        this->resize(initialSize);  // 微调大小以触发布局更新
        showNormal();  // 恢复窗口
        });

    connect(pAc3, &QAction::triggered, [=] {

        QList<QWidget*> widgets = Widget_page0->findChildren<QWidget*>(); // 找到所有子控件
        qDebug() << "Number of widgets found:" << widgets.size();

        // 根据 label_main_text_only 的状态设置控件的可见性
        for (QWidget* widget : widgets) {
            if (widget != label_text_time) {
                widget->setVisible(label_main_text_only); // 设置控件的可见性
            }
        }
        label_main_text_only = !label_main_text_only;

        });


    connect(pAc5, &QAction::triggered, [=] {
        
        MySubWindow* widget = new MySubWindow();
        widget->setWindowIcon(QIcon(":/Qt_focus/ico/xiaoyu.png"));
        QString widget_style=ui.centralWidget->styleSheet();
        widget->setStyleSheet(widget_style);

        widget->show();
        });

    connect(pAc6, &QAction::triggered, [=] {

        SandSimulator* widget = new SandSimulator();
        widget->setContentsMargins(0, 0, 0, 0);
        QVBoxLayout* layout = new QVBoxLayout(widget);
        layout->setContentsMargins(0, 0, 0, 0);
        widget->setMinimumSize(800, 500);
        //SandSimulator simulator;
        // 初始化状态栏
        //QStatusBar*My_statusBar = new QStatusBar();
        //My_statusBar->setMaximumHeight(20);
        //My_statusBar->setSizeGripEnabled(false);
        //layout->addWidget(My_statusBar, 0, Qt::AlignBottom );
        //// 设置状态栏样式
        //QString widget_statusbar = "font-size: 18px;background-color:#374357;"
        //    "color: #cee8ff;"
        //    "border-top-left-radius: 0px;"
        //    "border-top-right-radius: 0px;"
        //    "border-bottom-left-radius: 5px;"
        //    "border-bottom-right-radius:5px;"; // 深色
        //My_statusBar->setStyleSheet(widget_statusbar);
        //My_statusBar->showMessage("SandParticle Simulator!");
        widget->show();
        });

    connect(option1Action1, &QAction::triggered, [=] {
        QString appDir = QCoreApplication::applicationDirPath();//获取主程序目录
        QString program = appDir + "/Executable_program/Pysider6_timer.exe";//将exe文件放到主程序同级目录下
        /*QString path_osk = R"(C:\Windows\System32\osk.exe)";*/
        run_exe(program);
        });

    connect(option1Action2, &QAction::triggered, [=] {
        //QMessageBox::information(this, "title", "ac4");
        QString path_osk = R"(C:\Windows\System32\osk.exe)";
        run_exe(path_osk);
        });
}

void Qt_focus::color_select_RMenu()
{
    my_Menu_color = new QMenu(this);
    
    QAction* pAc11 = new QAction("select color");
    QAction* pAc22 = new QAction("accept color");

    my_Menu_color->addAction(pAc11);
    my_Menu_color->addAction(pAc22);


    connect(pAc11, &QAction::triggered, [=] {
        //颜色选择器
        QColorDialog* m_pColor = new QColorDialog(this);
        m_pColor->setWindowModality(Qt::ApplicationModal);
        m_pColor->setCurrentColor(QColor(Qt::red));//初始颜色
        m_pColor->show();
        ui.statusBar->showMessage("select color!");
        });

    connect(pAc22, &QAction::triggered, [=] {
       ui.statusBar->showMessage("accept color!");
        });

}

void Qt_focus::contextMenuEvent(QContextMenuEvent* event)
{
    // 确保默认菜单被初始化
    if (Rclick_Menu == nullptr) {
        Main_page_Rmenu();
    }
    // 检测 Shift 键是否被按下
    if (QApplication::keyboardModifiers() & Qt::ShiftModifier) {
        // 确保颜色菜单被初始化
        if (my_Menu_color == nullptr) {
            color_select_RMenu();
        }
        // 在当前鼠标位置显示 my_Menu_color 菜单
        my_Menu_color->exec(QCursor::pos());
    }
    else {
        // 在鼠标位置显示默认菜单
        Rclick_Menu->exec(event->globalPos());
    }
}

#pragma endregion

//主页关闭事件提示
void  Qt_focus::closeEvent(QCloseEvent* event) {
    stylesheet_QT style;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "prompt !", " Are you sure to quit!",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        event->accept();
    }
    else {
        event->ignore();
    }
    this->setStyleSheet(style.widget_gray1);

}

#pragma region //无边框实现//override
//实现鼠标控制窗口移动
void Qt_focus::maximizeRestore() {  // 定义最大化和恢复
    if (GLOBAL_STATE == 0) {  // 判断当前状态是否为正常状态
        showMaximized();  // 最大化窗口
        GLOBAL_STATE = 1;  // 更新状态为最大化
        // 设置布局边距等
        /*drapShadowLayout->setContentsMargins(0, 0, 0, 0);*/
        // 更新按钮文本或提示
        //button_max->setText("Restore");
        button_max->setToolTip("Restore");
        ui.statusBar->showMessage("Window has been maximized!", 1000);
    }
    else {  // 当前状态为最大化状态
        GLOBAL_STATE = 0;  // 更新状态为正常
        showNormal();  // 恢复窗口
        resize(width() + 2, height() + 2);  // 微调大小以触发布局更新
        // 恢复布局边距等
        /*drapShadowLayout->setContentsMargins(10, 10, 10, 10);*/
        // 更新按钮文本或提示
        //button_max->setText("Maximize");

        ui.statusBar->showMessage("Window has been restored!", 1000);
    }
}

void Qt_focus::mousePressEvent(QMouseEvent* event)  {
    if (event->button() == Qt::LeftButton) {
        // 记录鼠标点击的位置
        dragStartPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        isDragging = true;  // 标记为正在拖动
    }
}

void Qt_focus::mouseMoveEvent(QMouseEvent* event) {
    if (isDragging) {
        // 移动窗口到新的位置
        move(event->globalPosition().toPoint() - dragStartPosition);
        QPoint newPos = event->globalPosition().toPoint() - dragStartPosition;
        widget_customMove(newPos.x(), newPos.y());
        update();  // 更新窗口
    }
}

void Qt_focus::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        isDragging = false;  // 拖动结束
       
    }
}

void Qt_focus::widget_customMove(int x, int y) {
    // 获取所有的屏幕
    const QList<QScreen*> screens = QGuiApplication::screens();

    int screenWidth = 0;
    int screenHeight = 0;
    QRect screenGeometry;

    // 找到当前鼠标位置所在的屏幕
    for (QScreen* screen : screens) {
        QRect geometry = screen->geometry();
        if (geometry.contains(QPoint(x, y))) {
            screenGeometry = geometry;
            screenWidth = screenGeometry.width();
            screenHeight = screenGeometry.height();
            break;
        }
    }
    //// 获取主屏幕
    //QScreen* screen = QGuiApplication::primaryScreen();
    //QRect screenGeometry = screen->geometry();
    //const int margin = 50; // 吸附的边距

    const int margin = 50; // 吸附的边距

    // 吸附到屏幕边缘
    if (x < screenGeometry.left() + margin) {
        x = screenGeometry.left();  // 吸附至左边缘
    }
    else if (x > screenGeometry.right() - width() - margin) {
        x = screenGeometry.right() - width()+1;  // 吸附至右边缘
    }

    if (y < screenGeometry.top() + margin) {
        y = screenGeometry.top();  // 吸附至顶部边缘
    }
    else if (y > screenGeometry.bottom() - height() - margin) {
        y = screenGeometry.bottom() - height();  // 吸附至底部边缘
    }

    // 调用父类的 move 方法
    QMainWindow::move(x, y);
}

#pragma endregion

#pragma region //按键事件
//键盘按键a-z事件
void Qt_focus::keyPressEvent(QKeyEvent* event)
{
    pressedKeys.insert(event->key());
    //// 检测 E 键是否被按下
    //if (event->key() == Qt::Key_E) {
    //    // 处理 E 键相关逻辑，比如更新状态栏消息
    //    ui.statusBar->showMessage("E key is pressed.");
    //}
    // 检测 Q+A 键是否被按下
    if (pressedKeys.contains(Qt::Key_Q) && pressedKeys.contains(Qt::Key_A)) {
        ui.statusBar->showMessage("Q+A key is pressed.", 100);
    }
    if (event->key() == Qt::Key_Escape) {
        // 处理 E 键相关逻辑，比如更新状态栏消息
        ui.statusBar->showMessage("Escape key is pressed.", 1000);
    }
}
//键盘释放事件
void Qt_focus::keyReleaseEvent(QKeyEvent* event) {
    // 从集合中移除释放的键
    pressedKeys.remove(event->key());
    // 获取释放的键
    QChar keyChar = event->text()[0].toUpper(); // 获取按键对应的字符
    QString color = randonColor();
    QString style_current = ui.statusBar->styleSheet();//获取当前状态栏样式
    ui.statusBar->setStyleSheet(style_current + QString("color:%1;").arg(color));
    // 触发状态栏更新
    ui.statusBar->showMessage(QString("\t\t%1").arg(keyChar), 500);//显示释放的键

}
// 定义事件过滤器
bool Qt_focus::eventFilter(QObject* obj, QEvent* event) {
    if (obj == widget_upper|| obj == ui.statusBar) {
        //// 处理鼠标事件,进入获取位置信息
        //if (event->type() == QEvent::Enter) {
        //    qDebug() << "Mouse entered widget_upper";
        //}
        //else if (event->type() == QEvent::Leave) {
        //    qDebug() << "Mouse left widget_upper";
        //}
        //else if (event->type() == QEvent::MouseMove) {
        //    QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        //    qDebug() << "Mouse moved within widget_upper at:" << mouseEvent->pos();
        //}
        if (event->type() == QEvent::MouseButtonDblClick) { // 检测双击事件
            maximizeRestore(); // 调用 maximizeRestore 方法
            return true; // 事件被处理
        }
    }
    if (obj == label_text_time) {
        
        if (event->type() == QEvent::MouseButtonDblClick) { // 检测双击事件
            maximizeRestore(); // 调用 maximizeRestore 方法
            return true; // 事件被处理
        }
    }
    return QWidget::eventFilter(obj, event); // 调用基类事件过滤器
}
#pragma endregion

QString Qt_focus::randonColor() {
    auto generator = QRandomGenerator::global();
    int low_bound = 100;
    int red = generator->bounded(low_bound, 256);    // 生成 0-255 之间的随机红色值
    int green = generator->bounded(low_bound, 256);  // 生成 0-255 之间的随机绿色值
    int blue = generator->bounded(low_bound, 256);   // 生成 0-255 之间的随机蓝色值

    // 创建随机颜色字符串
    QString color = QString("rgb(%1, %2, %3)").arg(red).arg(green).arg(blue);
    return color;
}

void Qt_focus::hexToRGB(const std::string& hex, double& r, double& g, double& b) {
    std::stringstream ss;
    ss << std::hex << hex.substr(1); // 去掉开头的 '#'
    unsigned int color;
    ss >> color;
    r = ((color >> 16) & 0xFF) / 255.0;
    g = ((color >> 8) & 0xFF) / 255.0;
    b = (color & 0xFF) / 255.0;
}

void Qt_focus::Draw_audio_sensor() {

    if (m_chart == nullptr) {

        const QAudioDevice inputDevice = QMediaDevices::defaultAudioInput();//检查设备是否可以使用
        if (inputDevice.isNull()) {
            QMessageBox::warning(nullptr, "audio",
                "There is no audio input device available.");
            return;
        }
        else {
            ui.statusBar->showMessage("ok");
        }

        m_chart = new QChart();
        // 设置背景颜色
        double r, g, b;
        hexToRGB("#1e293b", r, g, b);
        qDebug() << r << g << b;
        m_chart->setBackgroundBrush(QBrush(QColor(r*255, g*255, b*255))); //背景颜色

        m_series = new QSplineSeries();//1
        hexToRGB("#FF3D3D", r, g, b);
        QPen pen(QColor(r * 255, g * 255, b * 255)); // 创建一个红色的画笔
        pen.setWidth(1);   // 设置画笔宽度
        m_series->setPen(pen); // 应用画笔到曲线系列
        m_chart->addSeries(m_series);//2

        widget_audio = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout(widget_audio);
        layout->setContentsMargins(0, 0, 0, 0);
        auto chartview = new QChartView(m_chart);
        chartview->setMinimumHeight(400);
        QTextEdit* textedit = new QTextEdit();

        QString message = QString("inputDevice%1").arg(inputDevice.description());
        textedit->setText(message);
        textedit->setMaximumHeight(50);
        layout->addWidget(chartview,0, Qt::AlignTop);
        layout->addWidget(textedit, 0, Qt::AlignTop);
        layout->addStretch(1);

        //设置音频采样格式
        QAudioFormat formatAudio;
        formatAudio.setSampleRate(1000);
        formatAudio.setChannelCount(1);
        formatAudio.setSampleFormat(QAudioFormat::UInt8);
        //判断采样格式是否支持
        /*QAudioDevice info(QMediaDevices::defaultAudioOutput());
        if (!info.isFormatSupported(formatAudio)) {
            qWarning() << "Raw audio format not supported by backend, cannot play audio.";
            ui.statusBar->showMessage(" format mistake! error!");
            return;
        }
        else {
            ui.statusBar->showMessage(" format ok");
        }*/
        //// 创建坐标轴
        QFont font;
        font.setPointSize(20);  // 设置字体大小
        font.setFamily("Arial"); // 设置字体类型
        auto axisX = new QValueAxis;
        axisX->setTitleText("Samples"); // 设置坐标轴标签
        axisX->setTitleFont(font);
        axisX->setRange(0, XYSeriesIODevice::sampleCount);
        auto axisY = new QValueAxis;
        axisY->setTitleText("Audio level");
        axisY->setTitleFont(font);
        float max_value = 0.5;
        axisY->setRange(-max_value, max_value);

        hexToRGB("#cee8ff", r, g, b);
        QColor color_axis(r * 255, g * 255, b * 255);
        QPen gridPen(QColor(r * 255, g * 255, b * 255)); // 
        //gridPen.setStyle(Qt::DashLine); // 设置为虚线（可选）
        axisX->setGridLinePen(gridPen);
        axisY->setGridLinePen(gridPen);
        axisY->setLabelsColor(color_axis); // 设置坐标轴标签颜色
        axisX->setLabelsColor(color_axis);

        m_chart->addAxis(axisX, Qt::AlignBottom);// 将坐标轴添加到 QChart 中
        m_series->attachAxis(axisX);// 将系列关联到坐标轴
        m_chart->addAxis(axisY, Qt::AlignLeft);
        m_series->attachAxis(axisY);
        m_chart->legend()->hide();
        m_chart->setTitle("Data from the microphone(" + inputDevice.description() + ")");
        m_chart->setTitleFont(font);
        //m_chart->createDefaultAxes();// 创建默认坐标轴
        // 
        //m_chart->setTheme(QChart::ChartThemeLight);
        hexToRGB("#FFFFFF", r, g, b);
        QBrush titleBrush(QColor(r * 255, g * 255, b * 255));
        m_chart->setTitleBrush(titleBrush);        // 应用颜色到标题
        axisX->setTitleBrush(titleBrush);
        axisY->setTitleBrush(titleBrush);
        //设置音频源
        m_audioSource = new QAudioSource(inputDevice, formatAudio);
        m_audioSource->setBufferSize(500);
        
        m_device = new XYSeriesIODevice(m_series);
        m_device->open(QIODevice::WriteOnly);
      

        m_audioSource->start(m_device);
       
        m_isRecording=true;
        ui.statusBar->showMessage("audio is recording!", 1000);
        //
        // 创建一个文件用于存储录音数据,未成功
        //initializeAudioFile();
        //writeAudioData();
        //
        //widget_audio->show();
    }
    else {
        ui.statusBar->showMessage("audio is already recording!", 1000);
        return;
    }
}

// 初始化函数中创建并打开文件
void Qt_focus::initializeAudioFile() {
    QFile* audioFile = new QFile("recorded_audio.raw");
    m_device->setAudioFile(audioFile); // 假定 m_device 是你已创建的设备实例

    // 尝试打开音频文件
    if (!m_device->getAudioFile()->open(QIODevice::WriteOnly)) {
        QMessageBox::warning(nullptr, "audio", "Unable to open file for writing.");
        return;
    }
   
}
// 函数用于处理音频数据并写入文件
void Qt_focus::writeAudioData() {
    // 确保音频文件已经打开
    if (m_device->getAudioFile()->isOpen() && m_device->getAudioFile()->isWritable()) {
        QByteArray audioData = m_device->readAudioData(); // 读取设备中的音频数据
        // 输出 audioData 的大小
        qDebug() << "Audio data size:" << audioData.size(); // 调试输出
        if (!audioData.isEmpty()) { // 检查读取到的数据是否有效
            qint64 bytesWritten = m_device->getAudioFile()->write(audioData); // 将数据写入文件
           
            if (bytesWritten == -1) { // 如果写入失败
                QMessageBox::warning(nullptr, "audio", "Failed to write audio data to file.");
            }
            else {
                // 可以选择输出写入的字节数
                qDebug() << "Wrote" << bytesWritten << "bytes to the audio file.";
                //显示数据
              
            }
        }
    }
    else {
        QMessageBox::warning(nullptr, "audio", "Audio file is not open for writing.");
    }
}
// 记得在适当的时候关闭文件
void Qt_focus::closeAudioFile() {
    if (m_device->getAudioFile()->isOpen()) {
        m_device->getAudioFile()->close();
    }
}

// 添加函数来暂停音频录制
void Qt_focus::pauseAudio() {

    if (m_isRecording=true) {
        m_audioSource->stop(); // 停止音频源
        m_isRecording = false;  // 更新状态为暂停
        ui.statusBar->showMessage("Audio recording paused", 1000);
    }
    else {
        ui.statusBar->showMessage("audio is not recording!", 1000);
        return;
    }
}
// 添加函数来继续音频录制
void Qt_focus::resumeAudio() {

    if (widget_audio) {
        if (!m_isRecording) {
            m_audioSource->start(m_device); // 重新开始录音
            m_isRecording = true; // 更新状态为录制
            ui.statusBar->showMessage("Audio recording resumed", 1000);
        }
    }
    else {
        ui.statusBar->showMessage("audio is not recording!", 1000);
    return;
    }
    
}

//启动外部程序
void Qt_focus::run_exe(QString& program) {

    //QString appDir = QCoreApplication::applicationDirPath();
    //QString program = appDir + "/run_exe/Console_sph.exe";//将exe文件放到主程序同级目录下

    //QString path_osk = R"(C:\Windows\System32\osk.exe)";
    //QString program = program;
    // 检查文件是否存在
    if (QFile::exists(program)) {
        qDebug() << "exe path:" << program;
        ui.statusBar->showMessage(tr(" %1").arg(program), 3000);//5s
    }
    else {
        QMessageBox::critical(nullptr, "Error", "Call error,Please check program!");
        return;
    }
    //start process_exe1
    //QProcess process_exe1;
    process_exe1.start(program);
    process_exe1.waitForStarted();
    process_exe1.waitForFinished();

    //QString strResult = QString::fromLocal8Bit(process_exe1.readAllStandardOutput());
    //QMessageBox msgBox(this);
    //msgBox.setText(strResult);
    //msgBox.exec();

    if (!process_exe1.startDetached(program)) {
        qDebug() << "Failed to start process:" << process_exe1.errorString(); // 捕捉错误信息
    }

}
//////////////////参考分割线/////////////////////////
#pragma region //Qt自带 qdialog
//Qdialog
    //颜色选择器
    //QColorDialog* m_pColor = new QColorDialog(this);
    //m_pColor->setWindowModality(Qt::ApplicationModal);
    //m_pColor->setCurrentColor(QColor(Qt::red));//初始颜色
    //m_pColor->show();

//    QInputDialog* input_dialog = new QInputDialog(this);
//    input_dialog->setWindowTitle("Set Focus Time");
//    input_dialog->setLabelText("Please enter the focus time:");
//    input_dialog->setIntRange(1, 120);
//    input_dialog->setIntStep(1);
//    input_dialog->setModal(true);
//    input_dialog->setInputMode(QInputDialog::IntInput);
//    input_dialog->setOkButtonText("OK");
//    input_dialog->setCancelButtonText("Cancel");
//    input_dialog->resize(300, 100);
//    input_dialog->show();
//connect(input_dialog, &QInputDialog::intValueSelected, this, [=](int value) {
//    int value = value * 60; // 转换为秒
//    ui.statusBar->showMessage(QString("Focus time has set to %1 minutes!").arg(QString::number(value)));
//});

//QProgressDialog* progressDialog = new QProgressDialog(this);
//progressDialog->setWindowTitle("Focus Time");
//progressDialog->setLabelText("Focus Time");
//progressDialog->setCancelButtonText("Cancel");
//progressDialog->setMinimumDuration(0);
//progressDialog->setAutoClose(true);
//progressDialog->setAutoReset(true);
//progressDialog->setRange(0, 100);
//progressDialog->setValue(60);
//progressDialog->show();

//QPrintPreviewDialog* previewDialog = new QPrintPreviewDialog(this);
//previewDialog->setWindowTitle("Print Preview");
//previewDialog->setWindowIcon(QIcon(":/Qt_focus/ico/focus.png"));
//previewDialog->resize(640, 480);
//previewDialog->show();

#pragma endregion

//lambda表达式示例：
//connect(QpushButton_3dclip_show, &QPushButton::clicked, this, [=]() {
//    if (actor_user_grid) {
//        actor_user_grid->VisibilityOff();
//        renderWindow->Render();
//        user_grid_plane_widget();
//        user_grid_plane_widget_x();
//        user_grid_plane_widget_y();
//    }
//    else
//    {
//        QErrorMessage message;
//        message.showMessage("Please add a grid first!");
//        message.exec();
//        ui.statusBar->showMessage("Please add a grid first!");
//    }
//    });

//打开默认浏览器网址;
// 
//// 要打开的URL，这里以 "https://www.example.com" 为例
//QUrl url("https://");
//// 打开默认浏览器
//if (QDesktopServices::openUrl(url)) {
//    qDebug() << "Default browser opened successfully.";
//}
//else {
//    qDebug() << "Failed to open the default browser.";
//}

//// 获取主屏幕
//QScreen* screen = QApplication::primaryScreen();

//// 获取屏幕的宽度和高度
//int screenWidth = screen->geometry().width();
//int screenHeight = screen->geometry().height();

//// 输出屏幕的宽度和高度
//qDebug() << "Screen Width:" << screenWidth;
//qDebug() << "Screen Height:" << screenHeight;
// 获取所有屏幕
//QList<QScreen*> screens = QGuiApplication::screens();

//// 遍历所有屏幕并输出它们的宽度和高度
//for (QScreen* screen : screens) {
//    int screenWidth = screen->geometry().width();
//    int screenHeight = screen->geometry().height();
//    qDebug() << "Screen Width:" << screenWidth;
//    qDebug() << "Screen Height:" << screenHeight;
//}