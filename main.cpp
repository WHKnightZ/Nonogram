#include <graphics.h>
#include <conio.h>

#define MAXX 800
#define MAXY 690
#define BGC 3

char NumText[][3] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14",
                     "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25"};
char WinText[][10] = {"You Lose!", "You Win!"};
char DifChar[] = {'E', 'N', 'H'};
char DifText[][7] = {"Easy", "Normal", "Hard"};
char TxtNono[] = "Nono";
char TxtGram[] = "Gram";
char TxtPlay[] = "Play";
char Txt1[] = "1";
char TxtMenu[] = "Menu";
char TxtChooseDifficult[] = "Choose Difficult:";
char TxtLock[] = "Lock";
char TxtX[] = "X";

int StartX, StartY, Width, X, Y;
int Row[9][9], Column[9][9], CountR[9], CountC[9], Table[9][9], LockLv[3];
int Level, DInt;
char DChar;

int Max(int x, int y) {
    return x > y ? x : y;
}

void BackGround() {
    int n = 8;
    setcolor(8);
    setfillstyle(1, BGC);
    for (int i = 1; i < n; i++)
        rectangle(i, i, MAXX - i, MAXY - i);
    bar(n + 1, n + 1, MAXX - n, MAXY - n);
}

void DrawFrame() {
    setfillstyle(1, 7);
    setcolor(8);
    bar(StartX + 1, StartY + 1, StartX + X * Width, StartY + Y * Width);
    for (int i = 0; i <= X; i++)
        line(StartX + i * Width, StartY, StartX + i * Width, StartY + Y * Width + 1);
    for (int i = 0; i <= Y; i++)
        line(StartX, StartY + i * Width, StartX + X * Width, StartY + i * Width);
    setcolor(0);
    rectangle(StartX - 2, StartY - 2, StartX + X * Width + 2, StartY + Y * Width + 2);
    rectangle(StartX - 3, StartY - 3, StartX + X * Width + 3, StartY + Y * Width + 3);
}

void CorrectCell(int a, int b) {
    a = StartX + a * Width - 1;
    b = StartY + b * Width - 1;
    setfillstyle(1, 8);
    bar(a + 3, b + 3, a + Width, b + Width);
}

void ErrorCell(int a, int b) {
    a = StartX + a * Width - 10;
    b = StartY + b * Width - 10;
    setcolor(0);
    line(a + 20, b + 20, a + Width, b + Width);
    line(a + Width, b + 20, a + 20, b + Width);
}

void WinLose(int num) {
    setbkcolor(11);
    settextstyle(10, 0, 5);
    setfillstyle(1, 11);
    setcolor(5);
    rectangle(248, 258, 552, 402); //-2,-2,+2,+2
    rectangle(249, 259, 551, 401); //-1,-1,+1,+1
    setcolor(9);
    rectangle(250, 260, 550, 400);
    rectangle(251, 261, 549, 399); //+1,+1,-1,-1
    bar(252, 262, 549, 399);       //+2,+2,-1,-1
    setcolor(0);
    outtextxy(290 + num * 18, 305, WinText[num]);
}

void DrawLife() {
    float f = 1.4142135;
    int i = 4 * f;
    int j = 4;
    int x, y;
    setcolor(13);
    setfillstyle(1, 12);
    x = 45;
    for (int k = 0; k < 3; k++) {
        y = 150 + k * 40;
        arc(x, y, 45, 225, 8);
        arc(x + 18, y, 315, 135, 8);
        line(x + 5, y - 5, x + 9, y - 1);
        line(x + 9, y - 1, x + 14, y - 6);
        line(x - 5, y + 5, x + 9, y + 19);
        line(x + 9, y + 19, x + 23, y + 5);
        floodfill(x + 1, y + 1, 13);
    }
    setcolor(0);
}

void UpdateLife(int life) {
    int x = 41;
    int y = 151 + life * 40;
    setfillstyle(1, 8);
    floodfill(x, y, BGC);
}

