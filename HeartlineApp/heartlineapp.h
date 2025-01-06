#ifndef HEARTLINEAPP_H
#define HEARTLINEAPP_H
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QColorDialog>

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QSlider>
#include <QLabel>
#include <QDateEdit>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDialog>
#include <QColorDialog>
#include <QDir>
#include <QTableWidget>
class HeartlineApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit HeartlineApp(QWidget *parent = nullptr);

private:
    // *** UI Components ***
    // Login screen components
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QPushButton *forgotPasswordButton; // 新增的“忘記密碼”按鈕
    QString currentUsername;
    QStackedWidget *stackedWidget; // 堆疊視窗，用於頁面切換
    QWidget *settingsPage;
    // Main screen components
    QTextEdit *diaryInput;
    QSlider *emotionSlider;
    QLabel *emotionLabel;
    QDateEdit *dateEdit;
    QPushButton *saveButton;
    QPushButton *settingsButton;
    QPushButton *exportButton;
    QCheckBox *darkModeCheckBox;
    QVBoxLayout *mainLayout;
    QWidget *mainWidget;
    QTableWidget *diaryTableWidget;
    // Settings screen components
    QWidget *settingsWidget; // 設定介面主控件
    void applyDarkMode(bool enabled);
    // *** Private Methods ***
    // UI setup methods
    void setupLoginUI(); // 初始化登入畫面
    void setupUI(); // 初始化主畫面
    void setupSettingsUI(); // 初始化設定畫面
QWidget *loginWidget;
    // Login-related methods
    void handleLogin(); // 處理登入邏輯
    void handleRegister(); // 處理註冊邏輯
    void handleForgotPassword(); // 處理“忘記密碼”的邏輯
    void resetUserPassword(const QString &username, const QString &newPassword); // 重設密碼
    bool validatePassword(const QString &username, const QString &password); // 驗證密碼
    void handleSettings();
    // Main functionality
    //void handleEditUserInfo();
    void saveDiary(); // 儲存日記
    void exportData(); // 匯出數據
    void toggleDarkMode(bool enabled); // 切換深色模式
    void addRowToTable(const QString &date, const QString &emotion, const QString &diaryContent);
    // Settings-related methods
    void handleEditUserInfo(); // 修改使用者資料
    void handleChangePassword(); // 修改密碼
    void handleChangeBackgroundColor(); // 修改背景顏色
    void handleClearData(); // 清理所有日記與數據
    void handleAccountManagement(); // 處理帳號管理
    void handleLogout(); // 登出功能
    void handleDeleteAccount();
    void handleEditEmail();

};

#endif // HEARTLINEAPP_H

