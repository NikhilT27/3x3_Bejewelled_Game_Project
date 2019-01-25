// NIKHIL B THAKARE
// MINI +logic code new + mouse

#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
#include<conio.h>
#include<time.h>
#include<string.h>

int gd=DETECT,gm;
int A1,A2,A3,A4,S=0;
int x,y,cl,a,b;
const int size=3;
const int sim=3;
union REGS in,out;
int callmouse()
{
 in.x.ax=1;
 int86(51,&in,&out);
 return 1;
 }

void mouseposi(int &xpos,int &ypos,int &click)
 {
  in.x.ax=3;
  int86(51,&in,&out);
  click=out.x.bx;
  xpos=out.x.cx;
  ypos=out.x.dx;
 }

int mousehide()
 {
  in.x.ax=2;
  int86(51,&in,&out);
  return 1;
 }

void setposi(int &xpos,int &ypos)
 {
 in.x.ax=4;
 in.x.cx=xpos;
 in.x.dx=ypos;
 int86(51,&in,&out);
  }

int checkinputvalid(int ,int ,int,int);
void display(int N[size][size],int ,int ,int ,int ,int ,int ,int );
int check(int N[size][size],int );
int beginME(void );
void TheEnd(int );
//update
void copyMatrix(int N[3][3],int Z[3][3]);
void dispMatrix(int Z[3][3]);
int freezecondi(int N[3][3],int Z[3][3]);
int checkRfreeze(int Z[3][3]);
int checkCfreeze(int Z[3][3]);
void swapR(int Z[3][3],int ,int ,int ,int );
void swapC(int Z[3][3],int ,int ,int ,int );
void inst();
void invalid();

void main()
{
 int temp,click1=0,click2=0,ind1=0,ind2=0,i,j,chance=3,valid,N[size][size],result,Z[3][3],ch,rdn,S1,S2,levelC=1;
 ch=beginME();
 switch(ch)
{
 case 1:
 inst();
 srand(time(NULL));
 {for(i=0;i<size;i++)
 {
   for(j=0;j<size;j++)
    {
     rdn=1+rand()%4;
     N[i][j]=rdn;
    }
 }
 copyMatrix(N,Z);
 result=freezecondi(N,Z);
 S=check(N,S);
 S=0;
 for(chance;chance>0;chance--)
 {
  copyMatrix(N,Z);
  result=freezecondi(N,Z);
  display(N,S,chance,0,0,result,1,levelC);
  S=check(N,S);//here should be auto check
RETRY:
 click1=click2=0;
 copyMatrix(N,Z);
 result=freezecondi(N,Z);
 display(N,S,chance,ind1,ind2,result,0,levelC);
 setposi(a,b);
 callmouse();
 do
 {
   mouseposi(x,y,cl);
//   gotoxy(10,9);
  //  printf("\n\tMouse Position is: %d,%d",x,y);
  //  printf("\n\tClick: %d",cl);
   if(cl==1)
   {
    if((x>20&&x<380)&&(y>20&&y<380))
    {

		 //rintf("count====%d",count);
    if(x>20&&x<140)
    {  A2=0;
      }
     else
    if(x>140&&x<260)
     {  A2=1;
       }
     else
     if(x>260&&x<380)
     {  A2=2;
	 }
    if(y>20&&y<140)
     {
       A1=0;
       }
      else
     if(y>140&&y<260)
     {   A1=1;
       }
     else
      if(y>260&&y<380)
     {   A1=2;
       }
       // printf("\n1=================[%d][%d]",A1,A2);
     click1=1; }
	}

     if(cl==2)
      {
       if((x>20&&x<380)&&(y>20&&y<380))
	 {
	if(x>20&&x<140)
	{    A4=0;
	  }
	 else
	 if(x>140&&x<260)
	 {     A4=1;
	   }
	 else
	  if(x>260&&x<380)
	 {   A4=2;
	   }
	 if(y>20&&y<140)
	  {
	    A3=0;
	    }
	   else
	  if(y>140&&y<260)
	  {    A3=1;
	    }
	 else
	   if(y>260&&y<380)
	  {     A3=2;
	    }

	    ///  printf("\n2-----[%d][%d]\n",A3,A4);
	 click2=1;}
	   }
	   else
	  if(cl==1)
	  { if(((x>440)&&(x<490))&&((y>400)&&(y<430)))
	   {
	  click1=1;
	  click2=1;
	  chance=0;
	   }}
	  }while((click1==0)||(click2==0));
if(chance==0)
{goto LAST;}
valid=checkinputvalid(A1,A2,A3,A4);
if(valid==1)
  // swapping of element
 {
  temp=N[A1][A2];
  N[A1][A2]=N[A3][A4];
  N[A3][A4]=temp;

 display(N,S,chance,ind1,ind2,result,1,levelC);
 S1=S;
  S=check(N,S);

 if(S1==S)
  {
  temp=N[A1][A2];
  N[A1][A2]=N[A3][A4];
  N[A3][A4]=temp;
 }
 if((S%50)==0)
 {levelC++;
 }
 display(N,S,chance,ind1,ind2,result,1,levelC);
 }else
 {invalid();
goto RETRY;
}
 }

}

case 2:
{break;}
};
 LAST:
 closegraph();
 TheEnd(S);
 getch();
}

