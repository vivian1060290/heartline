#include "HeartlineApp.h"
#include <QApplication>
#include <QHBoxLayout>

HeartlineApp::HeartlineApp(QWidget *parent)
    : QMainWindow(parent)
{
    setupLoginUI();
}

void HeartlineApp::setupLoginUI()
{
    // 標題
    QLabel *loginLabel = new QLabel("Login to Heartline App", this);
    loginLabel->setAlignment(Qt::AlignCenter);

    // 使用者名稱輸入框
    usernameInput = new QLineEdit(this);
    usernameInput->setPlaceholderText("Username");

    // 密碼輸入框
    passwordInput = new QLineEdit(this);
    passwordInput->setPlaceholderText("Password");
    passwordInput->setEchoMode(QLineEdit::Password);

    // 功能按鈕
    QPushButton *loginButton = new QPushButton("Login", this);
    QPushButton *registerButton = new QPushButton("Register", this);
    QPushButton *forgotPasswordButton = new QPushButton("Forgot Password?", this);

    // 版面配置
    QVBoxLayout *loginLayout = new QVBoxLayout;
    loginLayout->addWidget(loginLabel);
    loginLayout->addWidget(usernameInput);
    loginLayout->addWidget(passwordInput);
    loginLayout->addWidget(loginButton);
    loginLayout->addWidget(registerButton);
    loginLayout->addWidget(forgotPasswordButton);

    QWidget *loginWidget = new QWidget(this);
    loginWidget->setLayout(loginLayout);
    setCentralWidget(loginWidget);

    // 連接功能按鈕至對應的處理方法
    connect(loginButton, &QPushButton::clicked, this, &HeartlineApp::handleLogin);
    connect(registerButton, &QPushButton::clicked, this, &HeartlineApp::handleRegister);
    connect(forgotPasswordButton, &QPushButton::clicked, this, &HeartlineApp::handleForgotPassword);

}

void HeartlineApp::handleLogin()
{
    QString username = usernameInput->text();
    QString password = passwordInput->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Error", "Username and password cannot be empty.");
        return;
    }

    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to access user data.");
        return;
    }

    QTextStream in(&file);
    bool loginSuccess = false;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");

        if (parts.size() >= 2 && parts[0] == username && parts[1] == password) {
            loginSuccess = true;
            break;
        }
    }

    file.close();

    if (loginSuccess) {
        currentUsername = username;
        setupUI(); // 進入主畫面
    } else {
        QMessageBox::warning(this, "Login Error", "Invalid username or password.");
    }
}


void HeartlineApp::handleRegister()
{
    QDialog registerDialog(this);
    registerDialog.setWindowTitle("Register New Account");

    QLineEdit *newUsernameInput = new QLineEdit(&registerDialog);
    newUsernameInput->setPlaceholderText("New Username");

    QLineEdit *newPasswordInput = new QLineEdit(&registerDialog);
    newPasswordInput->setPlaceholderText("New Password");
    newPasswordInput->setEchoMode(QLineEdit::Password);

    QLineEdit *emailInput = new QLineEdit(&registerDialog);
    emailInput->setPlaceholderText("Email Address");

    QPushButton *submitRegisterButton = new QPushButton("Register", &registerDialog);

    QVBoxLayout *registerLayout = new QVBoxLayout;
    registerLayout->addWidget(new QLabel("Register a new account"));
    registerLayout->addWidget(newUsernameInput);
    registerLayout->addWidget(newPasswordInput);
    registerLayout->addWidget(emailInput);
    registerLayout->addWidget(submitRegisterButton);

    registerDialog.setLayout(registerLayout);

    connect(submitRegisterButton, &QPushButton::clicked, &registerDialog, [&]() {
        QString newUsername = newUsernameInput->text();
        QString newPassword = newPasswordInput->text();
        QString email = emailInput->text();

        if (newUsername.isEmpty() || newPassword.isEmpty() || email.isEmpty()) {
            QMessageBox::warning(&registerDialog, "Error", "Username, password, and email cannot be empty.");
            return;
        }

        // 檢查用戶名是否已經存在
        QFile file("users.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::critical(&registerDialog, "Error", "Failed to read user data.");
            return;
        }

        QTextStream in(&file);
        bool usernameExists = false;
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() >= 3 && parts[0] == newUsername) {
                usernameExists = true;
                break;
            }
        }
        file.close();

        if (usernameExists) {
            QMessageBox::warning(&registerDialog, "Error", "Username already exists. Please choose another one.");
        } else {
            // 將新用戶信息寫入文件
            if (!file.open(QIODevice::Append | QIODevice::Text)) {
                QMessageBox::critical(&registerDialog, "Error", "Failed to save user data.");
                return;
            }

            QTextStream out(&file);
            out << newUsername << "," << newPassword << "," << email << "\n";
            file.close();

            QMessageBox::information(&registerDialog, "Success", "Registration successful!");
            registerDialog.accept();
        }
    });

    registerDialog.exec();
}

