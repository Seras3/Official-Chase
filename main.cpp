#include <iostream>
#include <fstream>
#include <graphics.h>
#include <windows.h>
#include <time.h>

using namespace std;

ifstream f ("date.in");

int d,H,W,a[20][20],n,st[100],x1,y1,x2,y2,xc,yc,k,lscurt=9999999;
char ch;
int dirx[5]={0,-1,0,+1,0};
int diry[5]={0,0,+1,0,-1};

struct drum{
    int X;
    int Y;
}dr[25000];

void pozitionare()
{
    while(a[x1][y1]==0)
    {
        x1=rand()%n+1;
        y1=rand()%n+1;
    }
    while(a[x2][y2]==0||(x2==x1&&y2==y1))
    {
        x2=rand()%n+1;
        y2=rand()%n+1;
    }
}

void arena()
{
    readimagefile("pic/strg.jpg",0,0,W,H);
    readimagefile("pic/margst.jpg",0,2*d,3*d,(n+2)*d);
    readimagefile("pic/margdr.jpg",(3+n)*d,2*d,(6+n)*d,(n+2)*d);
    readimagefile("pic/margjos.jpg",3*d,(2+n)*d,(3+n)*d,H);
    readimagefile("pic/coltjos.jpg",0,(2+n)*d,3*d,H);
    readimagefile("pic/coltjos.jpg",(3+n)*d,(2+n)*d,W,H);
    readimagefile("pic/coltsusst.jpg",0,0,3*d,2*d);
    readimagefile("pic/coltsusdr.jpg",(3+n)*d,0,W,2*d);
    int i,j;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            if(a[i][j]==0)
                readimagefile("pic/wall.jpg",d*(j+2)+1,d*(i+1)+1,d*(j+3)-1,d*(i+2)+1);
            else
                if(i==x1&&j==y1)
                readimagefile("pic/p1.jpg",d*(j+2)+1,d*(i+1)+1,d*(j+3)-1,d*(i+2)+1);
            else
                if(i==x2&&j==y2)
                readimagefile("pic/p2.jpg",d*(j+2)+1,d*(i+1)+1,d*(j+3)-1,d*(i+2)+1);
}


void sol(int x, int y)
{
    if(a[x][y]==1)
    {
        k++;
        a[x][y]=2;
        if(x==x2&&y==y2)
        {
            if(k<lscurt)
                lscurt=k;
        }
        else
        {
            sol(x-1,y);
            sol(x,y+1);
            sol(x+1,y);
            sol(x,y-1);
        }
        k--;
        a[x][y]=1;
    }
}
void MarkTraseu(int lng)
{
    int i;
    for(i=1;i<=lng;i++)
        a[dr[i].X][dr[i].Y]=1;
}

void traseu(int i,int j,int lng)
{
    int x,sens[5],t,fvsens[5]={0,0,0,0,0};
    if(a[i][j]==0&&i>=1&&i<=n&&j<=n&&j>=1&&k<=lng)
    {
        a[i][j]=1;
        k++;
        dr[k].X=i;
        dr[k].Y=j;
        for(t=1;t<=4;t++)
        {
            do{
            x=rand()%4+1;
            }while(fvsens[x]==1);
            sens[t]=x;
            fvsens[x]=1;
        }
        for(t=1;t<=4;t++)
            traseu(i+dirx[sens[t]],j+diry[sens[t]],lng);
        if(k==lng)
        {
            x2=i;
            y2=j;
        }
        k--;
        a[i][j]=0;
    }

}
void init(int i, int j , int lng)
{
    k=0;
    lscurt=999999;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
        a[i][j]=0;
    lng=rand()%12+5; ///Lungime traseu sigur random
    x1=rand()%n+1;
    y1=rand()%n+1;
    traseu(x1,y1,lng);
    MarkTraseu(lng);
    xc=x1;yc=y1;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            if(a[i][j]==0)
                a[i][j]=rand()%2;
}