/*---------------------------------------*/
void display(int N[size][size],int S,int CL,int i1,int i2,int PM,int CG,int levelcount)//PM=possible moves,CL=chance left
{
   int i,j,C[9],c=0;
   char ch,arr1[5],arr2[5],arr3[5],inde1[2],inde2[2],LC[2];

  for(i=0;i<size;i++)
 {
   for(j=0;j<size;j++)
    {if(N[i][j]==1)
     {C[c]=9;}
     else
     if(N[i][j]==2)
     {C[c]=10;}
     else
     if(N[i][j]==3)
     {C[c]=12;}
     else
     if(N[i][j]==4)
     {C[c]=14;}
     c++;
    }

 }
 int rect1[10]={20,380,20,20,380,20,380,380,20,380};
 int rect2[10]={10,460,10,10,590,10,590,460,10,460};
 int rect3[10]={10,460,10,10,400,10,400,460,10,460};

  //diamond array
 int diamond1[12]={60,50,100,50,110,60,80,110,50,60,60,50};
 int diamond2[12]={180,50,220,50,230,60,200,110,170,60,180,50};
 int diamond3[12]={300,50,340,50,350,60,320,110,290,60,300,50};
 int diamond4[12]={60,170,100,170,110,180,80,230,50,180,60,170};
 int diamond5[12]={180,170,220,170,230,180,200,230,170,180,180,170};
 int diamond6[12]={300,170,340,170,350,180,320,230,290,180,300,170};
 int diamond7[12]={60,290,100,290,110,300,80,350,50,300,60,290};
 int diamond8[12]={180,290,220,290,230,300,200,350,170,300,180,290};
 int diamond9[12]={300,290,340,290,350,300,320,350,290,300,300,290};
 //small black squares
 int sq1[10]={500,175,500,145,580,145,580,175,500,175};
 int sq2[10]={550,225,550,195,580,195,580,225,580,225};
 int sq5[10]={550,275,550,245,580,245,580,275,580,275};
 int tdia1[12]={550,125,530,90,536,78,564,78,570,90,550,125};
 int level=0;
 level=((S/10)*34);

 initgraph(&gd,&gm,"C:\\TurboC3\\BGI");
 rectangle(1,1,638,478);
 setfillstyle(9,8);
 fillpoly(5,rect2); /* Boader */
 setfillstyle(9,7);
 fillpoly(5,rect3);
 setfillstyle(1,0);
 fillpoly(5,rect1); /* Square(Main Game) */
 setlinestyle(0,0,0);
 setfillstyle(1,0);
 fillpoly(5,sq1);
 fillpoly(5,sq2);
 fillpoly(5,sq5);
 bar(20,400,380,440);

 //line
 line(20,140,380,140);
 line(20,260,380,260);
 line(140,20,140,380);
 line(260,20,260,380);
 line(400,10,400,460);

 //Index Number
 outtextxy(30,30,"1>");
 outtextxy(150,30,"2>");
 outtextxy(270,30,"3>");
 outtextxy(30,150,"4>");
 outtextxy(150,150,"5>");
 outtextxy(30,270,"7>");
 outtextxy(270,150,"6>");
 outtextxy(150,270,"8>");
 outtextxy(270,270,"9>");

 //COLOUR TO GEMS
 setfillstyle(6,C[0]);
 fillpoly(6,diamond1);
 setfillstyle(6,C[1]);
 fillpoly(6,diamond2);
 setfillstyle(6,C[2]);
 fillpoly(6,diamond3);
  setfillstyle(6,C[3]);
  fillpoly(6,diamond4);
  setfillstyle(6,C[4]);
 fillpoly(6,diamond5);
  setfillstyle(6,C[5]);
 fillpoly(6,diamond6);
  setfillstyle(6,C[6]);
 fillpoly(6,diamond7);
  setfillstyle(6,C[7]);
 fillpoly(6,diamond8);
  setfillstyle(6,C[8]);
 fillpoly(6,diamond9);


 //BEJEWELED GAME TITLE
 setcolor(10);
 settextstyle(9,0,1);
 outtextxy(410,30,"BEJEWELED");
 outtextxy(411,30,"BEJEWELED");
 outtextxy(412,30,"BEJEWELED");
 setcolor(10);
 setfillstyle(1,10);
 fillpoly(6,tdia1);
 setcolor(10);
 outtextxy(430,70,"GAME");
 outtextxy(431,70,"GAME");
 outtextxy(432,70,"GAME");

 setcolor(14);
 line(410,70,570,70);
 line(450,110,520,110);
 setcolor(15);
 settextstyle(2,0,7);
 outtextxy(410,150,"SCORED :");
 outtextxy(411,150,"SCORED :");
 sprintf(arr1,"%d",S);//sprintf---->use to display no. store as character
 outtextxy(510,150,arr1);

 setcolor(15);
 setlinestyle(3,0,0);
 line(410,175,480,175);
 settextstyle(2,0,7);
 outtextxy(410,200,"CHANCE LEFT:");
 outtextxy(411,200,"CHANCE LEFT:");
 sprintf(arr2,"%d",CL);
 outtextxy(555,200,arr2);

 setlinestyle(3,0,0);
 line(410,225,535,225);

 settextstyle(2,0,7);
 outtextxy(410,250,"POSSIBLE ");
 outtextxy(411,250,"POSSIBLE ");
 outtextxy(470,270,"MOVES:");
 outtextxy(471,270,"MOVES:");
 sprintf(arr3,"%d",PM);
 outtextxy(555,250,arr3);

 setcolor(15);
 settextstyle(6,0,1);
 outtextxy(30,400,"Select GEMS using different mouse buttons");
 outtextxy(31,400,"Select GEMS using different mouse buttons");

 //Level up bar
 setlinestyle(0,0,0);
 setfillstyle(0,12);
 bar(20,435,580,455);//level up bar
 rectangle(21,436,579,454);
 setfillstyle(1,11);
 sprintf(LC,"%d",levelcount);

 bar(160,440,(level%340)+160,450);//increase level bar
 rectangle(159,439,501,451);

 int arrow1[8]={538,420,548,430,528,430,538,420};
 fillpoly(4,arrow1);
 settextstyle(0,0,1);
 outtextxy(510,442,"LEVEL UP");
 outtextxy(30,442,"EXPERIENCE BAR");
 settextstyle(6,0,3);
 outtextxy(532,380,LC);
 outtextxy(533,380,LC);
 outtextxy(534,380,LC);

 settextstyle(6,0,2);
 setcolor(12);
 outtextxy(450,400,"EXIT");
 outtextxy(451,400,"EXIT");
 rectangle(440,400,490,430);


 if(CG==1)
 {closegraph();}
}

