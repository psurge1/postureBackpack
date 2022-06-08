#define TILTPIN 12

void setup()
{
    pinMode(TILTPIN, INPUT);
    Serial.begin(9600);
}

void loop()
{
    Serial.println(digitalRead(TILTPIN));
}