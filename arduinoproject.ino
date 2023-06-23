#define a1 10
#define b1 11
#define c1 12
#define d1 13
#define A1 A0
#define B1 A1
#define C1 A2
#define D1 A3
int initial=1;
#define CLOCK_INTERRUPT_PIN 1
#include "RTClib.h"
RTC_DS3231 rtc;
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
char s[4][3]={"1st","2d","3rd","4th"};
char ch[7][10]={"M","Tu","W","Th","Fr","Sat","Sun"};
int T[7]={0,0,0,0,0,0,0};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
char v;

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
int a=0,i=0;
typedef struct
{
  int hourr;
  int minu;
  
}wakt;
wakt morning_dose,lunch_dose,night_dose; 

typedef struct 
{
  wakt tprise;
  int quantite;
}dose;
typedef struct
{
  int nbrest;
  int T[7]={0,0,0,0,0,0,0};
  int reg;
  dose* prises[7];
}dwe;
typedef struct noeudwe
{
  dwe d;
  int colonne;
  noeudwe* next;
}noeudwe;
typedef noeudwe* liste;
liste l;
int gethour(int n,int col,int lin)
{
  lcd.setCursor(col,lin);
  reglage(n);
  lcd.setCursor(col,lin);
  int  h=0;
  char v;
  int i=0;
  v = customKeypad.getKey();
  while(i<2)
  {
    v = customKeypad.getKey();
    if (v=='*')
{
  lcd.setCursor(col,lin);
  reglage(n);
  lcd.setCursor(col+2,lin);   
    return(n);
}
    else if((v>47)&&(v<58))
    {
      lcd.print(v);
      h=h*10+int(v)-48;
      i++;
    
    }
     
  }

  if(h<24)
  return(h);
  else{
   
    return(gethour(n,col,lin));
  }
    
    
}
int getmin(int n,int col,int lin)
{
  lcd.setCursor(col,lin);
  reglage(n); 
  lcd.setCursor(col,lin);
  int  h=0;
  char v;
  int i=0;
  v = customKeypad.getKey();
  while(i<2)
  {
    v = customKeypad.getKey();
    if((v>47)&&(v<58))
    {
      lcd.print(v);
      h=h*10+int(v)-48;
      i++;
    }
    else if (v=='*')
    {
      lcd.setCursor(col,lin);
      reglage(n);
      lcd.setCursor(col+2,lin);
    return(n);
    
  }
  }
  if(h<60)
  return(h);
  else{
  
    return(getmin(n,col,lin));
  }  
}
wakt getwakt(int hourr,int minu,int col,int lin)
{
  wakt t;
  t.hourr=hourr;
  t.minu=minu;
  lcd.setCursor(col,lin);
  reglage(hourr);
  lcd.print(':');
  reglage(minu);
  t.hourr=gethour(hourr,col,lin);
  lcd.print(":");
  t.minu=getmin(minu,col+3,lin);
  return(t);
}
/*dose getdose(int i,char *s)
{
char s[4][3]={"1st","2d","3rd","4th"};
  dose B;
  lcd.setCursor(5,i);
  lcd.print(s);
  lcd.print(" 00:00 n=");
  B.tprise=getwakt(8,i);
  lcd.print(" n=");
  B.nbr=getnum();
  return(B);
}*/