void HeartlineApp::setupSettingsUI()
{
    QDialog settingsDialog(this);
    settingsDialog.setWindowTitle("Settings");

    // 修改密碼按鈕
    QPushButton *changePasswordButton = new QPushButton("Change Password", &settingsDialog);

    // 切換深色模式按鈕
    QCheckBox *darkModeCheckBox = new QCheckBox("Enable Dark Mode", &settingsDialog);
    //darkModeCheckBox->setChecked(this->darkModeEnabled);

    // 修改 Email 按鈕
    QPushButton *editUserInfoButton = new QPushButton("Edit User Info", &settingsDialog);

    // 返回主畫面按鈕
    QPushButton *returnButton = new QPushButton("Return to Main Screen", &settingsDialog);

    // 更改背景顏色按鈕
    QPushButton *changeBackgroundColorButton = new QPushButton("Change Background Color", &settingsDialog);

    // 清除數據按鈕
    QPushButton *clearDataButton = new QPushButton("Clear All Data", &settingsDialog);

    // 刪除帳號按鈕
    QPushButton *deleteAccountButton = new QPushButton("Delete Account", &settingsDialog);

    // 設定介面佈局
    QVBoxLayout *settingsLayout = new QVBoxLayout;
    settingsLayout->addWidget(changePasswordButton);
    settingsLayout->addWidget(darkModeCheckBox);
    settingsLayout->addWidget(editUserInfoButton);
    settingsLayout->addWidget(changeBackgroundColorButton);
    settingsLayout->addWidget(clearDataButton);
    settingsLayout->addWidget(deleteAccountButton);
    settingsLayout->addWidget(returnButton);

    settingsDialog.setLayout(settingsLayout);

    // 按鈕功能連接
    connect(changePasswordButton, &QPushButton::clicked, this, &HeartlineApp::handleChangePassword);
    connect(darkModeCheckBox, &QCheckBox::toggled, this, &HeartlineApp::toggleDarkMode);
    connect(editUserInfoButton, &QPushButton::clicked, this, &HeartlineApp::handleEditUserInfo);
    connect(changeBackgroundColorButton, &QPushButton::clicked, this, &HeartlineApp::handleChangeBackgroundColor);
    connect(clearDataButton, &QPushButton::clicked, this, &HeartlineApp::handleClearData);
    connect(deleteAccountButton, &QPushButton::clicked, this, &HeartlineApp::handleDeleteAccount);
    connect(returnButton, &QPushButton::clicked, &settingsDialog, &QDialog::accept);

    // 顯示設定視窗
    settingsDialog.exec();
}

void HeartlineApp::handleDeleteAccount()
{
    // 確認是否執行刪除
    int result = QMessageBox::warning(
        this, "Delete Account",
        "Are you sure you want to delete your account? This action cannot be undone.",
        QMessageBox::Yes | QMessageBox::No);

    if (result == QMessageBox::No)
        return;

    // 獲取當前使用者名稱
    QString username = currentUsername;

    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to access user data.");
        return;
    }

    // 遍歷資料並刪除相應的帳號
    QTextStream in(&file);
    QString updatedData;
    bool accountDeleted = false;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");

        if (parts.size() >= 2 && parts[0] == username) {
            accountDeleted = true; // 找到帳號並刪除
            continue;
        }

        updatedData += line + "\n";
    }

    file.close();

    if (!accountDeleted) {
        QMessageBox::warning(this, "Error", "Account not found or already deleted.");
        return;
    }

    // 將更新後的資料寫回檔案
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to update user data.");
        return;
    }

    QTextStream out(&file);
    out << updatedData;
    file.close();

    QMessageBox::information(this, "Account Deleted", "Your account has been deleted.");

    // 重置當前使用者資訊並返回登入畫面
    currentUsername.clear();
    setupLoginUI();
}


