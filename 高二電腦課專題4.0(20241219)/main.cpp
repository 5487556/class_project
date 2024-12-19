#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define ALL(x) x.begin(), x.end()
#define pb(x) push_back(x)
#define lys1004 ios_base::sync_with_stdio(false);//, cin.tie(0), cout.tie(0);
//�}�o�]�w��---------------------------------------

const int Lv1_map_size = 11;//���n�]����,�]���Ʀa�Ϸ|�}www
const int Lv2_map_size = 21;
const int Lv3_map_size = 31;
const int start_r = 1, start_c = 1;//���a��l��m
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
    cout<<"�A���F~";
    cout<<"\n--------------------------\n";
}

struct map_data
{
    int Level = 0;
    int boom = 0;
    int coin = 0;
    int coin_data = 0;//�̦a�Ϥj�p�վ�����X�u���v ���u�i��]�ݭn
    int p_r = 1;//���a��m
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
//�n�J���U----------------------
void Register()
{
    ofstream out("data.txt", ios::app);
    string player_name;
    string player_code;
    cout<<"�Х����U�b��\n\n\n";
    cout<<"�г]�w���a�b��: ";
    cin>>p_dt.user_name;
    cout<<"\n�г]�w�K�X: ";
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
        cerr << "�L�k�}���ɮ� data.txt\n";
        return;
    }

    char cheak;
    cout << "\n�O�_�w���U? Y/n: ";
    cin >> cheak;
    system("cls");
    if (cheak == 'n' || cheak == 'N') {
        Register();
        return;
    }

    while (true) {
        string player_name, player_code;
        cout << "\n�п�J���a�W��: ";
        cin >> player_name;
        cout << "\n�п�J�K�X: ";
        cin >> player_code;
        system("cls");

        string line;
        vector<string> lines; // �x�s�Ҧ���
        bool found = false;

        // Ū�������ˬd�t��
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
                lines.push_back(line); // �t�異�ѡA�O�d�Ӧ�
            }
        }
        in.close();

        cout << "\n\n";
        if (found) {
            cout << "�n�J����!!\n\n";
            system("cls");
            // �g�^�ק�᪺�ɮ�
            ofstream out("data.txt");
            for (const string &l : lines) {
                out << l << '\n';
            }
            out.close();
            return;
        }
        else {
            cout << "�䤣�쪱�a�b���αK�X���~QQ\n\n";
            cout << "���U�b��: 1";
            cout << "\n���s�n�J: 2";
            cout << "\n�C�ȱb��: 3";
            cout << "\n�п�J���: ";
            int n;
            cin >> n;
            system("cls");
            if (n == 1) {
                Register();
            }
            else if (n == 2) {
                in.open("data.txt"); // ���s���}�ɮ׶i��U�@��Ū��
                continue;
            }
            else {
                break;
            }
        }
    }
}

//----------------------------------------------------------


//�H�����ͦa��
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

//��w��
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

//�񬵼u
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
    for(int i=0;i<4;i++)//BFS�������y,���|�}�a����
    {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(arr[nr][nc] == path || arr[nr][nc] == player)
        {
            water_mod(nr, nc, arr, power-1);
        }
    }
}

//���u�z��
void Small_boom(int r, int c, vector<vector<char>> &arr, int power)//�O�o��ɭԭn���]�p���u���z���¤O
{
    if(power == 0) return;
    if(arr[r][c] != player)
    {
        arr[r][c] = small_fire;
    }
    for(int i=0;i<4;i++)//BFS�����p���u�z��,���|�}�a����
    {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(arr[nr][nc] == path || arr[nr][nc] == player)
        {
            Small_boom(nr, nc, arr, power-1);
        }
    }
}

void Big_boom(int r, int c, vector<vector<char>> &arr, int len)//�j���u�z���|�M����ê�� (�ҫ��y�Z��)
{
    int power = rand()%4+1;//�H���¤O
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

//�L�X�a��
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

//��ܦa�ϸ�T
void Print_map_data(map_data &mp_dt)
{
    cout<<"\n\n";
    cout<<"��e�a�ϸ�T\n\n";
    cout<<"�a�ϵ���: "<<mp_dt.Level;
    cout<<"\n\n�����`��: "<<mp_dt.coin;
    cout<<"\n\n���u�`��: "<<mp_dt.boom;
    cout<<endl;
}
//��ܪ��a�ήɸ�T
void Print_player_data()
{
    cout<<"\n";
    cout<<"���a��������:"<<p_dt.user_coin<<endl;
}

void Print_user_data()
{
    cout<<"\n\n\n\n\n\n-----------------------------------";
    cout<<"\n";
    cout<<"�C���W��: "<<p_dt.user_name;
    cout<<"\n���a����: "<<p_dt.user_Level;
    cout<<"\n���������`��: "<<p_dt.user_coin;

    cout<<endl;
    cout<<"-----------------------------------\n\n\n\n\n\n";
}

void move_mod(int &boom_skill, int &water_skill, vector<vector<char>> &my_map, map_data &mp_dt)//����
{
    char player_move;
    bool error = false;
    cout<<endl<<"��J�ާ@: ";
    cin>>player_move;
    cout<<endl;
    player_move = tolower(player_move);//�Τ@�j�p�g
    if(player_move == 'w')
    {
        if(my_map[mp_dt.p_r-1][mp_dt.p_c] == wall)//���������Y��
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
    cout<<"�n�J�b��: 1\n�C�ȱb��: 2\n";
    cout<<"�п��: ";
    cin>>num;
    system("cls");
    cout<<"\n";
    if(num == 1) login();
    system("cls");

    int choose_Lv;
    int map_size;
    again://<---------------------------------�`�N!!!
    start://<---------------------------------�`�N!!
    system("cls");
    cout<<"�п�ܰg�c����\n"<<"��� : 1\n���� : 2\n���� : 3\n���a��T : 4\n"<<"�п�J>>";
    cin>>choose_Lv;
    system("cls");
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
            system("cls");
            goto again;
        default:
            cout<<"��J���~�Э��s��J";
            goto start;//<-----------------start�d��
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
        system("cls");
    }
    END = clock();
    if(!p_dt.game_over) p_dt.user_Level+=main_dt.Level;
    ofstream out("data.txt", ios::app);
    out<<p_dt.user_name<<" "<<p_dt.user_code<<" "<<p_dt.user_coin<<" "<<p_dt.user_Level<<endl;
    cout<<"\n---------------------------------\n";
    cout<<"�C������\n";
    cout<<"��O�ɶ�: "<< (END - START) / CLOCKS_PER_SEC << "��\n";
    cout<<"\n---------------------------------\n";
    char a;
    cout<<"�O�_�~��Y/n: ";
    cin>>a;
    if(tolower(a) == 'y') goto again;//<----------------------------���s�A�Ӥ@�M
    system("start chrome https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    return 0;

}