/*---------------------------------------*/
int checkinputvalid(int A1,int A2,int A3,int A4)
{
 {
  if((A1==0)&&(A2==0))
  {if(((A3==0)&&(A4==1))||((A3==1)&&(A4==0)))
   return(1);
  }
   if((A1==0)&&(A2==1))
  {if(((A3==0)&&(A4==0))||((A3==1)&&(A4==1))||((A3==0)&&(A4==2)))
   return(1);
  }
  if((A1==0)&&(A2==2))
  {if(((A3==0)&&(A4==1))||((A3==1)&&(A4==2)))
   return(1);
  }
   if((A1==1)&&(A2==0))
  {if(((A3==0)&&(A4==0))||((A3==1)&&(A4==1))||((A3==2)&&(A4==0)))
   return(1);
  }
   if((A1==1)&&(A2==1))
  {if(((A3==0)&&(A4==1))||((A3==1)&&(A4==0))||((A3==1)&&(A4==2))||((A3==2)&&(A4==1)))
   return(1);
  }
     if((A1==1)&&(A2==2))
  {if(((A3==0)&&(A4==2))||((A3==1)&&(A4==1))||((A3==2)&&(A4==2)))
   return(1);
  }
   if((A1==2)&&(A2==0))
  {if(((A3==1)&&(A4==0))||((A3==2)&&(A4==1)))
   return(1);
  }
   if((A1==2)&&(A2==1))
  {if(((A3==2)&&(A4==0))||((A3==1)&&(A4==1))||((A3==2)&&(A4==2)))
   return(1);
  }
    if((A1==2)&&(A2==2))
  {if(((A3==2)&&(A4==1))||((A3==1)&&(A4==2)))
   return(1);
  }

 }

return(0);
}

