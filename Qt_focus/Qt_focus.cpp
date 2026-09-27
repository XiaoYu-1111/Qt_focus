#include "Qt_focus.h"
#include "ui_Qt_focus.h"
#include "style.h"

// 绘图与渲染
#include <QPainter>
#include <QPixmap>

// 事件与控件
#include <QMouseEvent>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QContextMenuEvent>
#include <QTabBar>
#include <QLineEdit>

// 实用基础类
#include <QScreen>
#include <QGuiApplication>
#include <QDateTime>
#include <QTime>
#include <QTimer>
#include <QUrl>
#include <QDesktopServices>
#include <QRandomGenerator>

// 控件与布局
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QProgressBar>
#include <QLCDNumber>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QFrame>
#include <QMenu>
#include <QStatusBar>
#include <QColorDialog>
#include <QMessageBox>
#include <QSpacerItem>

// 自定义类
#include "roundprogressbar.h"
#include "tabhover.h"
#include "fontawesomeicons.h"
#include "my_button_class.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
#pragma execution_character_set("utf-8")
#endif

// ==================== 纯代码矢量图标绘制引擎 ====================
QIcon Qt_focus::createFontIcon(FontAwesomeIcons::IconIdentity id, const QColor& color, int size)
{
    QPixmap pix(size, size);
    pix.fill(Qt::transparent);

    QPainter painter(&pix);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    QFont font = FontAwesomeIcons::Instance().getFont();
    font.setPixelSize(size - 6);
    painter.setFont(font);
    painter.setPen(color);

    const QString iconStr(FontAwesomeIcons::Instance().getIconChar(id));
    painter.drawText(pix.rect(), Qt::AlignCenter, iconStr);

    return QIcon(pix);
}

Qt_focus::Qt_focus(QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::Qt_focusClass)
{
    ui->setupUi(this);

    // ==================== 1. 窗口基础设置 ====================
    this->setWindowTitle("RAIN Focus OS");
    this->setContentsMargins(0, 0, 0, 0);
    this->setContextMenuPolicy(Qt::DefaultContextMenu);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);

    // 代码生成程序主图标（绿叶图标）
    this->setWindowIcon(createFontIcon(FontAwesomeIcons::IconIdentity::icon_leaf, QColor("#344e41"), 48));

    this->resize(1020, 660);
    this->setMinimumSize(920, 580);
    m_initialSize = this->size();

    ui->mainToolBar->hide();
    ui->statusBar->setMinimumHeight(32);
    ui->statusBar->setMaximumHeight(36);

    QVBoxLayout* mainLayout = new QVBoxLayout(ui->centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // ==================== 2. 现代顶部导航条 ====================
    m_widgetUpper = new QWidget(this);
    m_widgetUpper->installEventFilter(this);
    ui->statusBar->installEventFilter(this);

    QHBoxLayout* layoutUpper = new QHBoxLayout(m_widgetUpper);
    // 左侧设为 28px（与下文卡片严格对齐），右侧留足 24px（防止右侧裁切）
    layoutUpper->setContentsMargins(28, 14, 24, 8);
    layoutUpper->setSpacing(8); // 三个圆点之间保持 8px 优雅间距

    m_labelTitle = new QLabel("RAIN FOCUS WORKSTATION", m_widgetUpper);
    m_labelTitle->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    layoutUpper->addWidget(m_labelTitle);
    layoutUpper->addStretch();

    // 尺寸调为 14px，视觉更饱满圆润
    const int btnSize = 14;
    auto setupWindowBtn = [btnSize](QPushButton* btn, const QString& tip) {
        btn->setFixedSize(btnSize, btnSize);
        btn->setToolTip(tip);
        btn->setCursor(Qt::PointingHandCursor);
        };

    m_btnMin = new QPushButton(m_widgetUpper);
    setupWindowBtn(m_btnMin, "Minimize");

    m_btnMax = new QPushButton(m_widgetUpper);
    setupWindowBtn(m_btnMax, "Maximize / Restore");

    m_btnClose = new QPushButton(m_widgetUpper);
    setupWindowBtn(m_btnClose, "Close");

    layoutUpper->addWidget(m_btnMin);
    layoutUpper->addWidget(m_btnMax);
    layoutUpper->addWidget(m_btnClose);

    connect(m_btnMax, &QPushButton::clicked, this, &Qt_focus::maximizeRestore);
    connect(m_btnMin, &QPushButton::clicked, this, &Qt_focus::showMinimized);
    connect(m_btnClose, &QPushButton::clicked, this, &Qt_focus::close);

    mainLayout->addWidget(m_widgetUpper);

    // ==================== 3. 主 Tab 导航栏（纯代码矢量图 + 文字） ====================
    QWidget* widgetMid = new QWidget(this);
    QHBoxLayout* layoutMid = new QHBoxLayout(widgetMid);
    // 左侧同样设置为 28px，让第一个 Tab 按钮“工作台”刚好对齐下方的卡片左边缘！
    layoutMid->setContentsMargins(28, 4, 28, 6);

    m_tabWidgetMain = new QTabWidget(widgetMid);
    m_tabWidgetMain->setMovable(true);
    m_tabWidgetMain->setUsesScrollButtons(true);
    m_tabWidgetMain->tabBar()->setIconSize(QSize(20, 20));

    layoutMid->addWidget(m_tabWidgetMain);
    mainLayout->addWidget(widgetMid);

    m_widgetPageHome = new QWidget();
    m_widgetPage0 = new QWidget();
    m_widgetPage1 = new QWidget();
    m_widgetPage2 = new QWidget();

    // 完全使用代码矢量图标 + 规范字距
    const QColor initialIconColor("#344e41");
    m_tabWidgetMain->addTab(m_widgetPageHome, createFontIcon(FontAwesomeIcons::IconIdentity::icon_home, initialIconColor), "  工作台");
    m_tabWidgetMain->addTab(m_widgetPage0, createFontIcon(FontAwesomeIcons::IconIdentity::icon_time, initialIconColor), "  专注心流");
    m_tabWidgetMain->addTab(m_widgetPage1, createFontIcon(FontAwesomeIcons::IconIdentity::icon_tasks, initialIconColor), "  目标清单");
    m_tabWidgetMain->addTab(m_widgetPage2, createFontIcon(FontAwesomeIcons::IconIdentity::icon_external_link, initialIconColor), "  启动台");

    // ==================== 4. 底部状态指示 ====================
    QWidget* widgetBottom = new QWidget(this);
    QHBoxLayout* layoutBottom = new QHBoxLayout(widgetBottom);
    layoutBottom->setContentsMargins(0, 2, 0, 4);

    layoutBottom->addSpacerItem(new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum));
    m_tabLabels.clear();
    for (int i = 0; i < m_tabWidgetMain->count(); ++i) {
        HoverLabel* labelDot = new HoverLabel(i, m_tabWidgetMain);
        labelDot->setText(" ● ");
        labelDot->setMaximumSize(24, 24);
        layoutBottom->addWidget(labelDot, 0, Qt::AlignCenter);
        m_tabLabels.append(labelDot);
    }
    layoutBottom->addSpacerItem(new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum));
    mainLayout->addWidget(widgetBottom);

    // ==================== 5. Page Home (便当网格 Bento Dashboard) ====================
