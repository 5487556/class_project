#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define ALL(x) x.begin(), x.end()
#define pb(x) push_back(x)
#define lys1004 ios_base::sync_with_stdio(false);//, cin.tie(0), cout.tie(0);
//開發設定區---------------------------------------

const int Lv1_map_size = 11;//不要設偶數,設偶數地圖會破www
const int Lv2_map_size = 21;
const int Lv3_map_size = 31;
const int start_r = 1, start_c = 1;//玩家初始位置
const char wall = '#';
const char path = ' ';
const char player = 'p';
const char coin = 'c';
const char small_fire = 'w';
const char water = '~';
const char big_boom = 'B';
const char small_boom = 'b';

//--------------------------------------------------

struct player_data
{
    string user_name = "Nan";
    string user_code = "Nan";
    unsigned long long int user_coin = 0;
    unsigned int user_Level = 0;
    bool game_over = false;
};

player_data p_dt;

void die()
{
    cout<<"\n--------------------------\n";
    cout<<"你死了~";
    cout<<"\n--------------------------\n";
}

struct map_data
{
    int Level = 0;
    int boom = 0;
    int coin = 0;
    int coin_data = 0;//依地圖大小調整錢幣出線機率 炸彈可能也需要
    int p_r = 1;//玩家位置
    int p_c = 1;
    int run = true;
    int map_len = 0;
};

const int dr[] = {0, 1, 0, -1};
const int dc[] = {1, 0, -1, 0};

void cheak_file()
{
    string file_name = "data.txt";
    ifstream in(file_name);
    string line;
    while(getline(in, line))
    {
        cout<<line<<" ";
    }
    in.close();
}

void login();
//登入註冊----------------------
void Register()
{
    ofstream out("data.txt", ios::app);
    string player_name;
    string player_code;
    cout<<"請先註冊帳號\n\n\n";
    cout<<"請設定玩家帳號: ";
    cin>>p_dt.user_name;
    cout<<"\n請設定密碼: ";
    cin>>p_dt.user_code;
    out<<p_dt.user_name<<" "<<p_dt.user_code<<" "<<0<<" "<<0<<endl;
    out.close();
    login();
    cout<<"\n";
    return;
}

void login()
{
    ifstream in("data.txt");
    if (!in.is_open()) {
        cerr << "無法開啟檔案 data.txt\n";
        return;
    }

    char cheak;
    cout << "\n是否已註冊? Y/n: ";
    cin >> cheak;
    if (cheak == 'n' || cheak == 'N') {
        Register();
        return;
    }

    while (true) {
        string player_name, player_code;
        cout << "\n請輸入玩家名稱: ";
        cin >> player_name;
        cout << "\n請輸入密碼: ";
        cin >> player_code;

        string line;
        vector<string> lines; // 儲存所有行
        bool found = false;

        // 讀取文件並檢查配對
        while (getline(in, line)) {
            string name, code, coin, level;
            istringstream iss(line);
            iss >> name >> code >> coin >> level;

            if (name == player_name && code == player_code) {
                found = true;
                p_dt.user_name = name;
                p_dt.user_code = code;
                p_dt.user_coin = stoi(coin);
                p_dt.user_Level = stoi(level);
            }
            else {
                lines.push_back(line); // 配對失敗，保留該行
            }
        }
        in.close();

        cout << "\n\n";
        if (found) {
            cout << "登入完成!!\n\n";

            // 寫回修改後的檔案
            ofstream out("data.txt");
            for (const string &l : lines) {
                out << l << '\n';
            }
            out.close();
            return;
        }
        else {
            cout << "找不到玩家帳號或密碼錯誤QQ\n\n";
            cout << "註冊帳號: 1";
            cout << "\n重新登入: 2";
            cout << "\n遊客帳號: 3";
            cout << "\n請輸入選擇: ";
            int n;
            cin >> n;
            if (n == 1) {
                Register();
            }
            else if (n == 2) {
                in.open("data.txt"); // 重新打開檔案進行下一次讀取
                continue;
            }
            else {
                break;
            }
        }
    }
}

//----------------------------------------------------------


