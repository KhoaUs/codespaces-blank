#include "Mylib.h"

char bg1[20][36];
char bg2[24][55];
char bg3[40][72];
//Ham chinh van hanh toan bo
void Operating_System()
{
    //Khai bao mang Arr luu cac gia tri cua tung o trong bang 2D, sub_arr mang lýu cac loai Pokemon va so luong cua no
    Board Pikachu;
    Pikachu.Arr = NULL;
    Pikachu.sub_arr = NULL;

    //Khoi tao de ramdo gia tri cua cac pokemon
    srand(time(NULL));

    cout << "Hay bat full man hinh de co trai nghiem tot nhat! " << endl;
    system("pause");
    system("cls");

    //Goi ham xu ly chinh
    play(Pikachu);

    //Thu hoi bo nho
    deleleDinamicArr (Pikachu);
    delete[] Pikachu.Arr;
    delete[] Pikachu.sub_arr;
}

void play(Board& Pikachu)
{
    int middle, rows, start_point;

    //luu thong tin nguoi choi
	player p;
	Score score;

    //khoi tao diem bat dau cua bang
    Coordinate pos_menu;

    //Tinh kich thuoc console
    calculateColumnsConsole(middle, rows);

    //Khai bao bien start_point cho bang, pos_menu cho toa do cua menu
    pos_menu.x = middle - 3;
    pos_menu.y = 21;

    drawMenu(middle);

    bool check = true;
    while (true)
    {
        if(_kbhit())
        {
            char c = _getch();
            check = true;

            gotoXY(pos_menu.x, pos_menu.y);
            cout << "__________";

            gotoXY(pos_menu.x, pos_menu.y - 2);
            cout << "__________";

            if (check)
            {
                if(c == 72)
                {
                    if(pos_menu.y == 21)
                    {
                        pos_menu.y = 21 + 8;
                    }
                    else
                    {
                        pos_menu.y -= 2;
                    }

                    selectOption(pos_menu);

                    //KiêÒm tra ðiêÌu kiêòn ðêÒ traình in dý taòi viò triì ðaìy
                    if(pos_menu.y != 29)
                    {
                        gotoXY(pos_menu.x, pos_menu.y + 2);
                        cout << "__________";
                    }
                    check = false;
                }

                if(c == 80)
                {
                    if(pos_menu.y == 29)
                    {
                        pos_menu.y = 29 - 8;
                    }
                    else
                    {
                        pos_menu.y += 2;
                    }

                    selectOption(pos_menu);
                    gotoXY(pos_menu.x, pos_menu.y - 2);
                    cout << "__________";
                    check = false;
                }

                if (c == 13 || c == 32)
                {
                        break;
                }
            }
        }
    }
    switch (pos_menu.y)
    {
        case 21:


            //cho nguoi choi chon do kho
            system("cls");
            selectLevel (Pikachu.size);
            start_point = middle - Pikachu.size * 4;
            setValueBoard (Pikachu);

            //luu thong tin nguoi choi
        	system("cls");
        	drawRec(start_point - 20, 5, start_point + 10, 8, '_', '|');
        	gotoXY(start_point - 18, 7);
        	cout << "NAME: ";
        	getline(cin, p.name);

        	//Ve bang
        	system("cls");
            drawBoard(Pikachu, start_point);
            operateBoard(Pikachu, start_point, score, p);
            play(Pikachu);
            break;
        case 23:
            //dan toi trang dang nhap de nhap tai khoan
            //de quay lai menu bap esc hoac chon "tro ve"
            system("cls");
            start_point = middle - Pikachu.size * 4;
            drawBoard(Pikachu, start_point);
            operateBoard(Pikachu, start_point, score, p);
            play(Pikachu);
            break;
        case 25:
            //dan toi trang dang nhap de nhap tai khoan, va hien thi thanh tich nguoi choi
            //de quay lai menu bap esc hoac chon "tro ve"
            cout << "Tinh nang dang duoc phat trien!";
            _getch();
            system("cls");
            play(Pikachu);
            break;
        case 27:
            //hien thi BXH, de quay lai menu bap esc hoac chon "tro ve"
            system("cls");
            titleLeaderBoard();
			readLeaderBoard();
			play(Pikachu);
            break;
        case 29:
            //thoat
            system("cls");
            break;
        default:
            cout << "Loi he thong, vui long reset va bao voi doi ngu ho tro!" << endl;
            break;
    }
}

void operateBoard (Board& Pikachu, int start_point, Score score, player p)
{
    char c;

    Pikachu.No_pokemon = Pikachu.size * Pikachu.size;

    //Khoi tao gia tri ban dau cua cac diem de khoi chay bang
    Pikachu.select = {-1, -1};
    Pikachu.cur = {1, 1};
    Pikachu.old = {1, 1};

    //To mau vung chon dau tien
    highLightBlock(Pikachu.cur, Pikachu.Arr, 143, start_point);

    while (true)
    {
        c = _getch();
        Pikachu.old.x = Pikachu.cur.x;
        Pikachu.old.y = Pikachu.cur.y;

        swapBoard(Pikachu, start_point);
        //Di chuyen len
        if(c == 72 || c == 'w' || c == 'W')
         {
             if(Pikachu.cur.y == 1)
             {
                 Pikachu.cur.y = Pikachu.size;
             }
             else
             {
                 Pikachu.cur.y--;
             }
         }
         //Di chuyen xuong
         if(c == 80 || c == 's' || c == 'S')
         {
             if(Pikachu.cur.y == Pikachu.size)
             {
                 Pikachu.cur.y = 1;
             }
             else
             {
                 Pikachu.cur.y++;
             }
         }
        //Di chuyen trai
         if(c == 75 || c == 'a' || c == 'A')
        {
            if(Pikachu.cur.x == 1)
            {
                Pikachu.cur.x = Pikachu.size;
            }
            else
            {
                Pikachu.cur.x--;
            }
        }
        //Di chuyen phai
        if(c == 77 || c == 'D' || c == 'd')
        {
            if(Pikachu.cur.x == Pikachu.size)
            {
                Pikachu.cur.x = 1;
            }
            else
            {
                Pikachu.cur.x++;
            }
        }
        //Tai lai neu man hinh hien thi loi
        if(c == 'r' || c == 'R')
        {
            system("cls");
            drawBoard(Pikachu, start_point);
        }
        //Enter hoac Space
        if(c == 13 || c == 32)
        {
            if(Pikachu.Arr[Pikachu.cur.x][Pikachu.cur.y] != -1)   //Neu o co Pikachu
            {
                highLightBlock(Pikachu.cur, Pikachu.Arr, 177, start_point);
                if(Pikachu.select.x == -1 && Pikachu.select.y == -1)   //Neu chua luu Pokemon nao
                {
                    Pikachu.select.x = Pikachu.cur.x;   //Luu vi tri Pokemon
                    Pikachu.select.y = Pikachu.cur.y;
                }
                else if(Pikachu.select.x != -1 && Pikachu.select.y != -1)   //Neu trong select da co Pokemon
                {
                    //So sanh 2 Pokemon co giong nhau khong
                    if(Pikachu.Arr[Pikachu.select.x][Pikachu.select.y] == Pikachu.Arr[Pikachu.cur.x][Pikachu.cur.y])
                    {
                        //Da match
                        if(matchWholeShape (Pikachu, start_point))
                        {
                            //Danh dau vi tri da xoa va xoa mau
                            Pikachu.Arr[Pikachu.select.x][Pikachu.select.y] = -1;
                            Pikachu.Arr[Pikachu.cur.x][Pikachu.cur.y] = -1;

                            //Xoa mau vung da match
                            highLightBlock(Pikachu.select, Pikachu.Arr, 0, start_point);
                            highLightBlock(Pikachu.cur, Pikachu.Arr, 177, start_point);

                            //Xoa khung sau khi match
                            drawRec((start_point + 9 * (Pikachu.select.x - 1)) , (5 * (Pikachu.select.y - 1)), (start_point + 9 * (Pikachu.select.x - 1) + 8), (4 + 5 * (Pikachu.select.y - 1)), ' ', ' ');
                            drawRec((start_point + 9 * (Pikachu.cur.x - 1)) , (5 * (Pikachu.cur.y - 1)), (start_point + 9 * (Pikachu.cur.x - 1) + 8), (4 + 5 * (Pikachu.cur.y - 1)), ' ', ' ');

                            //In background;
                            if(Pikachu.size == 4)
                            	getBackground1(bg1);
							if(Pikachu.size == 6)
								getBackground2(bg2);
							if(Pikachu.size == 8)
								getBackground3(bg3);
                            //In background

                        	print(Pikachu.select, start_point, Pikachu.size);
                        	print(Pikachu.cur, start_point, Pikachu.size);

                            //Reset toa do vung chon
                            Pikachu.select = {-1, -1};

                            //Tru so luong Pokemon con lai trong bang
                            Pikachu.No_pokemon -= 2;

                            //Neu so luong Pokemon da duoc Match het thi hien thi man hinh Win
                            if (Pikachu.No_pokemon == 0)
                            {
                                if(Pikachu.size == 4)
                                    print1(start_point);
                                if(Pikachu.size == 6)
                                    print2(start_point);
                                if(Pikachu.size == 8)
                                    print3(start_point);
                                printWin();
                                Sleep(3000);
                                score.total();
                                p.point = score.changeScore();
                                writeLeaderBoard(p);

                                system("cls");
                                titleLeaderBoard();
                                readLeaderBoard();
                                break;
                            }
                        }
                        //Hai Pokemon giong nhau nhung khong thuoc loai Matching nao
                        else
                        {
                            falseEffect (Pikachu, start_point);
                        }
                    }
                    //Neu 2 Pokemon khong giong nhau thi highlight false
                    else   falseEffect(Pikachu, start_point);
                }
            }
            else
            {
                gotoXY(0, 0);
                cout << "Khong co Pikachu de chon!";
                Sleep(300);
                gotoXY(0, 0);
                cout << "                         ";
            }

        }
        //Tro giup
        if(c == 'h' || c == 'H')
        {
            //Do sth
       //     suggestionFunction (Pikachu, start_point);
        }
        //Tinh nang moi - tinh nang swap!
        if(c == 'o' || c == 'O')
        {
            if(Pikachu.select.x == -1 || Pikachu.select.y == -1)
            {
                cout << "Vui long chon o can swap truoc khi bam 'o'!";

            }
            else
            {
            highLightBlock(Pikachu.select, Pikachu.Arr, Pikachu.Arr[Pikachu.old.x][Pikachu.old.y], start_point);
            swapPokemon(Pikachu);
            drawBoard(Pikachu, start_point);
            highLightBlock(Pikachu.cur, Pikachu.Arr, 143, start_point);
            gotoXY(0, 0);
            cout << "WELL DONE!!!";
            }
        }
        //Esc de thoat
        if(c == 27)
        {
            system("cls");
            break;
        }
        //Ktra xem co di chuyen chua
        if (Pikachu.cur.x != Pikachu.old.x || Pikachu.cur.y != Pikachu.old.y )
        {
            //Tranh to lai mau mac dinh cho o da chon
            if (Pikachu.select.x == Pikachu.cur.x && Pikachu.select.y == Pikachu.cur.y)
            {
                //To mau khac biet khi di lai vung da chon mot lan nua
                highLightBlock(Pikachu.cur, Pikachu.Arr, 199, start_point);
                c = _getch();
                if(c == 13 || c == 32 || c == 'b')
                {
                    Pikachu.select = {-1, -1};
                    gotoXY(0, 0);
                    cout << "Da bo chon                       ";
                    Sleep (200);
                    gotoXY(0, 0);
                    cout << "                                 ";
                }
            }
            else
            {
                //To mau vung con tro
                highLightBlock(Pikachu.cur, Pikachu.Arr, 143, start_point);
            }

            if (Pikachu.old.x != Pikachu.select.x || Pikachu.old.y != Pikachu.select.y)
            {
                //To lai mau mac dinh sau khi di chuyen
                highLightBlock(Pikachu.old, Pikachu.Arr, Pikachu.Arr[Pikachu.old.x][Pikachu.old.y], start_point);
            }
            else
            {
                //Xu ly sau khi di qua lai o da chon mot lan nua
                highLightBlock(Pikachu.old, Pikachu.Arr, 177, start_point);
            }
            gotoXY(1, 1);
            cout << Pikachu.cur.x << ", " << Pikachu.cur.y;
        }
    }
    Sleep(100);
}