// ==================== 5. Page Home (增强型 Bento Grid 生产力工作台) ====================
    m_page3LayoutGrid = new QVBoxLayout(m_widgetPageHome);
    m_page3LayoutGrid->setContentsMargins(28, 10, 28, 16);
    m_page3LayoutGrid->setSpacing(12);

    // ----------------- [Bento 1] 顶部微状态条 -----------------
    QFrame* bannerFrame = new QFrame(m_widgetPageHome);
    bannerFrame->setStyleSheet(R"(
        QFrame {
            background-color: #e5ede2;
            border: 1px solid #d8e3d3;
            border-radius: 10px;
            padding: 2px 10px;
        }
    )");
    QHBoxLayout* bannerLayout = new QHBoxLayout(bannerFrame);
    bannerLayout->setContentsMargins(10, 4, 10, 4);

    QLabel* bannerDot = new QLabel("●  FLOW ENGINE ACTIVE · 深度创作工作台已就绪", bannerFrame);
    bannerDot->setStyleSheet("color: #344e41; font-size: 12px; font-weight: 700; border: none; background: transparent;");
    bannerLayout->addWidget(bannerDot);
    bannerLayout->addStretch();

    QLabel* bannerSub = new QLabel("Focus & Create · 消除干扰", bannerFrame);
    bannerSub->setStyleSheet("color: #52796f; font-size: 11px; font-weight: 500; border: none; background: transparent;");
    bannerLayout->addWidget(bannerSub);
    m_page3LayoutGrid->addWidget(bannerFrame);

    // ----------------- [Bento 2] 第一层网格：时钟看板 + 指标与环境音 -----------------
    QHBoxLayout* row1Layout = new QHBoxLayout();
    row1Layout->setSpacing(12);

    // 【卡片 1】左侧主时钟看板 + 快捷预设启动
    QFrame* clockCard = new QFrame(m_widgetPageHome);
    clockCard->setStyleSheet(R"(
        QFrame {
            background-color: #ffffff;
            border: 1px solid #d8e3d3;
            border-radius: 14px;
        }
    )");
    QVBoxLayout* clockCardLayout = new QVBoxLayout(clockCard);
    clockCardLayout->setContentsMargins(22, 16, 22, 16);
    clockCardLayout->setSpacing(8);

    QLabel* lblClockTitle = new QLabel("当前系统心流时间", clockCard);
    lblClockTitle->setStyleSheet("color: #52796f; font-size: 12px; font-weight: 600; border: none;");
    clockCardLayout->addWidget(lblClockTitle);

    QLabel* lblBigClock = new QLabel("12:00:00", clockCard);
    lblBigClock->setAlignment(Qt::AlignCenter);
    lblBigClock->setStyleSheet("color: #1a2e1d; font-size: 48px; font-weight: 700; letter-spacing: -2px; border: none;");
    clockCardLayout->addWidget(lblBigClock);

    QLabel* lblDateStatus = new QLabel(clockCard);
    lblDateStatus->setAlignment(Qt::AlignCenter);
    lblDateStatus->setStyleSheet("color: #84a98c; font-size: 12px; font-weight: 500; border: none;");
    clockCardLayout->addWidget(lblDateStatus);

    // 3 个时长预设胶囊 (点击直接写入时长并跳至专注页启动)
    QHBoxLayout* presetRow = new QHBoxLayout();
    presetRow->setSpacing(8);

    auto addPresetBtn = [this, presetRow](const QString& text, int minutes) {
        QPushButton* btn = new QPushButton(text);
        btn->setFixedHeight(34);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setStyleSheet(R"(
            QPushButton {
                background-color: #f7faf5;
                color: #344e41;
                font-size: 12px;
                font-weight: 600;
                border: 1px solid #d8e3d3;
                border-radius: 8px;
            }
            QPushButton:hover {
                background-color: #344e41;
                color: #ffffff;
                border-color: #344e41;
            }
        )");
        connect(btn, &QPushButton::clicked, this, [this, minutes]() {
            m_focusTime = minutes * 60;
            m_tabWidgetMain->setCurrentIndex(1); // 自动切换至专注页
            resetLabelTime();                    // 立即进入大字倒计时
            });
        presetRow->addWidget(btn);
        };

    addPresetBtn("⚡ 15m 快速攻坚", 15);
    addPresetBtn("🍅 25m 标准番茄", 25);
    addPresetBtn("🚀 50m 深度沉浸", 50);
    clockCardLayout->addLayout(presetRow);

    row1Layout->addWidget(clockCard, 6);

    // 右侧分栏（指标卡片 + 沉浸白噪音伴奏卡片）
    QVBoxLayout* rightColLayout = new QVBoxLayout();
    rightColLayout->setSpacing(12);

    // 【卡片 2】指标概览卡片
    QFrame* metricCard = new QFrame(m_widgetPageHome);
    metricCard->setStyleSheet(R"(
        QFrame {
            background-color: #ffffff;
            border: 1px solid #d8e3d3;
            border-radius: 14px;
        }
    )");
    QHBoxLayout* metricLayout = new QHBoxLayout(metricCard);
    metricLayout->setContentsMargins(14, 12, 14, 12);

    auto addMetricItem = [](QHBoxLayout* layout, const QString& num, const QString& title) {
        QVBoxLayout* v = new QVBoxLayout();
        v->setSpacing(2);
        QLabel* lNum = new QLabel(num);
        lNum->setAlignment(Qt::AlignCenter);
        lNum->setStyleSheet("color: #344e41; font-size: 24px; font-weight: 700; border: none;");
        QLabel* lTitle = new QLabel(title);
        lTitle->setAlignment(Qt::AlignCenter);
        lTitle->setStyleSheet("color: #84a98c; font-size: 11px; font-weight: 600; border: none;");
        v->addWidget(lNum);
        v->addWidget(lTitle);
        layout->addLayout(v);
        };

    auto addSeparator = [](QHBoxLayout* layout) {
        QLabel* sep = new QLabel("|");
        sep->setAlignment(Qt::AlignCenter);
        sep->setStyleSheet("color: #d8e3d3; border: none; font-size: 14px;");
        layout->addWidget(sep);
        };

    addMetricItem(metricLayout, "25m", "单次心流");
    addSeparator(metricLayout);
    addMetricItem(metricLayout, "3 轮", "今日完成");
    addSeparator(metricLayout);
    addMetricItem(metricLayout, "100%", "精神精力");
    rightColLayout->addWidget(metricCard);

    // 【卡片 3】白噪音沉浸伴奏胶囊（RAIN Focus 专属）
    QFrame* soundCard = new QFrame(m_widgetPageHome);
    soundCard->setStyleSheet(R"(
        QFrame {
            background-color: #ffffff;
            border: 1px solid #d8e3d3;
            border-radius: 14px;
        }
    )");
    QVBoxLayout* soundCardLayout = new QVBoxLayout(soundCard);
    soundCardLayout->setContentsMargins(16, 12, 16, 12);
    soundCardLayout->setSpacing(8);

    QLabel* lblSoundTitle = new QLabel("沉浸氛围声态 (Focus Soundscapes)", soundCard);
    lblSoundTitle->setStyleSheet("color: #52796f; font-size: 12px; font-weight: 600; border: none;");
    soundCardLayout->addWidget(lblSoundTitle);

    QHBoxLayout* soundBtnRow = new QHBoxLayout();
    soundBtnRow->setSpacing(8);

    auto addSoundPill = [this, soundBtnRow](const QString& iconText, const QString& soundName) {
        QPushButton* btn = new QPushButton(iconText);
        btn->setCheckable(true);
        btn->setFixedHeight(32);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setStyleSheet(R"(
            QPushButton {
                background-color: #f7faf5;
                color: #344e41;
                font-size: 12px;
                font-weight: 600;
                border: 1px solid #d8e3d3;
                border-radius: 8px;
            }
            QPushButton:hover {
                background-color: #e5ede2;
            }
            QPushButton:checked {
                background-color: #344e41;
                color: #ffffff;
                border-color: #344e41;
            }
        )");
        connect(btn, &QPushButton::toggled, this, [this, btn, soundName](bool checked) {
            ui->statusBar->showMessage(QString("氛围音效: %1 - %2")
                .arg(soundName)
                .arg(checked ? "▶ 播放中" : "⏹ 已暂停"), 2000);
            });
        soundBtnRow->addWidget(btn);
        };

    addSoundPill("🌧️ 细雨", "白噪音·冥想细雨");
    addSoundPill("🌲 林海", "自然风·深山古松");
    addSoundPill("☕ 咖啡", "环境声·街角咖啡");
    addSoundPill("🌊 潮汐", "舒缓浪·纯净海岸");
    soundCardLayout->addLayout(soundBtnRow);

    rightColLayout->addWidget(soundCard);
    row1Layout->addLayout(rightColLayout, 4);
    m_page3LayoutGrid->addLayout(row1Layout);

    // ----------------- [Bento 3] 第二层网格：灵感箴言卡片 + 闪念便签卡片 -----------------
    QHBoxLayout* row2Layout = new QHBoxLayout();
    row2Layout->setSpacing(12);

    // 【卡片 4】每日心流法则与灵感箴言
    QFrame* quoteCard = new QFrame(m_widgetPageHome);
    quoteCard->setStyleSheet(R"(
        QFrame {
            background-color: #ffffff;
            border: 1px solid #d8e3d3;
            border-radius: 14px;
        }
    )");
    QVBoxLayout* quoteLayout = new QVBoxLayout(quoteCard);
    quoteLayout->setContentsMargins(18, 14, 18, 14);
    quoteLayout->setSpacing(6);

    QHBoxLayout* quoteHeader = new QHBoxLayout();
    QLabel* lblQuoteTitle = new QLabel("💡 深度心流手记 (Daily Insight)", quoteCard);
    lblQuoteTitle->setStyleSheet("color: #52796f; font-size: 12px; font-weight: 600; border: none;");
    QPushButton* btnRefreshQuote = new QPushButton("换一条 ↻", quoteCard);
    btnRefreshQuote->setCursor(Qt::PointingHandCursor);
    btnRefreshQuote->setStyleSheet("color: #84a98c; font-size: 11px; border: none; background: transparent; font-weight: 600;");

    quoteHeader->addWidget(lblQuoteTitle);
    quoteHeader->addStretch();
    quoteHeader->addWidget(btnRefreshQuote);
    quoteLayout->addLayout(quoteHeader);

    QLabel* lblQuoteContent = new QLabel("“把注意力投向当下最重要的单一目标，其余的一切皆可等待。”", quoteCard);
    lblQuoteContent->setWordWrap(true);
    lblQuoteContent->setStyleSheet("color: #1a2e1d; font-size: 13px; font-weight: 600; line-height: 1.4; border: none;");
    quoteLayout->addWidget(lblQuoteContent);

    // 动态换箴言词库
    QStringList quotes = {
        "“把注意力投向当下最重要的单一目标，其余的一切皆可等待。”",
        "“在注意力涣散的时代，深度工作能力正变得愈加稀缺与珍贵。”",
        "“心流的本质，是挑战与个人技能高度匹配时的浑然忘我。”",
        "“限制多任务切换，单一目标是最高效的生产力策略。”",
        "“不要等待灵感降临才开始，开启专注之后，灵感自会随之而来。”"
    };
    connect(btnRefreshQuote, &QPushButton::clicked, this, [lblQuoteContent, quotes]() {
        static int qIndex = 0;
        qIndex = (qIndex + 1) % quotes.size();
        lblQuoteContent->setText(quotes[qIndex]);
        });
    row2Layout->addWidget(quoteCard, 5);

    // 【卡片 5】极速杂念便签 (Quick Scratchpad)
    QFrame* memoCard = new QFrame(m_widgetPageHome);
    memoCard->setStyleSheet(R"(
        QFrame {
            background-color: #ffffff;
            border: 1px solid #d8e3d3;
            border-radius: 14px;
        }
    )");
    QVBoxLayout* memoLayout = new QVBoxLayout(memoCard);
    memoLayout->setContentsMargins(18, 14, 18, 14);
    memoLayout->setSpacing(6);

    QHBoxLayout* memoHeader = new QHBoxLayout();
    QLabel* lblMemoTitle = new QLabel("📝 闪念便签 (随时记下杂念，保持专注)", memoCard);
    lblMemoTitle->setStyleSheet("color: #52796f; font-size: 12px; font-weight: 600; border: none;");
    QPushButton* btnClearMemo = new QPushButton("清空 ✕", memoCard);
    btnClearMemo->setCursor(Qt::PointingHandCursor);
    btnClearMemo->setStyleSheet("color: #84a98c; font-size: 11px; border: none; background: transparent; font-weight: 600;");

    memoHeader->addWidget(lblMemoTitle);
    memoHeader->addStretch();
    memoHeader->addWidget(btnClearMemo);
    memoLayout->addLayout(memoHeader);

    QLineEdit* memoInput = new QLineEdit(memoCard);
    memoInput->setFixedHeight(36);
    memoInput->setPlaceholderText("记下刚才脑中闪过的琐事，专注结束后再处理...");
    memoInput->setStyleSheet(R"(
        QLineEdit {
            background-color: #f7faf5;
            color: #1a2e1d;
            font-size: 12px;
            font-weight: 500;
            border: 1px solid #d8e3d3;
            border-radius: 8px;
            padding-left: 10px;
        }
        QLineEdit:focus {
            border: 1.5px solid #344e41;
            background-color: #ffffff;
        }
    )");
    connect(btnClearMemo, &QPushButton::clicked, memoInput, &QLineEdit::clear);
    memoLayout->addWidget(memoInput);

    row2Layout->addWidget(memoCard, 5);
    m_page3LayoutGrid->addLayout(row2Layout);
    m_page3LayoutGrid->addStretch();

    // 时钟定时刷新 (包含安全的格式化)
    QTimer* clockTimer = new QTimer(this);
    connect(clockTimer, &QTimer::timeout, this, [this, lblBigClock, lblDateStatus]() {
        const QDateTime now = QDateTime::currentDateTime();
        lblBigClock->setText(now.toString("hh:mm:ss"));
        lblDateStatus->setText(QString("%1 · 深度心流准备完成")
            .arg(now.toString("yyyy年MM月dd日 dddd")));
        ui->statusBar->showMessage(QString("系统实时状态: %1").arg(now.toString("yyyy-MM-dd hh:mm:ss")));
        });
    clockTimer->start(1000);

    // ==================== 6. Page 0 (专注计时 Focus) ====================
    m_page0LayoutGrid = new QGridLayout(m_widgetPage0);
    m_page0LayoutGrid->setContentsMargins(24, 24, 24, 24);
    m_page0LayoutGrid->setSpacing(16);

    m_labelTime = new QLabel("25:00", m_widgetPage0);
    m_labelTime->setAlignment(Qt::AlignCenter);
    m_labelTime->installEventFilter(this);

    m_progressBar = new QProgressBar(m_widgetPage0);
    m_progressBar->setFixedHeight(8);
    m_progressBar->setRange(0, 100);

    m_btnSetFocus = new QPushButton("设定时长", m_widgetPage0);
    m_btnFocusReset = new QPushButton("开启心流", m_widgetPage0);
    m_btnFocusPause = new QPushButton("暂停计时", m_widgetPage0);

    const QSize actionBtnSize(140, 42);
    m_btnSetFocus->setFixedSize(actionBtnSize);
    m_btnFocusReset->setFixedSize(actionBtnSize);
    m_btnFocusPause->setFixedSize(actionBtnSize);

    m_page0LayoutGrid->addWidget(m_labelTime, 0, 0, 1, 3, Qt::AlignCenter);
    m_page0LayoutGrid->addWidget(m_progressBar, 1, 0, 1, 3);
    m_page0LayoutGrid->addWidget(m_btnSetFocus, 2, 0, Qt::AlignCenter);
    m_page0LayoutGrid->addWidget(m_btnFocusReset, 2, 1, Qt::AlignCenter);
    m_page0LayoutGrid->addWidget(m_btnFocusPause, 2, 2, Qt::AlignCenter);

    connect(m_btnSetFocus, &QPushButton::clicked, this, &Qt_focus::setLabelTime);
    connect(m_btnFocusReset, &QPushButton::clicked, this, &Qt_focus::resetLabelTime);
    connect(m_btnFocusPause, &QPushButton::clicked, this, &Qt_focus::pauseFocusTime);

    m_focusTime = 1500;
    m_timerCountdown = new QTimer(this);
    connect(m_timerCountdown, &QTimer::timeout, this, &Qt_focus::updateCountdown);

    // ==================== 7. Page 1 (任务清单 Tasks) ====================
    m_page1LayoutGrid = new QVBoxLayout(m_widgetPage1);
    m_page1LayoutGrid->setContentsMargins(24, 24, 24, 24);
    m_page1LayoutGrid->setSpacing(12);

    m_labelTaskTitle = new QLabel("专注任务清单 (Focus Objectives)", m_widgetPage1);
    m_labelTaskTitle->setAlignment(Qt::AlignLeft);
    m_page1LayoutGrid->addWidget(m_labelTaskTitle);

    m_taskContainer = new QWidget(m_widgetPage1);
    QVBoxLayout* taskLayout = new QVBoxLayout(m_taskContainer);
    taskLayout->setContentsMargins(0, 0, 0, 0);
    taskLayout->setSpacing(8);

    m_textEditTasks = new QTextEdit(m_taskContainer);
    m_textEditTasks->setFixedHeight(50);
    m_textEditTasks->setPlaceholderText("记录接下来的核心任务...");
    taskLayout->addWidget(m_textEditTasks);
    m_page1LayoutGrid->addWidget(m_taskContainer);

    QWidget* taskBtnRow = new QWidget(m_widgetPage1);
    QHBoxLayout* btnLayout = new QHBoxLayout(taskBtnRow);
    btnLayout->setContentsMargins(0, 0, 0, 0);

    m_btnAddTask = new QPushButton("+ 添加新任务", taskBtnRow);
    m_btnClearTask = new QPushButton("清空清单", taskBtnRow);
    m_btnAddTask->setFixedSize(120, 36);
    m_btnClearTask->setFixedSize(120, 36);

    btnLayout->addWidget(m_btnAddTask);
    btnLayout->addWidget(m_btnClearTask);
    btnLayout->addStretch();
    m_page1LayoutGrid->addWidget(taskBtnRow);
    m_page1LayoutGrid->addStretch();

    connect(m_btnAddTask, &QPushButton::clicked, this, [this, taskLayout]() {
        if (m_taskCount >= 8) {
            QMessageBox::information(this, "提示", "单次最多规划 8 项任务！");
            return;
        }
        QTextEdit* item = new QTextEdit(m_taskContainer);
        item->setFixedHeight(50);
        item->setStyleSheet(m_style.task_test);
        item->setPlaceholderText(QString("任务 #%1 ...").arg(m_taskCount + 1));
        taskLayout->addWidget(item);
        m_taskCount++;
        ui->statusBar->showMessage(QString("已新增任务 #%1").arg(m_taskCount), 2000);
        });

    connect(m_btnClearTask, &QPushButton::clicked, this, [this, taskLayout]() {
        if (m_taskCount == 0) return;
        while (taskLayout->count() > 1) {
            QLayoutItem* item = taskLayout->takeAt(1);
            if (item) {
                if (item->widget()) delete item->widget();
                delete item;
            }
        }
        m_taskCount = 0;
        ui->statusBar->showMessage("任务已全部清空", 2000);
        });

    // ==================== 8. Page 2 (快捷工作台 Links · 搜索栏升级为 QLineEdit) ====================
    m_page2LayoutGrid = new QVBoxLayout(m_widgetPage2);
    m_page2LayoutGrid->setContentsMargins(24, 24, 24, 24);
    m_page2LayoutGrid->setSpacing(14);

    m_labelLinkTitle = new QLabel("快捷生产力启动台 (Quick Launchpad)", m_widgetPage2);
    m_page2LayoutGrid->addWidget(m_labelLinkTitle);

    m_btnLink1 = new QPushButton("Qwerty Learner (肌肉记忆键入练习)", m_widgetPage2);
    m_btnLink2 = new QPushButton("Bilibili 视频流与知识库", m_widgetPage2);
    m_btnLink1->setFixedHeight(44);
    m_btnLink2->setFixedHeight(44);
    m_btnLink1->setCursor(Qt::PointingHandCursor);
    m_btnLink2->setCursor(Qt::PointingHandCursor);

    m_page2LayoutGrid->addWidget(m_btnLink1);
    m_page2LayoutGrid->addWidget(m_btnLink2);

    // 优化：高度自适应居中搜索栏（46px 高度，文字不再挤压截断）
    QFrame* searchCard = new QFrame(m_widgetPage2);
    QHBoxLayout* searchLayout = new QHBoxLayout(searchCard);
    searchLayout->setContentsMargins(0, 10, 0, 10);
    searchLayout->setSpacing(12);

    m_textEditSearch = new QLineEdit(searchCard);
    m_textEditSearch->setFixedHeight(46);
    m_textEditSearch->setPlaceholderText("键入关键词，回车或点击按钮快速搜索...");
    m_textEditSearch->setStyleSheet(R"(
        QLineEdit {
            background-color: #ffffff;
            color: #1a2e1d;
            font-size: 14px;
            font-weight: 500;
            border: 1.5px solid #d8e3d3;
            border-radius: 10px;
            padding-left: 16px;
            padding-right: 16px;
        }
        QLineEdit:focus {
            border: 1.5px solid #344e41;
            background-color: #f7faf5;
        }
    )");

    m_btnSearch = new MyQPushButton();
    m_btnSearch->setText("搜索");
    m_btnSearch->setFixedHeight(46);
    m_btnSearch->setFixedWidth(96);
    m_btnSearch->setCursor(Qt::PointingHandCursor);
    m_btnSearch->setStyleSheet(R"(
        QPushButton {
            background-color: #344e41;
            color: #ffffff;
            font-size: 14px;
            font-weight: 600;
            border-radius: 10px;
            border: none;
        }
        QPushButton:hover { background-color: #588157; }
        QPushButton:pressed { padding-top: 2px; }
    )");

    searchLayout->addWidget(m_textEditSearch);
    searchLayout->addWidget(m_btnSearch);
    m_page2LayoutGrid->addWidget(searchCard);
    m_page2LayoutGrid->addStretch();

    connect(m_btnLink1, &QPushButton::clicked, this, []() {
        QDesktopServices::openUrl(QUrl("https://qwerty.liumingye.cn/"));
        });
    connect(m_btnLink2, &QPushButton::clicked, this, []() {
        QDesktopServices::openUrl(QUrl("https://www.bilibili.com/"));
        });

    // 支持回车直接搜索
    connect(m_textEditSearch, &QLineEdit::returnPressed, m_btnSearch, &QPushButton::click);
    connect(m_btnSearch, &QPushButton::clicked, this, [this]() {
        const QString q = m_textEditSearch->text().trimmed();
        if (!q.isEmpty()) {
            QDesktopServices::openUrl(QUrl("https://www.baidu.com/s?wd=" + q));
        }
        });

    // ==================== 9. 执行主题注入 ====================
    applyTheme(m_currentTheme);
}

