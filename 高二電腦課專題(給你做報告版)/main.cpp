#include <bits/stdc++.h>
using namespace std;

// �w�q�@�Ǳ`�Ϊ����]�i�H��K�a²�ƥN�X�^
// #define int long long // �p�G�ݭn�B�z�j�ƹB��A�i�H�����o�檺����
#define ALL(x) x.begin(), x.end()                 // �ֳt���o�e���������d��
#define pb(x) push_back(x)                        // ²�ƦV�e�����[�J�������ާ@
#define lys1004 ios_base::sync_with_stdio(false); // ���ɿ�J��X�Ĳv

// �}�o�]�w��---------------------------------------

// �w�q�T�Ӥ��P���Ŧa�Ϫ��j�p�A�`�N�u��O�_�ơ]���Ʀa�ϥi��|�X���^
const int Lv1_map_size = 11;
const int Lv2_map_size = 21;
const int Lv3_map_size = 31;

// ���a��l��m
const int start_r = 1, start_c = 1;

// �U�عC����������Ÿ�
const char wall = '#';
const char path = ' ';
const char player = 'p';
const char coin = 'c';
const char small_fire = 'w';
const char water = '~';
const char big_boom = 'B';
const char small_boom = 'b';

//--------------------------------------------------

// ���a��T�����c��
struct player_data
{
    string user_name = "Nan";             // ���a�W��
    string user_code = "Nan";             // ���a�K�X
    unsigned long long int user_coin = 0; // ���a�ثe�֦��������ƶq
    unsigned int user_Level = 0;          // ���a����
    bool game_over = false;               // ���a�O�_���`
};

player_data p_dt; // �إߤ@�ӥ����ܼƨӦs�x���a����T

// ���a���`�����
void die()
{
    cout << "\n\n\n\n\n--------------------------\n";
    cout << "�A���F~"; // ���ܪ��a���`
    cout << "\n--------------------------\n\n\n\n\n\n\n";
}

// �a�ϸ�T�����c��
struct map_data
{
    int Level = 0;     // �a�ϵ���
    int boom = 0;      // �a�Ϥ����u���ƶq
    int coin = 0;      // �a�Ϥ��������ƶq
    int coin_data = 0; // �����X�{�����v
    int p_r = 1;       // ���a�Ҧb����
    int p_c = 1;       // ���a�Ҧb���C
    int run = true;    // �C���O�_�B��
    int map_len = 0;   // �a�Ϫ����
};

// �Ω�|�Ӥ�V���ʪ���M�C�ܤƶq
const int dr[] = {0, 1, 0, -1};
const int dc[] = {1, 0, -1, 0};

// �ˬd�ɮת����
void cheak_file()
{
    string file_name = "data.txt"; // �w�q�n�ˬd���ɮצW��
    ifstream in(file_name);        // �}���ɮ�
    string line;
    while (getline(in, line))
    {                        // ����Ū���ɮפ��e
        cout << line << " "; // ��X�ɮפ��e
    }
    in.close(); // �����ɮ�
}

// ����n��
void login();

// ���U�b�������
void Register()
{
    ofstream out("data.txt", ios::app); // �}���ɮס]�l�[�Ҧ��^
    cout << "�Х����U�b��\n\n\n";
    cout << "�г]�w���a�b��: ";
    cin >> p_dt.user_name; // ��J���a�b��
    cout << "\n�г]�w�K�X: ";
    cin >> p_dt.user_code;                                                          // ��J���a�K�X
    out << p_dt.user_name << " " << p_dt.user_code << " " << 0 << " " << 0 << endl; // �O�s���ɮ�
    out.close();                                                                    // �����ɮ�
    login();                                                                        // ���U�����᪽���i�J�n�J�y�{
    cout << "\n";
    return;
}

