#include <bits/stdc++.h>
using namespace std;

// 定義一些常用的宏（可以方便地簡化代碼）
// #define int long long // 如果需要處理大數運算，可以取消這行的註解
#define ALL(x) x.begin(), x.end()                 // 快速取得容器的首尾範圍
#define pb(x) push_back(x)                        // 簡化向容器中加入元素的操作
#define lys1004 ios_base::sync_with_stdio(false); // 提升輸入輸出效率

// 開發設定區---------------------------------------

// 定義三個不同等級地圖的大小，注意只能是奇數（偶數地圖可能會出錯）
const int Lv1_map_size = 11;
const int Lv2_map_size = 21;
const int Lv3_map_size = 31;

// 玩家初始位置
const int start_r = 1, start_c = 1;

// 各種遊戲中的物件符號
const char wall = '#';
const char path = ' ';
const char player = 'p';
const char coin = 'c';
const char small_fire = 'w';
const char water = '~';
const char big_boom = 'B';
const char small_boom = 'b';

//--------------------------------------------------

// 玩家資訊的結構體
struct player_data
{
    string user_name = "Nan";             // 玩家名稱
    string user_code = "Nan";             // 玩家密碼
    unsigned long long int user_coin = 0; // 玩家目前擁有的金幣數量
    unsigned int user_Level = 0;          // 玩家等級
    bool game_over = false;               // 玩家是否死亡
};

player_data p_dt; // 建立一個全域變數來存儲玩家的資訊

// 玩家死亡的函數
void die()
{
    cout << "\n\n\n\n\n--------------------------\n";
    cout << "你死了~"; // 提示玩家死亡
    cout << "\n--------------------------\n\n\n\n\n\n\n";
}

// 地圖資訊的結構體
struct map_data
{
    int Level = 0;     // 地圖等級
    int boom = 0;      // 地圖中炸彈的數量
    int coin = 0;      // 地圖中金幣的數量
    int coin_data = 0; // 金幣出現的機率
    int p_r = 1;       // 玩家所在的行
    int p_c = 1;       // 玩家所在的列
    int run = true;    // 遊戲是否運行
    int map_len = 0;   // 地圖的邊長
};

// 用於四個方向移動的行和列變化量
const int dr[] = {0, 1, 0, -1};
const int dc[] = {1, 0, -1, 0};

// 檢查檔案的函數
void cheak_file()
{
    string file_name = "data.txt"; // 定義要檢查的檔案名稱
    ifstream in(file_name);        // 開啟檔案
    string line;
    while (getline(in, line))
    {                        // 按行讀取檔案內容
        cout << line << " "; // 輸出檔案內容
    }
    in.close(); // 關閉檔案
}

// 函數聲明
void login();

// 註冊帳號的函數
void Register()
{
    ofstream out("data.txt", ios::app); // 開啟檔案（追加模式）
    cout << "請先註冊帳號\n\n\n";
    cout << "請設定玩家帳號: ";
    cin >> p_dt.user_name; // 輸入玩家帳號
    cout << "\n請設定密碼: ";
    cin >> p_dt.user_code;                                                          // 輸入玩家密碼
    out << p_dt.user_name << " " << p_dt.user_code << " " << 0 << " " << 0 << endl; // 保存到檔案
    out.close();                                                                    // 關閉檔案
    login();                                                                        // 註冊完成後直接進入登入流程
    cout << "\n";
    return;
}

