#include <SoftwareSerial.h>
SoftwareSerial Blue (10 , 11);


int Ldr2, thermistor2;
int y12_1 , y12_2 , y12_3 , y12_4;
byte isAuto = 0 ; // if on  auto mode the varablue is 1 otherwise 0 ;
int k = 0 ;
char flag ;

void setup() {
  Serial.begin(9600);
  Blue.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(5 , OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A5, OUTPUT);

}
void YL_1(int yl69) {
  if (yl69 > 1000) {
    Serial.println("pump on");
    digitalWrite(3, 1);
    digitalWrite(6, 1);
  } else if (yl69 < 980) {
    Serial.println("pump off");
    digitalWrite(3, 0);
    digitalWrite(6, 0);
  }
}
void YL_2(int yl69) {
  if (yl69 > 1000) {
    Serial.println("pump_2 on");
    digitalWrite(2, 1);
    digitalWrite(7, 1);

  } else if (yl69 < 980) {
    Serial.println("pump_2 off");
    digitalWrite(2, 0);
    digitalWrite(7, 1);
  }
}
void YL_3(int yl69) {
  if (yl69 > 1000) {
    Serial.println("pump_3 on");
    digitalWrite(1, 1);
    digitalWrite(8, 1);
  } else if (yl69 < 980) {
    Serial.println("pump_3 off");
    digitalWrite(1, 0);
    digitalWrite(8, 0);
  }
}
void YL_4(int yl69) {
  if (yl69 > 1000) {
    Serial.println("pump_4 on");
    digitalWrite(0, 1);
    digitalWrite(9, 1);
  } else if (yl69 < 980) {
    Serial.println("pump_4 off");
    digitalWrite(3, 0);
    digitalWrite(9, 0);
  }
}
void thermistor(int t) {
  int temp = (t * 5.0 / 1024) * 100;
  if (temp < 480) {
    Serial.println("fan on");
    digitalWrite(13, 1);
    digitalWrite(5, 1);
  } else if (temp > 990) {
    Serial.println("fan off");
    digitalWrite(13, 0);
    digitalWrite(5, 0);
  }
}
void LDR(int ldr) {
  if (ldr < 518) {
    Serial.println("lamp on");
    digitalWrite(12, 1);
    digitalWrite(4, 1);

  } else if (ldr > 170) {
    Serial.println("lamp off");
    digitalWrite(12, 0);
    digitalWrite(4, 0);

  }
}

void Data (char flag)  {
  k = 0 ;

  String Ldr = String(Ldr2);
  String thermistor = String(thermistor2);
  String yl_1 = String(y12_1);
  String yl_2 = String(y12_2);
  String yl_3 = String(y12_3);
  String yl_4 = String(y12_4);

  switch (flag) {
    case 'L' :
      while (k < Ldr.length()) {
        Blue.write(Ldr[k]);
        k++;
      }
      break;
    case 'T' :
      while (k < thermistor.length()) {
        Blue.write(thermistor[k]);
        k++;
      }
      break;
    case 'Y' :
      while (k < yl_1.length() ) {
        Blue.write(yl_1[k]);
        k++;
      }
      break;
    case 'U' :
      while ( k < yl_2.length()) {
        Blue.write(yl_2[k]);
      }
      break;
    case 'I':
      while ( k < yl_3.length() ) {
        Blue.write(yl_3[k]);
      }
      break;
    case 'O':
      while (k < yl_4.length() ) {
        Blue.write(yl_4[k]);
      }
  }
}
void function (char flag) {

  switch (flag) {
    case '1' :
      Serial.println("pump on");
      digitalWrite(3, 1);

      break;
    case '2' :
      Serial.println("pump off");
      digitalWrite(3, 0);

      break;
    case '3' :
      Serial.println("fan on");
      digitalWrite(6, 1);
      break;
    case '4':
      Serial.println("fan off");
      digitalWrite(6, 0);
      break;
    case '5' :
      Serial.println("lamp on");
      digitalWrite(5, 1);
      break;
    case '6':
      Serial.println("lamp off");
      digitalWrite(5, 0);
      break;
    case '7':
      Serial.println("Pump_2 : now on");
      digitalWrite(2, 1);
      break;
    case '8':
      Serial.println("Pump_2 : now off");
      digitalWrite(2, 0);

    case '9':
      Serial.println("Pump_3 : now on");
      digitalWrite(1, 1);
      break;
    case 'F':
      Serial.println("Pump_3 : now off");
      digitalWrite(1, 0);
    case 'H':
      Serial.println("Pump_4 : now on");
      digitalWrite(0, 1);
      break;
    case 'G':
        Serial.println("Pump_4 : now off");
        digitalWrite(0,0);
      }

      }

        void loop() {
        // put your main code here, to run repeatedly:
        k = 0 ;
        Ldr2 = analogRead(A1);
        thermistor2 = analogRead(A0);
        y12_1 = analogRead(A2);
        y12_2 = analogRead(A3);
        y12_3 = analogRead(A4);
        y12_4 = analogRead(A5);



        if (Blue.available() > 0 ) {
        Serial.print("Flag :");
        Serial.println(flag);
        flag = Blue.read();
        switch (flag)  {
        case 'A':
        isAuto = 1 ;
        break;
        case 'M' :
        isAuto = 0;
        break;
      }
        Data(flag);
      }

        if (isAuto == 1) { // is Auto
        LDR(Ldr2);
        YL_1(y12_1);
        YL_2(y12_2);
        YL_3(y12_3);
        YL_4(y12_4);

        thermistor(thermistor2);

      } else if (isAuto == 0 ) { // is manual
        function(flag);
      }
      }