// �n�J���
void login()
{
    ifstream in("data.txt"); // �}���ɮ�
    if (!in.is_open())
    { // �ˬd�ɮ׬O�_���\�}��
        cerr << "�L�k�}���ɮ� data.txt\n";
        return;
    }

    char cheak;
    cout << "\n�O�_�w���U? Y/n: ";
    cin >> cheak; // �ݪ��a�O�_�w���U
    if (cheak == 'n' || cheak == 'N')
    {               // �p�G���a�����U
        Register(); // �I�s���U���
        return;
    }

    while (true)
    {
        string player_name, player_code;
        cout << "\n�п�J���a�W��: ";
        cin >> player_name; // ��J���a�W��
        cout << "\n�п�J�K�X: ";
        cin >> player_code; // ��J�K�X

        string line;
        vector<string> lines; // �x�s�ɮפ��Ҧ�����
        bool found = false;   // �O�_���ǰt���b���M�K�X

        // Ū���ɮפ��e���ˬd�O�_�ǰt
        while (getline(in, line))
        {
            string name, code, coin, level;
            istringstream iss(line);
            iss >> name >> code >> coin >> level;

            if (name == player_name && code == player_code)
            { // �p�G�ǰt���\
                found = true;
                p_dt.user_name = name; // ��s���a��T
                p_dt.user_code = code;
                p_dt.user_coin = stoi(coin);
                p_dt.user_Level = stoi(level);
            }
            else
            {
                lines.push_back(line); // �p�G���ǰt�A�O�s�Ӧ�
            }
        }
        in.close(); // �����ɮ�

        cout << "\n\n";
        if (found)
        { // �p�G���ǰt���b��
            cout << "�n�J����!!\n\n";

            // �N�ק�᪺���e�g�^�ɮ�
            ofstream out("data.txt");
            for (const string &l : lines)
            {
                out << l << '\n';
            }
            out.close(); // �����ɮ�
            return;
        }
        else
        {
            // �p�G�n�J���ѡA���ѿﶵ�����a
            cout << "�䤣�쪱�a�b���αK�X���~QQ\n\n";
            cout << "���U�b��: 1";
            cout << "\n���s�n�J: 2";
            cout << "\n�C�ȱb��: 3";
            cout << "\n�п�J���: ";
            int n;
            cin >> n;
            if (n == 1)
            { // ���U�s�b��
                Register();
            }
            else if (n == 2)
            {                        // ���s���յn�J
                in.open("data.txt"); // ���s�}���ɮ�
                continue;
            }
            else
            { // �C�ȼҦ��A�����h�X�n�J�y�{
                break;
            }
        }
    }
}

//----------------------------------------------------------

// �H���ͦ��a��
void make_map(vector<vector<char>> &arr, int r, int c, int map_size)
{
    arr[r][c] = path;                                  // �N��e��m�]�����|
    vector<int> side = {0, 1, 2, 3};                   // �|�Ӥ�V�]�W�B�k�B�U�B���^
    shuffle(ALL(side), default_random_engine(rand())); // �H�����ä�V����
    for (auto i : side)
    {                              // �M���C�Ӥ�V
        int new_r = r + dr[i] * 2; // �p��s��m����
        int new_c = c + dc[i] * 2; // �p��s��m���C
        // �T�O�s��m�b�a�Ͻd�򤺡A�B�|���ͦ����|
        if (new_r >= 0 && new_r < map_size && new_c >= 0 && new_c < map_size * 2 && arr[new_r][new_c] == wall)
        {
            arr[r + dr[i]][c + dc[i]] = path;      // �b���I�����q���|
            make_map(arr, new_r, new_c, map_size); // ���k�B�z�U�@��m
        }
    }
}

// �H����m�w��
void put_coin(vector<vector<char>> &arr, map_data &mp_dt)
{
    int count_coin = 0; // �O����m���w���ƶq
    for (auto &i : arr)
    { // �M���a�Ϫ��C�@��
        for (auto &k : i)
        {                                     // �M���C�@�C
            int x = rand() % mp_dt.coin_data; // �ھھ��v�ͦ��H����
            if (x == 0 && k == path)
            {                 // �p�G�H���Ƭ�0�B�Ӧ�m�O���|
                k = coin;     // ��m�w��
                count_coin++; // �W�[�w���p��
            }
        }
    }
    mp_dt.coin = count_coin; // ��s�a�Ϥ����w���ƶq
}

// �H����m���u
void put_boom(vector<vector<char>> &arr, map_data &mp_dt)
{
    int count_boom = 0; // �O����m�����u�ƶq
    for (auto &i : arr)
    { // �M���a�Ϫ��C�@��
        for (auto &k : i)
        {                        // �M���C�@�C
            int x = rand() % 80; // �H�����v�ͦ�
            if (x == 0 && k == path)
            {                       // �p�G�H���Ƭ�0�B�Ӧ�m�O���|
                int n = rand() % 2; // �H����ܬ��u����
                if (n == 1)
                    k = big_boom; // �j���u
                else
                    k = small_boom; // �p���u
                count_boom++;       // �W�[���u�p��
            }
        }
    }
    mp_dt.boom = count_boom; // ��s�a�Ϥ������u�ƶq
}

