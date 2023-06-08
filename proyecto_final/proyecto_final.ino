#include <Wire.h>
//#include <HardwareSerial.h>
//HardwareSerial SerialPort(2);
//const uint8_t rx2=16;
//const uint8_t tx2 =17;
int sensorlum = 35;
int value = 0;
char modo;
int brillo;
void setup()
{
  //start serial connection
  Serial.begin(9600);
  //SerialPort.begin(115200,SERIAL_8N1,rx2,tx2);
  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(36, INPUT_PULLUP);
  pinMode(39, INPUT_PULLUP);
  pinMode(34, INPUT_PULLUP);
  pinMode(15, OUTPUT);
  pinMode(0, OUTPUT);
 // pinMode(32, OUTPUT);
  //pinMode(33, OUTPUT);
  digitalWrite(15, HIGH);
}

void scaner(){
    bool sensorVent = digitalRead(36);
    bool sensorpuert = digitalRead(39);
   
    if (!(sensorVent && sensorpuert)) {
      digitalWrite(15, LOW); //Al menos una de las entradas c y d están en LOW, Prende led
      Serial.println("ESTADO_ALERTA");
    //  digitalWrite(33,HIGH);
      //digitalWrite(32,LOW);
      //delay(300);
      //digitalWrite(33,LOW);
      //digitalWrite(32,HIGH);
      //SerialPort.println("0");
    } else {
      digitalWrite(15, HIGH); //En caso de que las dos estén en HIGH, apaga el LED
      Serial.println("ESTADO_SEGURO");
      //SerialPort.println("1");
    }
    Serial.print("puerta :");
    if (sensorpuert == false) {
      Serial.println("abierta");
      delay(100);
    } else {
      Serial.println("cerrada");
      delay(100);
    }
    Serial.print("ventana:");
    delay(100);
    if (sensorVent == false) {
      Serial.println("abierta");
      delay(100);
    } else {
      Serial.println("cerrada");
      delay(100);
    }
   
    delay(1500);
}
void control_brillo(){
  value = analogRead(sensorlum);
  brillo = map(value, 0, 1023, 0, 255);
  if (brillo >= 180) {
    digitalWrite(0, HIGH);
    Serial.println("HEADLIGHT_OFF");
    delay(100);
  }
  if (brillo < 180) {
    digitalWrite(0, LOW);
    Serial.println("HEADLIGHT_ON");
   delay(100);
  }
   
}
void loop() {
 // if(Serial.available()>0.3){
  // modo = Serial.read();
   //Serial.print(modo);}
  while(1<Serial.available()){
       modo = Serial.read();
       Serial.print(modo);
   }
  while (modo == 'O') {
    scaner();
    delay(500);
    while(1<Serial.available()){
       modo = Serial.read();
       Serial.print(modo);
   }
   }
  control_brillo();
     
    digitalWrite(15, HIGH);
    delay(500);

  }