Qt_focus::~Qt_focus()
{
    delete ui;
}

void Qt_focus::toggleTheme()
{
    // 在 5 套主题间依次轮转 (0 -> 1 -> 2 -> 3 -> 4 -> 0)
    int nextMode = (static_cast<int>(m_currentTheme) + 1) % 5;
    applyTheme(static_cast<stylesheet_QT::ThemeMode>(nextMode));
}

void Qt_focus::applyTheme(stylesheet_QT::ThemeMode mode)
{
    m_currentTheme = mode;
    m_style.setTheme(mode);

    // 1. 全局背景与边框
    this->setStyleSheet(m_style.widget_uicenter);
    ui->centralWidget->setStyleSheet(m_style.widget_uicenter);
    m_widgetUpper->setStyleSheet(m_style.widget_upper);
    ui->statusBar->setStyleSheet(m_style.widget_statusbar);
    m_labelTitle->setStyleSheet(m_style.label_title);

    m_btnMax->setStyleSheet(m_style.button_style_max);
    m_btnMin->setStyleSheet(m_style.button_style_min);
    m_btnClose->setStyleSheet(m_style.button_style_close);

    m_tabWidgetMain->setStyleSheet(m_style.Tab_widget);

    // 2. 矢量图标自动重绘为主色（紫色主题变深紫、蓝色变深蓝、草甸变森林绿）
    const QColor themeBrandColor = QColor(m_style.colors().brandPrimary);
    m_tabWidgetMain->setTabIcon(0, createFontIcon(FontAwesomeIcons::IconIdentity::icon_home, themeBrandColor));
    m_tabWidgetMain->setTabIcon(1, createFontIcon(FontAwesomeIcons::IconIdentity::icon_time, themeBrandColor));
    m_tabWidgetMain->setTabIcon(2, createFontIcon(FontAwesomeIcons::IconIdentity::icon_tasks, themeBrandColor));
    m_tabWidgetMain->setTabIcon(3, createFontIcon(FontAwesomeIcons::IconIdentity::icon_external_link, themeBrandColor));

    for (auto* dot : m_tabLabels) {
        if (dot) dot->setStyleSheet(m_style.label_tab);
    }

    // 3. 专注倒计时刷新
    if (m_labelTime) {
        updateCountdown();
    }
    if (m_progressBar) m_progressBar->setStyleSheet(m_style.style_bar);
    if (m_btnSetFocus) m_btnSetFocus->setStyleSheet(m_style.button_style_0);
    if (m_btnFocusReset) m_btnFocusReset->setStyleSheet(m_style.button_style_0);
    if (m_btnFocusPause) m_btnFocusPause->setStyleSheet(m_style.button_style_0);

    // 4. 任务清单
    if (m_labelTaskTitle) m_labelTaskTitle->setStyleSheet(m_style.label_main2);
    if (m_textEditTasks) m_textEditTasks->setStyleSheet(m_style.task_test);
    if (m_btnAddTask) m_btnAddTask->setStyleSheet(m_style.button_style_0);
    if (m_btnClearTask) m_btnClearTask->setStyleSheet(m_style.button_style_0);

    // 5. 启动台
    if (m_labelLinkTitle) m_labelLinkTitle->setStyleSheet(m_style.label_main2);
    if (m_btnLink1) m_btnLink1->setStyleSheet(m_style.button_style_0);
    if (m_btnLink2) m_btnLink2->setStyleSheet(m_style.button_style_0);
    if (m_btnSearch) m_btnSearch->setStyleSheet(m_style.button_style_0);

    // 状态栏提示当前生效的主题名
    ui->statusBar->showMessage(QString("已应用主题: %1").arg(stylesheet_QT::getThemeName(mode)), 2500);
}

