# heartline

組別:第18組
班級:四資工二甲
組員:范芷紜、潘怡潔


一、研究動機

在當今快速發展的社會中，在快速發展的社會中，情緒健康問題正影響著人們的幸福感和工作效率。研究顯示，許多成年人難以管理壓力和應對情緒波動。隨著生活節奏加快，我們迫切需要一種工具來幫助人們了解並有效管理情緒。
基於此，本專題旨在開發一款應用程式，專門用於記錄和分析用戶的日常心情日記，並通過情緒分析技術將日記內容轉化為可視化數據。這一工具不僅能幫助用戶更好地了解自身情緒變化的趨勢，還能為他們提供改善情緒管理的實際方法。
具體來說，用戶可以通過該應用程式方便地記錄日常心情和經歷。應用程式將運用先進的情緒分析技術，對日記內容進行分類和標註。透過這些分析結果，會幫助用戶直觀地了解情緒變化。
此外，隨著數據的積累，用戶可以從中發現影響自身情緒的模式和因素，從而採取針對性的措施來改善情緒狀態。這不僅是對個人情緒健康的一種有效管理工具，還可以作為心理健康研究的一個數據支持工具，提供有價值的數據參考。
此專題就是要把高深莫測的情緒變化轉化成具體的數據，讓每個人都能簡單明瞭地了解自己的心情走向。透過這款應用程式，用戶可以方便地管理自己的情緒，紀錄那些讓他們開心的時刻，找到應對生活挑戰的有效策略。我們的目標是讓每個人都能輕鬆地追蹤心情，讓生活變得更加美好和有趣。



二、使用技術
1. Qt Widgets:用於構建應用程式的圖形界面（GUI），包括按鈕、文本框、日曆等
2. Qt Charts:用於創建各種圖表，例如圓餅圖和折線圖，來可視化用戶的情緒數據
3. Qt Core:提供核心非GUI功能，如事件處理、數據處理和文件操作
4. Qt Network:支持網絡操作，如數據同步和備份等功能
5. Qt SQL:用於數據庫操作，可以使用SQLite來存儲用戶的日記內容和情緒分析結果
6. Qt QML:用於創建高效且具有動態效果的用戶界面，適合需要複雜動畫效果的部分
7. Qt Multithreading:用於多線程處理，確保應用程式在執行複雜任務時依然保持流暢
8. Qt File System:用於文件的讀寫操作，支持日記的自動保存和載入功能
9. Qt XML/JSON:用於數據格式化和解析，特別是在導出日記和情緒分析結果時會用到

三、主要功能

日記輸入

用戶可以每天輸入文字日記，描述自己的心情與經歷
界面設計應簡潔明瞭，支持多行文字輸入

情緒分析

使用簡單的情緒分析模型（例如基於關鍵字分析的正向/負向分類）
結果生成情緒標籤（如「開心」、「難過」、「焦慮」）

可視化圖表

利用 QtCharts 或 QML，將情緒數據轉化為可視化圖表：
圓餅圖：顯示不同情緒的分佈比例
折線圖：展示用戶情緒隨時間的變化趨勢

文件保存與導出

支持用戶將日記內容與情緒分析結果導出為文字檔（如 .txt 或 .csv）
自動保存數據到本地，並允許用戶重新載入

其他增強功能

日曆檢視：用戶可從日曆中選擇某一天查看日記與情緒
提醒功能：每日提醒用戶記錄日記
暗黑模式：提供主題切換功能，增強用戶體驗

四、使用方式

第一頁：歡迎頁 + 註冊/登入功能
顯示應用名稱 Heartline 和一段簡要描述，例如：「記錄你的心情，探索你的情緒旅程！Heartline 幫助你視覺化你的心情日記，隨時掌握你的情緒變化。」
註冊新帳號
輸入框(EX:用戶名稱/電子郵件/密碼與確認密碼)
點擊「註冊」後，顯示「註冊成功！」，並跳轉至登入頁
登入
輸入框(EX:用戶名稱或電子郵件/密碼)
成功登入後，進入主頁面
忘記密碼
點擊後通過電子郵件重設密碼

第二頁：設置主題與視覺樣式
主題設置
折線圖顏色：選擇喜歡的圖表線條顏色
背景顏色：調整圖表背景顏色
提供網格和標籤顯示開關
模式切換:提供光明模式/暗黑模式的切換按鈕


第三頁：日記輸入
日記內容輸入
提供情緒分數（0-10）滑動條或輸入框
日期選擇
預設當天日期，支持選擇過去或未來日期進行記錄
上傳照片
支持上傳一張與日記相關的照片，顯示在日記詳情中
保存日記
點擊「保存」按鈕，將日記存儲至本地數據庫並更新折線圖

第四頁：折線圖與分析
折線圖展示
X 軸：日期/Y 軸：情緒分數（0-10）
點擊折線圖數據點，查看當日詳情（日記內容、照片等）
時間範圍篩選
提供快速篩選選項：(EX:最近 7 天/最近 30 天/自定義日期範圍)
數據導出
CSV 格式：包含日期、情緒分數、日記內容及圖片路徑
折線圖圖片：保存為 PNG
數據匯入
匯入按鈕，導入舊數據（CSV 文件），自動更新折線圖

第五頁：數據清理與設置
數據清理
提示確認是否清空所有日記與數據，確認後，刪除所有用戶數據
帳號管理
用戶可以修改密碼、更新個人信息，或刪除帳號
退出/登入
切換到其他帳號使用
流程圖