// 登入函數
void login()
{
    ifstream in("data.txt"); // 開啟檔案
    if (!in.is_open())
    { // 檢查檔案是否成功開啟
        cerr << "無法開啟檔案 data.txt\n";
        return;
    }

    char cheak;
    cout << "\n是否已註冊? Y/n: ";
    cin >> cheak; // 問玩家是否已註冊
    if (cheak == 'n' || cheak == 'N')
    {               // 如果玩家未註冊
        Register(); // 呼叫註冊函數
        return;
    }

    while (true)
    {
        string player_name, player_code;
        cout << "\n請輸入玩家名稱: ";
        cin >> player_name; // 輸入玩家名稱
        cout << "\n請輸入密碼: ";
        cin >> player_code; // 輸入密碼

        string line;
        vector<string> lines; // 儲存檔案中所有的行
        bool found = false;   // 是否找到匹配的帳號和密碼

        // 讀取檔案內容並檢查是否匹配
        while (getline(in, line))
        {
            string name, code, coin, level;
            istringstream iss(line);
            iss >> name >> code >> coin >> level;

            if (name == player_name && code == player_code)
            { // 如果匹配成功
                found = true;
                p_dt.user_name = name; // 更新玩家資訊
                p_dt.user_code = code;
                p_dt.user_coin = stoi(coin);
                p_dt.user_Level = stoi(level);
            }
            else
            {
                lines.push_back(line); // 如果不匹配，保存該行
            }
        }
        in.close(); // 關閉檔案

        cout << "\n\n";
        if (found)
        { // 如果找到匹配的帳號
            cout << "登入完成!!\n\n";

            // 將修改後的內容寫回檔案
            ofstream out("data.txt");
            for (const string &l : lines)
            {
                out << l << '\n';
            }
            out.close(); // 關閉檔案
            return;
        }
        else
        {
            // 如果登入失敗，提供選項給玩家
            cout << "找不到玩家帳號或密碼錯誤QQ\n\n";
            cout << "註冊帳號: 1";
            cout << "\n重新登入: 2";
            cout << "\n遊客帳號: 3";
            cout << "\n請輸入選擇: ";
            int n;
            cin >> n;
            if (n == 1)
            { // 註冊新帳號
                Register();
            }
            else if (n == 2)
            {                        // 重新嘗試登入
                in.open("data.txt"); // 重新開啟檔案
                continue;
            }
            else
            { // 遊客模式，直接退出登入流程
                break;
            }
        }
    }
}

//----------------------------------------------------------

// 隨機生成地圖
void make_map(vector<vector<char>> &arr, int r, int c, int map_size)
{
    arr[r][c] = path;                                  // 將當前位置設為路徑
    vector<int> side = {0, 1, 2, 3};                   // 四個方向（上、右、下、左）
    shuffle(ALL(side), default_random_engine(rand())); // 隨機打亂方向順序
    for (auto i : side)
    {                              // 遍歷每個方向
        int new_r = r + dr[i] * 2; // 計算新位置的行
        int new_c = c + dc[i] * 2; // 計算新位置的列
        // 確保新位置在地圖範圍內，且尚未生成路徑
        if (new_r >= 0 && new_r < map_size && new_c >= 0 && new_c < map_size * 2 && arr[new_r][new_c] == wall)
        {
            arr[r + dr[i]][c + dc[i]] = path;      // 在兩點間打通路徑
            make_map(arr, new_r, new_c, map_size); // 遞歸處理下一位置
        }
    }
}

// 隨機放置硬幣
void put_coin(vector<vector<char>> &arr, map_data &mp_dt)
{
    int count_coin = 0; // 記錄放置的硬幣數量
    for (auto &i : arr)
    { // 遍歷地圖的每一行
        for (auto &k : i)
        {                                     // 遍歷每一列
            int x = rand() % mp_dt.coin_data; // 根據機率生成隨機數
            if (x == 0 && k == path)
            {                 // 如果隨機數為0且該位置是路徑
                k = coin;     // 放置硬幣
                count_coin++; // 增加硬幣計數
            }
        }
    }
    mp_dt.coin = count_coin; // 更新地圖中的硬幣數量
}

// 隨機放置炸彈
void put_boom(vector<vector<char>> &arr, map_data &mp_dt)
{
    int count_boom = 0; // 記錄放置的炸彈數量
    for (auto &i : arr)
    { // 遍歷地圖的每一行
        for (auto &k : i)
        {                        // 遍歷每一列
            int x = rand() % 80; // 隨機機率生成
            if (x == 0 && k == path)
            {                       // 如果隨機數為0且該位置是路徑
                int n = rand() % 2; // 隨機選擇炸彈類型
                if (n == 1)
                    k = big_boom; // 大炸彈
                else
                    k = small_boom; // 小炸彈
                count_boom++;       // 增加炸彈計數
            }
        }
    }
    mp_dt.boom = count_boom; // 更新地圖中的炸彈數量
}

// 模擬水流擴散
void water_mod(int r, int c, vector<vector<char>> arr, int power)
{
    if (power == 0)
        return; // 如果水流能量為0，終止遞迴
    if (arr[r][c] != player)
    {
        arr[r][c] = water; // 將當前位置設為水
    }
    for (int i = 0; i < 4; i++)
    {                       // BFS模擬水流，遍歷四個方向
        int nr = r + dr[i]; // 新行位置
        int nc = c + dc[i]; // 新列位置
        if (arr[nr][nc] == path || arr[nr][nc] == player)
        {                                      // 如果是路徑或玩家位置
            water_mod(nr, nc, arr, power - 1); // 遞迴繼續水流擴散
        }
    }
}