int main()
{
    H=GetSystemMetrics(1)-100;
    f>>n;
    d=H/(n+4);
    W=d*(n+6);
    int i,j,ok=0,lng;
    initwindow(W,H,"Catch",W/5);
    srand(time(NULL));
    /*for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
        f>>a[i][j];
    */
    init(x1,y1,lng);
    arena();
    sol(x1,y1);
    k=1;
    while(ok==0)
    {
        ch=getch();
        if(ch=='w'&&a[xc-1][yc]==1)
        {
            k++;
            a[xc][yc]=2;
            readimagefile("pic/wall.jpg",d*(yc+2)+1,d*(xc+1)+1,d*(yc+3)-1,d*(xc+2)-1);
            xc--;
            readimagefile("pic/p1.jpg",d*(yc+2)+1,d*(xc+1)+1,d*(yc+3)-1,d*(xc+2)-1);
        }
        else
            if(ch=='s'&&a[xc+1][yc]==1)
        {
            k++;
            a[xc][yc]=2;
            readimagefile("pic/wall.jpg",d*(yc+2)+1,d*(xc+1)+1,d*(yc+3)-1,d*(xc+2)-1);
            xc++;
            readimagefile("pic/p1.jpg",d*(yc+2)+1,d*(xc+1)+1,d*(yc+3)-1,d*(xc+2)-1);
        }
        else
            if(ch=='d'&&a[xc][yc+1]==1)
        {
            k++;
            a[xc][yc]=2;
            readimagefile("pic/wall.jpg",d*(yc+2)+1,d*(xc+1)+1,d*(yc+3)-1,d*(xc+2)-1);
            yc++;
            readimagefile("pic/p1.jpg",d*(yc+2)+1,d*(xc+1)+1,d*(yc+3)-1,d*(xc+2)-1);
        }
        else
            if(ch=='a'&&a[xc][yc-1]==1)
        {
            k++;
            a[xc][yc]=2;
            readimagefile("pic/wall.jpg",d*(yc+2)+1,d*(xc+1)+1,d*(yc+3)-1,d*(xc+2)-1);
            yc--;
            readimagefile("pic/p1.jpg",d*(yc+2)+1,d*(xc+1)+1,d*(yc+3)-1,d*(xc+2)-1);
        }

        if(xc==x2&&yc==y2)
        {
            ok=1;
            if(k<=lscurt)
            {
                readimagefile("pic/fundal.jpg",0,0,W,H);
                readimagefile("pic/win.jpg",3*d,5*d,13*d,10*d);
            do
            {
                ch=getch();
                if(ch=='r'||ch==27)
                readimagefile("pic/fundal.jpg",0,0,W,H);

                if(ch==27)
                    readimagefile("pic/admitted.jpg",3*d,5*d,13*d,10*d);
                else
                    if(ch=='r')
                {

                    ok=0;
                    init(x1,y1,lng);
                    arena();
                    sol(x1,y1);
                    k=1;
                }
            }
            while(ch!='r');
            }
            else
            {
                readimagefile("pic/fundal.jpg",0,0,W,H);
                readimagefile("pic/faster.jpg",3*d,5*d,13*d,10*d);
                do
            {
                ch=getch();
                if(ch=='r'||ch==27)
                readimagefile("pic/fundal.jpg",0,0,W,H);

                if(ch==27)
                    readimagefile("pic/admitted.jpg",3*d,5*d,13*d,10*d);
                else
                    if(ch=='r')
                {

                    ok=0;
                    init(x1,y1,lng);
                    arena();
                    sol(x1,y1);
                    k=1;
                }
            }
            while(ch!='r');
            }
        }
        else
        if(a[xc-1][yc]!=1&&a[xc][yc-1]!=1&&a[xc+1][yc]!=1&&a[xc][yc+1]!=1)
        {
            ok=1;
            readimagefile("pic/fundal.jpg",0,0,W,H);
            readimagefile("pic/noob.jpg",3*d,5*d,13*d,10*d);
            do
            {
                ch=getch();
                if(ch=='r'||ch==27)
                readimagefile("pic/fundal.jpg",0,0,W,H);

                if(ch==27)
                    readimagefile("pic/admitted.jpg",3*d,5*d,13*d,10*d);
                else
                    if(ch=='r')
                {

                    ok=0;
                    init(x1,y1,lng);
                    arena();
                    sol(x1,y1);
                    k=1;
                }
        }while(ch!='r');
    }
        }
    delay(10000);




    return 0;
}