void DrawNextPage() {
    setcolor(8);
    setfillstyle(1, 9);
    line(690, 530, 690, 570);
    line(690, 570, 710, 550);
    line(710, 550, 690, 530);
    floodfill(691, 550, 8);
    setcolor(0);
}

void DrawPrevPage() {
    setcolor(8);
    setfillstyle(1, 9);
    line(110, 530, 110, 570);
    line(110, 570, 90, 550);
    line(90, 550, 110, 530);
    floodfill(109, 550, 8);
    setcolor(0);
}

void SelectMenu() {
    do {
        BackGround();
        setlinestyle(0, 0, 4);
        setcolor(5);
        setbkcolor(BGC);
        settextstyle(10, 0, 8);
        outtextxy(120, 80, TxtNono);
        outtextxy(210, 150, TxtGram);
        setcolor(9);
        setfillstyle(1, 12);
        circle(600, 350, 120);
        floodfill(600, 350, 9);
        setbkcolor(12);
        settextstyle(8, 0, 6);
        setcolor(11);
        outtextxy(535, 320, TxtPlay);
        setlinestyle(0, 0, 1);
        setfillstyle(1, 11);
        setcolor(8);
        bar(151, 361, 360, 570);
        for (int i = 0; i <= 3; i++)
            line(150 + i * 70, 360, 150 + i * 70, 571);
        for (int i = 0; i <= 3; i++)
            line(150, 360 + i * 70, 360, 360 + i * 70);
        setcolor(0);
        rectangle(148, 358, 362, 572);
        rectangle(147, 357, 363, 573);
        setfillstyle(1, 8);
        bar(152, 362, 219, 429);
        bar(292, 362, 359, 429);
        bar(222, 432, 289, 499);
        bar(152, 502, 219, 569);
        bar(292, 502, 359, 569);
        settextstyle(10, 0, 4);
        setbkcolor(BGC);
        outtextxy(95, 380, Txt1);
        outtextxy(120, 380, Txt1);
        outtextxy(120, 450, Txt1);
        outtextxy(95, 520, Txt1);
        outtextxy(120, 520, Txt1);
        outtextxy(177, 285, Txt1);
        outtextxy(177, 320, Txt1);
        outtextxy(247, 320, Txt1);
        outtextxy(317, 285, Txt1);
        outtextxy(317, 320, Txt1);
        int a, b, Dif = 0, c, d, e, TextPos[] = {175, 365, 575}, Level2, MaxLevel = 0, Page, NextPage = 0;
        FILE *f;
        f = fopen("Score.txt", "r");
        fscanf(f, "%d%d%d", &LockLv[0], &LockLv[1], &LockLv[2]);
        fclose(f);
        char s[11];
        while (true) {
            if (ismouseclick(WM_LBUTTONDOWN)) {
                getmouseclick(WM_LBUTTONDOWN, a, b);
                if ((a - 600) * (a - 600) + (b - 350) * (b - 350) <= 120 * 120)
                    break;
            }
            delay(40);
        }
        BackGround();
        setcolor(0);
        setfillstyle(1, 9);
        setbkcolor(9);
        settextstyle(10, 0, 4);
        bar(24, 629, 112, 667);
        outtextxy(30, 630, TxtMenu);
        rectangle(20, 625, 115, 670);
        rectangle(19, 624, 116, 671);
        setfillstyle(1, 10);
        setbkcolor(10);
        settextstyle(10, 0, 3);
        setbkcolor(BGC);
        outtextxy(50, 40, TxtChooseDifficult);
        setbkcolor(10);
        rectangle(125, 100, 275, 150);
        bar(129, 104, 272, 147);
        rectangle(325, 100, 475, 150);
        bar(329, 104, 472, 147);
        rectangle(525, 100, 675, 150);
        bar(529, 104, 672, 147);
        outtextxy(TextPos[0], 115, DifText[0]);
        outtextxy(TextPos[1], 115, DifText[1]);
        outtextxy(TextPos[2], 115, DifText[2]);
        rectangle(123, 98, 277, 152);
        rectangle(323, 98, 477, 152);
        rectangle(523, 98, 677, 152);
        while (true) {
            if (ismouseclick(WM_LBUTTONDOWN)) {
                getmouseclick(WM_LBUTTONDOWN, a, b);
                if (b >= 98 && b <= 152) {
                    c = (a - 123) / 200;
                    if (a >= c * 200 + 123 && a <= c * 200 + 277) {
                        setfillstyle(1, 10);
                        settextstyle(10, 0, 3);
                        setbkcolor(10);
                        bar(129 + Dif * 200, 104, 272 + Dif * 200, 147);
                        outtextxy(TextPos[Dif], 115, DifText[Dif]);
                        Dif = c;
                        setfillstyle(1, 12);
                        setbkcolor(12);
                        bar(129 + Dif * 200, 104, 272 + Dif * 200, 147);
                        outtextxy(TextPos[Dif], 115, DifText[Dif]);
                        setfillstyle(1, BGC);
                        bar(90, 200, 710, 600);
                        setbkcolor(BGC);
                        Level2 = 1;
                        MaxLevel = 0;
                        Page = 0;
                        NextPage = 0;
                        while (true) {
                            sprintf(s, "Map%c%d.txt", DifChar[Dif], Level2);
                            f = fopen(s, "r");
                            if (f) {
                                if (Level2 > 12) {
                                    DrawNextPage();
                                    NextPage = 1;
                                    fclose(f);
                                    break;
                                }
                                d = ((Level2 - 1) / 4) * 140;
                                e = ((Level2 - 1) % 4) * 140;
                                rectangle(135 + e, 200 + d, 245 + e, 310 + d);
                                rectangle(138 + e, 203 + d, 242 + e, 307 + d);
                                settextstyle(10, 0, 5);
                                outtextxy(194 + e - 13 * strlen(NumText[Level2]), 218 + d, NumText[Level2]);
                                settextstyle(10, 0, 3);
                                if (Level2 > LockLv[Dif])
                                    outtextxy(164 + e, 260 + d, TxtLock);
                                Level2++;
                                MaxLevel++;
                                fclose(f);
                            } else
                                break;
                        }
                    }
                } else {
                    if (a >= 135 && a <= 665 && b >= 200 && b <= 590) {
                        d = (a - 135) / 140;
                        e = (b - 200) / 140;
                        if (a >= d * 140 + 135 && a <= d * 140 + 245 && b >= e * 140 + 200 && b <= e * 140 + 310)
                            if (e * 4 + d + Page * 12 < LockLv[Dif]) {
                                Level = e * 4 + Page * 12 + d + 1;
                                DChar = DifChar[Dif];
                                DInt = Dif;
                                break;
                            }
                    } else if (a >= 20 && a <= 115 && b >= 625 && b <= 670) {
                        Level = 0;
                        break;
                    } else if (b >= 530 && b <= 570) {
                        if (a >= 690 && a <= 710) {
                            if (NextPage) {
                                NextPage = 0;
                                Page++;
                                Level2 = Page * 12 + 1;
                                setfillstyle(1, BGC);
                                bar(90, 200, 710, 600);
                                DrawPrevPage();
                                while (true) {
                                    sprintf(s, "Map%c%d.txt", DifChar[Dif], Level2);
                                    f = fopen(s, "r");
                                    if (f) {
                                        if (Level2 > 12 * Page + 12) {
                                            DrawNextPage();
                                            NextPage = 1;
                                            fclose(f);
                                            break;
                                        }
                                        d = ((Level2 - 12 * Page - 1) / 4) * 140;
                                        e = ((Level2 - 12 * Page - 1) % 4) * 140;
                                        rectangle(135 + e, 200 + d, 245 + e, 310 + d);
                                        rectangle(138 + e, 203 + d, 242 + e, 307 + d);
                                        settextstyle(10, 0, 5);
                                        outtextxy(194 + e - 13 * strlen(NumText[Level2]), 218 + d, NumText[Level2]);
                                        settextstyle(10, 0, 3);
                                        if (Level2 > LockLv[Dif])
                                            outtextxy(164 + e, 260 + d, TxtLock);
                                        Level2++;
                                        MaxLevel++;
                                        fclose(f);
                                    } else
                                        break;
                                }
                            }
                        } else if (a >= 90 && a <= 110) {
                            if (Page > 0) {
                                NextPage = 1;
                                Page--;
                                Level2 = Page * 12 + 1;
                                setfillstyle(1, BGC);
                                bar(90, 200, 710, 600);
                                if (Page > 0)
                                    DrawPrevPage();
                                DrawNextPage();
                                while (true) {
                                    sprintf(s, "Map%c%d.txt", DifChar[Dif], Level2);
                                    f = fopen(s, "r");
                                    if (f) {
                                        if (Level2 > 12 * Page + 12) {
                                            fclose(f);
                                            break;
                                        }
                                        d = ((Level2 - 12 * Page - 1) / 4) * 140;
                                        e = ((Level2 - 12 * Page - 1) % 4) * 140;
                                        rectangle(135 + e, 200 + d, 245 + e, 310 + d);
                                        rectangle(138 + e, 203 + d, 242 + e, 307 + d);
                                        settextstyle(10, 0, 5);
                                        outtextxy(194 + e - 13 * strlen(NumText[Level2]), 218 + d, NumText[Level2]);
                                        settextstyle(10, 0, 3);
                                        if (Level2 > LockLv[Dif])
                                            outtextxy(164 + e, 260 + d, TxtLock);
                                        Level2++;
                                        MaxLevel++;
                                        fclose(f);
                                    } else
                                        break;
                                }
                            }
                        }
                    }
                }
            }
            delay(40);
        }
    } while (Level == 0);
}

