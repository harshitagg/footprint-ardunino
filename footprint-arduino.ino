// constants won't change. They're used here to 
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  3;// the number of the LED pin
const int vib=4;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;
// variables will change:
int buttonState = 0; 
int buttonState2 = 0; 
int ledState =0;// variable for reading the pushbutton status
int count=0;
int state=0;
int i=0;
boolean buttonPressed=true;
int buttonClickedTime=0;
void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT); 
  pinMode(vib, OUTPUT);   
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);    
  Serial.begin(9600); 
}

void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  ledState = digitalRead(ledPin);
  digitalWrite(vib, LOW);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState==LOW && buttonPressed == true && ledState==LOW)
  {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);
    String sendString = "active";
    Serial.println(sendString);  
    Serial.flush();
    buttonPressed = false;
    buttonClickedTime = millis();
  }
  if(buttonState == HIGH)
  {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  }

  if (millis() > buttonClickedTime + 500) 
  { 
    buttonPressed = true; 
  } 
  digitalWrite(ledPin, LOW);
  getCommands();

  delay(100);
}
void getCommands() {

  if (Serial.available()) {

    while (Serial.available()) {
      char inChar = (char)Serial.read(); 
      inputString += inChar;
      if (inChar == '\n') {
        stringComplete = true;
        break;
      }
    }
  }

  if (stringComplete) {
    // this might represent a command send from the 
    // phone side.  After reading it we would
    // parse it and then schedule the action.
    buttonState = digitalRead(buttonPin);
    if(inputString.startsWith("vibhigh"))
    {
      for(i=0;i<3;i++)
      {  
        while(count<100000) {
          digitalWrite(vib, HIGH);
          count++; 
        }

        while(count>=100000)
        { 
          digitalWrite(vib, LOW);
          count++;
          if(count==200000)
            count=0;
        }
        buttonState = digitalRead(buttonPin);

      }

      //  getCommands(); 
      delay(100);

    } 
    else if(inputString.startsWith("viblow"))
    {
      for(i=0;i<3;i++)
      {  
        while(count<10000) {
          digitalWrite(vib, HIGH);
          count++; 
        }

        while(count>=10000)
        {
          digitalWrite(vib, LOW);
          count++;
          if(count==100000)
            count=0;
        }
        buttonState = digitalRead(buttonPin);

      }

      //  getCommands(); 
      delay(100);

    }
    else if(inputString.startsWith("ledon"))
    {  
      digitalWrite(ledPin, HIGH);
      buttonState = digitalRead(buttonPin);
      delay(100);

    }   
    else if(inputString.startsWith("ledoff"))
    {  
      digitalWrite(ledPin, LOW);
      buttonState = digitalRead(buttonPin); 
      delay(100);

    }   
    else if(inputString.startsWith("vibveryhigh"))
    {
      for(i=0;i<3;i++)
      {  
        while(count<10000) {
          digitalWrite(vib, LOW);
          count++; 
        }

        while(count>=10000)
        {
          digitalWrite(vib, HIGH);
          count++;
          if(count==100000)
            count=0;
        }
        buttonState = digitalRead(buttonPin);

      }

      //  getCommands(); 
      delay(100);

    }
    else if(inputString.startsWith("stop"))
    {
      digitalWrite(vib, LOW); 
    }
    buttonState = digitalRead(buttonPin);

  }
  inputString = "";
  stringComplete = false;
}