/*---------------------------------------*/
int check(int N[size][size],int score)
{
 int random,x,root,i,j,c=0,r=0,countR=0,countC=0,val,prevscore;//GO=GameOver
  // For row check
do{
  prevscore=score;
  srand(time(NULL));
  for(i=0;i<size;i++)
 {
   root=N[i][c];
   countR=0;
   for(j=0;j<size;j++)
    {if(root==(N[i][j]))
     {countR++;
      if(countR==sim)
      {x=j;
       for(x=j;x>j-sim;x--)
       { Again1:
	 random=1+rand()%4;
	 if(random==root)
	 {goto Again1;}
	 N[i][x]=random;}
	 score+=10;
	countR=1;
	root=N[i][j];

	}
      }	else
      {countR=1;
       root=N[i][j];
      }
      }
     }

printf("\n/*-----------------*/\n");
  srand(time(NULL));
  for(i=0;i<size;i++)
 {
   root=N[r][i];
   countC=0;
   for(j=0;j<size;j++)
    {if(root==(N[j][i]))
     {countC++;
      if(countC==sim)
      {
       x=j;
       for(x=j;x>j-sim;x--)
       { Again2:
	 random=1+rand()%4;
	 if(random==root)
	 {goto Again2;}
	 N[x][i]=random;}
	  score+=10;
	countC=1;
	root=N[j][i];
	}
      }	else
      {countC=1;
       root=N[j][i];
      }
      }
     }
}while(prevscore!=score);
return(score);
}

/*---------------------------------------*/
int beginME(void )
{
 int i=0,X=10,Y=0,choice;
 initgraph(&gd,&gm,"C:\\TurboC3\\BGI");
 int Bigdiamond1[12]={120,100,220,100,270,150,170,300,70,150,120,100};
 int Sdiamond1[12]={70,170,110,170,120,180,90,230,60,180,70,170};
 int Sdiamond2[12]={190,230,230,230,240,240,210,290,180,240,190,230};

 while(i<15)
 {
  cleardevice();
  rectangle(1,1,638,478);

  setcolor(14);
  settextstyle(9,0,0);
  outtextxy(X,130,"BEJEWELED");
  outtextxy(X+1,130,"BEJEWELED");
  outtextxy(X+2,130,"BEJEWELED");

  outtextxy(Y+30,180,"GAME");
  outtextxy(Y+31,180,"GAME");
  outtextxy(Y+32,180,"GAME");

  setcolor(7);
  settextstyle(2,0,8);
  outtextxy(Y+30,240,"* START :)");
  outtextxy(Y+30,260,"* EXIT  :(");
  settextstyle(2,0,7);
  outtextxy(X,360,"MADE BY:");
  outtextxy(250,Y-20,"NIKHIL B. THAKARE");
  delay(50);
  X=X+20;
  Y=Y+30;
  i++;
  }
  setfillstyle(6,10);
  fillpoly(6,Bigdiamond1);
  setfillstyle(6,12);
  fillpoly(6,Sdiamond1);
  setfillstyle(6,14);
  fillpoly(6,Sdiamond2);
	     setposi(a,b);
	     callmouse();
	     do
	     {
		    mouseposi(x,y,cl);
		    gotoxy(10,9);

		   if(cl==1)
		   {
		    if(((x>450)&&(x<600))&&((y>240)&&(y<260)))
		    {choice=1;}
		    if(((x>450)&&(x<600))&&((y>260)&&(y<280)))
		    {choice=2;}

		   }
	   }while((choice!=1)&&(choice!=2));
	     mousehide();

  closegraph();
  return(choice);

}