// �������y�X��
void water_mod(int r, int c, vector<vector<char>> arr, int power)
{
    if (power == 0)
        return; // �p�G���y��q��0�A�פ�k
    if (arr[r][c] != player)
    {
        arr[r][c] = water; // �N��e��m�]����
    }
    for (int i = 0; i < 4; i++)
    {                       // BFS�������y�A�M���|�Ӥ�V
        int nr = r + dr[i]; // �s���m
        int nc = c + dc[i]; // �s�C��m
        if (arr[nr][nc] == path || arr[nr][nc] == player)
        {                                      // �p�G�O���|�Ϊ��a��m
            water_mod(nr, nc, arr, power - 1); // ���k�~����y�X��
        }
    }
}

// �p���u�z������
void Small_boom(int r, int c, vector<vector<char>> &arr, int power)
{
    if (power == 0)
        return; // �p�G�z���¤O��0�A�פ�k
    if (arr[r][c] != player)
    {
        arr[r][c] = small_fire; // �N��e��m�]�����K
    }
    for (int i = 0; i < 4; i++)
    {                       // BFS�����z���X���A�M���|�Ӥ�V
        int nr = r + dr[i]; // �s���m
        int nc = c + dc[i]; // �s�C��m
        if (arr[nr][nc] == path || arr[nr][nc] == player)
        {                                       // �p�G�O���|�Ϊ��a��m
            Small_boom(nr, nc, arr, power - 1); // ���k�����z���X��
        }
    }
}

// �j���u�z������
void Big_boom(int r, int c, vector<vector<char>> &arr, int len)
{
    int power = rand() % 4 + 1; // �H���ͦ��z���¤O�]1��4�^
    for (int i = 1; i < len; i++)
    { // �M���a�Ϫ��C�@��
        for (int k = 1; k < len * 2; k++)
        { // �M���a�Ϫ��C�@�C
            // �p�G�Ӧ�m�b�ҫ��y�Z���d�򤺡A�B���O�w��
            if (abs(i - r) + abs(c - k) <= power && arr[i][k] != coin)
            {
                arr[i][k] = path; // �M����ê���]�]�m�����|�^
            }
        }
    }
}

// ��m���a�óB�z�Ҧb��m������
void put_player(vector<vector<char>> &my_map, map_data &mp_dt)
{
    char place = my_map[mp_dt.p_r][mp_dt.p_c]; // ������a�Ҧb��m������
    if (place == coin)
    {                     // �p�G���a���b�w���W
        p_dt.user_coin++; // �W�[���a���w���ƶq
        mp_dt.coin--;     // �a�Ϥ����w���`�ƴ��
    }
    else if (place == small_boom)
    {                                                             // �p�G���a���b�p���u�W
        Small_boom(mp_dt.p_r, mp_dt.p_c, my_map, rand() % 5 + 1); // Ĳ�o�p���u�z��
    }
    else if (place == big_boom)
    {                                                          // �p�G���a���b�j���u�W
        Big_boom(mp_dt.p_r, mp_dt.p_c, my_map, mp_dt.map_len); // Ĳ�o�j���u�z��
    }
    else if (place == small_fire)
    {                          // �p�G���a���b���K�W
        die();                 // ���a���`
        p_dt.game_over = true; // �C������
        return;
    }
    my_map[mp_dt.p_r][mp_dt.p_c] = player; // �]�m���a�Ҧb��m�����a�Ÿ�
    if (mp_dt.coin == 0)
        mp_dt.run = false; // �p�G�w���ߧ��A����C��
}

// �L�X�a��
void print_map(vector<vector<char>> &arr)
{
    for (auto i : arr)
    { // �M���C�@��
        for (auto k : i)
        {              // �M���C�@�C
            cout << k; // �L�X�Ÿ�
        }
        cout << "\n"; // ����
    }
}

// ��ܦa�ϸ�T
void Print_map_data(map_data &mp_dt)
{
    cout << "\n\n��e�a�ϸ�T\n\n";
    cout << "�a�ϵ���: " << mp_dt.Level << "\n";
    cout << "�����`��: " << mp_dt.coin << "\n";
    cout << "���u�`��: " << mp_dt.boom << "\n\n";
}

// ��ܪ��a�Y�ɸ�T
void Print_player_data()
{
    cout << "\n���a��������: " << p_dt.user_coin << endl;
}

// ��ܪ��a������
void Print_user_data()
{
    cout << "\n\n-----------------------------------\n";
    cout << "�C���W��: " << p_dt.user_name << "\n";
    cout << "���a����: " << p_dt.user_Level << "\n";
    cout << "���������`��: " << p_dt.user_coin << "\n";
    cout << "-----------------------------------\n\n";
}

