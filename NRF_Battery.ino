#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10
#define Interrupt_pin 3
const uint64_t pipe = 0xE8E8F0F0E1LL; //0xE8E8F0F0E1LL 0xF0F0F0F0E1LL 
RF24 radio(CE_PIN, CSN_PIN); 
float force,fsr[4];
volatile int i;

#define Debug Serial
double load,min_load,max_load;
double prev_load;
double weightScale;
void setup() {
  // put your setup code here, to run once:
  i = 0;
  Serial.begin(9600);
  Serial.println("Starting");
  //pinMode(Interrupt_pin, INPUT);
  radio.begin();
  radio.openWritingPipe(pipe);
  //attachInterrupt(digitalPinToInterrupt(Interrupt_pin), transmit, CHANGE);
//  myCalibDebug();
}

void loop() {
  // put your main code here, to run repeatedly:
  load=8;
  Serial.print("Zaki: ");
//  calculateLoad();
  //radio.powerUp();
//  radio.begin();
//  radio.openWritingPipe(pipe);
  Serial.print("Load: ");
  Serial.println(load);
  fsr[0]=8;
  fsr[1]=4;
  fsr[2]=2;
  fsr[3]=10;
 // Serial.print(fsr[0]);
 // Serial.print(fsr[1]);
 // if (i == 1)
  //{
  radio.powerUp();
  Serial.println("Powered UP");
  delay(1000);
  
  bool okok = radio.write(fsr,sizeof(fsr));
  if(okok)
  {
    Serial.println("Writing Done");  
  }
  else
  {
    Serial.println("Writing Failed");
  }
  radio.powerDown();
  Serial.println("Powered Down");
  //delay(1000);
  i = 0;
  //}
}

void transmit()
{
  i = 1;
}

/*void myCalibDebug() {
  char debug_response[10],debug_read;
  unsigned int i=0;
  memset(debug_response,'\0',10);
  
  Debug.println("Enter the minumum load.");
  i=0;
  while(1){
    if(Debug.available()){
      debug_read=Debug.read();
      if(debug_read!='\n'){
        debug_response[i]=(char)debug_read; 
        i++;    
      }
      else {
        break;
      }
    }
  }
  Debug.print("Minimum load set to: ");
  min_load=atof(debug_response);
  Debug.println(min_load);
  scale.power_up();
  scale.set_scale();
  scale.tare();
  memset(debug_response,'\0',10);
  Debug.println("Enter the maximum load.");
  i=0;
  while(1){
    if(Debug.available()){
      debug_read=Debug.read();
      if(debug_read!='\n'){
        debug_response[i]=(char)debug_read; 
        i++;    
      }
      else {
        break;
      }
    }
  }
  Debug.print("Maximum load set to: ");
  max_load=atof(debug_response);
  Debug.println(max_load);
  weightScale = scale.get_units(10)/(((max_load-min_load)*1000));
  scale.set_scale(weightScale);
  scale.power_down();
  Debug.println("Calibration done");
}*/


/*void calculateLoad(){
  scale.power_up();
  load = scale.get_units(20);
  load = load / 1000;
//  if(debug) Debug.print("Raw load: ");
//  if(debug) Debug.println(load);
  load = load + min_load;
  if(load<0) load = 0;
//  if(debug) Debug.println(load);
  
  scale.power_down();
}*/

/*
void calculateLoad(){
  scale.power_up();
  load = scale.get_units(20);
  load = load/1000;
  if(load<0) load = 0.00;
  scale.power_down();
}
void calibrateLoad(){
  scale.power_up();
  while(1){
    Serial.println("Kindly put 0 Kg weight, waiting for 'done'.");
    if(Serial.available()){
      if(Serial.read() == 'd'){
        break;
      }
    }
    delay(1000);
  }
  scale.set_scale();
  scale.tare();
  while(1){
    Serial.println("Kindly put a 1 Kg weight, waiting for 'done'.");
    if(Serial.available()){
      if(Serial.read() == 'd'){
        Serial.println(scale.get_units(10), 1); 
        Serial.print("Scale set to: ");
        Serial.println(scale.get_units(10)/1000);
        scale.set_scale(scale.get_units(10)/1000);
        break;
      }
    }
    delay(1000);
  }
  scale.power_down();
}

*/