void resetBoard (Board& Pikachu)
{
    for (int i = 0; i <= Pikachu.size + 1; i++)
    {
        for (int j = 0; j <= Pikachu.size + 1; j++)
        {
            if (Pikachu.Arr[i][j] < 0 && Pikachu.Arr[i][j] != -1)
            {
                Pikachu.Arr[i][j] = -1;
            }
        }
    }
}

void selectLevel (int &size)
{
    int left, middle, rows;
    Coordinate pos_menu;

    //Tinh kich thuoc ma hinh console
    calculateColumnsConsole(middle, rows);

    left = middle - 7;
    pos_menu.x = middle - 3;
    pos_menu.y = 21;
    changeColor(5 | FOREGROUND_INTENSITY);
    cout << R"(
            __/\\\______________/\\\\\\\\\\\\\\\__/\\\________/\\\__/\\\\\\\\\\\\\\\__/\\\_______________________
             _\/\\\_____________\/\\\///////////__\/\\\_______\/\\\_\/\\\///////////__\/\\\_______________________
              _\/\\\_____________\/\\\_____________\//\\\______/\\\__\/\\\_____________\/\\\_______________________
               _\/\\\_____________\/\\\\\\\\\\\______\//\\\____/\\\___\/\\\\\\\\\\\_____\/\\\_______________________
                _\/\\\_____________\/\\\///////________\//\\\__/\\\____\/\\\///////______\/\\\_______________________
                 _\/\\\_____________\/\\\________________\//\\\/\\\_____\/\\\_____________\/\\\_______________________
                  _\/\\\_____________\/\\\_________________\//\\\\\______\/\\\_____________\/\\\_______________________
                   _\/\\\\\\\\\\\\\\\_\/\\\\\\\\\\\\\\\______\//\\\_______\/\\\\\\\\\\\\\\\_\/\\\\\\\\\\\\\\\___________
                    _\///////////////__\///////////////________\///________\///////////////__\///////////////____________
 )";
    changeColor(FOREGROUND_WHITE);
    drawFrame (left, 20, "    KHO");
    drawFrame (left, 22, " TRUNG BINH");
    drawFrame (left, 24, "     DE");
    selectOption(pos_menu);

    bool check = true;
    while (true)
    {
        if(_kbhit())
        {
            char c = _getch();
            check = true;

            gotoXY(pos_menu.x, pos_menu.y);
            cout << "__________";

            gotoXY(pos_menu.x, pos_menu.y - 2);
            cout << "__________";

            if (check)
            {
                //Di chuyen len
                if(c == 72)
                {
                    //neu da gap dinh, thi con tro nhay xuong duoi day
                    if(pos_menu.y == 21)
                    {
                        pos_menu.y = 25;
                    }
                    else
                    {
                        pos_menu.y -= 2;
                    }

                    selectOption(pos_menu);

                    //KiêÒm tra ðiêÌu kiêòn ðêÒ traình in dý taòi viò triì ðaìy
                    if(pos_menu.y != 25)
                    {
                        gotoXY(pos_menu.x, pos_menu.y + 2);
                        cout << "__________";
                    }
                    check = false;
                }
                //Di chuyen xuong
                if(c == 80)
                {
                    //Neu cham day, con tro tu tro len dau
                    if(pos_menu.y == 25)
                    {
                        pos_menu.y = 21;
                    }
                    else
                    {
                        pos_menu.y += 2;
                    }

                    selectOption(pos_menu);
                    gotoXY(pos_menu.x, pos_menu.y - 2);
                    cout << "__________";
                    check = false;
                }
                //Neu chon bang enter hoac space
                if (c == 13 || c == 32)
                {
                        break;
                }
            }
        }
    }

    switch(pos_menu.y)
    {
    case 21:
        if (rows >= 44)
        {
            size = 8;
            break;
        }
        else
        {
            system ("cls");
            gotoXY (0, 0);
            cout << R"(
                                          /$$$$$$\   /$$$$$$\ |$$\   $$\ $$$$$$$$\ $$$$$$\  /$$$$$$\  |$$\   $$\   |@@\
                                         /$$  __$$\ /$$  __$$\|$$ |  $$ |\__$$  __|\_$$  _||$$  __$$\ |$$$\  $$ |  |@@ |
                                        |$$ /  \__||$$ /  $$ ||$$ |  $$ |  |$$ |     $$ |  |$$ /  $$| |$$$$\ $$ |  |@@ |
                                        |$$ |      |$$$$$$$$ ||$$ |  $$ |  |$$ |     $$ |  |$$ |  $$| |$$ $$\$$ |  |@@ |
                                        |$$ |      |$$  __$$ ||$$ |  $$ |  |$$ |     $$ |  |$$ |  $$| |$$ \$$$$ |  |@@ |
                                        |$$ |  $$\ |$$ |  $$ ||$$ |  $$ |  |$$ |     $$ |  |$$ |  $$| |$$ |\$$$ |   \__|
                                         \$$$$$$  ||$$ |  $$ | \$$$$$$  |  |$$ |   $$$$$$\ \ $$$$$$ | |$$ | \$$ |   @@\
                                          \______/  \__|  \__|  \______/    \__|   \______| \______/   \__|  \__|   \__| )";

            changeColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            gotoXY (middle - 27, 15);
            cout << "Kich thuoc man hinh console khong du de choi che do nay! ";
            gotoXY (middle - 22, 16);
            cout << "He thong se tu dong chuyen sang level 'TRUNG BINH'!" ;
            gotoXY (middle - 16, rows - 2);
            changeColor(FOREGROUND_WHITE | FOREGROUND_INTENSITY);
            system("pause");
        }
    case 23:
        size = 6;
        break;
    case 25:
        size = 4;
        break;
    default:
        cout << "Loi he thong!" << endl;
    }
    system("cls");
}

