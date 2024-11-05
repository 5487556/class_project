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
const int start_r = 1, start_c = 1;
const char wall = '#';
const char path = ' ';
const char player = 'p';
const char coin = 'c';
const char big_boom = 'B';//炸彈系統未開發
const char small_boom = 'b';

//--------------------------------------------------

//玩家資料
struct player_data
{
    string user_name = "Nan";
    unsigned long long int user_coin = 0;
    unsigned int user_Lavel = 0;
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
//登入註冊(未debug完成)
void Register()
{
    ofstream out("data.txt", ios::app);
    string player_name;
    string player_code;
    cout<<"請先註冊帳號\n\n\n";
    cout<<"請設定玩家帳號: ";
    cin>>player_name;
    cout<<"\n請設定密碼: ";
    cin>>player_code;
    out<<player_name<<" "<<player_code<<endl;
    out.close();
    login();

    cout<<"\n";
}

void login()
{
    ifstream in("data.txt", ios::app);
    char cheak;
    cout<<"\n是否已註冊? Y/n: ";
    cin>>cheak;
    if(cheak == 'n' || cheak == 'N')
    {
        Register();
    }
    while(true){
        string player_name, player_code;
        cout<<"\n請輸入玩家名稱: ";
        cin>>player_name;
        cout<<"\n請輸入密碼: ";
        cin>>player_code;
        string line;
        bool found = false;
        while(getline(in, line))
        {
            string name = "", code = "";
            bool change = false;
            for(auto i:line)
            {
                if(change)
                {
                    if(i == ' ')
                        break;
                }
                if(i == ' ')
                {
                    change = true;
                    continue;
                }
                if(!change)
                {
                    name += i;
                }
                else
                {
                    code += i;
                }
            }
            if(name == player_name && code == player_code)
            {
                found = true;
                break;
            }
        }
        cout<<"\n\n";
        if(found)
        {
            cout<<"登入成功!!\n\n";
            return;
        }
        else
        {
            cout<<"找不到玩家帳號或密碼錯誤QQ\n\n";
            cout<<"註冊帳號: 1";
            cout<<"\n重新登入: 2";
            cout<<"\n遊客帳號: 3";
            cout<<"\n請輸入選擇: ";
            int n;
            cin>>n;
            if(n == 1)
            {
                Register();
            }
            else if(n == 2)
            {
                continue;
            }
            else
            {
                break;
            }
        }
    }
    in.close();
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
        if(new_r >= 0 && new_r < map_size && new_c >= 0 && new_c < map_size && arr[new_r][new_c] == wall)
        {
            arr[r + dr[i]][c + dc[i]] = path;
            make_map(arr, new_r, new_c, map_size);
        }
    }
}

//放硬幣
void put_coin(vector<vector<char>> &arr)
{
    for(auto &i:arr)
    {
        for(auto &k:i)
        {
            int x = rand()%10;
            if(x == 0 && k == path)
            {
                k = coin;
            }
        }
    }
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

signed main()
{
    lys1004
    srand(time(NULL));
    int num;
    cout<<"登入帳號: 1\n遊客帳號: 2\n";
    cout<<"請選擇: ";
    cin>>num;
    cout<<"\n";
    if(num == 1) login();
    int choose_Lv;
    int map_size;

    start://<---------------------------------注意!!

    cout<<"請選擇迷宮等級\n"<<"初級 : 1\n中級 : 2\n高級 : 3\n"<<"請輸入>>";
    cin>>choose_Lv;
    switch(choose_Lv)
    {
        case 1:
            map_size = Lv1_map_size;
            break;
        case 2:
            map_size = Lv2_map_size;
            break;
        case 3:
            map_size = Lv3_map_size;
            break;
        default:
            cout<<"輸入錯誤請重新輸入";
            goto start;//<-----------------start範圍
            break;
    }
    int n = map_size;
    vector<vector<char>> main_map(n, vector<char> (n, wall));
    make_map(main_map, start_r, start_c, map_size);
    put_coin(main_map);
    print_map(main_map);

    return 0;

}