/*---------------------------------------*/
void TheEnd(int S)
{
 char arr[20],name[10];
 FILE *fp2;
 fp2=fopen("SCORE1.txt","r");
 if(fp2!=NULL)
 {
  fgets(name,10,fp2);
 }
 int gd=DETECT,gm,i=0,X=10,Y=0;
 initgraph(&gd,&gm,"C:\\TurboC3\\BGI");
 while(i<15)
 {
  cleardevice();
  rectangle(1,1,638,478);

  setcolor(12);
  settextstyle(9,0,4);
  outtextxy(Y+10,150,"GAME OVER");
  outtextxy(Y+11,150,"GAME OVER");
  outtextxy(Y+12,150,"GAME OVER");

  setcolor(7);
  settextstyle(2,0,9);
  outtextxy(Y-90,240,name);
  outtextxy(Y+30,240,"SCORED:");
  sprintf(arr,"%d",S);
  outtextxy(X+30,240,arr);
  delay(50);
  X=X+25;
  Y=Y+15;
  i++;
  }
  getch();
  closegraph();
}

/*---------------------------------------*/
void copyMatrix(int N[3][3],int Z[3][3])
{
int i,j;
 for(i=0;i<3;i++)
 {
  for(j=0;j<3;j++)
  { Z[i][j]=N[i][j]; }
 }
}

/*----------------------------------*/
void swapR(int Z[3][3],int d,int e,int f,int g)
{
 int temp;
 temp=Z[d][e];
 Z[d][e]=Z[f][g];
 Z[f][g]=temp;
}
/*----------------------------------*/
void swapC(int Z[3][3],int e,int d,int g,int f)
{
 int temp;
 temp=Z[d][e];
 Z[d][e]=Z[f][g];
 Z[f][g]=temp;
}
/*----------------------------------*/
int freezecondi(int N[3][3],int Z[3][3])
{
 int count=0,i,j,rdn;
   swapR(Z,0,0,1,0); //1r
  if((checkRfreeze(Z))==1)
   {count++;}
   swapR(Z,0,0,1,0);

    swapR(Z,1,0,2,0); //2r
  if((checkRfreeze(Z))==1)
   {count++;}
   swapR(Z,1,0,2,0);

    swapR(Z,0,1,1,1); //3r
  if((checkRfreeze(Z))==1)
   {count++;}
  swapR(Z,0,1,1,1);

   swapR(Z,1,1,2,1);//4
  if((checkRfreeze(Z))==1)
   {count++;}
  swapR(Z,1,1,2,1);


    swapR(Z,0,2,1,2);//5
  if((checkRfreeze(Z))==1)
   {count++;}
   swapR(Z,0,2,1,2);


    swapR(Z,0,0,0,1);//6
  if((checkRfreeze(Z))==1)
   {count++;}
   swapR(Z,0,0,0,1);

  //column
   swapC(Z,0,0,1,0); //1c
  if((checkCfreeze(Z))==1)
   {count++;}
   swapC(Z,0,0,1,0);

    swapC(Z,1,0,2,0); //2c
  if((checkCfreeze(Z))==1)
   {count++;}
   swapC(Z,1,0,2,0);

    swapC(Z,0,1,1,1); //3c
  if((checkCfreeze(Z))==1)
   {count++;}
   swapC(Z,0,1,1,1);

   swapC(Z,1,1,2,1);//4
  if((checkCfreeze(Z))==1)
   {count++;}
   swapC(Z,1,1,2,1);

    swapC(Z,0,2,1,2);//5
  if((checkCfreeze(Z))==1)
   {count++;}
   swapC(Z,0,2,1,2);

    swapC(Z,0,0,0,1);//6
  if((checkCfreeze(Z))==1)
   {count++;}
   swapC(Z,0,0,0,1);


  if(count==0)
  {
    for(i=0;i<size;i++)
   {
     for(j=0;j<size;j++)
    {
     rdn=1+rand()%4;
     N[i][j]=rdn;
    }
   }
  }

   return(count);
}

