
// Include Libraries
#include "Arduino.h"
#include "HX711.h"


// Pin Definitions
#define SCALE_PIN_DAT	2
#define SCALE_PIN_CLK	4
int relay = 12;

// Global variables and defines

// object initialization
HX711 scale(SCALE_PIN_DAT, SCALE_PIN_CLK);
#define calibration_factor 50800
//

// define vars for testing menu
const int timeout = 100000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    pinMode(relay, OUTPUT);
    digitalWrite(relay, HIGH);
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    scale.set_scale(calibration_factor); 
    scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
    menuOption = menu();
    scale.tare();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{  
    if(menuOption == '1') {
    // SparkFun HX711 - Load Cell Amplifier - Test Code
    float scaleUnits = scale.get_units();
     digitalWrite(relay, LOW);
  
    //scale.get_units() returns a float
    Serial.print(scaleUnits); //You can change this to lbs but you'll need to refactor the calibration_factor
    Serial.println(" Kg"); //You can change this to lbs but you'll need to refactor the calibration_factor
   if(scaleUnits > 0.50)
    {
    digitalWrite(relay, HIGH);
      delay(10000);
   }
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
        digitalWrite(relay, HIGH);
      
    }

    }
}

// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) SparkFun HX711 - Load Cell Amplifier"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing SparkFun HX711 - Load Cell Amplifier"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
