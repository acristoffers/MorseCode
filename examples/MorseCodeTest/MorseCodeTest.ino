#define DEBUG

#include <MorseCode.h>

void setup()
{
    Serial.begin(9600);
    Serial.println("Started Buzzer");
    MorseCode::transmit( 13, "PARIS", 8, NOTE_C4);
    Serial.println("Finished Buzzer");

    Serial.println("Started LED");
    MorseCode::transmit( 8, "PARIS", 8 );
    Serial.println("Finished LED");
}

void loop()
{

}