int getnumofi(int n,int i,int col,int lin)
{
  int  h=0;
  char v;
  int j=0;
  lcd.setCursor(col,lin);
  
  if(i!=1)reglage(n);else lcd.print(n); 
  lcd.setCursor(col,lin);
  v = customKeypad.getKey();
  while(j<i)
  {
    v = customKeypad.getKey();
   
    if((v>47)&&(v<58))
    {
      lcd.print(v);
      h=h*10+int(v)-48;
      j++;
    }
    else if (v=='*')
    {
      lcd.setCursor(col+2,lin);
    return(n);
    
  }
  }
  
  return(h);
  
}  
void reglage(int n)
{
  if(n<10)
  {
    lcd.print("0");
    lcd.print(n);
  }
  else lcd.print(n);
}
void setdosestime(wakt* morning_dose,wakt* lunch_dose,wakt* night_dose) 
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("morning ");
  reglage((*morning_dose).hourr);lcd.print(":");
  reglage((*morning_dose).minu);
  lcd.setCursor(0,1);
  lcd.print("midday ");
  reglage((*lunch_dose).hourr);lcd.print(":");
  reglage((*lunch_dose).minu);  
  lcd.setCursor(0,2);
  lcd.print("night ");
  reglage((*night_dose).hourr);lcd.print(":");
  reglage((*night_dose).minu);
  char o=customKeypad.getKey();
  while(o!='#')
  {o=customKeypad.getKey();
  if(o=='A')
  (*morning_dose)=getwakt((*morning_dose).hourr,(*morning_dose).minu,8,0);
  if(o=='B')
  (*lunch_dose)=getwakt((*lunch_dose).hourr,(*lunch_dose).minu,7,1);
 if(o=='C')
  (*night_dose)=getwakt((*night_dose).hourr,(*night_dose).minu,6,2);
}
//if(o!='D')
}
void displine()
{
  int i;
  for(i=0;i<4;i++)
  {
    lcd.setCursor(6,i);
    lcd.print('|');
  }
}
void dispday(int i)
{
  const char s[7][10]={"SUN","MOND","TUES","WEDNES","THURS","FRI","SATUR"};
  lcd.setCursor(6-strlen(s[i]),1);lcd.print(s[i]);
  lcd.setCursor(3,2);lcd.print("DAY");
  displine();
}
void dispdaysreps(int* T)
{
  char s[7][10]={"Sun","M","Tu","W","Th","Fr","Sat"};
    int i=0;
    lcd.setCursor(0,0);
    while(i<7)
    {
      lcd.print(s[i]);
      lcd.print(' ');
      i++;
    }
    i=0;int p=2;
    while(i<7)
    {
      lcd.setCursor(p-1,2);
      lcd.print(T[i]);
      if(p==8)p=p+2;else p=p+3;
      i++;
    }
   
  
}

void dispdose(dose d,int i)
{
  char s[4][5]={"1ST ","2ND ","3RD ","4TH "};
  lcd.setCursor(7,i-1);
  lcd.print(s[i-1]);
 
  reglage(d.tprise.hourr);

  lcd.print(':');
  reglage(d.tprise.minu);
  lcd.print(" Q=");
  lcd.print(d.quantite);
}
void initdose(dose* d)
{
  (*d).tprise.hourr=0;
  (*d).tprise.minu=0;
  (*d).quantite=0;
}
dose getdose(int i,dose b)
{
  dose d;
  
  dispdose(d,i);
  d.tprise=getwakt(b.tprise.hourr,b.tprise.minu,11,i-1);
  d.quantite=getnumofi(b.quantite,1,19,i-1);
  return(d);
} 
void getdose1(int i,dose *d)
{
  
  
  dispdose(*d,i);
  (*d).tprise=getwakt((*d).tprise.hourr,(*d).tprise.minu,11,i-1);
  (*d).quantite=getnumofi((*d).quantite,1,19,i-1);
 
}
/*void getdoses(int r,dose* A)
{
  int i;
  for(i=0;i<r;i++)
  {
   
    initdose(&A[i]);
    dispdose(A[i],i+1);
  }
  i=0;
  for(i=0;i<r;i++)
  {
    getdose1(i+1,&A[i]);
  }
}*/
void getdoses1(int r,dose* A)
{
  int i;
  for(i=0;i<r;i++)
  {
    dispdose(A[i],i+1);
    
  }
  i=0;
  for(i=0;i<r;i++)
  {
    getdose1(i+1,&A[i]);
  }
}
void takerep(int *T)
{
  lcd.cursor();
  int i; int p=2;
  while(i<7)
  {
    
    T[i]=getnumofi(T[i],1,p-1,2);
    i++;
    if(p==8) p=p+2;else p=p+3;
  }
}
void remplirtabdoses(dose** t,wakt morning_dose,wakt lunch_dose,wakt night_dose,int a,int b,int c)
{
  int i=0,j=0;
  for(i=0;i<7;i++)
  {
    for(j=0;j<3;j++)
    {
      if(j==0)
      {
        (t[i][j]).tprise=morning_dose;
        (t[i][j]).quantite=a; 
      }
      if(j==1)
      {
        (t[i][j]).tprise=lunch_dose;
        (t[i][j]).quantite=b; 
      }
      if(j==2)
      {
        (t[i][j]).tprise=night_dose;
        (t[i][j]).quantite=c; 
      }
    }
  }
}