void HeartlineApp::setupUI()
{
    diaryInput = new QTextEdit(this);
    diaryInput->setPlaceholderText("Write your diary here...");

    emotionSlider = new QSlider(Qt::Horizontal, this);
    emotionSlider->setRange(1, 10);
    emotionLabel = new QLabel("Emotion Score: 1", this);

    dateEdit = new QDateEdit(QDate::currentDate(), this);
    dateEdit->setCalendarPopup(true);

    saveButton = new QPushButton("Save Diary", this);
    exportButton = new QPushButton("Open Data File", this);
    darkModeCheckBox = new QCheckBox("Enable Dark Mode", this);
    QPushButton *logoutButton = new QPushButton("Logout", this); // 登出按鈕
    QPushButton *settingsButton = new QPushButton("Settings", this); // 設定按鈕

    // 情感分數滑桿更新標籤
    connect(emotionSlider, &QSlider::valueChanged, this, [this](int value) {
        emotionLabel->setText(QString("Emotion Score: %1").arg(value));
    });

    // 按鈕功能
    connect(saveButton, &QPushButton::clicked, this, &HeartlineApp::saveDiary);
    connect(exportButton, &QPushButton::clicked, this, &HeartlineApp::exportData);
    connect(darkModeCheckBox, &QCheckBox::toggled, this, &HeartlineApp::toggleDarkMode);
    connect(logoutButton, &QPushButton::clicked, this, &HeartlineApp::handleLogout); // 登出功能
    connect(settingsButton, &QPushButton::clicked, this, [this]() {
        setupSettingsUI(); // 切換到設定頁面
    });

    // 主畫面佈局
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel("Date:"));
    mainLayout->addWidget(dateEdit);
    mainLayout->addWidget(new QLabel("Diary:"));
    mainLayout->addWidget(diaryInput);
    mainLayout->addWidget(emotionLabel);
    mainLayout->addWidget(emotionSlider);
    mainLayout->addWidget(saveButton);
    mainLayout->addWidget(exportButton);
    mainLayout->addWidget(darkModeCheckBox);
    mainLayout->addWidget(settingsButton); // 新增設定按鈕
    mainLayout->addWidget(logoutButton); // 加入登出按鈕

    mainWidget = new QWidget(this);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    setWindowTitle("Heartline App");
    resize(400, 600);
}

void HeartlineApp::handleLogout()
{
    // 清除當前登入狀態
    currentUsername.clear();

    // 返回登入畫面
    setupLoginUI();

    // 提示用戶
    QMessageBox::information(this, "Logout", "You have been logged out successfully.");
}
void HeartlineApp::handleEditUserInfo()
{
    QString newEmail = QInputDialog::getText(this, "Edit Email", "Enter your new email:");
    if (newEmail.isEmpty()) {
        QMessageBox::warning(this, "Edit Email", "Email cannot be empty.");
        return;
    }

    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to access user data.");
        return;
    }

    QTextStream in(&file);
    QStringList lines;
    bool emailUpdated = false;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() >= 3 && parts[0] == currentUsername) { // 匹配當前用戶
            emailUpdated = true;
            lines.append(QString("%1,%2,%3").arg(parts[0], parts[1], newEmail)); // 更新信箱
        } else {
            lines.append(line);
        }
    }
    file.close();

    if (!emailUpdated) {
        QMessageBox::warning(this, "Edit Email", "Failed to update email.");
        return;
    }

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const QString &line : lines) {
            out << line << "\n";
        }
        file.close();

        QMessageBox::information(this, "Edit Email", "Email updated successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to update user data.");
    }
}



void HeartlineApp::handleChangePassword()
{
    bool ok;
    QString newPassword = QInputDialog::getText(this, "Change Password",
                                                "Enter new password:", QLineEdit::Password,
                                                "", &ok);
    if (ok && !newPassword.isEmpty()) {
        // 假設使用者資訊儲存在 users.txt，格式為: username,password
        QFile file("users.txt");
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QTextStream in(&file);
            QString content;
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList parts = line.split(",");
                if (parts.size() >= 2 && parts[0] == currentUsername) {
                    content += currentUsername + "," + newPassword + "\n";
                } else {
                    content += line + "\n";
                }
            }
            file.resize(0); // 清空檔案內容
            QTextStream out(&file);
            out << content;
            file.close();

            QMessageBox::information(this, "Change Password", "Password updated successfully!");
        } else {
            QMessageBox::critical(this, "Error", "Failed to access user data.");
        }
    } else {
        QMessageBox::warning(this, "Change Password", "Password change was canceled.");
    }
}

