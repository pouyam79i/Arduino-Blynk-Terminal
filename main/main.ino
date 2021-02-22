#define BLYNK_PRINT Serial

#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "yourAuth";

#define W5100_CS  10
#define SDCARD_CS 4

// Attach virtual serial terminal to Virtual Pin V1
WidgetTerminal terminal(V1);

// You can send commands from Terminal to your hardware. Just use
// the same Virtual Pin as your Terminal Widget
BLYNK_WRITE(V1)
{
  
  // if you type "Marco" into Terminal Widget - it will respond: "Polo:"
  // if (String("pin") == param.asStr()) {
  //   terminal.println("You said: 'Marco'") ;
  //   terminal.println("I said: 'Polo'") ;
  // } else {

  //   // Send it back
  //   terminal.print("You said:");
  //   terminal.write(param.getBuffer(), param.getLength());
  //   terminal.println();
  // }

  String myInput = param.asStr();
  myInput.trim();
  
  myInput.trim();
  if(myInput.startsWith("pin") == true) {
    Serial.println("It has pin command");
    delay(500);
    Serial.print("The Input is: ");
    delay(500);
    Serial.println(myInput);
    Serial.print("Index of p: ");
    Serial.print(myInput.indexOf("p"));
    delay(500);
    Serial.print(" Index of first dash : ");
    Serial.println(myInput.indexOf("-"));
    Serial.print("Index of first dash : ");
    Serial.println(myInput.indexOf("-", myInput.indexOf("-") + 1));
    char str[myInput.length()+ 1];
    myInput.toCharArray(str, myInput.length() + 1);
    str[myInput.length()+1] = '\0';
    char func = str[myInput.indexOf("-")+1];
    char state = str[myInput.indexOf("-", myInput.indexOf("-")+1)+1];
    Serial.print("func: ");
    Serial.println(func);
    delay(100);
    Serial.print("state: ");
    Serial.println(state);
    Serial.println(str);
    int temp = myInput.indexOf("-") - 3;
    Serial.println(temp);
    int pinNumber = 0;
    if(temp==1)
  {
       pinNumber = int(str[3]) - 48;
      
  }else if(temp == 2){
  
    pinNumber = int(str[4]) - 48;
    pinNumber += 10;
    }
    Serial.print("pin num: ");
      Serial.println(pinNumber);
    
    if(func == 'o'){
    pinMode(pinNumber, OUTPUT);
    if(state == 'h'){
      digitalWrite(pinNumber, HIGH);
    }
    else if(state == 'l'){
      digitalWrite(pinNumber, LOW);
    }
  }else if(func == 'i'){
    pinMode(pinNumber, INPUT);
    delay(100);
    Serial.print("digital pin ");
    Serial.print(pinNumber);
    Serial.print(" value: ");
    Serial.println(digitalRead(pinNumber));
    
  }
  }

  // Ensure everything is sent
  terminal.flush();
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH); // Deselect the SD card

  Blynk.begin(auth);

  terminal.clear();

  terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.println(F("-------------"));
  terminal.println(F("Type 'Marco' and get a reply, or type"));
  terminal.println(F("anything else and get it printed back."));
  terminal.flush();
}

void loop()
{
  Blynk.run();
}
