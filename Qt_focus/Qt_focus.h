#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt_focus.h"
/// 自定义头文件
#include "my_button_class.h"
#include"mywindows_class.h"
#include"xyseriesiodevice.h"
#include "roundprogressbar.h"
#include"SandSimulator.h"//
#include"tabhover.h"
#include"CameraBackend.h"

#include"fontawesomeicons.h"

///QT-header
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <qgridlayout.h>
#include <QPushButton>
#include <QSplitter>
#include <qfiledialog.h>
#include <QTextEdit>
#include <QDockWidget>
#include <qdialog.h>
#include <QLabel>
#include <qmessagebox.h>
#include <qspinbox.h>
#include <QToolBox>
#include <QProgressBar>
#include <QTabBar> // 添加这一行
#include <QMouseEvent>
#include <QRandomGenerator>
#include <QPainterPath>
#include <QDesktopServices>
#include <QKeyEvent>
#include <QSet>
#include <QProcess>
#include<QLCDNumber>

//QT-widgets
#include<qcolordialog.h>
#include<qinputdialog.h>
#include<qprogressdialog.h>
#include <QPrintPreviewDialog>

#include <QTimer>  // 添加这一行
#include <QString>

//QT-audio

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QXYSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>

#include <QFont>

#include <QAudioDevice>
#include<qmediadevices.h>

#include <QAudioInput>
#include <QAudioSource>
#include<QAudioSink>
#include <QAudioFormat>

#include <sstream>

class Qt_focus : public QMainWindow
{
    Q_OBJECT

public:
    Qt_focus(QWidget *parent = nullptr);

    ~Qt_focus();

private:
    Ui::Qt_focusClass ui;

private:
    QFont fontAwesomeFont;
protected:
    //关闭窗口提示！
    void closeEvent(QCloseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    // 菜单事件
    void contextMenuEvent(QContextMenuEvent* event) override;
    void Main_page_Rmenu();
    void color_select_RMenu();



private:
    QSize initialSize;
    QMenu* Rclick_Menu = nullptr;
    QMenu* my_Menu_color = nullptr;
    // 添加析构函数
    QSet<int> pressedKeys;  // 声明 pressedKeys

    int GLOBAL_STATE = 0;
    bool isDragging = false;  // 拖动状态
    QPoint dragStartPosition;  // 鼠标点击位置

public:

    QWidget* widget_upper;
    QTextEdit* textEdit_history;
    QTabWidget* TabWidget_Main;
    QGridLayout* widget_mid_layout;

    QWidget* Widget_page_home;
    QWidget* Widget_page0;//页面成员声明
    QWidget* Widget_page1;
    QWidget* Widget_page2;
    QWidget* Widget_page3;
    QWidget* Widget_page4;
    QWidget* Widget_page5;

    QWidget* widget_settime;
    bool widget_settime_show = true;

    QGridLayout* page0_layout_grid;//页面0
    QVBoxLayout* page1_layout_grid;//页面1
    QVBoxLayout* page2_layout_grid;//页面2
    QVBoxLayout* page3_layout_grid;//页面3
    QVBoxLayout* page4_layout_grid;//页面4
    QVBoxLayout* page5_layout_grid;//页面5

    QList<QLabel*> label_tab;
    QList<QLabel*> labels;
    private:
        QTimer* timer_dot = nullptr;

    QLabel* label_text_time;
    bool label_main_text_only = false;
    QProgressBar* progress_bar;
    int Focus_time;
    int Focus_time2;
    int remainingTime;      // 剩余时间，以秒为单位
    int progress_Value;
    QTimer* timer;          // 声明一个 QTimer 指针

    QPushButton* button_set_focus;
    QPushButton* button_focus_reset;
    QPushButton* button_focus_pause;

    bool is_focus_start=false;
    bool is_focus_pause=false;

    //page2
    QLabel* label_task_title;
    QTextEdit* QtextEdit_tasks;
    int taskCount = 0;

    //无边框部分
    QPushButton* button_max;
    QPushButton* button_min;
    QPushButton* button_close;

    //音频部分
    QPushButton* pauseButton;
    XYSeriesIODevice* m_device;//音频部分
    QChart* m_chart;
    QLineSeries* m_series;
    QAudioInput* m_audioInput;
    QAudioSource* m_audioSource;

    QWidget* widget_audio;
    bool m_isRecording=false;
    bool audio_isPause = false;
    bool widget_bool = false;

    QProcess process_exe1;//exe进程

    bool isFrontCamera = false;

public slots:

    // 自定义函数
    void maximizeRestore();
    bool eventFilter(QObject* obj, QEvent* event);
    void widget_customMove(int x, int y);

QString getSystemTime();

void set_lable_time();
void start_lable_time();
void reset_lable_time();
void Pause_focus_time();
void updateCountdown();  // 新增槽函数

QString randonColor();
void hexToRGB(const std::string& hex, double& r, double& g, double& b);
//音频显示audio曲线
void Draw_audio_sensor();
void initializeAudioFile();
void writeAudioData();
void closeAudioFile();

void pauseAudio();
void resumeAudio();

//启动外部exe
void run_exe(QString& program);
void setAllWindowIcons(const QIcon& icon);
void Creat_fontawesomewin();

};