void reglayout(int *a,int *b,int *c)
{
  lcd.cursor();
  lcd.setCursor(3,0);
  lcd.print("TIME|   QUANTITY");
  lcd.setCursor(0,1);
  lcd.print("MORNING|");
  lcd.setCursor(14,1);
  reglage(*a);
  
  lcd.setCursor(2,2);
  lcd.print("LUNCH|");
  lcd.setCursor(14,2);
  reglage(*b);
  
  lcd.setCursor(2,3);
  lcd.print("NIGHT|");
  lcd.setCursor(14,3);
  reglage(*c);
  *a=getnumofi(*a,2,14,1);
  *b=getnumofi(*b,2,14,2);
  *c=getnumofi(*c,2,14,3);
}
void add_dose(dose**A,int *a)
{
  (*a)=(*a)+1;
  (*A)=(dose*)realloc(*A,(*a)*sizeof(dose));
  initdose(A[(*a)-1]);
  getdose1(*a,A[(*a)-1]);
  
  
}
void elimine_dose(dose** A,int *s,int a)
{
  dose*B=(dose*)malloc((*s)*sizeof(dose));
  for(int b=0;b<(*s);b++)
  {
    B[b]=*A[b];
  }
  free(*A);
  *s=(*s)-1;
  *A=(dose*)malloc((*s)*sizeof(dose));
  int i=1,j=1;
  while(i<(*s))
  {
    if(j!=a)
    {
      *A[i]=B[j];
      j++;
      i++;
    }
    else j++;
  }
  free(B);
  /*for(int b=0;b<(*s);b++)
  {
    dispdose
  }*/
}
dwe ajoutdwe(wakt morning_dose,wakt lunch_dose,wakt night_dose)
{
  dwe d;
  lcd.clear();
  lcd.print("nbrest=");
  d.nbrest=getnumofi(0,2,7,0);
  lcd.setCursor(0,1);
  lcd.print("A:SI REGULIER");
  lcd.setCursor(0,2);
  lcd.print("B:SI PERSONALISER");
  char o=customKeypad.getKey();
  int t=0;
  while(t==0)
  {
    o=customKeypad.getKey();
    if(o)
    {
    if(o=='A')
    {
      d.reg=1;t=1;
      int a=0,b=0,c=0;
      lcd.clear();
      reglayout(&a,&b,&c);
      
      for(int i=0;i<7;i++)
      {
        d.T[i]=3;
        d.prises[i]=(dose*)malloc(3*sizeof(dose));
      }
      remplirtabdoses(d.prises,morning_dose,lunch_dose,night_dose,a,b,c);
      
      
     }
    
    if(o=='B')
    {
      d.reg=2;t=2;
      lcd.clear();
      dispdaysreps(d.T);
      takerep(d.T);
      int x;
      lcd.clear();
      for(x=0;x<7;x++)
      {
        lcd.clear();
        dispday(x);
        lcd.setCursor(0,3);
        lcd.print("P=");
        lcd.print(d.T[x]);
        d.prises[x]=(dose*)malloc((d.T[x])*sizeof(dose));
        getdoses1(d.T[x],d.prises[x]);
      }
      
      
    }
    }
  }
  return(d);
}
void remplirtimedoses(dose** t,wakt morning_dose,wakt lunch_dose,wakt night_dose)
{
  int i=0,j=0;
  for(i=0;i<7;i++)
  {
    for(j=0;j<3;j++)
    {
      if(j==0)
      {
        (t[i][j]).tprise=morning_dose;
        
      }
      if(j==1)
      {
        (t[i][j]).tprise=lunch_dose;
         
      }
      if(j==2)
      {
        (t[i][j]).tprise=night_dose;
         
      }
    }
  }
}
void changingtime(dwe d,wakt morning_dose,wakt lunch_dose,wakt night_dose)
{
  if(d.reg==1)
  {
    remplirtimedoses(d.prises,morning_dose,lunch_dose,night_dose);
  }
}
liste checkdosestime(liste l,wakt morning_dose,wakt lunch_dose,wakt night_dose)
{
  liste l1=l;
  while(l1!=NULL)
  {
    changingtime(l1->d,morning_dose,lunch_dose,night_dose);
    l1=l1->next;
  }
  return(l);
}
dwe regdwe(dwe a)
{
  
  dwe b=a;
  int x;
  char v='9';
  int l=0;
  do
{
  lcd.clear();
  lcd.setCursor(0,2);
  lcd.print("CHOOSE A DAY ");
  lcd.setCursor(0,3);
  lcd.print("CHOOSE A NUM 0-->6");
  v=wait();
      if((v>47)&&(v<55))
      {
        char c;
        c=v;
        x=int(c)-48;
        lcd.clear();
        dispday(x);
        lcd.setCursor(0,3);
        lcd.print("P=");
        lcd.print(b.T[x]);
        for(int i=0;i<b.T[x];i++)
        {
          dispdose(b.prises[x][i],i+1);
        }
        /*
         for(int i=0;i<b.T[x];i++)
        {
          getdose1(i+1,&(b.prises[x][i]));
        }*/
        v=customKeypad.getKey();
        while(v!='#')
          {
              v=wait();
              if((v>48)&&(v<49+b.T[x]))
              {
                int i=0;
                char c;
                c=v;
                i=int(c)-48;
                getdose1(i,&(b.prises[x][i-1]));
              }
              
              if(v=='A')
              {
                b.T[x]++;
                b.prises[x]=(dose*)realloc(b.prises[x],(b.T[x])*sizeof(dose));
                initdose(&(b.prises[x][b.T[x]-1]));
                getdose1(b.T[x],&(b.prises[x][b.T[x]-1]));
                //add_dose(&(b.prises[x]),&(b.T[x]));
                
                lcd.setCursor(0,3);
                lcd.print("P=");
                lcd.print(b.T[x]);
                
                
              }
              if(v=='B')
              {
                lcd.clear();
                lcd.print("ENTER NUM OF DOSE");
                lcd.setCursor(5,1);
                lcd.print("TO DELETE");
                int y=0;                
                while(y==0)
                {
                  
              v=customKeypad.getKey();
              if((v>48)&&(v<49+b.T[x]))
                {
                  y=1;
                  lcd.setCursor(10,2);
                lcd.print(v);    
                  int i=0;
                  char c;
                  c=v;
                i=int(c)-48;
                elimine_dose(&(b.prises[x]),&(b.T[x]),i-1);
                lcd.clear();
                dispday(x);
                lcd.setCursor(0,3);
                lcd.print("P=");
                lcd.print(b.T[x]);
                for(int i=0;i<b.T[x];i++)
                {
                    dispdose(b.prises[x][i],i+1);
                }
                
              
                }
                
                }
                
                
              }
             lcd.setCursor(0,0);
      lcd.print("ekteb"); 
          v=wait();
          }
          v='a';
      
      lcd.setCursor(0,0);
      lcd.print("ekteb");}
      else if(v=='#')l=1; 
     
      
}while(l==0);

  return(b);
}
char wait()
{
  char v=(customKeypad.getKey());
  
  while(!v)
  {
  v=(customKeypad.getKey());
  }
  return(v);
  
}
wakt addnmin(wakt a,int nmin)
{
  wakt t;
  t=a;
  t.minu=t.minu+nmin;
  if ((t.minu)>=60)
  {
    t.minu=t.minu-60;
    (t.hourr)++;
  }
  return(t);
}
wakt substractnmin(wakt a,int nmin)
{
  wakt t;
  t=a;
  t.minu=t.minu-nmin;
  if(t.minu<0)
  {
    t.minu=t.minu+60;
    t.hourr--;
  }
  return(t);
  
  
}
int checkwakt(wakt t,int acthour,int actmmin)
{
  
}
int check(liste l,int n,int col,int lin)
{
  int i;
  int p=0;
  int b=0;
  i=getnumofi(0,1,col,lin);
  if(n==0)return(i);
 else
 {
  while((l->colonne!=i)&&(l->next!=NULL))
  {
    l=l->next;
  }
  if((l->next==NULL)&&(l->colonne!=i))return(i);
  else 
  {
  lcd.setCursor(3,2);
  lcd.print("ALREADY USED");
  return (check(l,n,col,lin));
  }
 }
}
liste ajoudwe(liste l,wakt morning_dose,wakt lunch_dose,wakt night_dose,int *n)
{
  int i;
  lcd.clear();
  lcd.print("SLOT NUMBER=");
  i=check(l,*n,12,0);
  (*n)++;
  liste l1;
  l1=(noeudwe*)malloc(sizeof(noeudwe));
  (l1->d)=ajoutdwe(morning_dose,lunch_dose,night_dose);
  (l1->colonne)=i;
  (l1->next)=l;
  return(l1);
}
liste eliminedweslotnum(liste l,int slot,int *n)
{     
  int p=0;

      (*n)--;
      /*for(p=0;p<n;p++)
      {
        if (T[p]==slot)T[p]=0;
      }*/
      liste l1=l;
      liste l2;
      if((l1->colonne)==slot)
      {
        l1=l1->next;
     free(l);
      
        return(l1);
      }
      else
      {
      
        while((((l1->next)->colonne)!=slot)&&((l1->next)!=NULL))
        {
          l1=l1->next;
        }
        if(l1->next!=NULL)
        liste l2=l1->next;
        l1->next=(l1->next)->next;
        free(l2);
        return(l);
      }
  
  
}
liste regdweslotnum(liste l,int slot)
{     
      liste l1=l;
      liste l2;
      if((l1->colonne)==slot)
      {
        l1->d=regdwe(l1->d);
      } 
      else
      {
      
        while((((l1->next)->colonne)!=slot)&&((l1->next)!=NULL))
        {
          l1=l1->next;
        }
        if(l1->next!=NULL)
        {
        liste l2=l1->next;
        l2->d=regdwe(l2->d);
        }
      }
  
  return(l);
}
int getday(char* s)
{
  char ch[7][4]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
  int i=0;
  while((ch[i][0]!=s[0])||(ch[i][1]!=s[1])||(ch[i][2]!=s[2]))
  {
   i++;
  }
  return(i);
}
void write(int a,int b,int c,int d){
digitalWrite(a1,a);
digitalWrite(b1,b);
digitalWrite(c1,c);
digitalWrite(d1,d);
}
void write1(int a,int b,int c,int d){
digitalWrite(A1,a);
digitalWrite(B1,b);
digitalWrite(C1,c);
digitalWrite(D1,d);
}
void onestep1(){
write1(1,0,0,0);
delay(2.5);
write1(1,1,0,0);
delay(2.5);
write1(0,1,0,0);
delay(2.5);
write1(0,1,1,0);
delay(2.5);
write1(0,0,1,0);
delay(2.5);
write1(0,0,1,1);
delay(2.5);
write1(0,0,0,1);
delay(2.5);
write1(1,0,0,1);
delay(2.5);
}

