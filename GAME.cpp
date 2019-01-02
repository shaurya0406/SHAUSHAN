#include<conio.h>
#include<iostream.h>
#include<string.h>
#include<stdio.h>
#include<dos.h>
#include<stdlib.h>
#include<ctype.h>
#include<iomanip.h>

void about();
void printLogo();
void Drawmenu();
void select(int);
void scroll(int);
int currentitem = 0;
int highscore;
char buff[255];

/*****************************MINESWEEPER****************************/
void printBoard(char[9][9]);
void checkAdjacent(char[9][9], char[9][9], int, int);
void placeMines(char [9][9]);
int exists(int[8][2], int[2]);
int checkWin(char[9][9], char[9][9]);
int adjacentSquares(int[8][2], int, int);

void printBoard(char playerBoard[9][9])
{
	cout << ' ';
	for (int n = 1; n <= 9; n++)
		cout << ' ' << n ;
	cout << endl<<endl;
	for (int i = 1; i <= 9;i++)
	{
		cout << i;
		for (int j = 1; j <= 9; j++)
		{
			cout << ' ';
			switch (playerBoard[i - 1][j - 1])
			{
			case 'F':
				textcolor(LIGHTBLUE);//177
				char temp[2] = {char(177), '\0'};
				textcolor(WHITE);
				break;
			case 'M':
				textcolor(RED);
				char temp[2] = {char(127),'\0'};
				cprintf(temp);
				textcolor(WHITE);
				break;
			case 'E':
				cout << '_';
				break;
			case 'H':
				cout << char(219);
				break;
			default:
				textcolor(YELLOW);
				char temp[2] = {playerBoard[i-1][j-1], '\0'};
				cprintf(temp);
				textcolor(WHITE);
			}
		}
		cout << endl << endl;
	}
}

void checkAdjacent(char playerBoard[9][9], char realBoard[9][9], int R, int C)
{
	int countM = 0;
	int squares[8][2];
	int countSq = adjacentSquares(squares, R, C);
	for (int i = 0; i < countSq; i++)
		if (realBoard[squares[i][0]-1][squares[i][1]-1] == 'M')
			countM++;
	if (countM > 0)
		playerBoard[R - 1][C - 1] = countM + 48;
	else
		playerBoard[R - 1][C - 1] = 'E';
}

void placeMines(char realBoard[9][9])
{
	for (int i = 0; i < 9;i++)
		for (int j = 0; j < 9;j++)
			realBoard[i][j] = 'E';
	int squares[8][2];
	for ( i = 0; i < 8;i++)
	{
		int x = (rand() % 9) + 1;
		int y = (rand() % 9) + 1;
		int temp[] = { x,y };
		while (exists(squares, temp))
		{
			int x = (rand() % 9) + 1;
			int y = (rand() % 9) + 1;
			temp[0] = x;
			temp[1] = y;
		}
		squares[i][0] = temp[0];
		squares[i][1] = temp[1];
		realBoard[x-1][y-1] = 'M';
	}
}

int exists(int squares[8][2], int item[2])
{
	int found = 0;
	for (int i = 0; i < 8 && !found; i++)
		if (squares[i][0] == item[0] && squares[i][1] == item[1])
			found = 1;
	return found;
}

int checkWin(char playerBoard[9][9], char realBoard[9][9])
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9;j++)
			if ((realBoard[i][j] == 'M'&&playerBoard[i][j] != 'F')|| (realBoard[i][j] != 'M' && (playerBoard[i][j] == 'H' || playerBoard[i][j] == 'F')))
				return 0;
	return 1;
}

int adjacentSquares(int squares[8][2], int R, int C)
{
	int count = 0;
	if (R + 1 <= 9)
	{
		squares[count][0] = R + 1;
		squares[count++][1] = C;
		if (C + 1 <= 9)
		{
			squares[count][0] = R + 1;
			squares[count++][1] = C + 1;
		}
		if (C - 1 >= 1)
		{
			squares[count][0] = R + 1;
			squares[count++][1] = C - 1;
		}
	}
	if (C + 1 <= 9)
	{
		squares[count][0] = R;
		squares[count++][1] = C + 1;
	}
	if (R - 1 >= 1)
	{
		squares[count][0] = R - 1;
		squares[count++][1] = C;

		if (C + 1 <= 9)
		{
			squares[count][0] = R - 1;
			squares[count++][1] = C + 1;
		}
		if (C - 1 >= 1)
		{
			squares[count][0] = R - 1;
			squares[count++][1] = C - 1;
		}
	}
	if (C - 1 >= 1)
	{
		squares[count][0] = R;
		squares[count++][1] = C - 1;
	}
	return count;
}


