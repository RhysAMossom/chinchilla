#define resistor1 10000
#define resistor2 10000
const int voltPin = 0;

//Variables for voltage divider

float denominator; 

void setup() {

  Serial.begin(9600);
  //Convert resistor values to division value
  //  Equation is previously mentions voltage divider equation
  //  R2 / (R1 + R2)
  //  In this case returns 0.20 or 1/5
  denominator = (float)resistor2 / (resistor1 + resistor2);

} // Void Setup Close

void loop() {

  float voltage;
  //Obtain RAW voltage data
  voltage = analogRead(voltPin);

  //Convert to actual voltage (0 - 5 Vdc)
  voltage = (voltage / 1024) * 5.0;

  //Convert to voltage before divider
  //  Divide by divider = multiply
  //  Divide by 1/5 = multiply by 5
  voltage = voltage / denominator;

  //Output to serial
  Serial.print("Volts: ");
  Serial.println(voltage);

  //Delay to make serial out readable
  delay(500);

} // void loop close 
