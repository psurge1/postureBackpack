#include <Servo.h>

#define TILTPIN1 2
#define TILTPIN2 8
#define TILTPIN3 10
#define TILTPIN4 12
// #define TILTPIN5 13

int TILTPINS[] = {TILTPIN1, TILTPIN2, TILTPIN3, TILTPIN4};
#define NUMTILTPINS sizeof(TILTPINS)/sizeof(int)

#define DELAYTIME 1000

#define FMOTORM1PIN  5
#define BMOTORM1PIN  4
#define M1ENABLE 11

#define FMOTORM2PIN  6
#define BMOTORM2PIN  7
#define M2ENABLE 3

#define INITSPEED 50
int SPEED1 = INITSPEED+14;
int SPEED2 = INITSPEED;

#define ENABLEMPIN 13

#define RESPONSEPIN 9
#define SERVODEFAULT 0 // 0 to 180
Servo responseServo;

void setup()
{
    responseServo.attach(RESPONSEPIN);
    for (int i = -1; i < NUMTILTPINS; ++i)
    {
        pinMode(TILTPINS[i], INPUT);
    }
    pinMode(FMOTORM1PIN, OUTPUT);
    pinMode(BMOTORM1PIN, OUTPUT);
    pinMode(M1ENABLE, OUTPUT);

    pinMode(BMOTORM2PIN, OUTPUT);
    pinMode(FMOTORM2PIN, OUTPUT);
    pinMode(M2ENABLE, OUTPUT);

    pinMode(ENABLEMPIN, INPUT);

    reset(true);

    Serial.begin(9600);
}

void loop()
{
    if (tiltedSpine())
    {
        responseServo.write(180);
        delay(1000);
        responseServo.write(0);
        delay(1000);
    }

    if (digitalRead(ENABLEMPIN) == 1)
    {
        startM(true, SPEED1, true); // right motor forward
        startM(false, SPEED2, true); // left motor backward
    }
    else
    {
        reset(false);
    }
}

void reset(bool response)
{
    digitalWrite(FMOTORM1PIN, LOW);
    digitalWrite(BMOTORM1PIN, LOW);
    analogWrite(M1ENABLE, SPEED1);

    digitalWrite(FMOTORM2PIN, LOW);
    digitalWrite(BMOTORM2PIN, LOW);
    analogWrite(M2ENABLE, SPEED2);

    if (response)
    {
        responseServo.write(SERVODEFAULT);
    }
}

void startM(bool side, int speed, bool dirF)
{
    if (side)
    {
        if (dirF)
        {
            digitalWrite(FMOTORM1PIN, HIGH);
            digitalWrite(BMOTORM1PIN, LOW);
        }
        else
        {
            digitalWrite(FMOTORM1PIN, LOW);
            digitalWrite(BMOTORM1PIN, HIGH);
        }
    }
    else
    {
        if (dirF)
        {
            digitalWrite(FMOTORM2PIN, HIGH);
            digitalWrite(BMOTORM2PIN, LOW);
        }
        else
        {
            digitalWrite(FMOTORM2PIN, LOW);
            digitalWrite(BMOTORM2PIN, HIGH);
        }
    }
}

bool tiltedSpine()
{
    // check bad posture if about half the tilt sensors are tilted
    int count = 0;
    for (int i = 0; i < NUMTILTPINS; ++i)
    {
        if (digitalRead(TILTPINS[i]) == 1)
        {
            count++;
            if (count == NUMTILTPINS/2)
            {
                return true;
            }
        }
    }
    return false;
}