/*----------------------------------*/
int checkRfreeze(int Z[3][3])
{
   int root,i,j,c=0,countR=0;
   // For row check
  for(i=0;i<3;i++)
 {
   root=Z[i][c];
   countR=0;
   for(j=1;j<3;j++)
    {if(root==(Z[i][j]))
     { countR++;
       if(countR==2)
	 {for(j=2;j>=0;j--)
	   {return 1;}
	 }
     }
    }
 }
 return 0;
}
/*----------------------------------*/
int checkCfreeze(int Z[3][3])
{
   int root,i,j,r=0,countC=0;
   for(j=0;j<3;j++)
 {
   root=Z[r][j];
   countC=0;
   for(i=1;i<3;i++)
    {if(root==(Z[i][j]))
     {countC++;
      if(countC==2)
      { for(i=2;i>=0;i--)
       {return 1;}
      }
      }
     }
    }
 return(0);


}
/*----------------------------------*/

void inst()
{
 int instexit=0;
 char name[15];
 FILE *fp1;
 fp1=fopen("SCORE1.txt","w");

 int gd=DETECT,gm,tri1[8]={90,115,80,125,80,105,90,115},tri2[8]={560,420,580,420,570,430,560,420},blink=0;
 initgraph(&gd,&gm,"C:\\TurboC3\\BGi");

while(blink!=3)
{ cleardevice();
 if((blink%2)==0)
 { fillpoly(4,tri1);}
 rectangle(1,1,638,478);
 settextstyle(6,0,1);
 outtextxy(100,100,"NAME PLZ !! ");
 rectangle(250,100,370,130);
 blink++;
 delay(300);
 }
 scanf("%s",&name);
 if(fp1!=NULL)
 {
  fputs(name,fp1);
 }
 fclose(fp1);
 setcolor(14);
 outtextxy(270,100,name);
 setcolor(15);
  outtextxy(180,240,"Select any two adjacent gems to swap,");
  outtextxy(170,270,"three similar gems lead to increase in score");
 settextstyle(1,0,2);
 outtextxy(270,200,"INSTRUCTION");
 rectangle(160,190,515,310);
 settextstyle(6,0,1);
 while(blink!=8)
 {if((blink%2)==0)
 {setfillstyle(1,0);}
  else
  setfillstyle(1,15);
  fillpoly(4,tri2);
  outtextxy(520,430,"Click Here");
  rectangle(510,430,620,460);
  blink++;
  delay(300);
  }
	     setposi(a,b);
	     callmouse();
	     do
	     {
		    mouseposi(x,y,cl);
		    gotoxy(10,9);
		   if(cl==1)
		   {
		    if((x>510&&x<600)&&(y>430&&y<460))
		    {instexit=1;}
		   }

	     }while(instexit!=1);
	     mousehide();
 closegraph();
 }

void invalid()
{
  initgraph(&gd,&gm,"C:\\TurboC3\\BGi");
  setfillstyle(1,0);
  bar(1,199,638,279);
  rectangle(3,201,636,277);
  setcolor(14);
  settextstyle(2,0,7);
  outtextxy(200,225,"Invalid Input RETRY !");
  outtextxy(201,225,"Invalid Input RETRY !");
  outtextxy(202,225,"Invalid Input RETRY !");
  delay(300);
  closegraph();

}
