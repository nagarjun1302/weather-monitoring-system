#include "LiquidCrystal_I2C.h"
#include "Keypad.h"

LiquidCrystal_I2C lcd(32, 16, 2);
int sensorPin = 0;
int LEDpin = 13;
int LDRpin = 1;
int LEDred = 12;
int LEDgreen = 2;

char keys[4][4] = {
                    {'1','2','3','A'},
                    {'4','5','6','B'},
                    {'7','8','9','C'},
                    {'*','0','#','D'}
};
/* Specify arduino Rows & Cols Pins */
byte rowPins[4] = {11, 10, 9, 8};
byte colPins[4] = {7, 6, 5, 4};

/* Create keypad object for using library */
Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);
char temp[5];
int temperatureToFind = 0;



void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.setCursor(0, 0);
  lcd.backlight();
  lcd.display();
  pinMode(LEDpin, OUTPUT);
  pinMode(LDRpin, INPUT);
  pinMode(LEDred, OUTPUT);
  pinMode(LEDgreen, OUTPUT);
  
}
 
void loop()
{
  /*getting temprature value from keypad*/
  char key = myKeypad.getKey();
  int len = strlen(temp);
  temp[len] = key;
  temp[len+1] = '\0';
  temperatureToFind = atoi(temp);
  int reading = analogRead(sensorPin);
 
  
 /* Converting temperature from binary to celsius */
 float temperature = ((reading * 5.0 / 1024.0) * 100.0) - 50;
 Serial.print("Temperature in deg Celsius = ");
 Serial.println(temperature);

   lcd.setCursor(0, 0);
   lcd.print("Temp degC: ");
   lcd.setCursor(11, 0);
   lcd.print(temperature);
  
  int LDRstatus = analogRead(LDRpin);
  Serial.print("Light intensity = ");
  Serial.println(LDRstatus);
  Serial.print(temperatureToFind);
  
  /*Re-initialising the temperature to find*/
  if(key == 'A')
  {
    temp[0] = '\0';
  }
  
  
  /*Keeping a check on the light intensity*/
  if (LDRstatus <= 500)
  {
    digitalWrite(LEDpin, LOW);
  }
  else
  {
    digitalWrite(LEDpin, HIGH);
  }
  
  lcd.setCursor(0, 1);
  lcd.print("Light int: ");
  lcd.setCursor(11, 1);
  lcd.print(LDRstatus);
  
  
  /*Keeping a check on the temperature*/
  if (temperature < temperatureToFind)
  {
    digitalWrite(LEDred, HIGH);
    digitalWrite(LEDgreen, LOW);
  }
  else if (temperature >= temperatureToFind && temperatureToFind != 0)
  {
    digitalWrite(LEDred, LOW);
    digitalWrite(LEDgreen, HIGH);
  }
 
 delay(100);
}
  