void DrawLevel() {
    setcolor(1);
    setbkcolor(BGC);
    settextstyle(10, 0, 3);
    outtextxy(40, 30, DifText[DInt]);
    outtextxy(40, 60, NumText[Level]);
    outtextxy(40, 90, NumText[X]);
    outtextxy(60, 90, TxtX);
    outtextxy(80, 90, NumText[Y]);
}

int main() {
    initwindow(MAXX + 9, MAXY + 13);
    char s[10];
    FILE *file;
    int n, check, MaxXY, x, y, a, b, Count, Got, Life, CoR[9], CoC[9], GotR[9], GotC[9], Game;
    while (true) {
        SelectMenu();
        Game = 1;
        while (true) {
            Count = 0;
            Got = 0;
            Life = 3;
            sprintf(s, "Map%c%d.txt", DChar, Level);
            FILE *f = fopen(s, "r");
            if (!f)
                break;
            fscanf(f, "%d", &X);
            fscanf(f, "%d", &Y);
            for (int i = 0; i < Y; i++)
                CountR[i] = CoR[i] = GotR[i] = 0;
            for (int i = 0; i < X; i++)
                CountC[i] = CoC[i] = GotC[i] = 0;
            for (int i = 0; i < Y; i++) {
                for (int j = 0; j < X; j++) {
                    Row[i][j] = 0;
                    Column[j][i] = 0;
                }
            }
            for (int i = 0; i < Y; i++)
                for (int j = 0; j < X; j++)
                    fscanf(f, "%d", &Table[i][j]);
            fclose(f);
            for (int i = 0; i < Y; i++) {
                check = 0;
                for (int j = 0; j < X; j++) {
                    n = Table[i][j];
                    if (n) {
                        CoR[i]++;
                        CoC[j]++;
                        Row[i][CountR[i]]++;
                        Count++;
                        check = 1;
                    } else {
                        if (check == 1)
                            CountR[i]++;
                        check = 0;
                    }
                }
                if (n)
                    CountR[i]++;
            }
            for (int i = 0; i < X; i++) {
                check = 0;
                for (int j = 0; j < Y; j++) {
                    n = Table[j][i];
                    if (n) {
                        Column[i][CountC[i]]++;
                        check = 1;
                    } else {
                        if (check == 1)
                            CountC[i]++;
                        check = 0;
                    }
                }
                if (n)
                    CountC[i]++;
            }
            MaxXY = Max(X, Y);
            Width = 320 / MaxXY + 25;
            StartX = (MAXX - X * Width) / 2 + 60;
            StartY = (MAXY - Y * Width) / 2 + 57;
            BackGround();
            DrawLevel();
            DrawFrame();
            DrawLife();
            setcolor(0);
            setfillstyle(1, 9);
            setbkcolor(9);
            settextstyle(10, 0, 4);
            bar(24, 629, 112, 667);
            outtextxy(30, 630, TxtMenu);
            rectangle(20, 625, 115, 670);
            rectangle(19, 624, 116, 671);
            settextstyle(10, 0, 4);
            setbkcolor(BGC);
            for (int i = 0; i < Y; i++) {
                n = CountR[i];
                for (int j = 0; j < n; j++) {
                    outtextxy(StartX - 10 - (n - j) * 25, StartY + 63 + i * Width - MaxXY * 6, NumText[Row[i][j]]);
                }
            }
            for (int i = 0; i < X; i++) {
                n = CountC[i];
                for (int j = 0; j < n; j++) {
                    outtextxy(StartX + 67 + i * Width - MaxXY * 5, StartY - 10 - (n - j) * 30, NumText[Column[i][j]]);
                }
            }
            while (true) {
                delay(20);
                if (ismouseclick(WM_LBUTTONDOWN)) {
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    if (x >= StartX && y >= StartY && x <= StartX + X * Width && y <= StartY + Y * Width) {
                        a = (x - StartX) / Width;
                        b = (y - StartY) / Width;
                        if (Table[b][a] >= 0) {
                            if (Table[b][a] == 1) {
                                CorrectCell(a, b);
                                GotC[a]++;
                                if (GotC[a] == CoC[a]) {
                                    setcolor(12);
                                    for (int j = 0; j < CountC[a]; j++) {
                                        outtextxy(StartX + 67 + a * Width - MaxXY * 5, StartY - 10 - (CountC[a] - j) * 30, NumText[Column[a][j]]);
                                    }
                                }
                                GotR[b]++;
                                if (GotR[b] == CoR[b]) {
                                    setcolor(12);
                                    for (int j = 0; j < CountR[b]; j++) {
                                        outtextxy(StartX - 10 - (CountR[b] - j) * 25, StartY + 63 + b * Width - MaxXY * 6, NumText[Row[b][j]]);
                                    }
                                }
                                Got++;
                                if (Got == Count)
                                    break;
                            } else {
                                ErrorCell(a, b);
                                Life--;
                                UpdateLife(Life);
                                if (Life == 0)
                                    break;
                            }
                            Table[b][a] = -1;
                        }
                    } else if (x >= 20 && x <= 115 && y >= 625 && y <= 670) {
                        Game = 0;
                        break;
                    }
                }
            }
            if (!Game)
                break;
            delay(1000);
            WinLose(Life > 0);
            if (Life > 0)
                Level++;
            if (Level > LockLv[DInt]) {
                LockLv[DInt] = Level;
                file = fopen("Score.txt", "w");
                fprintf(file, "%d %d %d", LockLv[0], LockLv[1], LockLv[2]);
                fclose(f);
            }
            delay(500);
        }
    }
    closegraph();
    return 0;
}
