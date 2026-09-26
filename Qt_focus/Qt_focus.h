#pragma once

#include <QMainWindow>
#include <QFont>
#include <QPoint>
#include <QProcess>
#include <QSet>
#include <QSize>
#include <QIcon>
#include <QColor>

#include "style.h"
#include "fontawesomeicons.h"

namespace Ui {
    class Qt_focusClass;
}

// 前置声明
class QCloseEvent;
class QKeyEvent;
class QMouseEvent;
class QContextMenuEvent;
class QWidget;
class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;
class QProgressBar;
class QTabWidget;
class QTimer;
class QGridLayout;
class QVBoxLayout;
class QMenu;
class QStatusBar;

class Qt_focus : public QMainWindow
{
    Q_OBJECT

public:
    explicit Qt_focus(QWidget* parent = nullptr);
    ~Qt_focus() override;

    // 核心工具：纯代码矢量图标生成器（无需任何 png 图片）
    static QIcon createFontIcon(FontAwesomeIcons::IconIdentity id, const QColor& color, int size = 28);

protected:
    void closeEvent(QCloseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;
    bool eventFilter(QObject* obj, QEvent* event) override;

private slots:
    void maximizeRestore();
    void widgetCustomMove(int x, int y);
    void toggleTheme();
    void applyTheme(stylesheet_QT::ThemeMode mode);

    void setLabelTime();
    void startLabelTime();
    void resetLabelTime();
    void pauseFocusTime();
    void updateCountdown();

    void createFontAwesomeWindow();
    void openLabelUrl();

private:
    void initMainPageRightMenu();
    void initColorSelectRightMenu();
    static QString getSystemTime();
    static QString getRandomColor();

private:
    Ui::Qt_focusClass* ui = nullptr;

    stylesheet_QT m_style;
    stylesheet_QT::ThemeMode m_currentTheme = stylesheet_QT::ThemeMode::LightSage;

    QSize m_initialSize;
    QPoint m_dragStartPosition;
    bool m_isDragging = false;
    int m_globalState = 0;
    QSet<int> m_pressedKeys;

    QMenu* m_rightClickMenu = nullptr;
    QMenu* m_colorMenu = nullptr;

    // 标题栏组件
    QWidget* m_widgetUpper = nullptr;
    QLabel* m_labelTitle = nullptr;
    QPushButton* m_btnMax = nullptr;
    QPushButton* m_btnMin = nullptr;
    QPushButton* m_btnClose = nullptr;

    // Tab 导航
    QTabWidget* m_tabWidgetMain = nullptr;
    QList<QLabel*> m_tabLabels;

    // 页面
    QWidget* m_widgetPageHome = nullptr;
    QWidget* m_widgetPage0 = nullptr;
    QWidget* m_widgetPage1 = nullptr;
    QWidget* m_widgetPage2 = nullptr;

    QVBoxLayout* m_page3LayoutGrid = nullptr;
    QGridLayout* m_page0LayoutGrid = nullptr;
    QVBoxLayout* m_page1LayoutGrid = nullptr;
    QVBoxLayout* m_page2LayoutGrid = nullptr;

    // Page Home
    QLabel* m_labelHomeMain = nullptr;

    // Page 0: 专注倒计时
    QWidget* m_widgetSetTime = nullptr;
    bool m_isWidgetSetTimeShow = true;
    QTimer* m_timerCountdown = nullptr;
    QLabel* m_labelTime = nullptr;
    bool m_isLabelMainTextOnly = false;
    QProgressBar* m_progressBar = nullptr;

    int m_focusTime = 0;
    int m_remainingTime = 0;
    int m_progressValue = 0;

    QPushButton* m_btnSetFocus = nullptr;
    QPushButton* m_btnFocusReset = nullptr;
    QPushButton* m_btnFocusPause = nullptr;

    bool m_isFocusStart = false;
    bool m_isFocusPause = false;

    // Page 1: 任务清单
    QLabel* m_labelTaskTitle = nullptr;
    QWidget* m_taskContainer = nullptr;
    QTextEdit* m_textEditTasks = nullptr;
    QPushButton* m_btnAddTask = nullptr;
    QPushButton* m_btnClearTask = nullptr;
    int m_taskCount = 0;

    // Page 2: 外链与搜索 (搜索框已升级为 QLineEdit)
    QLabel* m_labelLinkTitle = nullptr;
    QPushButton* m_btnLink1 = nullptr;
    QPushButton* m_btnLink2 = nullptr;
    QLineEdit* m_textEditSearch = nullptr;
    QPushButton* m_btnSearch = nullptr;
};