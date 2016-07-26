#include <Arduino.h>

#include <ESP8266WiFi.h>

extern "C" {
  #include "user_interface.h"
}

int c = 9;
int chr = 0;
String tmp ="";
String ph = ".'#-"; //Placeholder
String text = "Never gonna give you up Never gonna let you down Never gonna run around and desert you";
byte channel;

// Beacon Packet buffer
uint8_t packet[128] = { 0x80, 0x00, 0x00, 0x00, 
                /*4*/   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
                /*10*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                /*16*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 
                /*22*/  0xc0, 0x6c, 
                /*24*/  0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00, 
                /*32*/  0x64, 0x00, 
                /*34*/  0x01, 0x04, 
                /* SSID */
                /*36*/  0x00, 0x0e, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72,
                        0x01, 0x08, 0x82, 0x84,
                        0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c, 0x03, 0x01, 
                /*65*/  0x04};                

void setup() {
  delay(500);
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1); 
  Serial.begin(115200);
}

void loop() {    
    chr = 0;
    c = 10;        
    Serial.println("start"); 
    Serial.println(text.length()); 
    // Randomize channel //
   
    channel = random(1,12); 
    wifi_set_channel(channel);

    // Randomize SRC MAC
    packet[10] = packet[16] = random(256);
    packet[11] = packet[17] = random(256);
    packet[12] = packet[18] = random(256);
    packet[13] = packet[19] = random(256);
    packet[14] = packet[20] = random(256);
    packet[15] = packet[21] = random(256);    
    
    packet[65] = 1;
    while(chr < text.length()){
      for (int i = 41; i <= 52; i++){
        packet[i] = ph[0];
      }
      int pcount = 42; //Reset packet
      c++;
      Serial.println(c); 
      tmp = String(c); //convert int to string
      packet[38] = ph[1];
      packet[39] = tmp[0];
      packet[40] = tmp[1];
      packet[41] = ph[3];
      while(!isspace(text[chr]) && chr < text.length()){
        packet[pcount] = text[chr];
        pcount++;
        chr++;
      }
      for (int i=0; i <= 10; i++){
        wifi_send_pkt_freedom(packet, 66, 0);
      } 
      chr++;
    }   
    delay(1);
}