void Qt_focus::startLabelTime()
{
    m_remainingTime = m_focusTime;
    m_progressValue = m_remainingTime;
    m_progressBar->show();
    m_timerCountdown->start(1000);
    updateCountdown();
}

void Qt_focus::updateCountdown()
{
    if (m_remainingTime >= 0) {
        int hours = m_remainingTime / 3600;
        int minutes = (m_remainingTime % 3600) / 60;
        int seconds = m_remainingTime % 60;

        QString timeString;
        if (hours > 0) {
            timeString = QString("%1:%2:%3")
                .arg(hours, 2, 10, QChar('0'))
                .arg(minutes, 2, 10, QChar('0'))
                .arg(seconds, 2, 10, QChar('0'));
        }
        else {
            timeString = QString("%1:%2")
                .arg(minutes, 2, 10, QChar('0'))
                .arg(seconds, 2, 10, QChar('0'));
        }
        m_labelTime->setText(timeString);

        // ==================== 显著字号控制 ====================
        // 窗口缩放适配因子（防止在小窗口下拉伸溢出）
        float windowScale = static_cast<float>(m_widgetPage0->width()) / static_cast<float>(qMax(1, m_initialSize.width()));
        windowScale = qBound(0.85f, windowScale, 1.35f);

        int activeFontSize = 52; // 默认准备状态下的字号
        QString textColor;

        if (m_isFocusStart) {
            // 【核心优化】：只要开始倒计时，立即切换为极度醒目的 110px 巨幅字号！
            activeFontSize = static_cast<int>(110 * windowScale);

            if (m_isFocusPause) {
                textColor = "#e09f3e"; // 暂停状态：温暖琥珀色提醒
            }
            else {
                textColor = (m_currentTheme == stylesheet_QT::ThemeMode::LightSage) ? "#1a2e1d" : "#38bdf8";
            }
        }
        else {
            // 未开始/准备状态：保持内敛舒服的 52px 预览字号
            activeFontSize = static_cast<int>(52 * windowScale);
            textColor = (m_currentTheme == stylesheet_QT::ThemeMode::LightSage) ? "#52796f" : "#94a3b8";
        }

        // 应用高对比度、紧凑字距（letter-spacing）的现代大屏排版
        m_labelTime->setStyleSheet(QString(R"(
            QLabel {
                color: %1;
                font-size: %2px;
                font-weight: 800;
                letter-spacing: -3px;
                background: transparent;
                border: none;
            }
        )").arg(textColor).arg(activeFontSize));

        // 更新进度条
        if (m_progressValue > 0) {
            m_progressBar->setValue(((m_progressValue - m_remainingTime) * 100) / m_progressValue);
        }
        else {
            m_progressBar->setValue(0);
        }

        m_remainingTime--;
    }
    else {
        // 倒计时结束
        m_timerCountdown->stop();
        m_isFocusStart = false;
        m_labelTime->setText("FLOW COMPLETE");
        m_labelTime->setStyleSheet(QString(R"(
            QLabel {
                color: #52b788;
                font-size: 58px;
                font-weight: 800;
                letter-spacing: -1px;
            }
        )"));
        m_btnFocusReset->setText("开启新心流");
        m_btnFocusPause->setText("暂停");
        QApplication::beep();
    }
}

void Qt_focus::resetLabelTime()
{
    // 如果已经在倒计时中，点击重置则停止并恢复为准备状态
    if (m_isFocusStart) {
        m_timerCountdown->stop();
        m_isFocusStart = false;
        m_isFocusPause = false;
        m_btnFocusReset->setText("开启心流");
        m_btnFocusPause->setText("暂停计时");
        m_remainingTime = m_focusTime;
        m_progressBar->setValue(0);

        // 恢复为未开始时的正常字号
        int minutes = m_focusTime / 60;
        m_labelTime->setText(QString("%1:00").arg(minutes, 2, 10, QChar('0')));
        m_labelTime->setStyleSheet(R"(
            QLabel {
                color: #52796f;
                font-size: 52px;
                font-weight: 700;
                letter-spacing: -1px;
            }
        )");
        ui->statusBar->showMessage("已重置心流倒计时", 2000);
        return;
    }

    // 开启倒计时：状态置为 true，进入显著超大模式
    m_isFocusStart = true;
    m_isFocusPause = false;
    m_btnFocusReset->setText("重置心流");
    m_btnFocusPause->setText("暂停计时");
    startLabelTime();
}

void Qt_focus::pauseFocusTime()
{
    if (!m_isFocusStart) return;

    if (!m_isFocusPause) {
        m_timerCountdown->stop();
        m_isFocusPause = true;
        ui->statusBar->showMessage("心流计时已暂停");
        m_btnFocusPause->setText("继续计时");
    }
    else {
        m_timerCountdown->start(1000);
        m_isFocusPause = false;
        m_btnFocusPause->setText("暂停计时");
        ui->statusBar->showMessage("心流计时继续中...");
    }
    // 立即刷新文字与暂停样式
    updateCountdown();
}

void Qt_focus::setLabelTime()
{
    if (m_isWidgetSetTimeShow) {
        if (!m_widgetSetTime) {
            m_widgetSetTime = new QWidget(this, Qt::Window);
            m_widgetSetTime->setWindowIcon(createFontIcon(FontAwesomeIcons::IconIdentity::icon_time, QColor("#344e41")));
            m_widgetSetTime->setStyleSheet(m_style.widget_uicenter);
            m_widgetSetTime->setMinimumSize(360, 240);

            QGridLayout* layout = new QGridLayout(m_widgetSetTime);

            QLabel* lblPrompt = new QLabel("专注时长设置:", m_widgetSetTime);
            lblPrompt->setStyleSheet(m_style.label_main2);

            QSpinBox* spinBox = new QSpinBox(m_widgetSetTime);
            spinBox->setRange(1, 300);
            spinBox->setValue(25);
            spinBox->setStyleSheet(m_style.style_spinbox);
            spinBox->setFixedSize(120, 36);

            QLabel* lblUnit = new QLabel("分钟", m_widgetSetTime);
            lblUnit->setStyleSheet(m_style.label_main2);

            QPushButton* btnStart = new QPushButton("确认并启动", m_widgetSetTime);
            btnStart->setFixedSize(140, 38);
            btnStart->setStyleSheet(m_style.button_style_0);

            layout->addWidget(lblPrompt, 0, 0, Qt::AlignCenter);
            layout->addWidget(spinBox, 0, 1, Qt::AlignCenter);
            layout->addWidget(lblUnit, 0, 2, Qt::AlignCenter);
            layout->addWidget(btnStart, 1, 0, 1, 3, Qt::AlignCenter);

            connect(btnStart, &QPushButton::clicked, this, [this]() {
                m_isFocusStart = false; // 确保触发重置放大逻辑
                resetLabelTime();
                });

            connect(spinBox, &QSpinBox::valueChanged, this, [this](int value) {
                m_focusTime = value * 60;
                m_remainingTime = m_focusTime;
                ui->statusBar->showMessage(QString("心流时长已设置为 %1 分钟").arg(value), 3000);

                // 调整设置时显示舒服的预览字号
                m_labelTime->setText(QString("%1:00").arg(value, 2, 10, QChar('0')));
                m_labelTime->setStyleSheet(R"(
                    QLabel {
                        color: #52796f;
                        font-size: 52px;
                        font-weight: 700;
                    }
                )");
                });
        }
        m_widgetSetTime->show();
    }
    else {
        if (m_widgetSetTime) m_widgetSetTime->hide();
    }
    m_isWidgetSetTimeShow = !m_isWidgetSetTimeShow;
}

QString Qt_focus::getSystemTime()
{
    return QDateTime::currentDateTime().toString("hh:mm:ss");
}

void Qt_focus::initMainPageRightMenu()
{
    m_rightClickMenu = new QMenu(this);

    // ==================== 多主题子菜单 ====================
    QMenu* menuTheme = m_rightClickMenu->addMenu("🎨 调色盘主题 (Theme Palette)");

    auto addThemeAction = [this, menuTheme](const QString& name, stylesheet_QT::ThemeMode mode) {
        QAction* act = menuTheme->addAction(name);
        connect(act, &QAction::triggered, this, [this, mode]() {
            applyTheme(mode);
            });
        };

    addThemeAction("🌿 清爽米绿 (Light Sage)", stylesheet_QT::ThemeMode::LightSage);
    addThemeAction("🪻 优雅薰衣草 (Lavender)", stylesheet_QT::ThemeMode::Lavender);
    addThemeAction("🌊 冰川静蓝 (Nordic Blue)", stylesheet_QT::ThemeMode::NordicBlue);
    addThemeAction("🌻 夏日草甸 (Summer Meadow)", stylesheet_QT::ThemeMode::SummerMeadow);
    addThemeAction("🌙 极客暗黑 (Dark Slate)", stylesheet_QT::ThemeMode::DarkSlate);

    m_rightClickMenu->addSeparator();

    // 其它窗口控制
    QAction* actToggleTabBar = m_rightClickMenu->addAction("隐藏/显示 导航栏");
    QAction* actRestoreSize = m_rightClickMenu->addAction("还原窗口黄金尺寸");
    QAction* actFocusMode = m_rightClickMenu->addAction("极简专注看板模式");
    m_rightClickMenu->addSeparator();

    QAction* actFontAwesome = m_rightClickMenu->addAction("FontAwesome 图标库");
    QAction* actUrlWindow = m_rightClickMenu->addAction("外部项目链接");
    QAction* actAbout = m_rightClickMenu->addAction("关于软件");

    connect(actToggleTabBar, &QAction::triggered, this, [this]() {
        m_tabWidgetMain->tabBar()->setVisible(!m_tabWidgetMain->tabBar()->isVisible());
        });

    connect(actRestoreSize, &QAction::triggered, this, [this]() {
        QScreen* screen = QGuiApplication::primaryScreen();
        if (screen) {
            QRect screenGeom = screen->geometry();
            int x = (screenGeom.width() - m_initialSize.width()) / 2;
            int y = (screenGeom.height() - m_initialSize.height()) / 2;
            move(x, y);
            resize(m_initialSize);
            showNormal();
        }
        });

    connect(actFocusMode, &QAction::triggered, this, [this]() {
        const QList<QWidget*> widgets = m_widgetPage0->findChildren<QWidget*>();
        for (QWidget* w : widgets) {
            if (w != m_labelTime) {
                w->setVisible(m_isLabelMainTextOnly);
            }
        }
        m_isLabelMainTextOnly = !m_isLabelMainTextOnly;
        });

    connect(actFontAwesome, &QAction::triggered, this, &Qt_focus::createFontAwesomeWindow);
    connect(actUrlWindow, &QAction::triggered, this, &Qt_focus::openLabelUrl);

    connect(actAbout, &QAction::triggered, this, [this]() {
        QMessageBox msgBox(this);
        msgBox.setStyleSheet(m_style.widget_uicenter);
        msgBox.setWindowTitle("关于本软件");

        QPushButton* btnInfo = msgBox.addButton("软件说明", QMessageBox::ActionRole);
        QPushButton* btnQt = msgBox.addButton("关于 Qt", QMessageBox::ActionRole);
        msgBox.addButton("关闭", QMessageBox::RejectRole);

        msgBox.exec();
        if (msgBox.clickedButton() == btnInfo) {
            QMessageBox::about(this, "软件说明",
                "名称: RAIN Focus Workstation\n架构: Bento Grid / Modern Flow\n支持 5 套精选调色盘无缝切换");
        }
        else if (msgBox.clickedButton() == btnQt) {
            QMessageBox::aboutQt(this, "关于 Qt");
        }
        });
}

void Qt_focus::initColorSelectRightMenu()
{
    m_colorMenu = new QMenu(this);
    QAction* actSelectColor = m_colorMenu->addAction("选择高亮强调色");

    connect(actSelectColor, &QAction::triggered, this, [this]() {
        const QColor color = QColorDialog::getColor(Qt::white, this, "选择颜色");
        if (color.isValid()) {
            ui->statusBar->showMessage(QString("当前色彩选定: %1").arg(color.name()), 2000);
        }
        });
}

void Qt_focus::contextMenuEvent(QContextMenuEvent* event)
{
    if (QApplication::keyboardModifiers() & Qt::ShiftModifier) {
        if (!m_colorMenu) initColorSelectRightMenu();
        m_colorMenu->exec(QCursor::pos());
    }
    else {
        if (!m_rightClickMenu) initMainPageRightMenu();
        m_rightClickMenu->exec(event->globalPos());
    }
}

void Qt_focus::maximizeRestore()
{
    if (m_globalState == 0) {
        showMaximized();
        m_globalState = 1;
        m_btnMax->setToolTip("Restore");
        ui->statusBar->showMessage("窗口已最大化", 1000);
    }
    else {
        showNormal();
        m_globalState = 0;
        m_btnMax->setToolTip("Maximize");
        ui->statusBar->showMessage("窗口已恢复黄金尺寸", 1000);
    }
}

void Qt_focus::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_globalState == 0) {
        m_dragStartPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_isDragging = true;
    }
}