// 小炸彈爆炸模擬
void Small_boom(int r, int c, vector<vector<char>> &arr, int power)
{
    if (power == 0)
        return; // 如果爆炸威力為0，終止遞迴
    if (arr[r][c] != player)
    {
        arr[r][c] = small_fire; // 將當前位置設為火焰
    }
    for (int i = 0; i < 4; i++)
    {                       // BFS模擬爆炸擴散，遍歷四個方向
        int nr = r + dr[i]; // 新行位置
        int nc = c + dc[i]; // 新列位置
        if (arr[nr][nc] == path || arr[nr][nc] == player)
        {                                       // 如果是路徑或玩家位置
            Small_boom(nr, nc, arr, power - 1); // 遞迴模擬爆炸擴散
        }
    }
}

// 大炸彈爆炸模擬
void Big_boom(int r, int c, vector<vector<char>> &arr, int len)
{
    int power = rand() % 4 + 1; // 隨機生成爆炸威力（1到4）
    for (int i = 1; i < len; i++)
    { // 遍歷地圖的每一行
        for (int k = 1; k < len * 2; k++)
        { // 遍歷地圖的每一列
            // 如果該位置在曼哈頓距離範圍內，且不是硬幣
            if (abs(i - r) + abs(c - k) <= power && arr[i][k] != coin)
            {
                arr[i][k] = path; // 清除障礙物（設置為路徑）
            }
        }
    }
}

// 放置玩家並處理所在位置的物件
void put_player(vector<vector<char>> &my_map, map_data &mp_dt)
{
    char place = my_map[mp_dt.p_r][mp_dt.p_c]; // 獲取玩家所在位置的物件
    if (place == coin)
    {                     // 如果玩家站在硬幣上
        p_dt.user_coin++; // 增加玩家的硬幣數量
        mp_dt.coin--;     // 地圖中的硬幣總數減少
    }
    else if (place == small_boom)
    {                                                             // 如果玩家站在小炸彈上
        Small_boom(mp_dt.p_r, mp_dt.p_c, my_map, rand() % 5 + 1); // 觸發小炸彈爆炸
    }
    else if (place == big_boom)
    {                                                          // 如果玩家站在大炸彈上
        Big_boom(mp_dt.p_r, mp_dt.p_c, my_map, mp_dt.map_len); // 觸發大炸彈爆炸
    }
    else if (place == small_fire)
    {                          // 如果玩家站在火焰上
        die();                 // 玩家死亡
        p_dt.game_over = true; // 遊戲結束
        return;
    }
    my_map[mp_dt.p_r][mp_dt.p_c] = player; // 設置玩家所在位置為玩家符號
    if (mp_dt.coin == 0)
        mp_dt.run = false; // 如果硬幣撿完，停止遊戲
}

// 印出地圖
void print_map(vector<vector<char>> &arr)
{
    for (auto i : arr)
    { // 遍歷每一行
        for (auto k : i)
        {              // 遍歷每一列
            cout << k; // 印出符號
        }
        cout << "\n"; // 換行
    }
}

// 顯示地圖資訊
void Print_map_data(map_data &mp_dt)
{
    cout << "\n\n當前地圖資訊\n\n";
    cout << "地圖等級: " << mp_dt.Level << "\n";
    cout << "錢幣總數: " << mp_dt.coin << "\n";
    cout << "炸彈總數: " << mp_dt.boom << "\n\n";
}

// 顯示玩家即時資訊
void Print_player_data()
{
    cout << "\n玩家持有錢幣: " << p_dt.user_coin << endl;
}

// 顯示玩家完整資料
void Print_user_data()
{
    cout << "\n\n-----------------------------------\n";
    cout << "遊戲名稱: " << p_dt.user_name << "\n";
    cout << "玩家等級: " << p_dt.user_Level << "\n";
    cout << "持有錢幣總數: " << p_dt.user_coin << "\n";
    cout << "-----------------------------------\n\n";
}