void minesweeper()
{
	char reply = 'N';
	do
	{
		char realBoard[9][9], playerBoard[9][9];
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9;j++)
				playerBoard[i][j] = 'H';
		placeMines(realBoard);
		int mine = 0;
		while (!checkWin(playerBoard, realBoard) && !mine)
		{
			clrscr();
			printBoard(playerBoard);
			char mode;
			cout << endl;
			cout << "Do you want to place a flag, check a mine, remove a flag or quit the game? (F/M/R/X): ";
			cin >> mode;
			mode = toupper(mode);
			if (mode == 'M')
			{
				int R, C;
				cout << "Row: "; cin >> R;
				cout << "Column: ";cin >> C;
				if (realBoard[R - 1][C - 1] == 'M')
					mine++;
				else if (playerBoard[R - 1][C - 1]=='H' || playerBoard[R - 1][C - 1] == 'F')
					checkAdjacent(playerBoard, realBoard, R, C);
			}
			else if (mode == 'F')
			{
				int R, C;
				cout << "Row: "; cin >> R;
				cout << "Column: ";cin >> C;
				if (playerBoard[R - 1][C - 1] == 'H')
					playerBoard[R - 1][C - 1] = 'F';
			}
			else if (mode == 'R')
			{
				int R, C;
				cout << "Row: ";cin >> R;
				cout << "Column: ";cin >> C;
				if (playerBoard[R - 1][C - 1] == 'F')
					playerBoard[R - 1][C - 1] = 'H';
			}
      			else if (mode=='X')
      			{
       				Drawmenu();
       				scroll(currentitem);
     				return;
     			}
			else cout << "Invalid input!";
		}
		clrscr();
		if (mine)
		{
			printBoard(realBoard);
			int mineCounter = 0;
			for (int i = 0;i < 9;i++)
				for (int j = 0; j < 9;j++)
					if (playerBoard[i][j] == 'F' && realBoard[i][j] == 'M')
						mineCounter++;
			cout << endl << "You stepped on a mine!" << endl << "GAME OVER"<<endl<<"You found "<<mineCounter<<" mines."<<endl<<endl;
		}
		else
		{
			printBoard(playerBoard);
			cout << "You won the game!" << endl;
		}
		cout << "Do you want to play again? (Y/N): ";
		cin >> reply;
	} while (toupper(reply) != 'N');
    if (toupper(reply) == 'N') {
        Drawmenu();
        scroll(currentitem);
    }
}

/*****************************WORD***********************************/
void printLogo();
void printLetters(char[], int, int[]);
int wordCompleted(int[], int);
int editWord(char[], int, int[], char);
void displayString(char[], int N);

typedef struct WORD{
	char word[20];
	int length;
	int check[20];
};