void Qt_focus::mouseMoveEvent(QMouseEvent* event)
{
    if (m_isDragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragStartPosition);
    }
}

void Qt_focus::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_isDragging = false;
    }
}

void Qt_focus::widgetCustomMove(int x, int y)
{
    QMainWindow::move(x, y);
}

void Qt_focus::keyPressEvent(QKeyEvent* event)
{
    m_pressedKeys.insert(event->key());
    if (m_pressedKeys.contains(Qt::Key_Q) && m_pressedKeys.contains(Qt::Key_A)) {
        toggleTheme();
    }
    QMainWindow::keyPressEvent(event);
}

void Qt_focus::keyReleaseEvent(QKeyEvent* event)
{
    m_pressedKeys.remove(event->key());
    QMainWindow::keyReleaseEvent(event);
}

bool Qt_focus::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == m_widgetUpper || obj == ui->statusBar || obj == m_labelTime) {
        if (event->type() == QEvent::MouseButtonDblClick) {
            maximizeRestore();
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void Qt_focus::closeEvent(QCloseEvent* event)
{
    auto reply = QMessageBox::question(this, "退出提示", "确定要退出 Focus 工作台吗？",
        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        event->accept();
    }
    else {
        event->ignore();
    }
}

QString Qt_focus::getRandomColor()
{
    auto gen = QRandomGenerator::global();
    return QString("rgb(%1, %2, %3)")
        .arg(gen->bounded(120, 256))
        .arg(gen->bounded(120, 256))
        .arg(gen->bounded(120, 256));
}

void Qt_focus::createFontAwesomeWindow()
{
    FontAwesomeIcons& fontIcon = FontAwesomeIcons::Instance();
    const QString faFamily = fontIcon.getFont().family();

    QWidget* win = new QWidget(nullptr);
    win->setAttribute(Qt::WA_DeleteOnClose);
    win->setStyleSheet(m_style.widget_uicenter);
    win->setMinimumSize(500, 180);

    QHBoxLayout* layout = new QHBoxLayout(win);
    layout->setSpacing(20);

    auto addBtn = [&](FontAwesomeIcons::IconIdentity id, const QString& tip) {
        QPushButton* btn = new QPushButton(win);
        btn->setStyleSheet(QString(R"(
            QPushButton {
                font-family: "%1";
                font-size: 20px;
                color: #344e41;
                background-color: #ffffff;
                border: 1px solid #d8e3d3;
                border-radius: 8px;
            }
            QPushButton:hover {
                background-color: #344e41;
                color: #ffffff;
            }
        )").arg(faFamily));
        btn->setText(QString(fontIcon.getIconChar(id)));
        btn->setToolTip(tip);
        btn->setFixedSize(90, 48);
        layout->addWidget(btn);
        };

    addBtn(FontAwesomeIcons::IconIdentity::icon_user, "用户看板");
    addBtn(FontAwesomeIcons::IconIdentity::icon_gear, "偏好设置");
    addBtn(FontAwesomeIcons::IconIdentity::icon_internet_explorer, "网络资源");

    win->show();
}

void Qt_focus::openLabelUrl()
{
    QWidget* win = new QWidget(nullptr);
    win->setAttribute(Qt::WA_DeleteOnClose);
    win->setMinimumSize(480, 260);
    win->setStyleSheet(m_style.widget_uicenter);

    QVBoxLayout* layout = new QVBoxLayout(win);
    layout->setContentsMargins(20, 20, 20, 20);

    QLabel* label = new QLabel("<a href='https://github.com/XiaoYu-1111/Qt_focus' style='color:#588157;'>About Focus Repository</a>", win);
    label->setAlignment(Qt::AlignCenter);
    label->setOpenExternalLinks(true);
    layout->addWidget(label);

    QStatusBar* subStatusBar = new QStatusBar(win);
    subStatusBar->setStyleSheet(m_style.widget_statusbar);
    subStatusBar->showMessage("Ready");
    layout->addWidget(subStatusBar);

    win->show();
}