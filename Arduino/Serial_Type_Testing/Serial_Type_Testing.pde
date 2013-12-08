
int inMsg;

// Parsing
int stringToInt(String s){
  int l = s.length();
  int num;
  if (l < 1){num= -1;}
  else {
    num = 1;
  
    for(int i = 0; i<l; i++){
      switch(s[i]){
        case (int)'0':
         num = num*(10^i) + 0;
         break;
        case (int)'1':
         num = num*(10^i) + 1;
         break;
        case (int)'2':
         num = num*(10^i) + 2;
         break;
        case (int)'3':
         num = num*(10^i) + 3;
         break;
        case (int)'4':
         num = num*(10^i) + 4;
         break;
        case (int)'5':
         num = num*(10^i) + 5;
         break;
        case (int)'6':
         num = num*(10^i) + 6;
         break;
        case (int)'7':
         num = num*(10^i) + 7;
         break;
        case (int)'8':
         num = num*(10^i) + 8;
         break;
        case (int)'9':
         num = num*(10^i) + 9;
         break;
        default:
          Serial.println("Character is not a number");
          return -1;
       }
    }
  }
  return num;
}

int serReadInt()
{
 int i, serAva;                           // i is a counter, serAva hold number of serial available
 char inputBytes [7];                 // Array hold input bytes
 char * inputBytesPtr = &inputBytes[0];  // Pointer to the first element of the array
     
 if (Serial.available()>0)            // Check to see if there are any serial input
 {
   delay(5);                              // Delay for terminal to finish transmitted
                                              // 5mS work great for 9600 baud (increase this number for slower baud)
   serAva = Serial.available();  // Read number of input bytes
   for (i=0; i<serAva; i++)       // Load input bytes into array
     inputBytes[i] = Serial.read();
   inputBytes[i] =  '\0';             // Put NULL character at the end
   return atoi(inputBytesPtr);    // Call atoi function and return result
 }
 else
   return -1;                           // Return -1 if there is no input
}


void setup(){
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

void loop(){
    inMsg = serReadInt();
    if(inMsg > -1){
      Serial.println(inMsg);
      if (inMsg == 3){digitalWrite(13,HIGH);}
      else {digitalWrite(13,LOW);}
    }
    

}