void word()
{
	clrscr();
	randomize();
	WORD WORDS[10] = { { "CLAUSTROPHOBIA", 14, {0,0,1,1,0,0,0,1,0,0,1,0,1,1} }, { "KLEPTOMANIAC", 12, {0,0,1,0,0,1,0,1,0,1,1,0} }, {"PSYCHOSOMATIC",13,{0,0,0,0,0,1,0,1,0,1,0,1,0} }}, {"INFORMATION", 11, {1,0,0,1,0,0,1,0,1,1,0}}, {"ACCOMMODATE", 11, {1,0,0,1,0,0,1,0,1,0,1}}, {"HANDKERCHIEF", 12, {0,1,0,0,0,1,0,0,0,1,1,0}},{"AMBIDEXTROUS", 12, {1,0,0,1,0,1,0,0,0,1,1,0}}, {"EQUIVALENT", 10, {1,0,1,1,0,1,0,1,0,0}}, {"ARCHITECTURE", 12, {1,0,0,0,1,0,1,0,0,1,0,1}}, {"AFICIONADO", 10, {1,0,1,0,1,1,0,1,0,1}}};
	char reply;
	int score = 0;
	do
	{
		int j = random(10);
		char word[20];
		int length = WORDS[j].length;
		int check[20];
		for (int i = 0; i < length; i++)
		{
			check[i] = WORDS[j].check[i];
			word[i] = WORDS[j].word[i];
		}
		int guesses = 5;		
		while (!wordCompleted(check, length) && guesses)
		{
			cout << "Let's see if you can get this word right!" << endl;
			printLetters(word, length, check);
			char guess;
			cout << "Guess a letter: ";
			cin >> guess;
			guess = toupper(guess);
			int factor = editWord(word, length, check, guess);
			if (factor != 0)
			{
				score += 10 * factor;
				cout << "Right Guess!" << endl;
				cout << "There " << ((factor > 1) ? "were " : "was ") << factor << " " << guess << ((factor > 1) ? "'s." : ".") << endl;
				cout << "Your total score is " << score << "." << endl;
			}
			else
				cout << "Incorrect Guess!" << endl << "You have only " << --guesses << " guesses left." << endl;
			clrscr();
		}
		if (guesses > 0)
		{
			displayString(word, length);
			cout << "You got the word!" << endl;
			cout << "You scored " << score << " points.";
		}
		else
		{
			cout << "You were unable to guess the word!" << endl << "The word was: " << endl;
			displayString(word, length);
			cout << "You scored " << score << " points." << endl;
		}
		cout << endl << "Do you want to play again? (Y/N): ";
		cin >> reply;
		cout << endl;
	} while (toupper(reply) != 'N');
   if(toupper(reply) == 'N')
   {
       	window(1,1,80,25);
	textcolor(WHITE);
	textbackground(0);
	clrscr();
	Drawmenu();
	scroll(currentitem);
   }
}

void printLetters(char word[], int N, int check[])
{
	textcolor(YELLOW);
	for (int i = 0;i < N; i++)
		if (check[i])
			cout<<word[i]<<' ';
		else
			cout<<"_ ";
	cout << endl;
	textcolor(WHITE);
}

int wordCompleted(int check[], int N)
{
	for (int i = 0; i < N;i++)
		if (check[i] == 0)
			return 0;
	return 1;
}

int editWord(char word[], int N, int check[], char guess)
{
	int found = 0;
	for (int i = 0; i < N; i++)
		if (word[i] == guess && !check[i])
		{
			check[i]++;
			found++;
		}
	return found;
}

void displayString(char word[], int N)
{
	textcolor(YELLOW);
	for (int i = 0; i < N; i++)
		cout<<word[i];
	cout << endl;
	textcolor(WHITE);
}

/********************************************SNAKE***************************************/
#define TOP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

void score(int s=1)
{
    	FILE *fp;
	static unsigned long sc=0;
    	window(70,22,78,23);
    	if(s)
    	{
		sc++;
		cprintf("      ");
		window(70,22,78,23);
		cprintf("%ld",sc);
    	}	
    	else
		sc=0;
    	if (sc>highscore) {
		highscore = sc;
		itoa(highscore,buff,10);
		fp = fopen("/snake.txt", "w+");
		fprintf(fp, buff);
		fclose(fp);
    	}
}

