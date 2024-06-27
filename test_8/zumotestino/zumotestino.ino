#include <Wire.h>
#include <Zumo32U4.h>
#include "prox.h"

Zumo32U4LineSensors lineSensors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4Motors motors;
Zumo32U4Buzzer buzzer;
frontProxSensor proxSensors;

// waarden sensor output
unsigned int sensorWaarde[5];

// toewijzen constanten (deze moeten nog getest worden, met de huidge waarden zal het nog niet perfect werken)
int maxVermogen = 400; // hiermee kan snelheid gelimiteerd worden
const int error_offset = 2000; // moet getest worden, 2000 volgensmij standaard
const int diff_constant_int = 1.1; // range 0.01 - 1
const int diff_constant_afg = 1.6; // range 0 - ???
const int diff_constant_error = 0.3; // range 1 - ???

// initiele waarde
int16_t lastError = 0; // initele waarde geven aan lastError anders werkt algoritme niet
int brown;
int black;

void setup()
{
    // Wacht op button zodat de robot niet uit zichzelf gaat bewegen
    buttonA.waitForButton();
    // Initialiseer de lijnsensors
    lineSensors.initFiveSensors();
    //Calibreer de kleuren van de Lijn
    calibrateColor();
    // Roep de funcite aan die de sensors calibreert
    calibrateLineSensors();
    // Wacht 1 seconde
    delay(1000);
    //wacht op button
    buttonA.waitForButton();
    delay(200);
}

void calibrateColor()
{
    lineSensors.read(sensorWaarde);
    black = sensorWaarde[3];
    buzzer.play(">g32");
    buttonA.waitForButton();
    lineSensors.read(sensorWaarde);
    int gray = sensorWaarde[3];
    buzzer.play(">g32");
    buttonA.waitForButton();
    lineSensors.read(sensorWaarde);
    int green = sensorWaarde[3];
    buzzer.play(">g32");
    buttonA.waitForButton();
    lineSensors.read(sensorWaarde);
    brown = sensorWaarde[3];
    buzzer.play(">g32");
    buttonA.waitForButton();
}   

void calibrateLineSensors()
{
    // Wacht 3 seconden en draai dan over de lijn heen 
    delay(3000);
    // Deze for loop zorgt er voor dat de robot eerst naar links draait en dan naar rechts
    for(int i = 0; i < 90; i++)
    {
      motors.setSpeeds(300, -300);
      lineSensors.calibrate();
      lineSensors.readCalibrated(sensorWaarde);
      }

// Motors stoppen
motors.setSpeeds(0, 0);
}

void sensor_translatie()
{
    // Om de error te kunnen berekenen hebben wij de waarde nodig
    // van de sensor, deze word zelf niet aangeroepen maar wel gebruikt 
    // voor het berekenen van de rest van de waardes.
    int error = lineSensors.readLine(sensorWaarde);

    // De error_afstand is de afstand tot het midden van de lijn, deze wordt
    // berekend door de afgelezen waarde van de sensor en de error_offset hier 
    // van af te trekken. Dit geeft dan een exacte waarde van de afstand tot het 
    // midden van de lijn.
    int16_t error_afstand = error - error_offset;

    // Voor het PID algoritme gaan we naast de error_afstand nog 2 extra waarden gebruiken,
    // allereerst gaan we Derivative (afgeleide) berekenen door de vorige error af te trekken van de huidige error,
    // hierdoor krijg je een delta tussen de errors en deze zorgt er vervolgens voor dat de mate van 
    // correctie naar het midden van de lijn af gaat nemen.
    int16_t error_afg = error_afstand - lastError;

    // voor de 3e term van het PID deel tellen we de huidige error op bij de laatste error, dit is dan de "integraal".
    int16_t error_integral =+ error_afstand;

    // Hier voegen we alle delen bij elkaar, elk onderdeel heeft zijn eigen gewicht wat aangepast kan worden met de 
    // constanten die boven aan de code staan. Dit geeft de mogelijkheid om het volgen van de lijn te fine-tunen.
    int16_t error_output = (error_afstand * diff_constant_error) + (error_integral * diff_constant_int) + (diff_constant_afg * error_afg);
    
    lastError = error_afstand; // lastError schuift door zodat de loop blijft updaten.

    int16_t vermogen_links = maxVermogen + error_output;
    int16_t vermogen_rechts = maxVermogen - error_output;

    vermogen_links = constrain(vermogen_links, 0, maxVermogen);
    vermogen_rechts = constrain(vermogen_rechts, 0, maxVermogen);
    
    motors.setSpeeds(vermogen_links, vermogen_rechts);
    Serial.println(error);
}

void checkuitkomst()
{
    Serial.print(sensorWaarde[1]);
    Serial.print(" ");
    Serial.print(sensorWaarde[2]);
    Serial.print(" ");
    Serial.print(sensorWaarde[3]);
    Serial.println();
}

bool loop_prox = false;

void loop()
{
  while (loop_prox == false){
      lineSensors.read(sensorWaarde);
      if (sensorWaarde[2] < 500){
        maxVermogen = 250;
      }

      else {
      maxVermogen = 400;
      }
      sensor_translatie();
      checkuitkomst();
      if (buttonB.isPressed()){
      loop_prox = true;
      }
      else if (loop_prox == true){
        break;
      }
    }
    
  if(loop_prox == true){
    proxSensors.proxStart();
  }    
}

