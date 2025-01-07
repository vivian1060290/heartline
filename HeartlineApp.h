#ifndef HEARTLINEAPP_H
#define HEARTLINEAPP_H

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
#include <QPainter>
#include <QPaintEvent>
#include <QStackedWidget>
#include <QVector>
#include <QPointF>

class ChartWidget : public QWidget {
    Q_OBJECT

public:
    explicit ChartWidget(QWidget *parent = nullptr, const QVector<QPointF> &data = {});

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<QPointF> chartData;
};

class HeartlineApp : public QMainWindow {
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
    QPushButton *forgotPasswordButton;
    QString currentUsername;
    QStackedWidget *stackedWidget;
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
    QWidget *settingsWidget;
    void applyDarkMode(bool enabled);
    // *** Private Methods ***
    // UI setup methods
    void setupLoginUI();
    void setupUI();
    void setupSettingsUI();
    void setupChartUI();
    void setupLineChartUI(); // 新增聲明
    void setupPieChartUI(); // 新增聲明
    // Login-related methods
    void handleLogin();
    void handleRegister();
    void handleForgotPassword();
    void resetUserPassword(const QString &username, const QString &newPassword);
    bool validatePassword(const QString &username, const QString &password);
    void handleSettings();
    // Main functionality
    void saveDiary();
    void exportData();
    void toggleDarkMode(bool enabled);
    void addRowToTable(const QString &date, const QString &emotion, const QString &diaryContent);
    // Settings-related methods
    void handleEditUserInfo();
    void handleChangePassword();
    void handleChangeBackgroundColor();
    void handleClearData();
    void handleAccountManagement();
    void handleLogout();
    void handleDeleteAccount();
    void handleEditEmail();
};

#endif // HEARTLINEAPP_H
