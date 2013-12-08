/************* Things to change daily *******************/
#define DEBUG 0
#define TODAYS_PRESSURE 100643

// Pressure Sensor
  // Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!)
  // Connect GND to Ground
  // Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
  // Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
  // EOC is not used, it signifies an end of conversion
  // XCLR is a reset pin, also not used here
#include <Wire.h>
#include <Adafruit_BMP085.h>

// Battery Voltage Reader
#define resistor1 10000
#define resistor2 10000
#define voltPin 0
float denominator, v_bat, v_low = 3.3;
bool LOW_BAT = false;

// Pressure Sensor / Altimeter
Adafruit_BMP085 pressure_sensor;
float temperature, pressure, altitude, real_altitude;

// LEDs
#define pin_led1 8
#define pin_led2 9

// GPS Logger
#include <SD.h>
#include <avr/sleep.h>
#include "SoftwareSerial.h"
#include "GPSconfig.h"
bool buffer_done = false;

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

bool create_new_file(){
  static int error_count = 0;
  if (error_count > 100)
    error(1);
  // Initialize SD library and card
    if (!SD.begin(SD_CARD) && error_count < 3) {
    if(DEBUG)
       Serial.println("Card initialization failed.");
    //error(1);
    error_count++;
    return true;
  }
  // Create log file if it does not exist
  strcpy(buffer, "GPSlo000.txt");
  for (i = 0; i < 1000; i++) {
    buffer[5] = '0' + i/100;
    buffer[6] = '0' + i/10;
    buffer[7] = '0' + i%10; 
    if (!SD.exists(buffer)) {
      break;
    }
  }
  log_file = SD.open(buffer, FILE_WRITE);
  if (!log_file) {
    if(DEBUG){
      Serial.print("Failed to create file ");
      Serial.println(buffer);
    }
    //error(2);
    error_count++;
    return true;
  }
  if(DEBUG){
    Serial.print("Writing to file ");
    Serial.println(buffer);
  }
  return false;
}

void flash_LEDs(){
  if(LOW_BAT)
     return;
  else{
    for(int i = 0; i < 10; i++){
      digitalWrite(pin_led1, HIGH);
      digitalWrite(pin_led2, HIGH);
      delay(20);
      digitalWrite(pin_led1, LOW);
      digitalWrite(pin_led2, LOW);
      delay(20);
    }
  }
}

/********************************************* SETUP ***************************************/

void setup() {
  // GPS logger
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  WDTCSR = 0;
  if(DEBUG){
    Serial.begin(9600);
  }
  pinMode(PWR_PIN, OUTPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(SD_CARD, OUTPUT);
  digitalWrite(PWR_PIN, LOW);

  // Create log_file
  while(create_new_file())
    delay(1000);
  
  // Initialize communication with GPS
  gpsSerial.begin(GPS_RATE);
  
  // LEDs
  pinMode(pin_led1, OUTPUT);
  pinMode(pin_led2, OUTPUT);
  digitalWrite(pin_led2, HIGH);
  
  //Convert resistor values to division value
  denominator = (float)resistor2 / (resistor1 + resistor2);
  
  // display voltage on LEDs (one pulse per volt)
  v_bat = ((analogRead(voltPin)/ 1024) * 5.0)/ denominator;
  for(int i = 1; i<=4; i++){
    digitalWrite(pin_led1,HIGH);
    digitalWrite(pin_led2,HIGH);
    delay(1000);
    digitalWrite(pin_led1,LOW);
    digitalWrite(pin_led2,LOW);
    delay(1000);
  }
  
  // Pressure Sensor
  pressure_sensor.begin(); 
 flash_LEDs();
 delay(500); 
}// end setup()


/********************************************* LOOP ***************************************/
void loop() {
  // GPS
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
      buffer_done = true;
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
  }// end gps
  if(buffer_done){
    //Obtain RAW voltage data
    v_bat = analogRead(voltPin);
    //Convert to actual voltage (0 - 5 Vdc)
     v_bat = ( v_bat / 1024) * 5.0;
    //Convert to voltage before divider
     v_bat =  v_bat / denominator;
    
    // Pressure sensor
    pressure = pressure_sensor.readPressure();
    temperature = pressure_sensor.readTemperature();
    altitude = pressure_sensor.readAltitude();
    real_altitude = pressure_sensor.readAltitude(TODAYS_PRESSURE);
  
    if (v_bat < v_low){
      LOW_BAT = true;
      flash_LEDs();
      //digitalWrite(PWR_PIN, HIGH); // turn off gps
      if(DEBUG){
        Serial.print("Batery voltage: ");
        Serial.println(v_bat,5);
        Serial.println("Low battery. Powering down");
      }
      
      // close file
      log_file.print("Batery voltage: ");
      log_file.println(v_bat,5);
      log_file.println("Low battery. Powering down");
      log_file.close();
      
      delay(1000);
    }
    else{
      flash_LEDs();
      LOW_BAT = false;
      digitalWrite(PWR_PIN, LOW); // Turn on GPS
      if(!log_file)
        while(create_new_file())
          delay(1000);
      
      //Output to serial
      if(DEBUG){
        Serial.print("\nV_battery = ");
        Serial.print(v_bat,5);
        Serial.println(" Volts");
      
        Serial.print("Temperature = ");
        Serial.print(temperature,5);
        Serial.println(" *C");
          
        Serial.print("Pressure = ");
        Serial.print(pressure,5);
        Serial.println(" Pa");
          
        // Calculate altitude assuming 'standard' barometric
        // pressure of 1013.25 millibar = 101325 Pascal
        Serial.print("Altitude = ");
        Serial.print(altitude,5);
        Serial.println(" meters");
      
        // Calculate altitude using day's pressure
        Serial.print("Real altitude = ");
        Serial.print(real_altitude,5);
        Serial.println(" meters");
          
        Serial.println();
      }
      log_file.print(",sensors:,");      
      log_file.print(v_bat,5);
      log_file.print(",");
      log_file.print(temperature,5);
      log_file.print(",");
      log_file.print(pressure,5);
      log_file.print(",");
      log_file.print(altitude,5);
      log_file.print(",");
      log_file.println(real_altitude,5);
      
      buffer_done = false;
    }
      delay(250);
    }
} // end loop()

// Other GPS Functions
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
