#include <LiquidCrystal.h>

// Define arduino's pins

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
float tempreal;
int u;
float e;
float i;
int tempgoal;
#define TEMP_0_PIN         13   // Analog Input
#define TEMP_1_PIN         15   // Analog Input
#define TEMP_BED_PIN       14   // Analog Input
#define HEATER0            10
#define FAN2               44
// Define paramyters of 3rd degree polumonial
#define A0                 248.4417559865674
#define A1                 -.585044227650099
#define A2                 8.359737802680874*0.0001
#define A3                 -4.843789427166852*0.0000001
#define MAX                 26800 // How many steps does stepper motor need to move from lowest to higest position.

int x;
int y;
int z;
int countx;
int county;
int countz;
String help;
bool flag;
int czasq;
bool directionx;
bool directiony;
bool directionz;
float xpoz;
float ypoz;
float zpoz;


LiquidCrystal lcd(16,17, 23, 25, 27, 29);
int antiwindup;


void setup() {
  // put your setup code here, to run once:
  czasq=0;
  flag=1;
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
  Serial.begin(57600); // Start communication
  digitalWrite(TEMP_0_PIN,HIGH);
  pinMode(HEATER0, OUTPUT);
  digitalWrite(HEATER0,HIGH);
  x=digitalRead(X_MAX_PIN); // Check if position is the higehst possible for 3 motors
  y=digitalRead(Y_MAX_PIN);
  z=digitalRead(Z_MAX_PIN);
  while (!(x&&y&&z)) // to know where the motors are, we move each of them to highest possible place
  {
    if(x==0) digitalWrite(X_STEP_PIN,HIGH);
    if(y==0) digitalWrite(Y_STEP_PIN,HIGH);
    if(z==0) digitalWrite(Z_STEP_PIN,HIGH);
    digitalWrite(X_STEP_PIN,LOW);
    digitalWrite(Y_STEP_PIN,LOW);
    digitalWrite(Z_STEP_PIN,LOW);
    x=digitalRead(X_MAX_PIN);
    y=digitalRead(Y_MAX_PIN);
    z=digitalRead(Z_MAX_PIN);
  }
  xpoz=MAX; // after previous while, position is max
  ypoz=MAX;
  zpoz=MAX;
  lcd.begin(20,4); 
  temp=analogRead(TEMP_0_PIN); // temperature value received from input
  tempreal = temp*temp*temp*A3+temp*temp*A2+temp*A1+A0; // temperature in degree C
  tempgoal=30; //Starting best temperature
 

}

void loop() {
  // put your main code here, to run repeatedly:
   while (Serial.available()>0) // Read from serial
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
    flag = 0;
    help = Serial.readStringUntil('\n'); //JeA?li tak, to odczytaj je do znaku koA?ca linii i zapisz w zmiennej odebraneDane
    //odlicz = Serial.parseInt();
    sscanf(help.c_str(),"x %d y %d z %d t %d\n",&countx,&county,&countz,&tempgoal); // Save how much we want to move and target temperature
    if (countx < 0) //if we want to move lower
      {
        countx = countx * (-1);
          digitalWrite(X_DIR_PIN,HIGH);
          directionx=0;
      }
    else
    {
      digitalWrite(X_DIR_PIN,LOW);
      directionx=1;
    }
    if (county < 0)
      {
        county = county * (-1);
          digitalWrite(Y_DIR_PIN,HIGH);
          directiony=0;
      }
    else{
      digitalWrite(Y_DIR_PIN,LOW);
      directiony=1;
      }
    if (countz < 0)
      {
        countz = countz * (-1);
        digitalWrite(Z_DIR_PIN,HIGH);
        directionz=0;
      }
    else
    {
      digitalWrite(Z_DIR_PIN,LOW);
      directionz=1;
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
  //if(((x==0)&&(countx>0))||((directionx==0)&&(countx>0)))
  if ((countx>0)&&(((directionx==0)&&(xpoz>0)))) // when go down (and we are not in the lowest poont)
  {
    digitalWrite(X_STEP_PIN,HIGH); 
    countx--;//one step less
    xpoz--;// one step lower
  }
  if ((countx>0)&&(((directionx==1)&&(xpoz<MAX))))//when go up (and we are not in the highest poont)
  {
    digitalWrite(X_STEP_PIN,HIGH);
    countx--;//one step less
    xpoz++;// one step higher
  } 
  if ((county>0)&&(((directiony==0)&&(ypoz>0))))
  {
    digitalWrite(Y_STEP_PIN,HIGH);
    county--;
    ypoz--;
  }
  if ((county>0)&&(((directiony==1)&&(ypoz<MAX))))
  {
    digitalWrite(Y_STEP_PIN,HIGH);
    county--;
    ypoz++;
  } 
  if ((countz>0)&&(((directionz==0)&&(zpoz>0))))
  {
    digitalWrite(Z_STEP_PIN,HIGH);
    countz--;
    zpoz--;
  }
  if ((countz>0)&&(((directionz==1)&&(zpoz<MAX))))
  {
    digitalWrite(Z_STEP_PIN,HIGH);
    countz--;
    zpoz++;
  } 
 
  delayMicroseconds(200);//wait
  digitalWrite(X_STEP_PIN,LOW);
  digitalWrite(Y_STEP_PIN,LOW);
  digitalWrite(Z_STEP_PIN,LOW);
  delayMicroseconds(200);//wait
  if(countx == 0 && county == 0 && countz == 0  && flag == 0)// if moving finished
  {
    Serial.print("Ok temperatura = ");//send temp
    Serial.println(tempreal);
    flag = 1;// to not move here again 
  }

  czasq++;
  if (czasq==500) //after 0.1 second
  {
    e=tempgoal-tempreal; //dif between actual temp and target
    i=i+e*0.005; //sum
    u=floor((e+i)/50*255); //computed input
    if (u<=255 && u>=0) //if unput can be send
    {
      analogWrite(HEATER0,u); //send it
    }
    else
    {
      if (u>255) //if too high
      {
          analogWrite(HEATER0,255);
          antiwindup = 255-u;
          i = i+0.005*antiwindup; // to not make sum too high
      }
      else
      {
                analogWrite(HEATER0,0);
                antiwindup = 0-u;
                i = i+0.005*antiwindup;// to not make sum too low
      }
    }

      temp=analogRead(TEMP_0_PIN);//read temp
      tempreal = temp*temp*temp*A3+temp*temp*A2+temp*A1+A0;
	
	//send info on LCD 
	lcd.setCursor(0,0);
	lcd.print("Temperatura: ");
	lcd.print(tempreal);

	lcd.setCursor(0,1);
	lcd.print("X:");
	lcd.print(xpoz);
	lcd.setCursor(0,2);
	lcd.print("Y:");
	lcd.print(ypoz);
	lcd.setCursor(0,3);
	lcd.print("Z:");
	lcd.print(zpoz);


	lcd.print(u);
  czasq=0;
  }


}

