#include <SD.h>
#include <avr/sleep.h>
#include "SoftwareSerial.h"
#include "GPSconfig.h"

// power saving modes
#define SLEEPDELAY 0
#define TURNOFFGPS 0
#define LOG_RMC_FIXONLY 0

// what to log
#define LOG_RMC 1 // RMC-Recommended Minimum Specific GNSS Data, message 103,04
/*
#define LOG_GGA 0 // GGA-Global Positioning System Fixed Data, message 103,00
#define LOG_GLL 0 // GLL-Geographic Position-Latitude/Longitude, message 103,01
#define LOG_GSA 0 // GSA-GNSS DOP and Active Satellites, message 103,02
#define LOG_GSV 0 // GSV-GNSS Satellites in View, message 103,03
#define LOG_VTG 0 // VTG-Course Over Ground and Ground Speed, message 103,05
*/
#define TX_PIN    0
#define RX_PIN    1
#define PWR_PIN   2
#define LED1_PIN  3      // GPS fix
#define LED2_PIN  4      // Writing to file
#define SD_CARD   10
#define GPS_RATE  4800
#define BUFFSIZE  90

SoftwareSerial gpsSerial = SoftwareSerial(TX_PIN, RX_PIN);
char buffer[BUFFSIZE];
uint8_t index = 0;
uint8_t fix = 0;         // GPS fix
uint8_t i;
File log_file;

uint8_t hex_to_dec(char c) {
  if (c < '0') {
    return 0;
  }
  if (c <= '9') {
    return (c - '0');
  }
  if (c < 'A') {
    return 0;
  }
  if (c <= 'F') {
    return (c - 'A' + 10);
  }
}

void error(uint8_t errno) {
  while (1) {
    for (i = 0; i < errno; i++) {
      digitalWrite(LED1_PIN, HIGH);
      digitalWrite(LED2_PIN, HIGH);
      delay(100);
      
      digitalWrite(LED1_PIN, LOW);
      digitalWrite(LED2_PIN, LOW);
      delay(100);
    }
    
    for (; i < 10; i++) {
      delay(200);
    }
  }
}

void setup() {
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  WDTCSR = 0;
  
  Serial.begin(9600);
  
  pinMode(PWR_PIN, OUTPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(SD_CARD, OUTPUT);
  
  digitalWrite(PWR_PIN, LOW);
  
  // Initialize SD library and card
  if (!SD.begin(SD_CARD)) {
    Serial.println("Card initialization failed.");
    error(1);
  }
  
  // Create log file if it does not exist
  strcpy(buffer, "GPSlog00.txt");
  
  for (i = 0; i < 100; i++) {
    buffer[6] = '0' + i/10;
    buffer[7] = '0' + i%10;
    
    if (!SD.exists(buffer)) {
      break;
    }
  }
  
  log_file = SD.open(buffer, FILE_WRITE);
  
  if (!log_file) {
    Serial.print("Failed to create file ");
    Serial.println(buffer);
    error(2);
  }
  
  Serial.print("Writing to file ");
  Serial.println(buffer);
  
  gpsSerial.begin(GPS_RATE);
  
  delay(250);
}

void loop() {
  char c;
  uint8_t sum;
  
  if (gpsSerial.available()) {
    c = gpsSerial.read();
    
    if (index == 0) {
      while (c != '$') {
        c = gpsSerial.read();
      }
    }
    
    buffer[index] = c;
      
    if (c == '\n') {
      // Terminate string
      buffer[index+1] = 0;
      
      // If there is no checksum, clear buffer.
      if (buffer[index-4] != '*') {
        Serial.print('*');
        index = 0;
        return;
      }
      
      // Get checksum.
      sum = hex_to_dec(buffer[index-3]) * 16;
      sum += hex_to_dec(buffer[index-2]);
      
      // Check checksum.
      for (i = 1; i < (index-4); i++) {
        sum ^= buffer[i];
      }
      
      if (sum != 0) {
        Serial.print('~');
        index = 0;
        return;
      }
      
      if (strstr(buffer, "GPRMC")) {
        char *p = buffer;
        
        p = strchr(p, ',') + 1;
        p = strchr(p, ',') + 1;
        
        if (p[0] == 'V') {
          digitalWrite(LED1_PIN, LOW);
          fix = 0;
        } else {
          digitalWrite(LED1_PIN, HIGH);
          fix = 1;
        }
      }
      
      if (LOG_RMC_FIXONLY) {
        if (!fix) {
          Serial.print('_');
          index = 0;
          return;
        }
      }
      
      Serial.print(buffer);
      Serial.print('#');
      digitalWrite(LED2_PIN, HIGH);
      
      index++;
      
      log_file.write((uint8_t *) buffer, index);
      log_file.flush();
      
      digitalWrite(LED2_PIN, LOW);
      
      index = 0;
      
      if (TURNOFFGPS) {
        digitalWrite(PWR_PIN, HIGH);
      }
      
      delay(SLEEPDELAY * 1000);// change
      digitalWrite(PWR_PIN, LOW);
      
      return;
    }
    
    index++;
    
    if (index == BUFFSIZE-1) {
      Serial.print('!');
      index = 0;
    }
  }
}

void sleep_sec(uint8_t x) {
  while (x--) {
    // set the WDT to wake us up!
    WDTCSR |= (1 << WDCE) | (1 << WDE); // enable watchdog & enable changing it
    WDTCSR = (1 << WDE) | (1 << WDP2) | (1 << WDP1);
    WDTCSR |= (1 << WDIE);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
  }
}

SIGNAL(WDT_vect) {
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  WDTCSR = 0;
}
