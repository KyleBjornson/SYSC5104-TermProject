#include "ParallaxRobotShield.h"
#include "mbed.h"

ParallaxRobotShield::ParallaxRobotShield(PinName leftServoPin, PinName rightServoPin, PinName leftWhiskerPin, PinName rightWhiskerPin, int leftServoCenter, int rightServoCenter,
                                        double leftServoClockwiseOffset, double rightServoClockwiseOffset, double leftServoAntiClockwiseOffset, double rightServoAntiClockwiseOffset) :
                                        leftServo(leftServoPin) , rightServo(rightServoPin), leftWhisker(leftWhiskerPin) , rightWhisker(rightWhiskerPin)
{
    leftCenter = leftServoCenter;
    rightCenter = rightServoCenter;
    leftClockwiseOffset = leftServoClockwiseOffset;
    rightClockwiseOffset = rightServoClockwiseOffset;
    leftAntiClockwiseOffset = leftServoAntiClockwiseOffset;
    rightAntiClockwiseOffset = rightServoAntiClockwiseOffset;

    enable_left_motor();
    enable_right_motor();
}


void ParallaxRobotShield::left_servo(int speed)
{
    // 1300 - clockwise          leftCenter = 1500 - neutral           1700  - anticlockwise
    if(speed > 0)                // Clockwise
        leftServo.pulsewidth_us(leftCenter - (speed * leftClockwiseOffset));
    else                         // Anti-Clockwise
        leftServo.pulsewidth_us(leftCenter - (speed * leftAntiClockwiseOffset));
}


void ParallaxRobotShield::right_servo(int speed)
{
    // 1300 - clockwise          rightCenter = 1500 - neutral           1700  - anticlockwise
    if(speed > 0)                // Anti-Clockwise
        rightServo.pulsewidth_us(rightCenter + (speed * rightAntiClockwiseOffset));
    else                         // Clockwise
        rightServo.pulsewidth_us(rightCenter + (speed * rightClockwiseOffset));
}


void ParallaxRobotShield::forward(int speed)
{
    backward(-speed);
}


void ParallaxRobotShield::backward(int speed)
{
    left_servo(speed);
    right_servo(speed);
}


void ParallaxRobotShield::left(int speed)
{
    left_servo(speed);
    right_servo(-speed);
}


void ParallaxRobotShield::right(int speed)
{
    left(-speed);
}


void ParallaxRobotShield::turn_left(int speed)
{
    left_servo(speed);
}


void ParallaxRobotShield::turn_right(int speed)
{
    right_servo(speed);
}


void ParallaxRobotShield::enable_left_motor()
{
    leftServo.period_us(20000);        // Period is set to 20000 us by default which is equal to 50 Hz
    leftServo.pulsewidth_us(leftCenter);
}


void ParallaxRobotShield::enable_right_motor()
{
    rightServo.period_us(20000);       // Period is set to 20000 us by default which is equal to 50 Hz
    rightServo.pulsewidth_us(rightCenter);
}


void ParallaxRobotShield::stopLeft()
{
	leftServo.pulsewidth_us(leftCenter);
    leftServo.period_us(0);

}


void ParallaxRobotShield::stopRight()
{
	rightServo.pulsewidth_us(rightCenter);
    rightServo.period_us(0);
}


void ParallaxRobotShield::stopAll()
{
    stopRight();
    stopLeft();
}


int ParallaxRobotShield::leftWhiskerContact()
{
    if(leftWhisker.read() == 0)
        return 1;
    else     
        return 0;
}


int ParallaxRobotShield::rightWhiskerContact()
{
    if(rightWhisker.read() == 0)
        return 1;
    else     
        return 0;
}


int ParallaxRobotShield::lightSensor(PinName lightSensor)
{
    DigitalInOut QTR(lightSensor);       // the QTR-1RC light sensor
    int black;
    Timer t;
    QTR.output();
    QTR = 1;
    t.start();
    QTR.input();
    while (QTR == 1 || t.read_us() < 3000);
    black = t.read_us();        
    t.stop();
    t.reset();
    printf("LS value %d ", black);
    if(black > 3100)       // Black
        return 1; 
    else 
        return 0; 
}


int ParallaxRobotShield::bumpSensor(PinName bumpSensor)
{
    DigitalIn bump(bumpSensor);       // the 10 cm Sharp GP2Y0D810Z0F Digital Distance Sensor
    if(bump.read() == 0)
        return 1;
    else
        return 0;
}


double ParallaxRobotShield::distanceSensor(PinName trigPin, PinName echoPin)
{
    DigitalOut trig(trigPin);       // Sends out an Ultasonicsonic signal
    DigitalIn echo(echoPin);        // Recieves an Ultasonicsonic signal
    Timer timer;        // for measuring the duration of the signal's joyless journey
    
    timer.reset();
    trig = 0;
    wait_us(2);
    trig = 1;
    wait_us(10);
    trig = 0;
    while(echo == 0);
    timer.start();
    while(echo == 1);
    timer.stop();

    // Distance = ( (Duration of travel) * (Speed of Ultasonicsonic: 340m/s) ) / 2
    return (timer.read_us() * 0.034) / 2.0;        // Microseconds are used for accuracy
}


/** Optional implementation for future use
void ParallaxRobotShield::whiskersLED(PinName left_LED, PinName right_LED)
{
    DigitalOut leftLED(left_LED);
    DigitalOut rightLED(right_LED);
    if(leftWhiskerContact())
    {
        leftLED = 1;
        wait(0.1);
    }
    if(rightWhiskerContact())
    {
       rightLED = 1;    
       wait(0.1);
    }
    leftLED = 0;
    rightLED = 0;
}
*/
