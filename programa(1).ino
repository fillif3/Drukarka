#include <LiquidCrystal.h>

#define X_MIN_PIN           3
#ifndef X_MAX_PIN
  #define X_MAX_PIN         2
#endif
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_CS_PIN           53

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_CS_PIN           49

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_CS_PIN           40


float temp;
float tempp;
int u;
float e;
float i;
int licznik;
int czasg=0;
int oczekiwanatemp;
#define TEMP_0_PIN         13   // Analog Input
#define TEMP_1_PIN         15   // Analog Input
#define TEMP_BED_PIN       14   // Analog Input
#define HEATER0            10
#define FAN2               44
#define A0                 248.4417559865674
#define A1                 -.585044227650099
#define A2                 8.359737802680874*0.0001
#define A3                 -4.843789427166852*0.0000001
#define MAX                 26800

int x;
int y;
int z;
int odliczx;
int odliczy;
int odliczz;
String pomoc;
bool flaga;
int czasq;
bool xgora;
bool ygora;
bool zgora;
float xpoz;
float ypoz;
float zpoz;


LiquidCrystal lcd(16,17, 23, 25, 27, 29);
int antiwindup;


void setup() {
  // put your setup code here, to run once:
  czasq=0;
  flaga=1;
  pinMode(X_MAX_PIN,INPUT);
  digitalWrite(X_MAX_PIN,HIGH);
  pinMode(Y_MAX_PIN,INPUT);
  digitalWrite(Y_MAX_PIN,HIGH);
  pinMode(Z_MAX_PIN,INPUT);
  digitalWrite(Z_MAX_PIN,HIGH);
  pinMode(X_ENABLE_PIN,OUTPUT);
  digitalWrite(X_ENABLE_PIN,LOW);
  pinMode(X_DIR_PIN,OUTPUT);
  digitalWrite(X_DIR_PIN,LOW);
  pinMode(X_STEP_PIN,OUTPUT);
  pinMode(Y_ENABLE_PIN,OUTPUT);
  digitalWrite(Y_ENABLE_PIN,LOW);
  pinMode(Y_DIR_PIN,OUTPUT);
  digitalWrite(Y_DIR_PIN,LOW);
  pinMode(Y_STEP_PIN,OUTPUT);
  pinMode(Z_ENABLE_PIN,OUTPUT);
  digitalWrite(Z_ENABLE_PIN,LOW);
  pinMode(Z_DIR_PIN,OUTPUT);
  digitalWrite(Z_DIR_PIN,LOW);
  pinMode(Z_STEP_PIN,OUTPUT);
  digitalWrite(TEMP_0_PIN,HIGH);
  Serial.begin(57600);
  digitalWrite(TEMP_0_PIN,HIGH);
  pinMode(HEATER0, OUTPUT);
  digitalWrite(HEATER0,HIGH);
  x=digitalRead(X_MAX_PIN);
  //Serial.print(x);
  y=digitalRead(Y_MAX_PIN);
  //Serial.print(y);
  z=digitalRead(Z_MAX_PIN);
  digitalWrite(X_DIR_PIN,LOW);
  digitalWrite(Y_DIR_PIN,LOW);
  digitalWrite(Z_DIR_PIN,LOW);
  while (!(x&&y&&z))
  {
    if(x==0) digitalWrite(X_STEP_PIN,HIGH);
    if(y==0) digitalWrite(Y_STEP_PIN,HIGH);
    if(z==0) digitalWrite(Z_STEP_PIN,HIGH);
    digitalWrite(X_STEP_PIN,LOW);
    digitalWrite(Y_STEP_PIN,LOW);
    digitalWrite(Z_STEP_PIN,LOW);
    x=digitalRead(X_MAX_PIN);
    Serial.print(x);
    y=digitalRead(Y_MAX_PIN);
    Serial.print(y);
    z=digitalRead(Z_MAX_PIN);
  }
  xpoz=MAX;
  ypoz=MAX;
  zpoz=MAX;
  lcd.begin(20,4);
  temp=analogRead(TEMP_0_PIN);
  tempp = temp*temp*temp*A3+temp*temp*A2+temp*A1+A0;
  oczekiwanatemp=30;
 

}

