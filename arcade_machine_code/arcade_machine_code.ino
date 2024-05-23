//All the button pins
//const int button1Pin = 12;
//const int button2Pin = 11;
//const int button3Pin = 10;
//const int button4Pin = 9;
//const int button5Pin = 8;
//const int button6Pin = 7;
//const int button7Pin = 6;
//const int button8Pin = 5;

int buttonPins[8];
//for (int i=0; i<8; i++){
//  buttonPins[i] = 12-i;
//}

//All the joystick pins
const int joystick1xPin = A0;
const int joystick1yPin = A1;
const int joystick2xPin = A2;
const int joystick2yPin = A3;

//Button state variables
//int button1State = 0;
//int button2State = 0;
//int button3State = 0;
//int button4State = 0;
//int button5State = 0;
//int button6State = 0;
//int button7State = 0;
//int button8State = 0;

int buttonStates[8];
//for (int j=0; i<8; i++){
//  buttonStates[j] = 0;
//}

//Joystick state values
float joystick1xValue = 513.0;
float joystick1yValue = 513.0;
float joystick2xValue = 513.0;
float joystick2yValue = 513.0;


void setup() {
  // put your setup code here, to run once:
  //set botton and joystick pins as inputs
  for (int i=0; i<8; i++){
    buttonPins[i] = 12-i;
  }
  
  for(int i=0;i<8;i++){
    pinMode(buttonPins[i], INPUT);
  }

  for (int i=0; i<8; i++){
    buttonStates[i] = 0;
  }
  
//  pinMode(button1Pin, INPUT);
//  pinMode(button2Pin, INPUT);
//  pinMode(button3Pin, INPUT);
//  pinMode(button4Pin, INPUT);
//  pinMode(button5Pin, INPUT);
//  pinMode(button6Pin, INPUT);
//  pinMode(button7Pin, INPUT);
//  pinMode(button8Pin, INPUT);
  pinMode(joystick1xPin, INPUT);
  pinMode(joystick1yPin, INPUT);
  pinMode(joystick2xPin, INPUT);
  pinMode(joystick2yPin, INPUT);

  //Setting LED pin to output for demo purposes
  pinMode(13, OUTPUT);

  //Begin serial for debugging purposes
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  //Read all sensor states
  for (int i=0;i<8;i++){
    buttonStates[i] = digitalRead(buttonPins[i]);
  }
//  button1State = digitalRead(button1Pin);
//  button2State = digitalRead(button2Pin);
//  button3State = digitalRead(button3Pin);
//  button4State = digitalRead(button4Pin);
//  button5State = digitalRead(button5Pin);
//  button6State = digitalRead(button6Pin);
//  button7State = digitalRead(button7Pin);
//  button8State = digitalRead(button8Pin);
  joystick1xValue = analogRead(joystick1xPin);
  joystick1yValue = analogRead(joystick1yPin);
  joystick2xValue = analogRead(joystick2xPin);
  joystick2yValue = analogRead(joystick2yPin);
  Serial.flush();
  String message = "<";
  for (int i=0;i<8;i++){
    message += String(buttonStates[i]);
    message += ",";
  }
  message += String(map(joystick1xValue,0,1023,-32767,32767));
  message += ",";
  message += String(map(joystick1yValue,0,1023,-32767,32767));
  message += ",";
  message += String(map(joystick2xValue,0,1023,-32767,32767));
  message += ",";
  message += String(map(joystick2yValue,0,1023,-32767,32767));
  message += ">";
  Serial.write(message.c_str());
  delay(10);
}