void onestep(){
write(1,0,0,0);
delay(5);
write(1,1,0,0);
delay(5);
write(0,1,0,0);
delay(5);
write(0,1,1,0);
delay(5);
write(0,0,1,0);
delay(5);
write(0,0,1,1);
delay(5);
write(0,0,0,1);
delay(5);
write(1,0,0,1);
delay(5);
}
void turnmotorntours(int n)
{ int o=n*512;
  int y=0;
  while(y<o)
  {
    onestep();
    y++;
  }
}
void selectslot(int n)
{
 gooto(n);
 delay(1500); 
}
void gooto(int z)
{
 
  int u;
   if(z!=initial)
   {
    
    if (z<initial)
   {
    Serial.print("a");
    u=(3-initial)+z;Serial.print(u);
    u=(u*512)/3;
    
    int f=0;
    while(f<u)
    {
      onestep1();
      f++;
    }
   }
    else
    {Serial.print("b");
      u=z-initial;Serial.print(u);
      u=(u*512)/3;
      
      int f=0;
    while(f<u)
    {
      onestep1();
      f++;
    }
    }
    initial=z;
  Serial.print(initial);
}
}
void servall()
{
  lcd.clear();
  lcd.print("serving");
  delay(5000);
  DateTime now = rtc.now();

  liste r=l;
  while (r)
  {
    dwe med=r->d;
    int place=l->colonne;
    selectslot(place);
    int i=0;
    for(i=0;i<med.T[now.dayOfTheWeek()];i++)
    {
      if(((med.prises[now.dayOfTheWeek()][i].tprise.hourr)==now.hour())&&((med.prises[now.dayOfTheWeek()][i].tprise.minu)==now.minute()))
      {
        
        turnmotorntours(med.prises[now.dayOfTheWeek()][i].quantite);
    }
  }
  r=r->next;
}
  int f=difalarm();
  rtc.clearAlarm(1);
  rtc.setAlarm1(
            rtc.now() + TimeSpan(f*60),
            DS3231_A1_Hour // this mode triggers the alarm when hour minutes seconds match. See Doxygen for other options
    );
}
int compare(wakt t1,wakt t2)
{
  if (t1.hourr=t2.hourr)
  {
    if(t1.minu>=t2.minu)
    return(0);
    else return(1);
  }
  if(t1.hourr>t2.hourr) return(0);
  else return(1);
}
int dif(wakt t1,wakt t2)
{
  int w;
  w=(t2.hourr)*60+t2.minu-(t1.hourr)*60-t1.minu;
  return(w);
}
int difalarm()
{
  int prev=3600;
  liste r=l;
  int difference;
  DateTime noww = rtc.now();
  while(r)
  {
     
      wakt tawa;
      tawa.hourr=noww.hour(); 
      tawa.minu=noww.minute();
    for(int i=0;i<((r->d).T[noww.dayOfTheWeek()]);i++)
    {
      
      wakt z=(r->d).prises[noww.dayOfTheWeek()][i].tprise;
      
    
      if ((dif(tawa,z)>0)&&((dif(tawa,z))<prev))
      prev=(dif(tawa,z));
      
    }
    
    r=r->next;
    }
    if (prev==3600)
    {
      
      r=l;
      
     while(r)
  {
      wakt tawa;
      tawa.hourr=0;
      tawa.minu=0;
     for(int i=0;i<((r->d).T[noww.dayOfTheWeek()+1]);i++)
    {
      
      wakt z=(r->d).prises[noww.dayOfTheWeek()+1][i].tprise;
      
    
      if ((dif(tawa,z)>0)&&((dif(tawa,z))<prev))
      prev=(dif(tawa,z));
      
    }
    r=r->next;
    }
    
      prev=prev+24*60-(noww.hour())*60-(noww.minute());
    
    }
    return (prev);
}
char customKey;
int b,k;
dwe dop;