// 處理玩家移動操作
void move_mod(int &boom_skill, int &water_skill, vector<vector<char>> &my_map, map_data &mp_dt)
{
    char player_move;
    cout << "\n輸入操作: ";
    cin >> player_move;                 // 獲取玩家操作
    player_move = tolower(player_move); // 統一為小寫
    if (player_move == 'w')
    { // 向上移動
        if (my_map[mp_dt.p_r - 1][mp_dt.p_c] == wall)
            return;                          // 遇到牆壁停止
        my_map[mp_dt.p_r][mp_dt.p_c] = path; // 清除舊位置
        mp_dt.p_r -= 1;                      // 更新行位置
    }
    else if (player_move == 'd')
    { // 向右移動
        if (my_map[mp_dt.p_r][mp_dt.p_c + 1] == wall)
            return;
        my_map[mp_dt.p_r][mp_dt.p_c] = path;
        mp_dt.p_c += 1; // 更新列位置
    }
    else if (player_move == 's')
    { // 向下移動
        if (my_map[mp_dt.p_r + 1][mp_dt.p_c] == wall)
            return;
        my_map[mp_dt.p_r][mp_dt.p_c] = path;
        mp_dt.p_r += 1;
    }
    else if (player_move == 'a')
    { // 向左移動
        if (my_map[mp_dt.p_r][mp_dt.p_c - 1] == wall)
            return;
        my_map[mp_dt.p_r][mp_dt.p_c] = path;
        mp_dt.p_c -= 1;
    }
    else if (player_move == 'b' && boom_skill != 0)
    { // 使用大炸彈技能
        Big_boom(mp_dt.p_r, mp_dt.p_c, my_map, mp_dt.map_len);
        boom_skill--;
    }
    else if (player_move == 'c' && water_skill != 0)
    { // 使用水流技能
        water_mod(mp_dt.p_r, mp_dt.p_c, my_map, 4);
        water_skill--;
    }
    else if (player_move == 'n')
    { // 結束遊戲
        mp_dt.run = false;
    }
}

signed main()
{
    srand(time(NULL)); // 初始化隨機數種子
    int num;
    cout << "登入帳號: 1\n遊客帳號: 2\n請選擇: ";
    cin >> num;
    if (num == 1)
        login(); // 處理登入
    int choose_Lv;
    int map_size;
again:
start:
    cout << "請選擇迷宮等級\n初級 : 1\n中級 : 2\n高級 : 3\n玩家資訊 : 4\n請輸入>>";
    cin >> choose_Lv;
    map_data main_dt; // 初始化地圖數據
    switch (choose_Lv)
    {
    case 1:
        map_size = Lv1_map_size;
        main_dt.Level = 1;
        main_dt.coin_data = 10;
        main_dt.map_len = map_size;
        break;
    case 2:
        map_size = Lv2_map_size;
        main_dt.Level = 2;
        main_dt.coin_data = 40;
        main_dt.map_len = map_size;
        break;
    case 3:
        map_size = Lv3_map_size;
        main_dt.Level = 3;
        main_dt.coin_data = 100;
        main_dt.map_len = map_size;
        break;
    case 4:
        Print_user_data();
        goto again; // 回到選單
    default:
        cout << "輸入錯誤請重新輸入";
        goto start; // 回到開始選擇
    }
    vector<vector<char>> main_map(map_size, vector<char>(map_size * 2 + 1, wall)); // 初始化地圖
    make_map(main_map, start_r, start_c, map_size);                                // 生成地圖
    put_boom(main_map, main_dt);                                                   // 放置炸彈
    put_coin(main_map, main_dt);                                                   // 放置硬幣
    double START = clock();
    while (main_dt.run)
    {                                                         // 遊戲循環
        int boom_skill = 3, water_skill = 3;                  // 初始化技能次數
        put_player(main_map, main_dt);                        // 更新玩家位置
        print_map(main_map);                                  // 印出地圖
        Print_player_data();                                  // 顯示玩家資訊
        Print_map_data(main_dt);                              // 顯示地圖資訊
        move_mod(boom_skill, water_skill, main_map, main_dt); // 處理移動
        if (p_dt.game_over)
            break; // 如果遊戲結束，退出循環
    }
    double END = clock();
    if (!p_dt.game_over)// 通關後提升玩家等級
        p_dt.user_Level += main_dt.Level;
    ofstream out("data.txt");             // 保存玩家數據
    out << p_dt.user_name << " " << p_dt.user_code << " " << p_dt.user_coin << " " << p_dt.user_Level << endl;
    cout << "\n遊戲結束\n花費時間: " << (END - START) / CLOCKS_PER_SEC << "秒\n";
    char a;
    cout << "是否繼續Y/n: ";
    cin >> a;
    if (tolower(a) == 'y')
        goto again; // 重新開始遊戲
    return 0;
}
