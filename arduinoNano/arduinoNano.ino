#include <Servo.h>
#include <Arduino.h>
#include <Wire.h>
#include <NewPing.h>

#define servoPin 12

/// Servo
Servo servo;

/// sensors
long MAX_DIS = 350;
NewPing sensor01(3,4, MAX_DIS);
NewPing sensor02(5,6, MAX_DIS);
NewPing sensor03(7,8, MAX_DIS);
NewPing sensor04(9,10, MAX_DIS);

void setup()
{
    Serial.begin(115200);
    Serial.setTimeout(5);
    Wire.begin();
    
    /// Servo
    servo.attach(servoPin);
    servo.write(0);

    delay(100);
}
char msg[100];
void Data2Wifi(long D1, long A1, long D2, long A2, long D3, long A3, long D4, long A4)
{

    sprintf(msg, "%ld %ld %ld %ld %ld %ld %ld %ld\n", D1, A1, D2, A2, D3, A3, D4, A4);
    Serial.write(msg);
}

long i = 0;
bool reverse = false;


long distance01 = 0;
long distance02 = 0;
long distance03 = 0;
long distance04 = 0;
void loop()
{
    long angle01 = -i*75 ;
    long angle02 = angle01 - 90*100;
    long angle03 = angle01 + 90*100;
    long angle04 = angle01 + 180*100;
        
    servo.write(i);
        
    /// Sensors
    distance01 = sensor01.ping_cm();
    distance02 = sensor02.ping_cm();
    distance03 = sensor03.ping_cm();
    distance04 = sensor04.ping_cm();
    Data2Wifi(distance01, angle01, distance02, angle02, distance03, angle03, distance04, angle04);
       
    i= i + ((reverse == true) ? -1 : 1);
    if (i == 120) reverse = true;
    else if (i == 0) reverse = false;
}