void HeartlineApp::handleChangeBackgroundColor()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Select Background Color");
    if (color.isValid()) {
        QString style = QString("background-color: %1;").arg(color.name());
        mainWidget->setStyleSheet(style); // 套用顏色到主視窗
        QMessageBox::information(this, "Change Background Color", "Background color updated!");
    } else {
        QMessageBox::warning(this, "Change Background Color", "No color selected.");
    }
}

void HeartlineApp::handleClearData()
{
    int confirmation = QMessageBox::warning(this, "Confirm Data Deletion",
                                            "Are you sure you want to clear all diary entries and data? This action cannot be undone.",
                                            QMessageBox::Yes | QMessageBox::No);
    if (confirmation == QMessageBox::Yes) {
        QDir dir("diary/" + currentUsername);
        if (dir.exists()) {
            dir.removeRecursively();
        }
        QMessageBox::information(this, "Success", "All data has been cleared.");
    }
}

void HeartlineApp::saveDiary()
{
    if (currentUsername.isEmpty()) {
        QMessageBox::warning(this, "Error", "No user logged in.");
        return;
    }

    QDir userDir("diary/" + currentUsername);
    if (!userDir.exists()) {
        userDir.mkpath(".");
    }

    // 使用用戶選擇的日期
    QString selectedDate = dateEdit->date().toString("yyyy-MM-dd");
    QString fileName = selectedDate + ".csv";
    QString filePath = userDir.filePath(fileName);

    QString diary = diaryInput->toPlainText();
    int emotion = emotionSlider->value();

    if (diary.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Diary content cannot be empty!");
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to save the diary!");
        return;
    }

    QTextStream out(&file);
    // 若檔案是新建的，寫入標題
    if (file.size() == 0) {
        out << "Date,Emotion,Diary\n";
    }
    out << selectedDate << "," << emotion << "," << diary.replace(",", " ") << "\n";
    file.close();

    QMessageBox::information(this, "Success", "Diary saved successfully!");
    diaryInput->clear();
    emotionSlider->setValue(1);
}

void HeartlineApp::exportData()
{
    if (currentUsername.isEmpty()) {
        QMessageBox::warning(this, "Error", "No user logged in. Please log in first.");
        return;
    }

    // 要求輸入密碼進一步驗證
    QString password = QInputDialog::getText(this, "Password Required", "Enter your password:", QLineEdit::Password);
    if (password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Password cannot be empty.");
        return;
    }

    // 驗證密碼
    if (!validatePassword(currentUsername, password)) {
        QMessageBox::critical(this, "Access Denied", "Invalid password. Cannot access files.");
        return;
    }

    // 檢查用戶資料夾
    QDir dir("diary/" + currentUsername);
    if (!dir.exists()) {
        QMessageBox::warning(this, "Error", "No diary folder found for the current user.");
        return;
    }

    // 讓用戶選擇要還原的檔案
    QString fileName = QFileDialog::getOpenFileName(this, "Open Diary File", dir.absolutePath(), "CSV Files (*.csv)");
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to open the diary file.");
        return;
    }

    QTextStream in(&file);
    QStringList fileLines = in.readAll().split("\n");
    file.close();

    if (fileLines.isEmpty()) {
        QMessageBox::warning(this, "Error", "The selected file is empty.");
        return;
    }

    // 檢查檔案的第一行（標題）
    QStringList header = fileLines[0].split(",");
    if (header.size() < 3 || header[0].trimmed() != "Date" || header[1].trimmed() != "Emotion" || header[2].trimmed() != "Diary") {
        QMessageBox::critical(this, "Error", "The selected file format is invalid.");
        qDebug() << "Invalid header:" << header;
        return;
    }

    // 還原檔案內容
    QString restoredData;
    for (int i = 1; i < fileLines.size(); ++i) {
        QString line = fileLines[i].trimmed();
        if (line.isEmpty()) {
            continue; // 跳過空行
        }

        QStringList entry = line.split(",");
        if (entry.size() < 3) {
            qDebug() << "Invalid line format at index" << i << ":" << line;
            continue; // 跳過格式錯誤的行
        }

        QString date = entry[0].trimmed();
        QString emotion = entry[1].trimmed();
        QString diaryContent = entry[2].trimmed();

        // 將解析後的資料還原成字串
        restoredData += QString("Date: %1, Emotion: %2, Diary: %3\n").arg(date, emotion, diaryContent);
    }

    if (restoredData.isEmpty()) {
        QMessageBox::warning(this, "Error", "No valid data found in the selected file.");
        return;
    }

    // 輸出還原結果到除錯訊息或視窗
    qDebug() << "Restored Data:\n" << restoredData;

    // 顯示還原內容給用戶
    QMessageBox::information(this, "Restored Data", restoredData);
}