//隨機產生地圖
void make_map(vector<vector<char>> & arr, int r, int c, int map_size)
{
    arr[r][c] = path;
    vector<int> side = {0, 1, 2, 3};
    shuffle(ALL(side), default_random_engine(rand()));
    for(auto i:side)
    {
        int new_r = r + dr[i]*2;
        int new_c = c + dc[i]*2;
        if(new_r >= 0 && new_r < map_size && new_c >= 0 && new_c < map_size*2 && arr[new_r][new_c] == wall)
        {
            arr[r + dr[i]][c + dc[i]] = path;
            make_map(arr, new_r, new_c, map_size);
        }
    }
}

//放硬幣
void put_coin(vector<vector<char>> &arr, map_data &mp_dt)
{
    int count_coin = 0;
    for(auto &i:arr)
    {
        for(auto &k:i)
        {
            int x = rand()%mp_dt.coin_data;
            if(x == 0 && k == path)
            {
                k = coin;
                count_coin++;
            }
        }
    }
    mp_dt.coin = count_coin;
}

//放炸彈
void put_boom(vector<vector<char>> &arr, map_data &mp_dt)
{
    int count_boom = 0;
    for(auto &i:arr)
    {
        for(auto &k:i)
        {
            int x = rand()%80;
            if(x == 0 && k == path)
            {
                int n = rand()%2;
                if(n == 1) k = big_boom;
                else k = small_boom;
                count_boom++;
            }
        }
    }
    mp_dt.boom = count_boom;
}

void water_mod(int r, int c, vector<vector<char>> arr, int power)
{
    if(power == 0) return;
    if(arr[r][c] != player)
    {
        arr[r][c] = water;
    }
    for(int i=0;i<4;i++)//BFS模擬水流,不會破壞牆體
    {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(arr[nr][nc] == path || arr[nr][nc] == player)
        {
            water_mod(nr, nc, arr, power-1);
        }
    }
}

//炸彈爆炸
void Small_boom(int r, int c, vector<vector<char>> &arr, int power)//記得到時候要先設小炸彈的爆炸威力
{
    if(power == 0) return;
    if(arr[r][c] != player)
    {
        arr[r][c] = small_fire;
    }
    for(int i=0;i<4;i++)//BFS模擬小炸彈爆炸,不會破壞牆體
    {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(arr[nr][nc] == path || arr[nr][nc] == player)
        {
            Small_boom(nr, nc, arr, power-1);
        }
    }
}

void Big_boom(int r, int c, vector<vector<char>> &arr, int len)//大炸彈爆炸會清除障礙物 (曼哈頓距離)
{
    int power = rand()%4+1;//隨機威力
    for(int i=1;i<len;i++)
    {
        for(int k=1;k<len*2;k++)
        {
            if(abs(i-r)+abs(c-k) <= power && arr[i][k] != coin)
            {
                arr[i][k] = path;
            }
        }
    }
}

void put_player(vector<vector<char>> &my_map, map_data &mp_dt)
{
    char place = my_map[mp_dt.p_r][mp_dt.p_c];
    if(place == coin)
    {
         p_dt.user_coin++;
         mp_dt.coin--;
    }
    else if(place ==small_boom)
    {
        Small_boom(mp_dt.p_r, mp_dt.p_c, my_map, rand()%5+1);
    }
    else if(place == big_boom)
    {
        Big_boom(mp_dt.p_r, mp_dt.p_c, my_map,mp_dt.map_len);
    }
    else if(place == small_fire)
    {
        die();
        p_dt.game_over = true;
        return;
    }
    my_map[mp_dt.p_r][mp_dt.p_c] = player;
    if(mp_dt.coin == 0) mp_dt.run = false;
}

//印出地圖
void print_map(vector<vector<char>> &arr)
{
    for(auto i:arr)
    {
        for(auto k:i)
        {
            cout<<k;
        }
        cout<<"\n";
    }
}

//顯示地圖資訊
void Print_map_data(map_data &mp_dt)
{
    cout<<"\n\n";
    cout<<"當前地圖資訊\n\n";
    cout<<"地圖等級: "<<mp_dt.Level;
    cout<<"\n\n錢幣總數: "<<mp_dt.coin;
    cout<<"\n\n炸彈總數: "<<mp_dt.boom;
    cout<<endl;
}
//顯示玩家及時資訊
void Print_player_data()
{
    cout<<"\n";
    cout<<"玩家持有錢幣:"<<p_dt.user_coin<<endl;
}