void status(char *s,int c=WHITE)
{
	window(70,23,78,25);
    	textcolor(c);
    	cprintf("%s",s);
    	for(int x=strlen(s);x<7;x++)
		cprintf(" ");
    	textcolor(WHITE);
}
void snake()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    textcolor(WHITE);
    cprintf("                                                           ³ HIGHSCORE :     ³  ");
    cprintf("   ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿  ");
    for(int i=0;i<17;i++)
    cprintf("   ³                                                                         ³  ");
    cprintf("   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ  ");
    cprintf("   ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿   Press 'x' to Exit            ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿  ");
    cprintf("   ³  S N A K E  G A M E  ³   Press spc to Pause and Play  ³ SCORE : 0       ³  ");
    cprintf("   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ                                ³ STATUS: Playing ³  ");
    cprintf("                                                           ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ  ");
    int snkx[20],snky[20],d=LEFT,p=0,sz=6,restart=1;
    FILE *fp;
    fp = fopen("/snake.txt", "r");
    fgets(buff, 255, (FILE*)fp);
    highscore = atoi(buff);
    fclose(fp);
    window(73,1,78,2);
    cprintf("%d",highscore);
    while(1)
    {
	if(restart)
	{
	    for(i=0;i<6;i++)
		snkx[i]=30+i*2;
	    for(i=6;i<20;i++)
		snkx[i]=0;
	    for(i=0;i<20;i++)
		snky[i]=9;
	    sz=6;
	    p=0;
	    d=LEFT;
	    restart=0;
	    score();
	    window(6,3,76,19);
	    for(i=0;i<610;i++)
		cprintf("  ");
	}
	int x,y;
	if(p!=1)
	{
	    do
	    {
		x=random(70)+6;
	    }while(x%2==1);
	    y=random(16)+3;
	    p=1;
	    window(x,y,x+1,y+1);
	    textcolor(LIGHTGREEN);
	    cprintf("%c",1);
	    textcolor(WHITE);
	}
	while(!kbhit())
	{
	    status("Playing",LIGHTGREEN);
	    window(snkx[sz-1],snky[sz-1],snkx[sz-1]+2,snky[sz-1]+2);
	    cprintf(" ");
	    for(i=0;i<sz-1;i++)
	    {
		window(snkx[i],snky[i],snkx[i]+1,snky[i]+1);
		cprintf("ß");
	    }
	    for(i=sz-1;i>=1;i--)
	    {
		snkx[i]=snkx[i-1];
		snky[i]=snky[i-1];
	    }
	    switch(d)
	    {
		case RIGHT : snkx[0]+=2; break;
		case LEFT  : snkx[0]-=2; break;
		case TOP   : snky[0]-=1; break;
		case DOWN  : snky[0]+=1;
	    }
	    delay(200);
	    if(x==snkx[0] && y==snky[0])
	    {
		int f=0;
		do{
		    do{
			x=random(70)+6;
		    }while(x%2==1);
		    y=random(16)+3;
		    for(i=0;i<sz;i++)
			if(snkx[i]==x && snky[i]==y)
			    f=1;
		}while(f);
		p=1;
		window(x,y,x+1,y+1);
		textcolor(LIGHTGREEN);
		cprintf("%c",1);
		textcolor(WHITE);
		score();
		sz++;
		switch(d)
		{
		    case RIGHT : 
			snkx[sz-1]+=2;
			snky[sz-1]=snky[sz-2];
			break;
		    case LEFT  : 
			snkx[sz-1]-=2;
			snky[sz-1]=snky[sz-2];
			break;
		    case TOP   :
			snky[sz-1]-=1;
			snkx[sz-1]=snkx[sz-2];
			break;
		    case DOWN  : 
			snky[sz-1]+=1;
			snkx[sz-1]=snkx[sz-2];
		}
	    }
	    int sflag=0;
	    for(i=0;i<sz-1;i++)
		if(snkx[sz-1]==snkx[i] && snky[sz-1]==snky[i])
		{
		    sflag=1;
		    break;
		}
	    if(snkx[0]<5 || snkx[0]>76 || snky[0]<3 || snky[0]>19)
		sflag=1;
	    if(sflag)
	    {
		textcolor(LIGHTRED);
		for(i=1;i<sz;i++)
		{
		    window(snkx[i],snky[i],snkx[i]+1,snky[i]+1);
		    cprintf("");
		}
		status("Stopped",LIGHTRED);
		score(0);
		restart=1;
		break;
	    }
	}
	char ch=getch();
	switch(tolower(ch))
	{
	    case 'x' :
		{
		 window(1,1,80,25);
		 textcolor(WHITE);
		 textbackground(0);
		 clrscr();
		 Drawmenu();
		 scroll(currentitem);            
		 return;
		}
	    case  32 :
		status("Paused",YELLOW);
		getch();
		break;
	    case 0 : {
		char chh=getch();
		switch(chh)
		{
		    case 72 :
			if(d==LEFT || d== RIGHT)
			    d=TOP;
		    break;
		    case 80 :
			if(d==LEFT || d== RIGHT)
			    d=DOWN;
		    break;
		    case 75 :
			if(d==TOP || d==DOWN)
			    d=LEFT;
		    break;
		    case 77 :
			if(d==TOP || d==DOWN)
			    d=RIGHT;
		}
	    } break;
	}
    }
}
	
/********************************************TICTACTOE***************************************/
int  rowcheck(char ch[3][3])
{
    int i;
    char ans;
    for(i=0;i<3;i++)
	if(ch[i][0]==ch[i][1] && ch[i][1]==ch[i][2])
	{
	    ans=ch[i][0];
	    break;
	}
    if(ans=='O')
	return 1;
    else if(ans=='X')
	return 2;
    else
	return 0;
}
	
