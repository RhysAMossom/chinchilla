float temp_in_celsius = 0, temp_in_kelvin=0, temp_in_fahrenheit=0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{

  //Reads the input and converts it to Kelvin degrees
  temp_in_kelvin = analogRead(0) * 0.004882812 * 100;
 
  //Converts Kelvin to Celsius minus 2.5 degrees error
  temp_in_celsius = temp_in_kelvin - 2.5 - 273.15;
 
  temp_in_fahrenheit = ((temp_in_kelvin - 2.5) * 9 / 5) - 459.67;

  //Print the temperature in Celsius to the serial port
  Serial.print("Celsius: ");
  Serial.println(temp_in_celsius);                 

  //Print the temperature in Fahrenheit to the serial port
  Serial.print("Fahrenheit: ");
  Serial.println(temp_in_fahrenheit);
  Serial.println();


  delay(1000);
}