void Print_user_data()
{
    cout<<"\n\n\n\n\n\n-----------------------------------";
    cout<<"\n";
    cout<<"遊戲名稱: "<<p_dt.user_name;
    cout<<"\n玩家等級: "<<p_dt.user_Level;
    cout<<"\n持有錢幣總數: "<<p_dt.user_coin;
    cout<<endl;
    cout<<"-----------------------------------\n\n\n\n\n\n";
}

void move_mod(int &boom_skill, int &water_skill, vector<vector<char>> &my_map, map_data &mp_dt)//移動
{
    char player_move;
    bool error = false;
    cout<<endl<<"輸入操作: ";
    cin>>player_move;
    cout<<endl;
    player_move = tolower(player_move);//統一大小寫
    if(player_move == 'w')
    {
        if(my_map[mp_dt.p_r-1][mp_dt.p_c] == wall)//防止把牆壁吃掉
        {
            error = false;
            return;
        }
        my_map[mp_dt.p_r][mp_dt.p_c] = path;
        mp_dt.p_r-=1;
    }
    else if(player_move == 'd')
    {
        if(my_map[mp_dt.p_r][mp_dt.p_c+1] == wall)
        {
            error = false;
            return;
        }
        my_map[mp_dt.p_r][mp_dt.p_c] = path;
        mp_dt.p_c+=1;
    }
    else if(player_move == 's')
    {
        if(my_map[mp_dt.p_r+1][mp_dt.p_c] == wall)
        {
            error = false;
            return;
        }
        my_map[mp_dt.p_r][mp_dt.p_c] = path;
        mp_dt.p_r+=1;
    }
    else if(player_move == 'a')
    {
        if(my_map[mp_dt.p_r][mp_dt.p_c-1] == wall)
        {
            error = false;
            return;
        }
        my_map[mp_dt.p_r][mp_dt.p_c] = path;
        mp_dt.p_c-=1;
    }
    else if(tolower(player_move) == 'b' && boom_skill!=0)
    {
        Big_boom(mp_dt.p_r, mp_dt.p_c, my_map,mp_dt.map_len);
        boom_skill--;
    }
    else if(tolower(player_move) == 'c' && boom_skill!=0)
    {
        water_mod(mp_dt.p_r, mp_dt.p_c, my_map, 4);
        water_skill--;
    }
    else if(player_move == 'n')
    {
        mp_dt.run = false;
    }

}

signed main()
{
    lys1004
    srand(time(NULL));
    double START, END;
    int num;
    cout<<"登入帳號: 1\n遊客帳號: 2\n";
    cout<<"請選擇: ";
    cin>>num;
    cout<<"\n";
    if(num == 1) login();
    int choose_Lv;
    int map_size;
    again://<---------------------------------注意!!!
    start://<---------------------------------注意!!

    cout<<"請選擇迷宮等級\n"<<"初級 : 1\n中級 : 2\n高級 : 3\n玩家資訊 : 4\n"<<"請輸入>>";
    cin>>choose_Lv;
    map_data main_dt;
    switch(choose_Lv)
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
            goto again;
        default:
            cout<<"輸入錯誤請重新輸入";
            goto start;//<-----------------start範圍
            break;
    }
    int n = map_size;
    vector<vector<char>> main_map(n, vector<char> (n*2+1, wall));
    make_map(main_map, start_r, start_c, map_size);
    put_boom(main_map, main_dt);
    put_coin(main_map, main_dt);
    START = clock();
    while(main_dt.run)
    {
        int boom_skill = 3, water_skill = 3;
        put_player(main_map, main_dt);
        print_map(main_map);
        Print_player_data();
        Print_map_data(main_dt);
        move_mod(boom_skill, water_skill, main_map, main_dt);
        if(p_dt.game_over) break;
    }
    END = clock();
    if(!p_dt.game_over) p_dt.user_Level+=main_dt.Level;
    ofstream out("data.txt");
    out<<p_dt.user_name<<" "<<p_dt.user_code<<" "<<p_dt.user_coin<<" "<<p_dt.user_Level<<endl;
    cout<<"\n---------------------------------\n";
    cout<<"遊戲結束\n";
    cout<<"花費時間: "<< (END - START) / CLOCKS_PER_SEC << "秒\n";
    cout<<"\n---------------------------------\n";
    char a;
    cout<<"是否繼續Y/n: ";
    cin>>a;
    if(tolower(a) == 'y') goto again;//<----------------------------重新再來一遍
    system("start https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    return 0;

}