int  colcheck(char ch[3][3])
{
    int i;
    char ans;
    for(i=0;i<3;i++)
	if(ch[0][i]==ch[1][i] && ch[1][i]==ch[2][i])
	{
	    ans=ch[0][i];
	    break;
	}    
    if(ans=='O')
	return 1;
    else if(ans=='X')
	return 2;
    else
	return 0;
}
	
int  diagcheck(char ch[3][3])
{
    char ans;
    if(ch[0][0]==ch[1][1] && ch[1][1]==ch[2][2])
	ans=ch[0][0];
    if(ch[0][2]==ch[1][1] && ch[1][1]==ch[2][0])
	ans=ch[0][2];
    if(ans=='O')
	return 1;
    else if(ans=='X')
	return 2;
    else
	return 0;
}

void printInColor(char c)
{
	if (c == 'X')
		textcolor(LIGHTRED);
	else if (c == 'O')
		textcolor(LIGHTBLUE);
	char str[4] = {' ', c, ' ', '\0'};
	cprintf(str);
	textcolor(WHITE);
}
	
void rewrite(char ch[3][3])
{
	int i = 0;
	cout << "   |   |" << endl;
	printInColor(ch[i / 3][i % 3]);
	cout<< '|';
	i++;
	printInColor(ch[i / 3][i % 3]);
	i++;
	cout << "|";
	printInColor(ch[i / 3][i % 3]);
	i++;
	for (int j = 0;j < 2;j++)
	{
		cout << endl << "___|___|___" << endl << "   |   |" << endl << " ";
		printInColor(ch[i / 3][i % 3]);
		cout << "|";
		i++;
		printInColor(ch[i / 3][i % 3]);
		cout << "|";
		i++;
		printInColor(ch[i / 3][i % 3]);
		i++;
	}
	cout <<endl<< "   |   |" << endl << endl;
}

void tictactoe()
{
    clrscr();
    char ch[3][3]={'1','2','3','4','5','6','7','8','9'};
    int x,y,i,j,num,chance=1;
    rewrite(ch);
    while(chance++<=9)
    {
	cout<<"Player "<<chance%2+1<<", enter position.";
	cout<<endl;
	cin>>num;
	x=(num-1)/ 3;
	y=(num-1) % 3;
	if(ch[x][y]=='X'||ch[x][y]=='O')
	{
	    chance--;
	    clrscr();
	    rewrite(ch);
	    goto end;
	}
	if(chance % 2 == 0)
	    ch[x][y]='O';
	else
	    ch[x][y]='X';
	clrscr();
	rewrite(ch);
	if(rowcheck(ch)!=0)
	{
	    cout<<"Player "<<rowcheck(ch)<<" wins!!";
	    cout<<endl;
	    break;
	}
	if(colcheck(ch)!=0)
	{
	    cout<<"Player "<<colcheck(ch)<<" wins!!\n";
	    cout<<"PRESS X "<<endl;
	    break;
	}
	if(diagcheck(ch)!=0)
	{
	    cout<<"Player "<<diagcheck(ch)<<" wins!!\n";
	    cout<<"PRESS X "<<endl;
	    break;
	}
	if(chance==10)
	    cout<<"It is a Draw!!!\n PRESS X to EXIT";
    end:;
    }
    if(getch()=='x')
    {
	Drawmenu();
	scroll(currentitem);
    }
}

/********************************************DINOSAUR***************************************/
int t,speed=40;
	
void getup()
{
	textcolor(BLACK);
	textbackground(YELLOW);
	clrscr();
	window(10,2,70,3);
	cprintf("Press X to Exit, Press Space to Jump");
	window(62,2,80,3);
	cprintf("SCORE : ");
	window(62,4,80,5);
	cprintf("HIGHSCORE : ");
	window(1,25,80,25);
	for(int x=0;x<79;x++)
	cprintf("ß");
	textcolor(0);
}