// �B�z���a���ʾާ@
void move_mod(int &boom_skill, int &water_skill, vector<vector<char>> &my_map, map_data &mp_dt)
{
    char player_move;
    cout << "\n��J�ާ@: ";
    cin >> player_move;                 // ������a�ާ@
    player_move = tolower(player_move); // �Τ@���p�g
    if (player_move == 'w')
    { // �V�W����
        if (my_map[mp_dt.p_r - 1][mp_dt.p_c] == wall)
            return;                          // �J���������
        my_map[mp_dt.p_r][mp_dt.p_c] = path; // �M���¦�m
        mp_dt.p_r -= 1;                      // ��s���m
    }
    else if (player_move == 'd')
    { // �V�k����
        if (my_map[mp_dt.p_r][mp_dt.p_c + 1] == wall)
            return;
        my_map[mp_dt.p_r][mp_dt.p_c] = path;
        mp_dt.p_c += 1; // ��s�C��m
    }
    else if (player_move == 's')
    { // �V�U����
        if (my_map[mp_dt.p_r + 1][mp_dt.p_c] == wall)
            return;
        my_map[mp_dt.p_r][mp_dt.p_c] = path;
        mp_dt.p_r += 1;
    }
    else if (player_move == 'a')
    { // �V������
        if (my_map[mp_dt.p_r][mp_dt.p_c - 1] == wall)
            return;
        my_map[mp_dt.p_r][mp_dt.p_c] = path;
        mp_dt.p_c -= 1;
    }
    else if (player_move == 'b' && boom_skill != 0)
    { // �ϥΤj���u�ޯ�
        Big_boom(mp_dt.p_r, mp_dt.p_c, my_map, mp_dt.map_len);
        boom_skill--;
    }
    else if (player_move == 'c' && water_skill != 0)
    { // �ϥΤ��y�ޯ�
        water_mod(mp_dt.p_r, mp_dt.p_c, my_map, 4);
        water_skill--;
    }
    else if (player_move == 'n')
    { // �����C��
        mp_dt.run = false;
    }
}

signed main()
{
    srand(time(NULL)); // ��l���H���ƺؤl
    int num;
    cout << "�n�J�b��: 1\n�C�ȱb��: 2\n�п��: ";
    cin >> num;
    if (num == 1)
        login(); // �B�z�n�J
    int choose_Lv;
    int map_size;
again:
start:
    cout << "�п�ܰg�c����\n��� : 1\n���� : 2\n���� : 3\n���a��T : 4\n�п�J>>";
    cin >> choose_Lv;
    map_data main_dt; // ��l�Ʀa�ϼƾ�
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
        goto again; // �^����
    default:
        cout << "��J���~�Э��s��J";
        goto start; // �^��}�l���
    }
    vector<vector<char>> main_map(map_size, vector<char>(map_size * 2 + 1, wall)); // ��l�Ʀa��
    make_map(main_map, start_r, start_c, map_size);                                // �ͦ��a��
    put_boom(main_map, main_dt);                                                   // ��m���u
    put_coin(main_map, main_dt);                                                   // ��m�w��
    double START = clock();
    while (main_dt.run)
    {                                                         // �C���`��
        int boom_skill = 3, water_skill = 3;                  // ��l�Ƨޯস��
        put_player(main_map, main_dt);                        // ��s���a��m
        print_map(main_map);                                  // �L�X�a��
        Print_player_data();                                  // ��ܪ��a��T
        Print_map_data(main_dt);                              // ��ܦa�ϸ�T
        move_mod(boom_skill, water_skill, main_map, main_dt); // �B�z����
        if (p_dt.game_over)
            break; // �p�G�C�������A�h�X�`��
    }
    double END = clock();
    if (!p_dt.game_over)// �q���ᴣ�ɪ��a����
        p_dt.user_Level += main_dt.Level;
    ofstream out("data.txt");             // �O�s���a�ƾ�
    out << p_dt.user_name << " " << p_dt.user_code << " " << p_dt.user_coin << " " << p_dt.user_Level << endl;
    cout << "\n�C������\n��O�ɶ�: " << (END - START) / CLOCKS_PER_SEC << "��\n";
    char a;
    cout << "�O�_�~��Y/n: ";
    cin >> a;
    if (tolower(a) == 'y')
        goto again; // ���s�}�l�C��
    return 0;
}