void loop() {
  // put your main code here, to run repeatedly:
   while (Serial.available()>0)
  {
//   if (digitalRead(guzik) == 1)
  //  {
   // digitalWrite(X_ENABLE_PIN,LOW);
   // digitalWrite(Y_ENABLE_PIN,LOW);
   // digitalWrite(Z_ENABLE_PIN,LOW);
   /// }
   // else
   // digitalWrite(X_ENABLE_PIN,HIGH);
   // digitalWrite(Y_ENABLE_PIN,HIGH);
   // digitalWrite(Z_ENABLE_PIN,HIGH);
   // }
    flaga = 0;
    pomoc = Serial.readStringUntil('\n'); //JeA?li tak, to odczytaj je do znaku koA?ca linii i zapisz w zmiennej odebraneDane
    //odlicz = Serial.parseInt();
    sscanf(pomoc.c_str(),"x %d y %d z %d t %d\n",&odliczx,&odliczy,&odliczz,&oczekiwanatemp);
    if (odliczx < 0)
      {
        odliczx = odliczx * (-1);
          digitalWrite(X_DIR_PIN,HIGH);
          xgora=0;
      }
    else
    {
      digitalWrite(X_DIR_PIN,LOW);
      xgora=1;
    }
    if (odliczy < 0)
      {
        odliczy = odliczy * (-1);
          digitalWrite(Y_DIR_PIN,HIGH);
          ygora=0;
      }
    else{
      digitalWrite(Y_DIR_PIN,LOW);
      ygora=1;
      }
    if (odliczz < 0)
      {
        odliczz = odliczz * (-1);
        digitalWrite(Z_DIR_PIN,HIGH);
        zgora=0;
      }
    else
    {
      digitalWrite(Z_DIR_PIN,LOW);
      zgora=1;
    }
  } 
  x=digitalRead(X_MAX_PIN);
  //if (x) xpoz=MAX;
  //Serial.print(x);
  y=digitalRead(Y_MAX_PIN);
  //if (y) ypoz=MAX;
  //Serial.print(y);
  z=digitalRead(Z_MAX_PIN);
  //if (z) zpoz=MAX;
  //Serial.println(z);
  //if(((x==0)&&(odliczx>0))||((xgora==0)&&(odliczx>0)))
  if ((odliczx>0)&&(((xgora==0)&&(xpoz>0))))
  {
    digitalWrite(X_STEP_PIN,HIGH);
      odliczx--;
      if (xgora) xpoz++;
      else xpoz--;
  }
  if ((odliczy>0)&&(((ygora==0)&&(ypoz>0))))
  {
    digitalWrite(Y_STEP_PIN,HIGH);
    odliczy--;
    if (ygora) ypoz++;
    else ypoz--;
  }
  if ((odliczz>0)&&(((zgora==0)&&(zpoz>0))))
  {
    digitalWrite(Z_STEP_PIN,HIGH);
    odliczz--;
    if (zgora) zpoz++;
    else zpoz--;
  }
  delayMicroseconds(200);
  digitalWrite(X_STEP_PIN,LOW);
  digitalWrite(Y_STEP_PIN,LOW);
  digitalWrite(Z_STEP_PIN,LOW);
  delayMicroseconds(200);
  if(odliczx == 0 && odliczy == 0 && odliczz == 0  && flaga == 0)
  {
    Serial.print("Ok temperatura = ");
    Serial.println(tempp);
    flaga = 1;
  }

  czasq++;
  if (czasq==500)
  {
    e=oczekiwanatemp-tempp;
    i=i+e*0.005;
    u=floor((e+i)/50*255);
    if (u<=255 && u>=0)
    {
      analogWrite(HEATER0,u);
    }
    else
    {
      if (u>255)
      {
          analogWrite(HEATER0,255);
          antiwindup = 255-u;
          i = i+0.005*antiwindup;
      }
      else
      {
                analogWrite(HEATER0,0);
                antiwindup = 0-u;
                i = i+0.005*antiwindup;
      }
    }
    //  Serial.println("wskaźnik cyf, temepratura, blad, wartosc sterujaca");
      temp=analogRead(TEMP_0_PIN);
      tempp = temp*temp*temp*A3+temp*temp*A2+temp*A1+A0;
//    Serial.println(temp);
  //  Serial.println(tempp);
    //  Serial.println(e);
      // Serial.println(i);
        //Serial.println(u);

	lcd.setCursor(0,0);
	lcd.print("Temperatura: ");
	lcd.print(tempp);

	lcd.setCursor(0,1);
	lcd.print("X:");
	lcd.print(xpoz);
	lcd.setCursor(0,2);
	lcd.print("Y:");
	lcd.print(ypoz);
	lcd.setCursor(0,3);
	lcd.print("Z:");
	lcd.print(zpoz);

//lcd.setCursor(0,2);
//lcd.print("i:");
//lcd.print(i);

//lcd.setCursor(0,3);
//if (u>=100) lcd.print("u:");
//if ((u<100)&&(u>=10))  lcd.print("u:0");
//if ((u<=10)&&(u>=0)) lcd.print("u:00");
//if (u<0) lcd.print("u: ");
//lcd.print("   ");

	lcd.print(u);
  czasq=0;
  }


}