void ds(int jump=0)
{
	static int a=1;
	if(jump==0)
		t=0;
	else if(jump==2)
		t--;
	else t++;
	window(2,15-t,18,25);
	cprintf("                 ");
	cprintf("         ÜÛßÛÛÛÛÜ");
	cprintf("         ÛÛÛÛÛÛÛÛ");
	cprintf("         ÛÛÛÛÛßßß");
	cprintf(" Û      ÜÛÛÛÛßßß ");
	cprintf(" ÛÛÜ  ÜÛÛÛÛÛÛÜÜÜ ");
	cprintf(" ßÛÛÛÛÛÛÛÛÛÛÛ  ß ");
	cprintf("   ßÛÛÛÛÛÛÛß     ");
	if(jump==1 || jump==2){
		cprintf("    ÛÛß ßÛ       ");
		cprintf("    ÛÜ   ÛÜ      ");
	}else if(a==1)
	{
		cprintf("    ßÛÛß  ßßß    ");
		cprintf("      ÛÜ         ");
		a=2;
	}
	else if(a==2)
	{
		cprintf("     ßÛÜ ßÛ      ");
		cprintf("          ÛÜ     ");
		a=1;
	}
	cprintf("                ");
	delay(speed);
}
	
void obstacle()
{
	static int x=0,scr=0;    
	FILE *fp;
	fp = fopen("/dinosaur.txt", "r");
	fgets(buff, 255, (FILE*)fp);
	int dinosaur_highscore = atoi(buff);
	fclose(fp);
	window(74,4,80,5);
	cprintf("%d",dinosaur_highscore);	
	if(x==56 && t<4)
	{
		scr=0;
		speed=40;
		window(36,8,60,9);
		cprintf("Game Over");
		getch();
		window(36,8,60,9);
		cprintf("         ");
	}
	window(74-x,20,80-x,25);
	cprintf("Û    Û ");
	cprintf("Û    Û ");
	cprintf("ÛÜÜÜÜÛ ");
	cprintf("  Û    ");
	cprintf("  Û  " );
	x++;
	if(x==73)
	{
		x=0;
		scr++;
		window(70,2,80,3);
		cprintf("     ");
		window(70,2,80,3);
		cprintf("%d",scr);
		if(speed>20)
			speed--;
	}
	if(scr>dinosaur_highscore)
	{
		dinosaur_highscore = scr;
		itoa(dinosaur_highscore,buff,10);
		fp = fopen("/dinosaur.txt", "w+");
		fprintf(fp, buff);
		fclose(fp);
	}
}
	
void dinosaur()
{
	char ch;
	int i;
	getup();
	do{
		while(!kbhit())
		{
			ds();
			obstacle();
		}
		ch=getch();
		if(ch==' ')
		{
			for(i=0;i<10;i++)
			{
				ds(1);
				obstacle();
			}
			for(i=0;i<10;i++)
			{
				ds(2);
				obstacle();
			}	
		}
		else if (ch=='x')
		{
			window(1,1,80,25);
	 		textcolor(WHITE);
	 		textbackground(0);
	 		clrscr();
	 		Drawmenu();
	 		scroll(currentitem);
		}
	}while(ch !='x');
}
	
/********************************************MENU***************************************/
void Drawbox(int l,int b,int x ,int y,char text[])
{
   textcolor(YELLOW);
   int n = y;
   int a = l-1;
   gotoxy(x,y);
   char w[70] = " ";
   char h[25] = " ";
   h[0] = '³';
   for(int i = 0;i<l;i++)
   {
   	w[i]='Ä';
   	h[i+1] = ' ';
   }
   h[a] = '³';
   cprintf(w);
   n++;
   for(int j = 0 ;j<b;j++)
   {
    gotoxy(x,n);
    cprintf(h);
    n++;
   }
   gotoxy(x,n);
   cprintf(w);
   gotoxy(x+2,y+(b%2));
   textcolor(WHITE);
   cprintf(text);
}
	
void Highlight(int l, int b,int x , int y , char a)
{
   int m = x,n=y;
   char w[70] = " ";
   for(int i = 0;i<l;i++)
   	w[i] = a;
   textcolor(RED);
   gotoxy(m,n+b+1);
   cprintf(w);
   textcolor(WHITE);
}
	
void Drawmenu()
{
	clrscr();
	printLogo();
  	Drawbox(20,1,30,5,"TIC TAC TOE");
  	Drawbox(20,1,30,8,"RAMPAGE");
  	Drawbox(20,1,30,11,"SLITHER");
  	Drawbox(20,1,30,14,"WORDOPEDIA");
  	Drawbox(20,1,30,17,"MINESWEEPER");
    Drawbox(20,1,30,20,"ABOUT");
  	gotoxy(35,23);
  	cout<<"PRESS X TO EXIT";
}
	