//Ham ve bang
void drawBoard (Board Pikachu, int start_point)
{
    for (int j = 0; j < Pikachu.size; j++)
    {
        for (int i = 0; i < Pikachu.size; i++)
        {
            //Chon mau khung
            if(Pikachu.Arr[i + 1][j + 1] != -1)
            {
                //Chon mau khung
                changeColor (FOREGROUND_INTENSITY);
                drawRec((start_point + 9 * i ), (5 * j), (start_point + 9 * i + 8), (4 + 5 * j), '-', '|');

                //Chon mau chu
                changeColor (Pikachu.Arr[i + 1][j + 1] | FOREGROUND_INTENSITY);
                gotoXY (start_point + 9 * i  + 4, 5 * j + 2);
                cout << char('A' + Pikachu.Arr[i + 1][j + 1]);
            }
        }
    }
}


void changeColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

//Ham tinh kich thuoc man hinh console
void calculateColumnsConsole(int &middle, int &rows)
{
    //CONSOLE_SCREEN_BUFFER_INFO la mot kieu du lieu chua thong tin ve bo dem man hinh
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    //Ham GetConsoleScreenBufferInfo se lay thong tin bo dem man hinh console, bien csbi se luu thong tin kich thuoc va vi tri cua man hinh console
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    middle = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

//Khoi tao gia tri bang
void setValueBoard (Board& Pikachu)
{
    //Khai bao bien count de dem so luong pokemon da set, Pikachu.sub_size de luu so loai pokemon
    int count = 0;
    Pikachu.sub_size = Pikachu.size * 2;

    //Cap phat dong cho mang
    Pikachu.Arr = new int *[Pikachu.size + 2];
    Pikachu.sub_arr = new int [Pikachu.sub_size];

    //Set so luong cua cac loai pokemon ban dau la 0, vi chua co pokemon nao
    for (int i = 0; i < Pikachu.sub_size; i++)
    {
        Pikachu.sub_arr[i] = 0;
    }

    //muc dich tao ra mot hinh chu nhat phu ben ngoai de ho tro matching
    for (int i = 0; i <= Pikachu.size + 1; i++)
    {
        Pikachu.Arr[i] = new int [Pikachu.size + 2];
    }

    for (int i = 0; i <= Pikachu.size + 1; i++)
    {
        for(int j = 0; j <= Pikachu.size + 1; j++)
        {
            //Tao mot hinh vuong phu ben ngoai de ho tro cho viet matching loai U
            if (i == 0 || j == 0 || i == Pikachu.size + 1 || j == Pikachu.size + 1)
            {
                Pikachu.Arr[j][i] = -1;
            }
            else
            {
                //De lai mot so luong Pikachu.sub_size phan tu de lam chan so luong cac pokemon
                if (count < (Pikachu.size * Pikachu.size - Pikachu.sub_size))
                {
                    //random cac loai pokemon va dem so luong da ramdon
                    Pikachu.Arr[j][i] = rand() % Pikachu.sub_size;
                    count++;

                    //Dem so luong cac loai pokemon, chi so index trong mang sub_arr ung voi gia tri cua pokemon, con gia tri tai index do se ung voi so luong loai do
                    Pikachu.sub_arr[Pikachu.Arr[j][i]]++;
                }
                //chi random den mot so luong Pikachu.size * Pikachu.size - Pikachu.sub_size sau do ktra xem pokemon nao dang le thi se tang them mot, neu khong con pokemon nao le, se tao so le sau do lam chan
                else
                {
                    int sub_count = count;
                    for (int p = 0; p < Pikachu.sub_size; p++)
                    {
                        if ((Pikachu.sub_arr[p] % 2) != 0 )
                        {
                            //neu so luong cua loai pokemon p la le, se tang len 1 de lam chan
                            Pikachu.Arr[j][i] = p;
                            Pikachu.sub_arr[p]++;

                            //tang bien sub_count de khang dinh rang con pokemon co so luong le
                            sub_count++;
                            break;
                        }
                    }

                    //Neu nhu khong con pokemon nao le, hay lam cho no le :D
                    if (sub_count == count)
                    {
                        //random va dem so luong cac loai pokemon
                        Pikachu.Arr[j][i] = rand() % Pikachu.sub_size;
                        Pikachu.sub_arr[Pikachu.Arr[j][i]]++;
                    }
                    count++;
                }
            }
        }
    }
}

//Ham tro con tro van ban den vi tri co toa do x, y
void gotoXY(int x, int y){
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{x,y});
}

//Ham ve cac duong matc
void drawLine (Board& Pikachu, int start_point)
{
    for (int i = 0; i < 4; i++)
    {
        int color;
        changeColor (i + 1 | FOREGROUND_INTENSITY);
        color = 154 + 10 * i;

        for (int i = 0; i <= Pikachu.size + 1; i++)
        {
            for (int j = 0; j <= Pikachu.size + 1; j++)
            {
                if (Pikachu.Arr[i][j] == -2)
                {
                    gotoXY((start_point + 9 * (i - 1)), (2 + 5 * (j - 1)));
                    cout << "=========";
                }

                if (Pikachu.Arr[i][j] == -3)
                {
                    for (int k = 0; k < 5; k++)
                    {
                    gotoXY((start_point + 4 + 9 * (i - 1)), (5 * (j - 1) + k));
                    cout << char(166);
                    }
                }

                if (Pikachu.Arr[i][j] == -4)     // ╔ ╗╚ ╝
                {
                    for (int k = 3; k < 5; k++)
                    {
                    gotoXY((start_point + 4 + 9 * (i - 1)), (5 * (j - 1) + k));
                    cout << char(166);
                    }
                    gotoXY((start_point + 9 * (i - 1)), (2 + 5 * (j - 1)));
                    cout << "====o";
                }

                if (Pikachu.Arr[i][j] == -5)
                {
                    for (int k = 0; k < 2; k++)
                    {
                    gotoXY((start_point + 4 + 9 * (i - 1)), (5 * (j - 1) + k));
                    cout << char(166);
                    }
                    gotoXY((start_point + 9 * (i - 1)), (2 + 5 * (j - 1)));
                    cout << "====o";
                }

                if (Pikachu.Arr[i][j] == -6)
                {
                    for (int k = 0; k < 2; k++)
                    {
                    gotoXY((start_point + 4 + 9 * (i - 1)), (5 * (j - 1) + k));
                    cout << char(166);
                    }
                    gotoXY((start_point + 9 * (i - 1)), (2 + 5 * (j - 1)));
                    cout << "    o====";
                }

                if (Pikachu.Arr[i][j] == -7)
                {
                    for (int k = 3; k < 5; k++)
                    {
                    gotoXY((start_point + 4 + 9 * (i - 1)), (5 * (j - 1) + k));
                    cout << char(166);
                    }
                    gotoXY((start_point + 9 * (i - 1)), (2 + 5 * (j - 1)));
                    cout << "    o====";
                }
            }
        }
        //Lam noi bat cac o duoc match
        highLightBlock(Pikachu.select, Pikachu.Arr, color, start_point);
        highLightBlock(Pikachu.cur, Pikachu.Arr, color, start_point);
        Sleep(100);
    }
    resetBoard (Pikachu);
    for (int i = 0; i <= Pikachu.size + 1; i++)
    {
        for (int j = 1; j <= Pikachu.size + 1; j++)
        {
            if (Pikachu.Arr[i][j] == -1)
            {
                for (int k = 0; k < 5; k++)
                {
                    gotoXY((start_point + 9 * (i - 1)), (5 * (j - 1)+ k));
                    cout << "         ";
                }
            }
        }
    }
}