void HeartlineApp::handleEditEmail()
{
    QString newEmail = QInputDialog::getText(this, "Edit Email", "Enter new email address:");
    if (newEmail.isEmpty()) {
        QMessageBox::warning(this, "Edit Email", "Email cannot be empty.");
        return;
    }

    QFile file("users.txt");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to access user data.");
        return;
    }

    QTextStream in(&file);
    QString content;
    bool emailUpdated = false;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() >= 3 && parts[0] == currentUsername) {
            emailUpdated = true;
            content += QString("%1,%2,%3\n").arg(parts[0], parts[1], newEmail);
        } else {
            content += line + "\n";
        }
    }
    file.close();

    if (emailUpdated) {
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << content;
            file.close();
            QMessageBox::information(this, "Edit Email", "Email updated successfully!");
        }
    } else {
        QMessageBox::warning(this, "Edit Email", "Failed to update email.");
    }
}

void HeartlineApp::addRowToTable(const QString &date, const QString &emotion, const QString &diaryContent) {
    int currentRow = diaryTableWidget->rowCount();
    diaryTableWidget->insertRow(currentRow); // 添加新行
    diaryTableWidget->setItem(currentRow, 0, new QTableWidgetItem(date));
    diaryTableWidget->setItem(currentRow, 1, new QTableWidgetItem(emotion));
    diaryTableWidget->setItem(currentRow, 2, new QTableWidgetItem(diaryContent));
}


bool HeartlineApp::validatePassword(const QString &username, const QString &password)
{
    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to read user data.");
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() >= 2 && parts[0] == username && parts[1] == password) {
            return true; // 密碼驗證成功
        }
    }
    return false; // 密碼驗證失敗
}



void HeartlineApp::resetUserPassword(const QString &username, const QString &newPassword)
{
    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to update user data.");
        return;
    }

    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() >= 3 && parts[0] == username) {
            parts[1] = newPassword; // 更新密碼
            line = parts.join(",");
        }
        lines.append(line);
    }
    file.close();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::critical(this, "Error", "Failed to update user data.");
        return;
    }

    QTextStream out(&file);
    for (const QString &line : lines) {
        out << line << "\n";
    }
    file.close();
}
void HeartlineApp::handleForgotPassword()
{
    QString email = QInputDialog::getText(this, "Forgot Password", "Enter your registered email:");
    if (email.isEmpty()) {
        QMessageBox::warning(this, "Forgot Password", "Email cannot be empty.");
        return;
    }

    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to access user data.");
        return;
    }

    QTextStream in(&file);
    QStringList lines;
    QString newPassword;
    bool emailFound = false;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() >= 3 && parts[2] == email) {
            emailFound = true;

            // 使用當前時間戳生成新密碼
            newPassword = QString::number(QDateTime::currentSecsSinceEpoch() % 1000000).rightJustified(6, '0');

            // 更新用戶密碼
            lines.append(QString("%1,%2,%3").arg(parts[0], newPassword, email));
        } else {
            lines.append(line);
        }
    }
    file.close();

    if (!emailFound) {
        QMessageBox::warning(this, "Forgot Password", "Email not found.");
        return;
    }

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const QString &line : lines) {
            out << line << "\n";
        }
        file.close();

        QMessageBox::information(this, "Forgot Password",
                                 QString("Your new password is: %1").arg(newPassword));
    } else {
        QMessageBox::critical(this, "Error", "Failed to update user data.");
    }
}


void HeartlineApp::toggleDarkMode(bool enabled)
{
    if (enabled) {
        qApp->setStyleSheet("QWidget { background-color: #121212; color: #FFFFFF; } QPushButton { background-color: #2E2E2E; } QLineEdit, QTextEdit { background-color: #1E1E1E; color: #FFFFFF; }");
    } else {
        qApp->setStyleSheet("");
    }
}