void scroll(int c)
{
 clrscr();
 Drawmenu();
 switch(c)
 {
 case 0:
	Highlight(20,1,30,5,'*');
       	break;
 case 1:
	Highlight(20,1,30,8,'*');
	break;
 case 2:
	Highlight(20,1,30,11,'*');
        break;
 case 3:
	Highlight(20,1,30,14,'*');
        break;
 case 4:
	Highlight(20,1,30,17,'*');
 	break;
 case 5:
	Highlight(20,1,30,21,'*');
	break;
 default:
       	return;
 }
}
void select(int c)
{
 switch(c)
 {
 case 0:
	tictactoe();
   	break;
 case 1:
	dinosaur();
   	break;
 case 2:
    	snake();
    	break;
 case 3:
        word();
  	break;
 case 4:
	minesweeper();
	break;
 case 5:
       	about();
	break;
 default:
 	return;
 }
}

void printLogo()
{
	gotoxy(15,1);
	cout << char(201) << char(205) << char(187) << ' ' << char(201) << char(205) << char(187) << ' ' << char(201) << char(205) << char(205) << ' ' << char(201) << char(205) << char(187) << ' ' << char(203) << char(205) << char(187) << ' ' << char(201) << char(205) << char(205) << ' ';
	cout << char(201) << char(203) << char(187) << ' ' << char(201) << char(205) << char(187) << ' ' << char(201) << char(205) << char(205) << ' ' << char(205) << char(203) << char(205) << ' ' << char(201) << char(205) << char(205) << ' ' << char(201) << char(205) << char(187);
	gotoxy(15,2);
	cout << char(204) << char(205) << char(185) << ' ' << char(204) << char(203) << char(188) << ' ' << char(186) << "   " << char(204) << char(205) << char(185) << ' ' << char(186) << ' ' << char(186) << ' ' << char(204) << char(205) << char(205) << ' ';
	cout << char(186) << char(186) << char(186) << ' ' << char(204) << char(205) << char(185) << ' ' << char(200) << char(205) << char(187) << "  " << char(186) << "  " << char(204) << char(205) << char(205) << ' ' << char(204) << char(203) << char(188);
	gotoxy(15,3);
	cout << char(186) << ' ' << char(186) << ' ' << char(186) << char(200) << char(205) << ' ' << char(200) << char(205) << char(205) << ' ' << char(186) << ' ' << char(186) << ' ' << char(202) << char(205) << char(188) << ' ' << char(200) << char(205) << char(205) << ' ';
	cout << char(186) << ' ' << char(186) << ' ' << char(186) << ' ' << char(186) << ' ' << char(205) << char(205) << char(188) << "  " << char(186) << "  " << char(200) << char(205) << char(205) << ' ' << char(186) << char(200) << char(205);
}


void about()
{
    	clrscr();
    	textcolor(LIGHTBLUE);
    	cprintf("ARCADEMASTER");
		textcolor(WHITE);
		cout<<endl<<"Computer Science Final Project"<<endl<<"by SHAURYA CHANDRA & SHASHANK NARAIN"<<endl<<"Class 11 G"<<endl<<"Press any key to go back to MAIN MENU";
    	if(getch())
    	{
     		clrscr();
     		Drawmenu();
     		scroll(currentitem);
    	}
}

/********************************************MAIN***************************************/
void main()
{
   randomize();
   clrscr();
   _setcursortype(_NOCURSOR);
   char a,b;
   int totalitems = 5;
   Drawmenu();
   scroll(currentitem);
   do{
	a=getch();
   	switch(tolower(a))
   	{
     		case 0:
     		{
		b = getch();
	    	switch(b)
	    	{
	      	case 80:
	       	{
		if(currentitem<totalitems)
		{
		     currentitem++;
		     scroll(currentitem);
		}
		else if(currentitem ==totalitems)
		{
		     currentitem = 0;
		     scroll(currentitem);
		}
		}
		  break;
	      case 72:
	       {
		if(currentitem>0)
		{
		     currentitem--;
		     scroll(currentitem);
		}
		else if(currentitem == 0)
		{
		     currentitem = totalitems;
		     scroll(currentitem);
		}
	       }
	 	break;
	 case 13:
	     select(currentitem);
	 break;
	}
      }
     break;
     case 13:
     select(currentitem);
     break;
     case 'x':
     return;
    }
   }while(a!='x');
}