void falseEffect (Board Pikachu, int start_point)
{
    int color;
    for (int i = 0; i < 6; i++)
    {
        if (i % 2 ==0)
            color = 207;
        else
            color = 174;

        highLightBlock(Pikachu.select, Pikachu.Arr, color, start_point);
        highLightBlock(Pikachu.cur, Pikachu.Arr, color, start_point);
        Sleep(50);
    }
}
bool matchShapeI(Board& Pikachu)
{
    //Kiem tra xem hai toa do co trung nhau khong truoc do trong ham cha
    //Kiem tra co cung hang, hay cung cot hay khong
    //Truong hop cung truc Oy
    if (Pikachu.cur.y == Pikachu.select.y)
    {
        if(Pikachu.cur.x > Pikachu.select.x)
        {
            for (int i = Pikachu.select.x + 1; i < Pikachu.cur.x; i++)
            {
                if(Pikachu.Arr[i][Pikachu.cur.y] != -1)
                {
                    resetBoard (Pikachu);
                    return 0;
                }
                Pikachu.Arr[i][Pikachu.cur.y] = -2;
            }
            return 1;
        }
        else
        {
            for (int i = Pikachu.select.x - 1; i > Pikachu.cur.x; i--)
            {
                if(Pikachu.Arr[i][Pikachu.cur.y] != -1)
                {
                    resetBoard (Pikachu);
                    return 0;
                }
                Pikachu.Arr[i][Pikachu.cur.y] = -2;
            }
            return 1;
        }
    }

    //Truong hop trung truc Ox
    else if (Pikachu.cur.x == Pikachu.select.x)
    {
        if(Pikachu.cur.y > Pikachu.select.y)
        {
            for (int i = Pikachu.select.y + 1; i < Pikachu.cur.y; i++)
            {
                if(Pikachu.Arr[Pikachu.cur.x][i] != -1)
                {
                    resetBoard (Pikachu);
                    return 0;
                }
                Pikachu.Arr[Pikachu.cur.x][i] = -3;
            }
            return 1;
        }
        else
        {
            for (int i = Pikachu.select.y - 1; i > Pikachu.cur.y; i--)
            {
                if (Pikachu.Arr[Pikachu.cur.x][i] != -1)
                {
                    resetBoard (Pikachu);
                    return 0;
                }
                Pikachu.Arr[Pikachu.cur.x][i] = -3;
            }
            return 1;
        }
    }
    return 0;
}

bool matchShapeL(Board& Pikachu)
{
    if (Pikachu.cur.x == Pikachu.select.x || Pikachu.cur.y == Pikachu.select.y)
    {
        return 0;
    }

    //Chia lam 4 trýõng hop cho loai nay, khi select ben phai cua Pikachu.cur
    if(Pikachu.cur.x < Pikachu.select.x && Pikachu.cur.y > Pikachu.select.y)
    {

        //Truong hop 1: ngang - len: NGANG
        for (int i = Pikachu.cur.x + 1; i <= Pikachu.select.x; i++)
        {

            //Truong hop 2: len - ngang, neu gap o khong trong se vao TH2 de xet tiep
            if (Pikachu.Arr[i][Pikachu.cur.y] != -1)
            {
                resetBoard (Pikachu);   //Reset lai cac vung du lieu da danh dau truoc do cho viec Matching
                for (int t = Pikachu.cur.y - 1; t >= Pikachu.select.y; t--)
                {
                    if (Pikachu.Arr[Pikachu.cur.x][t] != -1)
                    {
                        resetBoard (Pikachu);   //Reset lai cac vung du lieu da danh dau truoc do cho viec Matching
                        return 0;
                    }

                    Pikachu.Arr[Pikachu.cur.x][t] = -3;  //Danh dau duong thang len
                }
                for (int p = Pikachu.cur.x + 1; p < Pikachu.select.x; p++)
                {
                    if (Pikachu.Arr[p][Pikachu.select.y] != -1)
                    {
                        resetBoard (Pikachu);   //Reset lai cac vung du lieu da danh dau
                        return 0;
                    }

                    Pikachu.Arr[p][Pikachu.select.y] = -2;   //Danh dau de ve duong thang ngang qua
                }

                Pikachu.Arr[Pikachu.cur.x][Pikachu.select.y] = -7;   //Danh dau giao diem
                return 1;
            }

            Pikachu.Arr[i][Pikachu.cur.y] = -2;  //Danh dau hang ngang de ve matching
        }

        //LEN
        for (int j = Pikachu.cur.y - 1; j > Pikachu.select.y; j--)
        {
            if (Pikachu.Arr[Pikachu.select.x][j] != -1)
            {
                resetBoard (Pikachu); //Reset lai cac vung du lieu da danh dau
                return 0;
            }
        }

        Pikachu.Arr[Pikachu.select.x][Pikachu.cur.y] = -5; //Danh dau giao diem
        return 1;
    }

    //Truong hop 3 + 4
    if (Pikachu.cur.x < Pikachu.select.x && Pikachu.cur.y < Pikachu.select.y)
    {
        //Truong hop 3: ngang - xuong: NGANG
        for (int i = Pikachu.cur.x + 1; i <= Pikachu.select.x; i++)
        {

            //Truong hop 4: xuong - ngang, neu gap o khong trong, se xet vao TH4
            if (Pikachu.Arr[i][Pikachu.cur.y] != -1)
            {
                resetBoard (Pikachu);   //Reset lai cac vung du lieu da danh dau truoc do cho viec Matching
                for (int t = Pikachu.cur.y + 1; t <= Pikachu.select.y; t++)
                {
                    if (Pikachu.Arr[Pikachu.cur.x][t] != -1)
                    {
                        resetBoard (Pikachu); //Reset lai cac vung du lieu da danh dau
                        return 0;
                    }
                    Pikachu.Arr[Pikachu.cur.x][t] = -3;   //Danh dau hang doc
                }
                for (int p = Pikachu.cur.x + 1; p < Pikachu.select.x; p++)
                {
                    if (Pikachu.Arr[p][Pikachu.select.y] != -1)
                    {
                        resetBoard (Pikachu); //Reset lai cac vung du lieu da danh dau
                        return 0;
                    }
                    Pikachu.Arr[p][Pikachu.select.y] = -2;      //Danh dau hang ngang
                }

                Pikachu.Arr[Pikachu.cur.x][Pikachu.select.y] = -6;      //Danh dau giao diem
                return 1;
            }

            Pikachu.Arr[i][Pikachu.cur.y] = -2;  //Danh dau hang ngang
        }

        //XUONG
        for (int j = Pikachu.cur.y + 1; j < Pikachu.select.y; j++)
        {
            if (Pikachu.Arr[Pikachu.select.x][j] != -1)
            {
                resetBoard (Pikachu); //Reset lai cac vung du lieu da danh dau
                return 0;
            }
            Pikachu.Arr[Pikachu.select.x][j] = -3; //Danh dau hang doc
        }
        Pikachu.Arr[Pikachu.select.x][Pikachu.cur.y] = -4;  //Danh dau giao diem
        return 1;
    }

    //Chia 4 truong hop 5 - 8 cho viec select ben trai cur
    //TH 5 + 6
    //Th 5: Ngang - len
    if (Pikachu.cur.x > Pikachu.select.x && Pikachu.cur.y > Pikachu.select.y)
    {
        //NGANG
        for(int i = Pikachu.cur.x - 1; i >= Pikachu.select.x; i--)
        {
            //Th6: Len - ngang: Neu di ngang gap o khong trong se vao TH6
            if(Pikachu.Arr[i][Pikachu.cur.y] != -1)
            {
                //LEN
                resetBoard (Pikachu);   //Reset lai cac vung du lieu da danh dau
                for (int t = Pikachu.cur.y - 1; t >= Pikachu.select.y; t--)
                {
                    if(Pikachu.Arr[Pikachu.cur.x][t] != -1)
                    {
                        resetBoard (Pikachu); //Reset lai cac vung du lieu da danh dau
                        return 0;
                    }
                    Pikachu.Arr[Pikachu.cur.x][t] = -3;
                }
                //NGANG
                for (int k = Pikachu.cur.x -  1; k > Pikachu.select.x; k--)
                {
                    if(Pikachu.Arr[k][Pikachu.select.y] != -1)
                    {
                        resetBoard (Pikachu); //Reset lai cac vung du lieu da danh dau
                        return 0;
                    }
                    Pikachu.Arr[k][Pikachu.select.y] = -2;      //Danh dau hang ngang
                }
                Pikachu.Arr[Pikachu.cur.x][Pikachu.select.y] = -4;   //Danh dau giao diem
                return 1;
            }
            Pikachu.Arr[i][Pikachu.cur.y] = -2;     //Danh dau hang ngang
        }

        //LEN
        for (int j = Pikachu.cur.y - 1; j > Pikachu.select.y; j--)
        {
            if (Pikachu.Arr[Pikachu.select.x][j] != -1)
            {
                resetBoard (Pikachu); //Reset lai cac vung du lieu da danh dau
                return 0;
            }
            Pikachu.Arr[Pikachu.select.x][j] = -3;      //Danh dau hang doc
        }
        Pikachu.Arr[Pikachu.select.x][Pikachu.cur.y] = -6;     //Danh dau giao diem
        return 1;
    }

    //Th 7 - 8
    //Th 7: Ngang - xuong
    if (Pikachu.cur.x > Pikachu.select.x && Pikachu.cur.y < Pikachu.select.y)
    {
        //NGANG
        for (int i = Pikachu.cur.x - 1; i >= Pikachu.select.x; i--)
        {

            //Th8: xuong - ngang; gap o khong trong se vao TH8
            if(Pikachu.Arr[i][Pikachu.cur.y] != -1)
            {
                //XUONG
                resetBoard (Pikachu);   //Reset lai cac vung du lieu da danh dau
                for (int t = Pikachu.cur.y + 1; t <= Pikachu.select.y; t++)
                {
                    if (Pikachu.Arr[Pikachu.cur.x][t] != -1)
                    {
                        resetBoard (Pikachu); //Reset lai cac vung du lieu da danh dau
                        return 0;
                    }
                    Pikachu.Arr[Pikachu.cur.x][t] = -3;     //Danh dau hang doc
                }

                //ngang
                for (int k = Pikachu.cur.x - 1; k > Pikachu.select.x; k--)
                {
                    if (Pikachu.Arr[k][Pikachu.select.y] != -1)
                    {
                        resetBoard (Pikachu); //Reset lai cac vung du lieu da danh dau
                        return 0;
                    }
                    Pikachu.Arr[k][Pikachu.select.y] = -2;      //Danh dau hang ngang
                }
                Pikachu.Arr[Pikachu.cur.x][Pikachu.select.y] = -5;      //Danh dau giao diem
                return 1;
            }
            Pikachu.Arr[i][Pikachu.cur.y] = -2;     //Danh dau hang ngang
        }
        //XUONG
        for (int j = Pikachu.cur.y + 1; j < Pikachu.select.y; j++)
        {
            if(Pikachu.Arr[Pikachu.select.x][j] != -1)
            {
                resetBoard (Pikachu); //Reset lai cac vung du lieu da danh dau
                return 0;
            }
            Pikachu.Arr[Pikachu.select.x][j] = -3;      //Danh dau hang doc
        }
        Pikachu.Arr[Pikachu.select.x][Pikachu.cur.y] = -7;    //Danh dau giao diem
        return 1;
    }
    resetBoard (Pikachu); //Double check!
    return 0;
}

