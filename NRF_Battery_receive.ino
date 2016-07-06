/* YourDuinoStarter Example: nRF24L01 Receive Joystick values

 - WHAT IT DOES: Receives data from another transceiver with
   2 Analog values from a Joystick or 2 Potentiometers
   Displays received values on Serial Monitor
 - SEE the comments after "//" on each line below
 - CONNECTIONS: nRF24L01 Modules See:
 http://arduino-info.wikispaces.com/Nrf24L01-2.4GHz-HowTo
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 9
   4 - CSN to Arduino pin 10
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED
   
 - V1.00 11/26/13
   Based on examples at http://www.bajdi.com/
   Questions: terry@yourduino.com */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
/*-----( Declare Constants and Pin Numbers )-----*/
#define CE_PIN   9
#define CSN_PIN 10

const uint64_t pipe = 0xE8E8F0F0E1LL;

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

float fsr[4];
int i;
String reply;
String OK = "OK";

void setup()
{
  Serial.begin(9600);
  Serial.println(F("\n------Starting------\n"));
  //delay(1000);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
}

void loop()
{
  //Serial.println("here");
  if (radio.available())
  {
    Serial.println("here");
    Serial.println(radio.available());
    delay(500);
    // Read the data payload until we've received everything
    bool done = false;
    //while (radio.available())
    //{
      // Fetch the data payload
      Serial.println("here_loop");
       radio.read(fsr, sizeof(fsr));
      for(i=0;i<4;i++){
        //if(fsr[3] == 10){
            //Serial.print("Battery = ");
            Serial.println(fsr[i]);
        //}
      }
    //}
  }
  else
  {    
      Serial.println("No radio available");
      Serial.println(radio.available());
  }
}

int subStr(String reply, String OK)
{
  int i = 0;
  while(i<reply.length())
  {
    if (reply[i]==OK[0])
      {
        if (reply[i+1] = OK[1])
          return 1;
      }
     i = i+1;
  }
  return 0;
}

void giveCmd(String cmd)
{
  while(1)
  {
    Serial.println(cmd);
    delay(1500);
    reply = Serial.readString();
    if(subStr(reply,OK))
      break;
  }
}

void giveCmd_slow(String cmd)
{
  while(1)
  {
    Serial.println(cmd);
    delay(5000);
    reply = Serial.readString();
    if(subStr(reply,OK))
      break;
  }
}

void giveCmd_fast(String cmd)
{
  String DO = "DO";
  
  while(1)
  {
    Serial.println(cmd);
    delay(500);
    reply = Serial.readString();
    if(subStr(reply,DO))
      break;
  }
}
