#include <Servo.h> 

Servo myservo; // Lager en Servo variabel for å styr Servo motoren

// Her definerer vi pin til Force Sensor, Høytalleren og knappen.
const int forceSensorPin = A0;
const int speakerPin = 3;
const int buttonPin = 2;

// Her setter vi terskelen for å detektere trykket på sensoren
const int pressureThreshold = 5;

int pos = 0; // Denne variabelen blir brukt senere i programmet når vi bruker Servo motoren
bool kjoerProgram = false; // Vi lager en boolean kontroller som har en hovedoppgave om å være en av/på knapp for prototypen

void setup() {
  // Setter pin modes
  pinMode(forceSensorPin, INPUT); // Force Sensor tar inn en verdi
  pinMode(speakerPin, OUTPUT); // Høytalleren gir ut en lyd
  pinMode(buttonPin, INPUT_PULLUP); // Bruker INPUT_PULLUP for å aktivere en intern motstand som hindrer at inngangspinnen flakker mellom høye og lave verdier når knappen ikke er aktivert
  myservo.attach(9); // Setter Servo motoren til pin 9
}

void loop() {
  if (digitalRead(buttonPin) == LOW) { //Når knappen blir trykket ned
    if (!kjoerProgram) {
      kjoerProgram = true; // Starter programmet
    }
    while (digitalRead(buttonPin) == LOW) {} // Denne kode delen sørger for at programmet venter til brukeren har sluppet knappen
  }
  
  int sensorValue = analogRead(forceSensorPin); //Leser verdien fra sensoren og legger den i variabelen sensorValue

  if (kjoerProgram) { //Når knappen blir trykket ned, starter hovedprogrammet
    while (kjoerProgram) { // while løkke som har en hovedoppgave at høytalleren skal spille lyd i loop helt til sensoren blir trykket ned
      tone(speakerPin, 114, 8000); // Gir lyd til høytalleren
      for (int i = 0; i < 40; i++){ // Dette er en for løkke som kjører 40 ganger med 200 millisekunder pauserom, totalt 8 sekunder
      // Denne loopen sjekker hele tiden om sensoren blir trykket ned
        if (!kjoerProgram) {
          return; // Dersom sensoren blir trykket ned returner programmet her og resetter programmet
        }
      delay(200);
  
      sensorValue = analogRead(forceSensorPin); // Henter verdien til sensoren
      if (sensorValue > pressureThreshold) { // Hvis verdien er høy, altså sensoren blir trykket ned kjører denne if-statementen
        noTone(speakerPin); // Slår av høytalleren
        for (pos = 0; pos <= 180; pos += 1) { // går fra 0 grader til 180 grader. Altså den forteller Servo at den skal bevege seg 1 grad for hver gang for-løkka kjører
          myservo.write(pos);                      // Sier til Servo at den skal gå til posisjonen i variable 'pos', som da er en grad mer for hver gang for-løkka kjører
          delay(15);                               // venter 15ms mellom hver beveglse slik at motoren får tid til å nå posisjonen sin
        }                                          
        for (pos = 180; pos >= 0; pos -= 1) { // Denne gjør det samme som den over, bare at den går fra 180 grader til 0 grader
          myservo.write(pos);                    
          delay(15);                             
        }                                     // Det er altså denne delen som sørger for at prototypen gir ut godteri
        kjoerProgram = false; //Resetter programmet
        }
      }

      for (int i = 0; i < 100; i++){ // Etter at for løkken over kjører i 8 sekunder, vil da denne for løkken kjøre i 20 sekunder
        if (!kjoerProgram){          // Hensikten med denne for løkken er at dyret skal kunne lete i 20 sekunder før prototypen begynner å lage lyd igjen
          return;
        }
        delay(200);
        
        sensorValue = analogRead(forceSensorPin);
        if (sensorValue > pressureThreshold) {       // Samme som over, sjekker verdien til sensoren hele tiden, slik at hvis sensoren er trykket ned vil godteriet komme ut
          noTone(speakerPin); // Slår av høytalleren9
          for (pos = 0; pos <= 180; pos += 1) { // går fra 0 grader til 180 grader. Altså den forteller Servo at den skal bevege seg 1 grad for hver gang for-løkka kjører
            myservo.write(pos);                      // Sier til Servo at den skal gå til posisjonen i variable 'pos', som da er en grad mer for hver gang for-løkka kjører
            delay(15);                               // venter 15ms mellom hver beveglse slik at motoren får tid til å nå posisjonen sin
          }
          for (pos = 180; pos >= 0; pos -= 1) { // Denne gjør det samme som den over, bare at den går fra 180 grader til 0 grader
            myservo.write(pos);                    
            delay(15);                             
          }
          kjoerProgram = false; //Resetter programmet
        }
      }
    }
  }
}