bool matchShapeZ (Board& Pikachu)
{

    //Se co 8 truong hop, tuong tu L
    //De ap dung loai Z, hai diem khong duoc thang hang
    if (Pikachu.cur.x == Pikachu.select.x || Pikachu.cur.y == Pikachu.select.y)
    {
        return 0;
    }

    //Gop 8 truong hop thanh 4 truong hop bang cach ep vi tri co toa do x nho hon thanh vi tri cua Pikachu.cur, sau do xet tu trai sang phai
    if (Pikachu.cur.x > Pikachu.select.x)
    {

        //Khai bao 2 bien tam de luu thong tin cho buoc xu ly tiep theo
        Coordinate temp;

        temp = Pikachu.cur;
        Pikachu.cur = Pikachu.select;       //Hoa doi hai vi tri
        Pikachu.select = temp;
    }

    //select ben tren
    if (Pikachu.cur.y > Pikachu.select.y)
    {

        //th1: ngang - len - ngang
        //NGANG
        for (int i = Pikachu.cur.x + 1; i < Pikachu.select.x; i++)
        {
            if (Pikachu.Arr[i][Pikachu.cur.y] != -1)
            {
                resetBoard (Pikachu);   //Reset lai cac vung du lieu da danh dau
                break;
            }
            else
            {
                Pikachu.Arr[i][Pikachu.cur.y] = -2;     //Danh dau hang ngang
                int j;

                //LEN
                for (j = Pikachu.cur.y - 1; j > Pikachu.select.y; j--)
                {
                    if(Pikachu.Arr[i][j] != -1)
                    {
                        break;
                    }
                }
                //Toi duoc vi tri dinh
                if(j == Pikachu.select.y)
                {
                    int k = i;

                    //NGANG
                    for (k; k < Pikachu.select.x; k++)
                    {
                        if (Pikachu.Arr[k][Pikachu.select.y] != -1)
                        {
                            break;
                        }
                    }
                    //Da duyet den phan tu cuoi cung
                    if (k == Pikachu.select.x)
                    {
                        //Doc
                        for (j = Pikachu.cur.y - 1; j > Pikachu.select.y; j--)
                        {
                            Pikachu.Arr[i][j] = -3;     //Danh dau hang doc
                        }

                        for (k = i; k < Pikachu.select.x; k++)
                        {
                            Pikachu.Arr[k][Pikachu.select.y] = -2;
                        }

                        Pikachu.Arr[i][Pikachu.cur.y] = -5;
                        Pikachu.Arr[i][Pikachu.select.y] = -7;
                        return 1;
                    }
                }
            }
        }

        //th2: len - ngang - len
        //LEN
        for(int i = Pikachu.cur.y - 1; i > Pikachu.select.y; i--)
        {
            if(Pikachu.Arr[Pikachu.cur.x][i] != -1)
            {
                resetBoard(Pikachu);       //Reset vung du lieu da danh dau
                break;
            }
            else
            {
                Pikachu.Arr[Pikachu.cur.x][i] = -3;     //Danh dau hang doc
                int j = Pikachu.cur.x + 1;
                //NGANG
                for(; j < Pikachu.select.x; j++)
                {
                    if(Pikachu.Arr[j][i] != -1)
                    {
                        break;
                    }
                }
                if (j == Pikachu.select.x)
                {
                    int k = i;
                    for(; k > Pikachu.select.y; k--)
                    {
                        if(Pikachu.Arr[Pikachu.select.x][k] != -1)
                        {
                            break;
                        }
                    }
                    if (k == Pikachu.select.y)
                    {
                        //Doc
                        for(k = i; k > Pikachu.select.y; k--)
                        {
                            Pikachu.Arr[Pikachu.select.x][k] = -3;     //Danh dau hang doc
                        }
                        //Ngang
                        for(j = Pikachu.cur.x + 1; j < Pikachu.select.x; j++)
                        {
                            Pikachu.Arr[j][i] = -2;         //Danh dau hang ngang
                        }
                        Pikachu.Arr[Pikachu.cur.x][i] = -7;
                        Pikachu.Arr[Pikachu.select.x][i] = -5;
                        return 1;
                    }
                }
            }
        }
    }

    //Pikachu.select ben duoi Pikachu.cur
    else if (Pikachu.cur.y < Pikachu.select.y)
    {

        //th3: ngang - xuong - ngang
        //NGANG
        for (int i = Pikachu.cur.x + 1; i < Pikachu.select.x; i++)
        {
            if (Pikachu.Arr[i][Pikachu.cur.y] != -1)
            {
                resetBoard(Pikachu);
                break;
            }
            else
            {
                Pikachu.Arr[i][Pikachu.cur.y] = -2;
                int j;
                //XUONG
                for (j = Pikachu.cur.y + 1; j < Pikachu.select.y; j++)
                {
                    if(Pikachu.Arr[i][j] != -1)
                    {
                        break;
                    }
                }
                if(j == Pikachu.select.y)
                {
                    int k = i;
                    //NGANG
                    for (k; k < Pikachu.select.x; k++)
                    {
                        if (Pikachu.Arr[k][Pikachu.select.y] != -1)
                        {
                            break;
                        }
                    }
                    if (k == Pikachu.select.x)
                    {
                        //Ngang
                        for (k = i; k < Pikachu.select.x; k++)
                        {
                            Pikachu.Arr[k][Pikachu.select.y] = -2;     //Danh dau hang ngang
                        }
                        //Doc
                        for (j = Pikachu.cur.y + 1; j < Pikachu.select.y; j++)
                        {
                            Pikachu.Arr[i][j] = -3;

                        }
                        Pikachu.Arr[i][Pikachu.cur.y] = -4;
                        Pikachu.Arr[i][Pikachu.select.y] = -6;
                        return 1;
                    }
                }
            }
        }

        //th4: xuong - ngang - xuong
        //Xuong
        for(int i = Pikachu.cur.y + 1; i < Pikachu.select.y; i++)
        {
            if(Pikachu.Arr[Pikachu.cur.x][i] != -1)
            {
                resetBoard(Pikachu);
                break;
            }
            else
            {
                Pikachu.Arr[Pikachu.cur.x][i] = -3;
                int j = Pikachu.cur.x + 1;

                //Ngang
                for(; j < Pikachu.select.x; j++)
                {
                    if(Pikachu.Arr[j][i] != -1)
                    {
                        break;
                    }
                }
                if (j == Pikachu.select.x)
                {
                    int k = i;

                    //Xuong
                    for(; k < Pikachu.select.y; k++)
                    {
                        if(Pikachu.Arr[Pikachu.select.x][k] != -1)
                        {
                            break;
                        }
                    }
                    if (k == Pikachu.select.y)
                    {
                        //Xuong
                        for(k = i; k < Pikachu.select.y; k++)
                        {
                            Pikachu.Arr[Pikachu.select.x][k] = -3;
                        }

                        //Ngang
                        for(j = Pikachu.cur.x + 1; j < Pikachu.select.x; j++)
                        {
                            Pikachu.Arr[j][i] = -2;
                        }
                        Pikachu.Arr[Pikachu.cur.x][i] = -6;
                        Pikachu.Arr[Pikachu.select.x][i] = -4;
                        return 1;
                    }
                }
            }
        }
    }
    resetBoard(Pikachu);
    return 0;
}

