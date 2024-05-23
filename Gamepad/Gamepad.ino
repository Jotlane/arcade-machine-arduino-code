#include "HID-Project.h"

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

const byte numChars = 46;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing


boolean newData = false;

int buttonss[8];
int joystickLX;
int joystickLY;
int joystickRX;
int joystickRY;


void setup() {
  Serial1.begin(115200);
  Serial.begin(115200);
  // Sends a clean report to the host. This is important on any Arduino type.
  Gamepad.begin();
}

void loop() {

  recvWithStartEndMarkers();
  if (newData == true) {
      strcpy(tempChars, receivedChars);
          // this temporary copy is necessary to protect the original data
          //   because strtok() used in parseData() replaces the commas with \0
      parseData();
      newData = false;
      for (int i = 0;i<8;i++){
        if (buttonss[i]){
          Gamepad.press(i+1);
          //Serial.print(i+1);
          //Serial.println(" is pressed");
        }
        else{
          //Serial.print(i+1);
          //Serial.println(" is released");
          Gamepad.release(i+1);
        }
      }
      Gamepad.xAxis(joystickLX);
      Gamepad.yAxis(joystickLY);
      Gamepad.rxAxis(joystickRX);
      Gamepad.ryAxis(joystickRY);
      Serial.println("begin");
      //Serial.println(joystickLX);
      //Serial.println(joystickLY);
      //Serial.println(joystickRX);
      //Serial.println(joystickRY);
      Gamepad.write();
  }
}



//============

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
    while (Serial1.available() > 0 && newData == false) {
        rc = Serial1.read();
        if (recvInProgress == true) {
          
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
                Serial.println(receivedChars);
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============

void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index
    strtokIndx = strtok(tempChars,",");
    for (int i = 0; i<8; i++){
      buttonss[i] = atoi(strtokIndx);
      strtokIndx = strtok(NULL, ",");
    }
    joystickLX = atoi(strtokIndx);
    strtokIndx = strtok(NULL, ",");
    joystickLY = atoi(strtokIndx);
    strtokIndx = strtok(NULL, ",");
    joystickRX = atoi(strtokIndx);
    strtokIndx = strtok(NULL, ",");
    joystickRY = atoi(strtokIndx);
    strtokIndx = strtok(NULL, ",");    
}
