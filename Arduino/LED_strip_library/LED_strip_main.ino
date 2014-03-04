/********************** Interrupt Functions **************************/

void increment_effect(){
  effect = (effect + 1) % REGULAR_EFFECTS;
}

void toggle_effect_flow(){
  //continuous_flow = digitalRead(FLOW_PIN);
  continuous_flow = !continuous_flow;
}

void special_effect(){
  effect = REGULAR_EFFECTS;
}

void special_function(){


/********************** Arduino Functions **************************/
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  // add random seed
  randomSeed(analogRead(1));

  // Attach interrupts
  attachInterrupt(0, increment_effect, RISING); // pin 2
  attachInterrupt(1, toggle_effect_flow, CHANGE); // pin 3
  attachInterrupt(2, special_effect, RISING); // pin 21
//  attachInterrupt(3, int3, FALLING); // pin 20
//  attachInterrupt(4, int4, LOW); // pin 19
//  attachInterrupt(5, int5, RISING); // pin 18

  Serial.begin(9600);
  pinMode(FLOW_LED_PIN,OUTPUT);
}

void loop(){
  Serial.print("effect: ");
  Serial.print(effect);
  digitalWrite(FLOW_LED_PIN,continuous_flow);
  Serial.print("\tcontinuous flow: ");
  Serial.println(continuous_flow);
}