bool matchShapeU (Board& Pikachu)
{

    //Hoan doi vi tri sao cho vi tri diem Pikachu.select luon ben phai cua Pikachu.cur
    if (Pikachu.cur.x > Pikachu.select.x)
    {
        //Khai bao 2 bien tam de luu thong tin cho buoc xu ly tiep theo
        Coordinate temp;

        temp = Pikachu.cur;

        Pikachu.cur = Pikachu.select;

        Pikachu.select = temp;
    }

    //Th1 : len - ngang - xuong
    //LEN
    for (int i = Pikachu.cur.y - 1; i >= 0; i--)
    {
        if (Pikachu.Arr[Pikachu.cur.x][i] != -1)
        {
            break;
        }

        if(i != 0)
        {
            Pikachu.Arr[Pikachu.cur.x][i] = -3;      //Danh dau hang doc len
        }
        //NGANG
        int j = Pikachu.cur.x + 1;
        for (; j < Pikachu.select.x; j++)
        {
            if (Pikachu.Arr[j][i] != -1)
            {
                break;
            }
        }
        if (j == Pikachu.select.x)
        {
            //XUONG
            int k = i;
            for (; k < Pikachu.select.y; k++)
            {
                if (Pikachu.Arr[Pikachu.select.x][k] != -1)
                {
                    break;
                }
            }
            //Du dieu kien Matching
            if (k == Pikachu.select.y)
            {
                if (i != 0)
                {
                    //ngang
                    for (j = Pikachu.cur.x + 1; j < Pikachu.select.x; j++)
                    {
                        Pikachu.Arr[j][i] = -2;     //Danh dau hang ngang
                    }

                    Pikachu.Arr[Pikachu.cur.x][i] = -7;     //Danh dau cac giao diem
                    Pikachu.Arr[Pikachu.select.x][i] = -4;
                }
                //xuong
                for (k = i + 1; k < Pikachu.select.y; k++)
                {
                    if(k != 0)
                    {
                        Pikachu.Arr[Pikachu.select.x][k] = -3;    //Danh dau hang doc xuong
                    }
                }
                return 1;
            }
        }
    }
    resetBoard(Pikachu);  //Reset du lieu da danh dau

    //Th2: Xuong - ngang - len
    //XUONG
    for (int i = Pikachu.cur.y + 1; i <= Pikachu.size + 1; i++)
    {
        if (Pikachu.Arr[Pikachu.cur.x][i] != -1)
        {
            break;
        }
        Pikachu.Arr[Pikachu.cur.x][i] = -3;

        //Ngang;
        int j = Pikachu.cur.x + 1;
        for (; j < Pikachu.select.x; j++)
        {
            if(Pikachu.Arr[j][i] != -1)
            {
                break;
            }
        }
        if (j == Pikachu.select.x)
        {

            //len
            int k = i;
            for (; k > Pikachu.select.y; k--)
            {
                if (Pikachu.Arr[j][k] != -1)
                {
                    break;
                }
            }
            if(k == Pikachu.select.y)
            {
                //Ngang
                for (j = Pikachu.cur.x + 1; j < Pikachu.select.x; j++)
                {
                    Pikachu.Arr[j][i] = -2;     //Danh dau hang ngang
                }
                //Doc
                for (k = i; k > Pikachu.select.y; k--)
                {
                    Pikachu.Arr[j][k] = -3;     //Danh dau hang doc
                }
                Pikachu.Arr[Pikachu.cur.x][i] = -6;     //Danh dau cac giao diem
                Pikachu.Arr[Pikachu.select.x][i] = -5;
                return 1;
            }
        }
    }
    resetBoard(Pikachu);

    //Th3: ngang qua phai
    //Ngang
    for (int i = Pikachu.cur.x + 1; i <= Pikachu.size + 1; i++)
    {
        if (Pikachu.Arr[i][Pikachu.cur.y] != -1)
        {
            break;
        }
        Pikachu.Arr[i][Pikachu.cur.y] = -2;         //Danh dau hang ngang
        //Duyet ngang qua phai den khi nao i vuot qua Pikachu.select.x
        if (i > Pikachu.select.x)
        {
            //Truong hop Pikachu.select nam ben tren cua Pikachu.cur --> di len
            if (Pikachu.cur.y > Pikachu.select.y)
            {
                int j = Pikachu.cur.y - 1;
                for (; j > Pikachu.select.y; j--)
                {
                    if (Pikachu.Arr[i][j] != -1)
                    {
                        break;
                    }
                }
                if (j == Pikachu.select.y)
                {
                    int k = i;
                    for (; k > Pikachu.select.x; k--)
                    {
                        if (Pikachu.Arr[k][j] != -1)
                        {
                            break;
                        }
                    }
                    if (k == Pikachu.select.x)
                    {
                        //Doc
                        for (j = Pikachu.cur.y - 1; j > Pikachu.select.y; j--)
                        {
                            Pikachu.Arr[i][j] = -3;         //Danh dau hang doc
                        }
                        //Ngang
                        for (k = i; k > Pikachu.select.x; k--)
                        {
                            Pikachu.Arr[k][j] = -2;     //Danh dau hang ngang
                        }
                        Pikachu.Arr[i][Pikachu.cur.y] = -5;         //Danh dau cac giao diem
                        Pikachu.Arr[i][Pikachu.select.y] = -4;
                        return 1;
                    }
                }
            }

            //Truong hop Pikachu.select nam ben duoi cua Pikachu.cur
            if (Pikachu.cur.y < Pikachu.select.y)
            {
                int j = Pikachu.cur.y + 1;
                for (; j < Pikachu.select.y; j++)
                {
                    if (Pikachu.Arr[i][j] != -1)
                    {
                        break;
                    }
                }
                if (j == Pikachu.select.y)
                {
                    int k = i;
                    for (; k > Pikachu.select.x; k--)
                    {
                        if (Pikachu.Arr[k][j] != -1)
                        {
                            break;
                        }
                    }
                    if (k == Pikachu.select.x)
                    {
                        //DOC
                        for (j = Pikachu.cur.y + 1; j < Pikachu.select.y; j++)
                        {
                            Pikachu.Arr[i][j] = -3;     //Danh dau hang doc
                        }
                        //NGANG
                        for (k = i; k > Pikachu.select.x; k--)
                        {
                            Pikachu.Arr[k][j] = -2;     //Danh dau hang ngang
                        }
                        Pikachu.Arr[i][Pikachu.cur.y] = -4;         //Danh dau cac giao diem
                        Pikachu.Arr[i][Pikachu.select.y] = -5;
                        return 1;
                    }
                }
            }
        }
    }
    resetBoard(Pikachu);

    //Th4 ngang qua trai
    for (int i = Pikachu.cur.x - 1; i >= 0; i--)
    {
        if (Pikachu.Arr[i][Pikachu.cur.y] != -1)
        {
            break;
        }
        Pikachu.Arr[i][Pikachu.cur.y] = -2;     // danh dau hang ngang

        //Truong hop Pikachu.select nam duoi Pikachu.cur
        if (Pikachu.cur.y < Pikachu.select.y)
        {
            int j = Pikachu.cur.y + 1;
            for (; j < Pikachu.select.y; j++)
            {
                if (Pikachu.Arr[i][j] != -1)
                {
                    break;
                }
            }

            //neu duyet duoc toi vi tri toa do bang Pikachu.select.y thi tiep tuc duyet ngang
            if (j == Pikachu.select.y)
            {
                int k = i;
                for (; k < Pikachu.select.x; k++)
                {
                    if (Pikachu.Arr[k][Pikachu.select.y] != -1)
                    {
                        break;
                    }
                }
                if (k == Pikachu.select.x)
                {
                    //Hang doc
                    for (j = Pikachu.cur.y + 1; j < Pikachu.select.y; j++)
                    {
                        Pikachu.Arr[i][j] = -3;     //Danh dau hang doc
                    }
                    //Hang ngang
                    for (; k < Pikachu.select.x; k++)
                    {
                        Pikachu.Arr[k][Pikachu.select.y] = -2;     //Danh dau hang doc
                    }

                    Pikachu.Arr[i][Pikachu.cur.y] = -7;     //Danh dau cac giao diem
                    Pikachu.Arr[i][Pikachu.select.y] = -6;
                    return 1;
                }
            }
        }

        //Truong hop Pikachu.select nam tren Pikachu.cur
        else if (Pikachu.cur.y > Pikachu.select.y)
        {
            int j = Pikachu.cur.y - 1;
            for (; j > Pikachu.select.y; j--)
            {
                if (Pikachu.Arr[i][j] != -1)
                {
                    break;
                }
            }

            //neu duyet duoc toi vi tri toa do bang Pikachu.select.y thi tiep tuc duyet ngang
            if (j == Pikachu.select.y)
            {
                int k = i;
                for (; k < Pikachu.select.x; k++)
                {
                    if (Pikachu.Arr[k][Pikachu.select.y] != -1)
                    {
                        break;
                    }
                }
                if (k == Pikachu.select.x)
                {
                    //Doc
                    for (j = Pikachu.cur.y - 1; j > Pikachu.select.y; j--)
                    {
                        Pikachu.Arr[i][j] = -3;     //Danh dau hang doc
                    }
                    //Ngang
                    for (k = i; k < Pikachu.select.x; k++)
                    {
                        Pikachu.Arr[k][Pikachu.select.y] = -2;      //Danh dau hang ngang
                    }

                    Pikachu.Arr[i][Pikachu.cur.y] = -6;     //Danh dau cac giao diem
                    Pikachu.Arr[i][Pikachu.select.y] = -7;
                    return 1;
                }
            }
        }
    }
    resetBoard(Pikachu);
    return 0;
}

