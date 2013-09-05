#include <Arduino.h>

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#ifdef DEBUG
 #define debug(x)        Serial.println(String() + x);
 #define debug_inline(x) Serial.print(String() + x);
#else
 #define debug(x)
 #define debug_inline(x)
#endif

namespace MorseCode
{
    void digital_dot(int pin, int duration)
    {
        digitalWrite(pin, HIGH);
        delay(1 * duration);
        digitalWrite(pin, LOW);
    }

    void digital_dash(int pin, int duration)
    {
        digitalWrite(pin, HIGH);
        delay(3 * duration);
        digitalWrite(pin, LOW);
    }

    void analog_dot(int pin, int duration, int frequency)
    {
        tone(pin, frequency, duration);
        delay(duration);
    }

    void analog_dash(int pin, int duration, int frequency)
    {
        duration *= 3;
        tone(pin, frequency, duration);
        delay(duration);
    }

    // inter-element gap
    void gap(int duration)
    {
        delay(1 * duration);
    }

    // don't ask why short. It's 3 durations long # between letters
    void short_gap(int duration)
    {
        delay(3 * duration);
    }

    // between words
    void medium_gap(int duration)
    {
        delay(7 * duration);
    }

    void play(int pin, int wpm, int frequency, char *c)
    {
        debug(c)
        while ( *c ) {
            if ( frequency == 0 ) {
                switch ( *c ) {
                    case '.':
                        digital_dot(pin, wpm);
                        gap(wpm);
                        break;

                    case '-':
                        digital_dash(pin, wpm);
                        gap(wpm);
                        break;
                }
            } else {
                switch ( *c ) {
                    case '.':
                        analog_dot(pin, wpm, frequency);
                        gap(wpm);
                        break;

                    case '-':
                        analog_dash(pin, wpm, frequency);
                        gap(wpm);
                        break;
                }
            }
            c++;
        }
        short_gap(wpm);
    }

    // pin to use, text to transmit, words per minute, frequency ( in case of using a buzzer )
    void transmit(int pin, char *s, int wpm, int frequency = 0)
    {
        if ( wpm < 1 ) {
            wpm = 8;
        }

        // The word PARIS is standard for defining code speed
        // It has 50 elements
        // so it is 1 minute divided by wpm*words, wich will be dot speed
        wpm = (60 * 1000L) / (50 * wpm);

        if ( frequency == 0 ) {
            pinMode(pin, OUTPUT);
        }

        while ( *s ) {
            switch ( *s ) {
                case 'a':
                case 'A':
                    play(pin, wpm, frequency, ".-");
                    break;

                case 'b':
                case 'B':
                    play(pin, wpm, frequency, "-...");
                    break;

                case 'c':
                case 'C':
                    play(pin, wpm, frequency, "-.-.");
                    break;

                case 'd':
                case 'D':
                    play(pin, wpm, frequency, "-..");
                    break;

                case 'e':
                case 'E':
                    play(pin, wpm, frequency, ".");
                    break;

                case 'f':
                case 'F':
                    play(pin, wpm, frequency, "..--.");
                    break;

                case 'g':
                case 'G':
                    play(pin, wpm, frequency, "--.");
                    break;

                case 'h':
                case 'H':
                    play(pin, wpm, frequency, "....");
                    break;

                case 'i':
                case 'I':
                    play(pin, wpm, frequency, "..");
                    break;

                case 'j':
                case 'J':
                    play(pin, wpm, frequency, ".---");
                    break;

                case 'k':
                case 'K':
                    play(pin, wpm, frequency, "-.-");
                    break;

                case 'l':
                case 'L':
                    play(pin, wpm, frequency, ".-..");
                    break;

                case 'm':
                case 'M':
                    play(pin, wpm, frequency, "--");
                    break;

                case 'n':
                case 'N':
                    play(pin, wpm, frequency, "-.");
                    break;

                case 'o':
                case 'O':
                    play(pin, wpm, frequency, "---");
                    break;

                case 'p':
                case 'P':
                    play(pin, wpm, frequency, ".--.");
                    break;

                case 'q':
                case 'Q':
                    play(pin, wpm, frequency, "--.-");
                    break;

                case 'r':
                case 'R':
                    play(pin, wpm, frequency, ".-.");
                    break;

                case 's':
                case 'S':
                    play(pin, wpm, frequency, "...");
                    break;

                case 't':
                case 'T':
                    play(pin, wpm, frequency, "-");
                    break;

                case 'u':
                case 'U':
                    play(pin, wpm, frequency, "..-");
                    break;

                case 'v':
                case 'V':
                    play(pin, wpm, frequency, "...-");
                    break;

                case 'w':
                case 'W':
                    play(pin, wpm, frequency, ".--");
                    break;

                case 'x':
                case 'X':
                    play(pin, wpm, frequency, "-..-");
                    break;

                case 'y':
                case 'Y':
                    play(pin, wpm, frequency, "-.--");
                    break;

                case 'z':
                case 'Z':
                    play(pin, wpm, frequency, "--..");
                    break;

                case '0':
                    play(pin, wpm, frequency, "-----");
                    break;

                case '1':
                    play(pin, wpm, frequency, ".----");
                    break;

                case '2':
                    play(pin, wpm, frequency, "..---");
                    break;

                case '3':
                    play(pin, wpm, frequency, "...--");
                    break;

                case '4':
                    play(pin, wpm, frequency, "....-");
                    break;

                case '5':
                    play(pin, wpm, frequency, ".....");
                    break;

                case '6':
                    play(pin, wpm, frequency, "-....");
                    break;

                case '7':
                    play(pin, wpm, frequency, "--...");
                    break;

                case '8':
                    play(pin, wpm, frequency, "---..");
                    break;

                case '9':
                    play(pin, wpm, frequency, "----.");
                    break;

                default:
                    medium_gap(wpm);
            }

            s++;
        }
    }
}
