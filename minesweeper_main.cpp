#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
#define MAXSIDES 25
#define MAXMINES 100
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
int SIDES,MINES;

bool isValid(int x,int y)
{
    return (x>=0 && x<SIDES && y>=0 && y<SIDES);
}
bool isMine(int x,int y,char realBoard[][MAXSIDES])
{
    if(isValid(x,y))
    {
        return (realBoard[x][y]=='*');
    }
    return false;
}

void printBoard(char myBoard[][MAXSIDES])
{
    //cout<<SIDES<<"\n";
    cout<<"    ";
    for(int i=0;i<SIDES;i++)
        printf("%4d",i);
    cout<<"\n";
    for(int i=0;i<SIDES;i++)
    {
        printf("%4d",i);
        for(int j=0;j<SIDES;j++)
        {
            if(myBoard[i][j]=='*')
            {
                SetConsoleTextAttribute(hConsole,4);
            }
            printf("%4c",myBoard[i][j]);
            SetConsoleTextAttribute(hConsole,15);
        }
        cout<<"\n";
    }
}

void initialize(char realBoard[][MAXSIDES],char myBoard[][MAXSIDES])
{
    srand(time(NULL));
    for(int i=0;i<SIDES;i++)
    {
        for(int j=0;j<SIDES;j++)
        {
            myBoard[i][j]='-';
            realBoard[i][j]='-';
        }
    }
}

void placeMines(int mines[][2],char realBoard[][MAXSIDES])
{
    bool markMine[MAXSIDES][MAXSIDES]={0};
    for(int i=0;i<MINES;)
    {
        int random = rand()%(SIDES*SIDES);
        int x = random/SIDES;
        int y = random%SIDES;
        if(markMine[x][y]==0)
        {
            mines[i][0]=x;
            mines[i][1]=y;
            i++;
            markMine[x][y]=1;
            realBoard[x][y]='*';
        }
    }
}

void printMines(int mines[][2])
{
    for(int i=0;i<MINES;i++)
    {
        cout<<mines[i][0]<<"  "<<mines[i][1]<<"\n";
    }
}

void replaceMine(int x,int y,char realBoard[][MAXSIDES])
{
    for(int i=0;i<SIDES;i++)
    {
        for(int j=0;j<SIDES;j++)
        {
            if(realBoard[i][j]!='*')
            {
                realBoard[i][j]='*';
                realBoard[x][y]='-';
                return;
            }
        }
    }
}

int countAdjacentMines(int x,int y,char realBoard[][MAXSIDES])
{
    int count=0;
    if(isMine(x-1,y-1,realBoard))
        count++;
    if(isMine(x-1,y,realBoard))
        count++;
    if(isMine(x-1,y+1,realBoard))
        count++;
    if(isMine(x,y-1,realBoard))
        count++;
    if(isMine(x,y+1,realBoard))
        count++;
    if(isMine(x+1,y-1,realBoard))
        count++;
    if(isMine(x+1,y,realBoard))
        count++;
    if(isMine(x+1,y+1,realBoard))
        count++;
    return count;
}

bool playGameUtil(int x,int y,char realBoard[][MAXSIDES],char myBoard[][MAXSIDES],int mines[][2],int *movesLeft)
{
    if(myBoard[x][y]!='-')
        return false;
    else if(realBoard[x][y]=='*')
    {
        cout<<"It's a Mine!!!!!!"<<"\n";
        myBoard[x][y]='*';
        //printBoard(myBoard);
        for(int i=0;i<MINES;i++)
        {
            //cout<<mines[i][0]<<"  "<<mines[i][1]<<"\n";
            myBoard[mines[i][0]][mines[i][1]]='*';
        }
        printBoard(myBoard);
        SetConsoleTextAttribute(hConsole, 4);
        cout<<"\n\t\tYOU LOST!!\n";
        SetConsoleTextAttribute(hConsole, 15);
        return true;
    }
    else
    {
        int c=countAdjacentMines(x,y,realBoard);
        myBoard[x][y]=c+'0';
        (*movesLeft)--;
        if(c!=0){
            if(!isMine(x-1,y-1,realBoard))
                playGameUtil(x-1,y-1,realBoard,myBoard,mines,movesLeft);
            if(!isMine(x-1,y,realBoard))
                playGameUtil(x-1,y,realBoard,myBoard,mines,movesLeft);
            if(!isMine(x-1,y+1,realBoard))
                playGameUtil(x-1,y+1,realBoard,myBoard,mines,movesLeft);
            if(!isMine(x,y-1,realBoard))
                playGameUtil(x,y-1,realBoard,myBoard,mines,movesLeft);
            if(!isMine(x,y+1,realBoard))
                playGameUtil(x,y+1,realBoard,myBoard,mines,movesLeft);
            if(!isMine(x+1,y-1,realBoard))
                playGameUtil(x+1,y-1,realBoard,myBoard,mines,movesLeft);
            if(!isMine(x+1,y,realBoard))
                playGameUtil(x+1,y,realBoard,myBoard,mines,movesLeft);
            if(!isMine(x+1,y+1,realBoard))
                playGameUtil(x+1,y+1,realBoard,myBoard,mines,movesLeft);
        }
        return false;
    }
}
void playGame()
{
    char realBoard[MAXSIDES][MAXSIDES];
    char myBoard[MAXSIDES][MAXSIDES];
    bool gameover = false;
    int mines[MAXMINES][2];
    int movesLeft = SIDES*SIDES - MINES ; 
    int x,y;
    int currentMoveIndex=0;
    initialize(realBoard,myBoard);
    placeMines(mines,realBoard);
    //printBoard(realBoard);
    //printMines(mines);
    //printBoard(myBoard);
    while(gameover==false)
    {
        printBoard(myBoard);
        cout<<"\nMoves Left: "<<movesLeft<<"\n";
        if(currentMoveIndex==0)
            cout<<"Enter any coordinate of your choice: ";
        else
            cout<<"enter any non-mine coordinates: ";
        cin>>x>>y;
        cout<<"\n";
        if(currentMoveIndex==0)
        {
            if(isMine(x,y,realBoard))
                replaceMine(x,y,realBoard);
        }
        currentMoveIndex++;
        gameover = playGameUtil(x,y,realBoard,myBoard,mines,&movesLeft);
        if(gameover==false && movesLeft==0){
            SetConsoleTextAttribute(hConsole, 2);
            cout<<"\t\tYOU WON!! :)\n";
            SetConsoleTextAttribute(hConsole, 15);
            gameover=true;
        }
    }
    return;
}
void chooseDifficulty()
{
    cout<<"Choose your difficulty level by selecting appropriate option: \n";
    cout<<"Enter 0 for BEGINNER (9*9 cells with 10 Mines)\n";
    cout<<"Enter 1 for INTERMEDIATE (16*16 cells with 40 Mines)\n";
    cout<<"Enter 2 for ADVANCE (24*24 cells with 99 Mines)\n";
    cout<<"SELECTED LEVEL: ";
    int diff;
    cin>>diff;
    if(diff==0)
    {
        SIDES =  9;
        MINES = 10;
    }
    else if(diff==1)
    {
        SIDES = 16;
        MINES = 40;
    }
    else if(diff ==2)
    {
        SIDES = 24;
        MINES = 99;
    }
    return;
}
int main()
{
    cout<<"\n\t\tThis is MineSweeper Game.\nYou have to find out all non-mine locations without stepping on any mine in your way.\n";
    cout<<"\t\t\tCHECK OUT!!!\t\n";
    chooseDifficulty();
    playGame();
    return 0;
}