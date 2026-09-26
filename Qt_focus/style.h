#pragma once
#include <QString>

// ==================== 1. 设计令牌 (Design Tokens) ====================
struct ThemeColors {
    QString bgApp;          // 应用主背景色
    QString bgCard;         // 卡片容器背景色
    QString bgCardHover;    // 卡片悬停色
    QString bgHeader;       // 顶部/边框背景色
    QString borderSubtle;   // 极细边框线颜色
    QString borderFocus;    // 聚焦/高亮边框线颜色

    QString textPrimary;    // 主标题文字
    QString textSecondary;  // 副标题/说明文字
    QString textMuted;      // 弱化占位文字

    QString brandPrimary;   // 品牌主色 (用于主按钮、核心图标、时钟等)
    QString brandAccent;    // 点缀/副高亮色
    QString brandText;      // 按钮文字色

    QString statusSuccess;  // 成功色
    QString statusWarning;  // 警告色
    QString statusDanger;   // 危险色
};

// ==================== 2. 现代样式管理类 ====================
class stylesheet_QT {
public:
    enum class ThemeMode {
        LightSage,     // 🌿 清爽米绿 (Light Sage)
        Lavender,      // 🪻 优雅薰衣草 (Lavender)
        NordicBlue,    // 🌊 冰川静蓝 (Nordic Blue)
        SummerMeadow,  // 🌻 夏日草甸 (Summer Meadow)
        DarkSlate      // 🌙 极客暗黑 (Dark Slate)
    };

    explicit stylesheet_QT(ThemeMode mode = ThemeMode::LightSage) {
        setTheme(mode);
    }

    const ThemeColors& colors() const { return m_c; }

    static QString getThemeName(ThemeMode mode) {
        switch (mode) {
        case ThemeMode::LightSage:    return "清爽米绿 (Light Sage)";
        case ThemeMode::Lavender:     return "优雅薰衣草 (Lavender)";
        case ThemeMode::NordicBlue:   return "冰川静蓝 (Nordic Blue)";
        case ThemeMode::SummerMeadow: return "夏日草甸 (Summer Meadow)";
        case ThemeMode::DarkSlate:    return "极客暗黑 (Dark Slate)";
        default:                      return "默认主题";
        }
    }

    void setTheme(ThemeMode mode) {
        switch (mode) {
        case ThemeMode::LightSage:
            // 🌿 护眼淡绿背景 + 森林绿胶囊
            m_c = {
                "#eef3eb", "#ffffff", "#f7faf5", "#e5ede2", "#d8e3d3", "#3a5a40",
                "#1a2e1d", "#52796f", "#84a98c",
                "#344e41", "#588157", "#ffffff",
                "#52b788", "#e09f3e", "#d90429"
            };
            break;

        case ThemeMode::Lavender:
            // 🪻 图1：莫兰迪薰衣草紫调 (灰白底 + 柔和紫)
            m_c = {
                "#f5f3f8", "#ffffff", "#faf8fc", "#ece7f2", "#dfd5ea", "#6b3ba7",
                "#2a183d", "#6e5d80", "#9f90b3",
                "#6b3ba7", "#9568af", "#ffffff",
                "#48bb78", "#e09f3e", "#d90429"
            };
            break;

        case ThemeMode::NordicBlue:
            // 🌊 图2：冰川微冷蓝调 (淡冷灰蓝底 + 海洋深蓝)
            m_c = {
                "#edf4f8", "#ffffff", "#f5f9fc", "#e1edf5", "#cde1ee", "#026896",
                "#0e2938", "#476b80", "#7f9fb3",
                "#026896", "#38a3d8", "#ffffff",
                "#38b2ac", "#dd6b20", "#e53e3e"
            };
            break;

        case ThemeMode::SummerMeadow:
            // 🌻 图3：夏日草甸 (奶白暖米色 + 暖阳橙 + 森林叶绿)
            m_c = {
                "#faf7ee", "#ffffff", "#fdfcf7", "#f3edd8", "#e8dfc5", "#467a57",
                "#2a241b", "#695f51", "#9e9383",
                "#467a57", "#f28e00", "#ffffff",
                "#467a57", "#f28e00", "#c0392b"
            };
            break;

        case ThemeMode::DarkSlate:
        default:
            // 🌙 极客深色风格
            m_c = {
                "#0f172a", "#1e293b", "#334155", "#111827", "#334155", "#38bdf8",
                "#f8fafc", "#94a3b8", "#64748b",
                "#38bdf8", "#0284c7", "#0f172a",
                "#34d399", "#fbbf24", "#f87171"
            };
            break;
        }
        buildStylesheets();
    }

    // ==================== 暴露的 QSS 属性 ====================
    QString widget_uicenter;
    QString widget_gray1;
    QString widget_upper;
    QString widget_statusbar;

    QString label_title;
    QString label_main;
    QString label_main2;
    QString label_tab;
    QString label_dot;
    QString label_fontawesome;

    QString button_style_0;
    QString button_style_max;
    QString button_style_min;
    QString button_style_close;
    QString button_fontawesome;

    QString Tab_widget;
    QString task_test;
    QString style_spinbox;
    QString style_bar;
    QString sliderStyle;

private:
    ThemeColors m_c;

