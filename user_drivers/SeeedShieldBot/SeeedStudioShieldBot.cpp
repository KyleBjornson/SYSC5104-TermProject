#include "SeeedStudioShieldBot.h"
#include "mbed.h"


SeeedStudioShieldBot::SeeedStudioShieldBot(
    PinName mot1A, PinName mot1En, PinName mot1B,
    PinName mot2A, PinName mot2En, PinName mot2B,
    PinName sensor_right, PinName sensor_inright, PinName sensor_center, PinName sensor_inleft, PinName sensor_left
) :
    motor1A(mot1A), motor1En(mot1En), motor1B(mot1B),
    motor2A(mot2A), motor2En(mot2En), motor2B(mot2B),
    rightSensor(sensor_right), inRightSensor(sensor_inright), centreSensor(sensor_center), inLeftSensor(sensor_inleft), leftSensor(sensor_left)
{
    // Something should go here...
}

void SeeedStudioShieldBot::right_motor(float speed)
{
    // The bit that's actually needed...
    if (speed >= 0) {
        motor1A = speed;
        motor1B = 0;
    } else {
        motor1A = 1 + speed;
        motor1B = 1;
    }
}

void SeeedStudioShieldBot::left_motor(float speed)
{
    // Useful bit
    if (speed >= 0) {
        motor2A = speed;
        motor2B = 0;
    } else {
        motor2A = 1 + speed;
        motor2B = 1;
    }
}

// The following two functions turn the robot on the spot...

void SeeedStudioShieldBot::left(float speed)
{
    left_motor(-speed);
    right_motor(speed);
}

void SeeedStudioShieldBot::right(float speed)
{
    left_motor(speed);
    right_motor(-speed);
}

void SeeedStudioShieldBot::turn_left(float speed)
{
    left_motor(speed);
    right_motor(0);
}

void SeeedStudioShieldBot::turn_right(float speed)
{
    left_motor(0);
    right_motor(speed);
}

// Again, until we get PWM on the pin w/o PWM, there's no way we can really have this any other way than 1...
// This is the case for both forwards and backwards...

// FIXED, using jumper between pins 8 and 3 on top of the robot board... unfortunately it wastes an io pin, but is easier than using software IO.
// It also means that the 'lid' can't go on top.

void SeeedStudioShieldBot::forward(float speed)
{
    if (speed == 0) {
        left_motor(0);
        right_motor(0);
    } else {
        left_motor(speed);
        right_motor(speed);
    }
}

void SeeedStudioShieldBot::backward(float speed)
{
    if (speed == 0) {
        left_motor(0);
        right_motor(0);
    } else {
        left_motor(-speed);
        right_motor(-speed);
    }
}

void SeeedStudioShieldBot::enable_right_motor()
{
    motor1En = 1;
}

void SeeedStudioShieldBot::enable_left_motor()
{
    motor2En = 1;
}

void SeeedStudioShieldBot::disable_right_motor()
{
    motor1En = 0;
}

void SeeedStudioShieldBot::disable_left_motor()
{
    motor2En = 0;
}

// Give a value representative of the overall data received by the sensors...
// Output between +1 and -1.
// Positive is right, negative left...
float SeeedStudioShieldBot::line_position()
{
    float output = 0;
    if (rightSensor == 1) {
        output += 0.5;
    }
    if (inRightSensor == 1) {
        output += 0.5;
    }
    if (leftSensor == 1) {
        output -= 0.5;
    }
    if (inLeftSensor == 1) {
        output -= 0.5;
    }

    return output;
}

int SeeedStudioShieldBot::getCentreSensor(){
	return centreSensor;
}

int SeeedStudioShieldBot::getRightSensor(){
	return rightSensor;
}

int SeeedStudioShieldBot::getInRightSensor(){
	return inRightSensor;
}

int SeeedStudioShieldBot::getLeftSensor(){
	return leftSensor;
}

int SeeedStudioShieldBot::getInLeftSensor(){
	return inLeftSensor;
}

void SeeedStudioShieldBot::stop(int motor)
{
    if (motor == 1) {
        stopLeft();
    } else if (motor == 2) {
        stopRight();
    }
}

void SeeedStudioShieldBot::stopLeft()
{
    motor1A = 0;
    motor1B = 0;
}

void SeeedStudioShieldBot::stopRight()
{
    motor2A = 0;
    motor2B = 0;
}

void SeeedStudioShieldBot::stopAll()
{
    stopLeft();
    stopRight();
}