bool matchWholeShape (Board& Pikachu, int start_point)
 {

     //Trung vi tri thi in ra thong bao va ngung xu ly
    if (Pikachu.cur.x == Pikachu.select.x && Pikachu.cur.y == Pikachu.select.y)
    {
     gotoXY (0, 0);
     cout << "Khong duoc chon lai vi tri cu!   ";
     return 0;
    }

    Coordinate sub_cur, sub_select;
    sub_cur = Pikachu.cur;
    sub_select = Pikachu.select;

    //    Loai I
    if(matchShapeI(Pikachu))
    {
        gotoXY (0, 0);
        cout << "Match loai I                   ";
        drawLine(Pikachu, start_point);
        return 1;
    }

    //    Loai L
    if(matchShapeL(Pikachu))
    {
        gotoXY (0, 0);
        cout << "Match loai L                  ";
        drawLine(Pikachu, start_point);
        return 1;
    }

    //    Loai Z
    if(matchShapeZ(Pikachu))
    {
        gotoXY (0, 0);
        cout << "Match loai Z                 ";
        drawLine(Pikachu, start_point);

        Pikachu.cur = sub_cur;
        Pikachu.select = sub_select;
        return 1;
    }
    //  Loai U
    if(matchShapeU(Pikachu))
    {
        gotoXY (0, 0);
        cout << "Match loai U                   ";
        drawLine(Pikachu, start_point);

        Pikachu.cur = sub_cur;
        Pikachu.select = sub_select;
        return 1;
    }

    //Truong hop khong thuoc loai matching nao
    gotoXY (0, 0);
    cout << "Khong thuoc loai matching nao!  ";

    Pikachu.cur = sub_cur;
    Pikachu.select = sub_select;
    return 0;
}

void drawFrame (int pos_x, int pos_y, string str)
{
    for (int i = pos_x + 1; i < pos_x + 17; i++)
    {
        gotoXY(i, pos_y - 1);
        cout << '_';
        gotoXY(i, pos_y + 1);
        cout << '_';
    }
    for (int j = pos_y; j < pos_y + 2; j++)
    {
        gotoXY(pos_x, j);
        cout << '|';
        gotoXY(pos_x + 17, j);
        cout << '|';
    }
    gotoXY(pos_x + 3, pos_y);
    cout << str;
}


//Ham ve hinh chu nhat
void drawRec(int begin_x, int begin_y, int end_x, int end_y, char ch_1, char ch_2)
{
    //Ve cac duong thang ngang
    for (int i = begin_x + 1; i < end_x; i++)
    {
        gotoXY(i , begin_y);
        cout << ch_1;
        gotoXY(i, end_y);
        cout << ch_1;
    }

    //Ve cac doan thang xuong
    for (int j = begin_y + 1 ; j < end_y ; j++)
    {
        gotoXY(begin_x, j);
        cout << ch_2;
        gotoXY(end_x, j);
        cout << ch_2;
    }
}

void highLightBlock(Coordinate select, int **arr, int color, int start_point)
{
    Coordinate pos;
    pos.x = start_point + 9 * (select.x - 1);
    pos.y = 5 * (select.y - 1);

    changeColor(color | FOREGROUND_INTENSITY);
    for (int i = pos.x + 1; i < pos.x + 8 ; i++)
    {
        for(int j = pos.y + 1; j < pos.y + 4; j++)
        {
            gotoXY(i, j);
            cout << " ";
        }
    }
    gotoXY(pos.x + 4, pos.y + 2);
    if(arr[select.x][select.y] == -1)
    {
        cout << " ";
    }
    else
    {
        cout << char('A' + arr[select.x][select.y]);
    }
    changeColor(BACKGROUND_BLACK | FOREGROUND_WHITE);
}

//Ve man hinh bat dau
void drawMenu(int middle)
{
    int left;
    Coordinate first;
    left = middle - 7;
    first.x = middle - 3;
    first.y = 21;

    for (int i = 20; i >= 0; i--)
    {
    //Ve tieu de
        if (i % 2 == 0)
        {
            changeColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        }
        else changeColor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);

        gotoXY(left - 40 - 2 * i, 0);
        cout << "|||||||||     ||||||   |||     ||| |||||||||| ||||       ||||    ||||||    ||| ||     || ||";
        gotoXY(left - 40 - 2 * i, 1);
        cout << " ||      || ||      ||   ||   ||    ||          ||||    ||||   ||      ||    || ||     ||";
        gotoXY(left - 40 - 2 * i, 2);
        cout << " ||      || ||      ||   ||  ||     ||          || ||  || ||   ||      ||    ||  ||    ||";
        gotoXY(left - 40 - 2 * i, 3);
        cout << " ||      || ||      ||   || ||      ||   |      ||  ||||  ||   ||      ||    ||   ||   ||";
        gotoXY(left - 40 - 2 * i, 4);
        cout << " ||||||||   ||  ||  ||   ||||       |||||||     ||   ||   ||   ||  ||  ||    ||    ||  ||";
        gotoXY(left - 40 - 2 * i, 5);
        cout << " ||         ||      ||   || ||      ||   |      ||        ||   ||      ||    ||     || ||";
        gotoXY(left - 40 - 2 * i, 6);
        cout << " ||         ||      ||   ||  ||     ||          ||        ||   ||      ||    ||      ||||";
        gotoXY(left - 40 - 2 * i, 7);
        cout << " ||         ||      ||   ||   ||    ||          ||        ||   ||      ||    ||       |||";
        gotoXY(left - 40 - 2 * i, 8);
        cout << "||||          ||||||    ||||  |||| |||||||||| |||||      |||||   ||||||    || ||    ||  ||";

        Sleep (150);

        if (i != 0)
        {
            system("cls");
        }
    }

    for (int i = 0; i < 5; i++)
    {
        changeColor(2 + i | FOREGROUND_INTENSITY);

        drawFrame (left, 16, "PIKACHU GAME");
        gotoXY(left + 7, 17);
        cout << "MENU";
        Sleep (100);
        drawFrame (left, 20, "   BAT DAU");
        Sleep (100);
        drawFrame (left, 22, "  TIEP TUC");
        Sleep (100);
        drawFrame (left, 24, " THANH TICH");
        Sleep (100);
        drawFrame (left, 26, "     BXH");
        Sleep (100);
        drawFrame (left, 28, "    THOAT");
    }

    changeColor (BACKGROUND_BLACK || FOREGROUND_WHITE);
    selectOption(first);
}

//lam noi bat khung chon menu
void selectOption (Coordinate select)
{
    changeColor(FOREGROUND_RED | FOREGROUND_INTENSITY );

    gotoXY(select.x, select.y);
    for (int i = select.x; i < select.x + 10; i++)
    {
    cout << "-";
    }

    gotoXY(select.x, select.y - 2);
    for (int i = select.x; i < select.x + 10; i++)
    {
        cout << "-";
    }

    _getch();
    changeColor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
}

bool subMatching (Board Pikachu)
{
    return (matchShapeI(Pikachu) || matchShapeL(Pikachu) || matchShapeU(Pikachu) || matchShapeZ(Pikachu));
}
//Tinh nang swap
void swapPokemon (Board& Pikachu)
{
    swap (Pikachu.Arr[Pikachu.select.x][Pikachu.select.y],Pikachu.Arr[Pikachu.cur.x][Pikachu.cur.y]);    //Hoan doi 2 gia tri
    Pikachu.select = {-1, -1};      //Reset vung chon
}


//Tinh nang goi y
void suggestionFunction(Board Pikachu, int start_point)
{
    //Xet tu vi tri dau tien
    for(int i = 1; i <= Pikachu.size; i++)
    {
        for (int j = 1; j <= Pikachu.size; j++)
        {

            //Neu no la mot o co Pokemon thi gan cho select
            if(Pikachu.Arr[i][j] != -1)
            {
                Pikachu.select = {i, j};    //Gan toa do cho select
                //Duyet tu phtu phia sau select den phtu cuoi cung cua mang
                for(int m = i; m <= Pikachu.size; m++)
                {
                    int n;

                    if (m == i)
                    {
                        n = j + 1;
                    }
                    else
                    {
                        n = 1;
                    }

                    for (; n <= Pikachu.size; n++)
                    {
                        //Neu duyet den phtu bang phtu kia thi gan cho cur va xet xem no co matching khong
                        if(Pikachu.Arr[m][n] == Pikachu.Arr[Pikachu.select.x][Pikachu.select.y])
                        {
                            Pikachu.cur = {m, n};   //Gan toa do cho cur
                            if (matchWholeShape(Pikachu, start_point) == 1)      //Neu 2 o match duoc voi nhau
                            {
                                highLightBlock (Pikachu.cur, Pikachu.Arr, 251, start_point);        //Highlight 2 o match duoc vs nhau
                                highLightBlock (Pikachu.select, Pikachu.Arr, 251, start_point);
                                return;
                            }
                            //Tra lai cac gia tri ban dau
                            //resetBoard(Pikachu);
                        }
                    }
                }
            }
        }
    }
}