    void buildStylesheets() {
        // 主背景
        widget_uicenter = QString(R"(
            QWidget {
                background-color: %1;
                color: %2;
                font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", "PingFang SC", "Microsoft YaHei", sans-serif;
            }
        )").arg(m_c.bgApp, m_c.textPrimary);

        // 卡片级容器背景
        widget_gray1 = QString(R"(
            QWidget {
                background-color: %1;
                border: 1px solid %2;
                border-radius: 14px;
                color: %3;
            }
        )").arg(m_c.bgCard, m_c.borderSubtle, m_c.textPrimary);

        // 顶部操作区
        widget_upper = QString(R"(
            QWidget {
                background-color: %1;
                border-bottom: 1px solid %2;
            }
        )").arg(m_c.bgHeader, m_c.borderSubtle);

        // 状态栏
        widget_statusbar = QString(R"(
            QStatusBar {
                background-color: %1;
                color: %2;
                font-size: 12px;
                border-top: 1px solid %3;
                padding-left: 10px;
            }
            QStatusBar::item { border: none; }
        )").arg(m_c.bgCard, m_c.textSecondary, m_c.borderSubtle);

        // 标题与文字
        label_title = QString(R"(
            QLabel {
                color: %1;
                font-size: 13px;
                font-weight: 700;
                letter-spacing: 0.5px;
            }
        )").arg(m_c.brandPrimary);

        label_main = QString(R"(
            QLabel {
                color: %1;
                font-weight: 800;
                letter-spacing: -2px;
            }
        )").arg(m_c.brandPrimary);

        label_main2 = QString(R"(
            QLabel {
                color: %1;
                font-size: 16px;
                font-weight: 700;
            }
        )").arg(m_c.brandPrimary);

        // 现代化主按钮
        button_style_0 = QString(R"(
            QPushButton {
                background-color: %1;
                color: %2;
                font-size: 13px;
                font-weight: 600;
                border: 1px solid transparent;
                border-radius: 8px;
                padding: 6px 14px;
            }
            QPushButton:hover {
                background-color: %3;
            }
            QPushButton:pressed {
                padding-top: 7px;
                padding-left: 15px;
            }
        )").arg(m_c.brandPrimary, m_c.brandText, m_c.brandAccent);

        // 交通灯控制按钮
       // 彻底解决裁切问题：border: none; padding: 0px; margin: 0px; 配合 14px 纯圆
        button_style_close = "QPushButton { background-color: #ef4444; border: none; border-radius: 7px; padding: 0px; margin: 0px; } QPushButton:hover { background-color: #dc2626; }";
        button_style_min = "QPushButton { background-color: #f59e0b; border: none; border-radius: 7px; padding: 0px; margin: 0px; } QPushButton:hover { background-color: #d97706; }";
        button_style_max = "QPushButton { background-color: #10b981; border: none; border-radius: 7px; padding: 0px; margin: 0px; } QPushButton:hover { background-color: #059669; }";
        // Tab 导航栏
        Tab_widget = QString(R"(
            QTabWidget::pane {
                border: none;
                background: transparent;
            }
            QTabBar {
                background-color: transparent;
                qproperty-drawBase: 0;
            }
            QTabBar::tab {
                background-color: transparent;
                color: %1;
                font-size: 13px;
                font-weight: 600;
                padding: 8px 18px;
                margin: 0px 8px 0px 0px; /* 只向右侧增加间距，左侧不悬空缩进 */
                border-radius: 10px;
                border: 1px solid transparent;
            }
            QTabBar::tab:hover {
                background-color: %2;
                color: %3;
            }
            QTabBar::tab:selected {
                background-color: %4;
                color: %5;
                border: 1px solid %6;
            }
        )").arg(m_c.textSecondary, m_c.bgCardHover, m_c.textPrimary,
    m_c.bgCard, m_c.brandPrimary, m_c.borderSubtle);

        // 任务输入框
        task_test = QString(R"(
            QTextEdit {
                background-color: %1;
                color: %2;
                font-size: 14px;
                border: 1px solid %3;
                border-radius: 8px;
                padding: 8px 12px;
            }
            QTextEdit:focus {
                border: 1.5px solid %4;
                background-color: %5;
            }
        )").arg(m_c.bgCard, m_c.textPrimary, m_c.borderSubtle, m_c.borderFocus, m_c.bgApp);

        // 微调选择器
        style_spinbox = QString(R"(
            QSpinBox, QDoubleSpinBox {
                background-color: %1;
                color: %2;
                font-size: 14px;
                font-weight: 600;
                border: 1px solid %3;
                border-radius: 8px;
                padding: 4px 8px;
            }
            QSpinBox:focus, QDoubleSpinBox:focus {
                border: 1.5px solid %4;
            }
        )").arg(m_c.bgCard, m_c.textPrimary, m_c.borderSubtle, m_c.borderFocus);

        // 进度条
        style_bar = QString(R"(
            QProgressBar {
                background-color: %1;
                border: 1px solid %2;
                border-radius: 4px;
                height: 8px;
                text-align: center;
                color: transparent;
            }
            QProgressBar::chunk {
                background-color: %3;
                border-radius: 4px;
            }
        )").arg(m_c.bgCard, m_c.borderSubtle, m_c.brandPrimary);

        label_tab = QString(R"(
            QLabel { color: %1; font-size: 14px; }
            QLabel:hover { color: %2; }
        )").arg(m_c.textMuted, m_c.brandPrimary);

        label_dot = QString(R"(QLabel { color: %1; font-size: 32px; font-weight: bold; })").arg(m_c.brandAccent);
        label_fontawesome = QString(R"(QLabel { color: %1; font-size: 18px; } QLabel:hover { color: %2; })").arg(m_c.textSecondary, m_c.brandPrimary);
        button_fontawesome = QString(R"(
            QPushButton { background-color: %1; color: %2; border: 1px solid %3; border-radius: 8px; }
            QPushButton:hover { background-color: %4; color: %5; }
        )").arg(m_c.bgCard, m_c.textPrimary, m_c.borderSubtle, m_c.brandPrimary, m_c.brandText);
    }
};