int n=0;
void frontpage()
{
  DateTime now = rtc.now();
  lcd.setCursor(1,0);
  int d=now.year();int m=now.month();int j=now.day();int hh=now.hour();int mm=now.minute();
  reglage(d);lcd.print('/');reglage(m);lcd.print('/');reglage(j);
  lcd.print("   ");
  reglage(hh);lcd.print(':');reglage(mm);

  lcd.setCursor(0,1);
  int r;
  if (n!=0)
  {
  r=difalarm();
  int h=r/60;int m1=(r%60);
  lcd.print("NEXT DOSE IN  ");
  reglage(h);lcd.print(':');
  reglage(m1);
  }
else 
{
lcd.setCursor(2,1);
lcd.print("NO DOSES PLANNED"); 
} 
  lcd.setCursor(0,2);
  lcd.print("THE MACHINE CONTAINS");
 
  lcd.setCursor(8,3);
  lcd.print(n);
  lcd.print("  MED(S)");
  

}
void setup()
{
  rtc.begin();
  /* if(rtc.lostPower()) {
        // this will adjust to the date and time at compilation
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }*/
  (morning_dose).hourr=9;
(morning_dose).minu=55;
(lunch_dose).hourr=13;
(lunch_dose).minu=0;
(night_dose).hourr=21;
(night_dose).minu=20; 
                        // initialize the lcd 
  lcd.init();
  lcd.backlight();
 //  lcd.cursor();
  // Print a message to the LCD.
  /*lcd.backlight();
 
  dosestime(&morning_dose,&midday_dose,&night_dose);
  lcd.setCursor(0,3); 
  reglage((morning_dose).hour);lcd.print(":");
  reglage((morning_dose).minu);

  reglage((midday_dose).hour);lcd.print(":");
  reglage((midday_dose).minu);  
  
  reglage((night_dose).hour);lcd.print(":");
  reglage((night_dose).minu);
  

  int a=0,b=0,c=0;
      lcd.clear();
      reglayout(&a,&b,&c);
      dispdayrep(T);
      takerep(T);
      lcd.setCursor(0,3);
      for(int u=0;u<7;u++)
      {
        lcd.print(T[u]);
        lcd.print(' ');
      dop=ajoutdwe(morning_dose,lunch_dose,night_dose);
     
      dop=regdwe(dop);}*/
      l=NULL;
/*
  lcd.clear();
  liste l;
  
  int *T;
 int  n=0;
  l=ajoudwe(l,morning_dose,lunch_dose,night_dose,&T,&n);
  delay(500);
  l=ajoudwe(l,morning_dose,lunch_dose,night_dose,&T,&n);
  delay(500);
  lcd.clear();
  l=eliminedweslotnum(l,4,T,n);
  lcd.clear();
  delay(20);
  lcd.print(l->colonne);
  wakt n1,n2,n3;
  lcd.clear();
  n1=addnmin(morning_dose,9);
  n2=substractnmin(lunch_dose,5);
   reglage(n1.hour);lcd.print(":");
  reglage((n1).minu);
lcd.setCursor(0,2)
  reglage((n2).hour);lcd.print(":");
  reglage((n2).minu);*/  
   /*if(rtc.lostPower()) {
        // this will adjust to the date and time at compilation}*/
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    
    rtc.disable32K();
    pinMode(CLOCK_INTERRUPT_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(CLOCK_INTERRUPT_PIN), servall, FALLING);
    rtc.clearAlarm(1);
    rtc.clearAlarm(2);
    rtc.writeSqwPinMode(DS3231_OFF);
    rtc.disableAlarm(2);
//rtc.adjust(DateTime(2022, 6, 30, 9, 54, 0));
    
    
}
int mm=0;
void loop() {
  frontpage();
  /*lcd.noCursor();
  lcd.setCursor(0,2);
  lcd.print("le nbr dwe=");
  lcd.print(n);*/
  
  
  char c=customKeypad.getKey();
  if(c=='A')
  {
    lcd.clear();
    l=ajoudwe(l,morning_dose,lunch_dose,night_dose,&n);
    lcd.clear();
    rtc.clearAlarm(1);
    int r=difalarm();
    /*rtc.setAlarm1(
            rtc.now() + TimeSpan(r*60),
            DS3231_A1_Hour // this mode triggers the alarm when hour minutes seconds match. See Doxygen for other options
    );
    

    /*lcd.print(l->d.prises[3][2].tprise.hourr);
    lcd.print(":");
    lcd.print(l->d.prises[3][2].tprise.minu);*/
    delay(1000);
  }
  else if(c=='B')
  {
    int a;
    lcd.clear();
    lcd.print("ekteb");
    char b;
    b=wait();
    if((b>48)&&(b<56))
    {
    a=int(b)-48;
    l=eliminedweslotnum(l,a,&n);
     }
     lcd.clear();
     rtc.clearAlarm(1);
    int r=difalarm();
     /*rtc.setAlarm1(
            rtc.now() + TimeSpan(r*60),
            DS3231_A1_Hour // this mode triggers the alarm when hour minutes seconds match. See Doxygen for other options
    );*/
    mm=r;
    delay(1000);
  }
  else if  (c=='C')
  {
    int a;
    lcd.clear();
    char b;
    lcd.print("ekteb");
    b=wait();
    if((b>48)&&(b<56))
    {
    a=int(b)-48;
    l=regdweslotnum(l,a);
     }
     lcd.clear();
     rtc.clearAlarm(1);
    int r=difalarm();
    /* rtc.setAlarm1(
            rtc.now() + TimeSpan(r*60),
            DS3231_A1_Hour // this mode triggers the alarm when hour minutes seconds match. See Doxygen for other options
    );*/
    mm=r;
    delay(1000);
  }
  else if(c=='D')
  {
    setdosestime(&morning_dose,&lunch_dose,&night_dose);
    l=checkdosestime(l,morning_dose,lunch_dose,night_dose);
    lcd.clear();
    rtc.clearAlarm(1);
    int r=difalarm();
   /* rtc.setAlarm1(
            rtc.now() + TimeSpan(r*60),
            DS3231_A1_Hour // this mode triggers the alarm when hour minutes seconds match. See Doxygen for other options
    );*/
    mm=r;
    delay(1000);
  }
  

}