//Ham kiem tra xem co con nhung Pokemon co the matching duoc voi nhau duoc hay khong
bool isDone (Board Pikachu, int start_point)
{
    //Xet tu vi tri dau tien
    for(int i = 1; i <= Pikachu.size; i++)
    {
        for (int j = 1; j <= Pikachu.size; j++)
        {

            //Neu no la mot o co Pokemon thi gan cho select
            if(Pikachu.Arr[i][j] != -1)
            {
                Pikachu.select = {i, j};    //Gan toa do cho select
                //Duyet tu phtu phia sau select den phtu cuoi cung cua mang
                for(int m = i; m <= Pikachu.size; m++)
                {
                    int n;

                    if (m == i)
                    {
                        n = j + 1;
                    }
                    else
                    {
                        n = 0;
                    }

                    for (; n <= Pikachu.size; n++)
                    {
                        //Neu duyet den phtu bang phtu kia thi gan cho cur va xet xem no co matching khong
                        if(Pikachu.Arr[m][n] == Pikachu.Arr[Pikachu.select.x][Pikachu.select.y])
                        {
                            Pikachu.cur = {m, n};   //Gan toa do cho cur
                            if (subMatching(Pikachu))      //Neu 2 o match duoc voi nhau
                            {
                                //Tra lai cac gia tri ban dau
                                resetBoard(Pikachu);
                                return true;     //Tra lai true neu nhu con cap matching
                            }
                            //Tra lai cac gia tri ban dau
                            resetBoard(Pikachu);
                        }
                    }
                }
            }
        }
    }
    //Sau khi kiem tra toan bo bang nhung khong phat hien ra cac cap matching thi return false
    return false;
}

//Ham nay kiem tra xem bang dang xet co con matching nao khong, neu khong con no se tien hanh swap  cac Pokemon trong bang den khi nao co cap matching
void swapBoard (Board& Pikachu, int start_point)
{
    if (isDone(Pikachu, start_point))
        return;
    else
    {
        while (true)
        {
            int i, j;
            i = rand() % (Pikachu.size + 1);
            j = rand() % (Pikachu.size + 1);

            if(Pikachu.Arr[i][j] != -1)
            {
                Pikachu.select = {i, j};
            }
            else
            {
                continue;
            }

            while(true)
            {
                i = rand() % (Pikachu.size + 1);
                j = rand() % (Pikachu.size + 1);

                if(Pikachu.Arr[i][j] != -1)
                {
                    Pikachu.cur = {i, j};
                    swapPokemon(Pikachu);
                    drawBoard(Pikachu, start_point);
                    return swapBoard(Pikachu, start_point);
                }
            }
        }
    }
}

//leaderboard
void changeTime(int t)
{
	    	int h = 0, m = 0, s = 0;
	    	while(t >= 3600){
	    		h++;
	    		t -= 3600;
			}
			while(t >= 60){
				m++;
				t -= 60;
			}
			s = t;
			cout << h << ":" << m << ":";
			if(s < 10)
				cout << "0" << s;
			else
				cout << s;
}

void titleLeaderBoard()
{
	gotoXY(56, 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "LEADERBOARD";
    gotoXY(25, 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "NAME";
    gotoXY(59, 6);
    cout << "POINT";
    gotoXY(94, 6);
    cout << "TIME";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    gotoXY(25, 7);
    for (int i = 0; i < 75; i++) {
        cout << "=";
    }
}

void readLeaderBoard()
{
	ifstream f;
    f.open("leaderboard.txt");
    if (f) {
        player p;

        int i = 0;
        while (getline(f, p.name, ' ')) {
            f >> p.point;
            f.get();
            gotoXY(26, 7 + i);
            for (int j = 0; j < 75; j++) {
                cout << "=";
            }
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10 - i / 2);
            gotoXY(26, 8 + i);
            cout << p.name;
            gotoXY(60, 8 + i);
            cout << p.point;
            gotoXY(92, 8 + i);
        	changeTime(3000 - p.point);
		    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            i += 2;
        }
        f.close();
    }
    _getch();
    system("cls");
}

void writeLeaderBoard(player p)
{
    ifstream fin("leaderboard.txt");
    if (fin) {
        player* list = new player[10];
        int no_player = 0;
        string s;

        while (getline(fin, s, ' ')) {
            list[no_player].name = s;
            fin >> list[no_player].point;
            fin.get();
            no_player++;
        }

        int index = no_player - 1;
        for (index; index >= 0; index--) {
            if (p.point <= list[index].point) {
                break;
            }
        }

        if (no_player < 10) {
            for (int i = no_player; i > index + 1; i--) {
                list[i] = list[i - 1];
            }
            list[index + 1] = p;
            no_player++;
        }
        else {
            if (index != no_player - 1) {
                for (int i = no_player - 1; i > index + 1; i--) {
                    list[i] = list[i - 1];
                }
                list[index + 1] = p;
            }
        }
        fin.close();


        ofstream fout("leaderboard.txt");

        for (int i = 0; i < no_player; i++) {
            fout << list[i].name << " " << list[i].point << endl;
        }

        fout.close();

        delete[]list;
    }
    else {
        ofstream fout("leaderboard.txt");
        fout << p.name << " " << p.point << endl;
        fout.close();
    }
}

void getBackground1(char bg1[][36])
{
    ifstream fin("pika.txt");
    if (fin) {
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 36; j++)
            {
                bg1[i][j] = fin.get();
            }
            fin.ignore();
        }
        fin.close();
    }
    else {
        memset(bg1, ' ', sizeof(bg1));
    }
}

void getBackground2(char bg2[][55])
{
    ifstream fin("charidza54.txt");
    if (fin) {
        for (int i = 0; i < 24; i++)
        {
            for (int j = 0; j < 55; j++)
            {
                bg2[i][j] = fin.get();
            }
            fin.ignore();
        }
        fin.close();
    }
    else {
        memset(bg2, ' ', sizeof(bg2));
    }
}

void getBackground3(char bg3[][72])
{
    ifstream fin("lucario.txt");
    if (fin) {
        for (int i = 0; i < 45; i++)
        {
            for (int j = 0; j < 56; j++)
            {
                bg3[i][j] = fin.get();
            }
            fin.ignore();
        }
        fin.close();
    }
    else {
        memset(bg3, ' ', sizeof(bg3));
    }
}

void printWin()
{
    changeColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << R"(
              __     ______  _    _            _____  ______
              \ \   / / __ \| |  | |     /\   |  __ \|  ____|
               \ \_/ / |  | | |  | |    /  \  | |__) | |__
                \   /| |  | | |  | |   / /\ \ |  _  /|  __|
                 | | | |__| | |__| |  / ____ \| | \ \| |____
              ___|_|_ \____/ \____/  /_/__  \_\_|_ \_\______|____
             |__   __| |  | |  ____| |  _ \|  ____|/ ____|__   __|
                | |  | |__| | |__    | |_) | |__  | (___    | |
                | |  |  __  |  __|   |  _ <|  __|  \___ \   | |
                | |  | |  | | |____  | |_) | |____ ____) |  | |
                |_|  |_|  |_|______| |____/|______|_____/   |_|


   )";
    changeColor(FOREGROUND_BLACK);
}

void print(Coordinate select, int start_point, int size)
{
	int pos_x = start_point + 9 * (select.x - 1);
    int pos_y = 5 + 5 * (select.y - 1);
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 9; j++){
			gotoXY(pos_x + j, pos_y + i);
			if(size == 4)
				cout << bg1[i +(select.y - 1) * 4][j + (select.x - 1) * 9];
			if(size == 6)
				cout << bg2[i +(select.y - 1) * 4][j + (select.x - 1) * 9];
			if(size == 8)
				cout << bg3[i +(select.y - 1) * 4][j + (select.x - 1) * 9];
		}
	}
}

void print1(int start_point)
{
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 37; j++){
			gotoXY(start_point + j - 1, 5 + i);
			cout << bg1[i][j - 1];
		}
		Sleep(100);
	}
}

void print2(int start_point)
{
	for(int i = 0; i < 24; i++){
		for(int j = 0; j < 55; j++){
			gotoXY(start_point + j - 1, 5 + i);
			cout << bg2[i][j - i];
			//Sleep(1);
		}
		Sleep(100);
	}
}

void print3(int start_point)
{
	for(int i = 0; i < 40; i++){
		for(int j = 0; j < 56; j++){
			gotoXY(start_point + j - 1, 5 + i);
			cout << bg3[i][j - 1];
			//Sleep(1);
		}
		Sleep(50);
	}
}

//thu hoi bo nho
void deleleDinamicArr(Board Pikachu)
{
    for (int i = 0; i <= Pikachu.size + 1; i++)
    {
        delete[] Pikachu.Arr[i];
    }
}
