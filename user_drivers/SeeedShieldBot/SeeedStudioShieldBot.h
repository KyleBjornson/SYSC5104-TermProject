#include "mbed.h"

/** Seeed Studio Shield Bot Control Class
 *  In order to use this properly, you need to connect a jumper between pins eight and three on the shield bot, and you can't use either pins 8 or 3, which correspond to PTA13 and PTA12, respectively.
 *  Also, in order to provide power to the freedom board, when running just of a lipo battery, you need to connect between 5V and VIN on the shield bot.
 *  Code/notes above only tested with version 0.9b, may not be needed/may not work in other cases...
*/
class SeeedStudioShieldBot {
    public:
    
        /** Create a shield bot object
         *
         * @param mot1A Left Motor A pin, default D8
         * @param mot1B Left Motor B pin, default D9
         * @param mot1En Left Motor enable pin, default D11
         * @param mot2A Right Motor A pin, default D12
         * @param mot2B Right Motor B pin, default D10
         * @param mot2En Right Motor enable pin, default D13
         * @param sensor_right Sensor right pin, default A0
         * @param sensor_inright Sensor in-right pin, default A1
         * @param sensor_center Sensor right pin, default A2
         * @param sensor_inleft Sensor in-left pin, default A3
         * @param sensor_left Sensor left pin, default D4
         */
        SeeedStudioShieldBot(PinName mot1A, PinName mot1En, PinName mot1B, PinName mot2A, PinName mot2En, PinName mot2B, PinName sensor_right, PinName sensor_inright, PinName sensor_center, PinName sensor_inleft, PinName sensor_left);

        /** Switch on the left motor at the given speed.
         *  @param speed The speed, from 0.0 to 1.0 at which to spin the motor.
         */
        void left_motor(float speed);
        
        /** Switch on the right motor at the given speed.
         *  @param speed The speed, from 0.0 to 1.0 at which to spin the motor.
         */
        void right_motor(float speed);
        
        /** Switch on both motors, forwards at the given speed.
         *  @param speed The speed, from 0.0 to 1.0 at which to spin the motor.
         */
        void forward(float speed);
        
        /** Switch on both motors, backwards at the given speed.
         *  @param speed The speed, from 0.0 to 1.0 at which to spin the motor.
         */
        void backward(float speed);
        
        /** Switch on both motors at the given speed, in opposite directions so as to turn left.
         *  @param speed The speed, from 0.0 to 1.0 at which to spin the motors.
        */
        void left(float speed);
        
        /** Switch on both motors at the given speed, in opposite directions so as to turn right.
         *  @param speed The speed, from 0.0 to 1.0 at which to spin the motors.
         */
        void right(float speed);
        
        /** Turns left.
         *  @param speed The speed, from 0.0 to 1.0 at which to spin the motor.
         */
        void turn_left(float speed);
        
        /** Turns right.
         *  @param speed The speed, from 0.0 to 1.0 at which to spin the motor.
         */
        void turn_right(float speed);
        
        /** Disable the left motor, by driving enable pin for the second motor low...
         */
        void disable_left_motor();
        
        /** Disable the left motor, by driving enable pin for the first motor low...
         */
        void disable_right_motor();
        
        /** Enable the left motor, by driving enable pin for the second motor high...
         */
        void enable_left_motor();
        
        /** Enable the left motor, by driving enable pin for the first motor high...
         */
        void enable_right_motor();
        
        /** Stop a chosen motor.
         *  @param motor Number, either 1 or 2 choosing the motor.
         */
        void stop(int motor);
        
        /** Stop left motor.
         */
        void stopLeft();
        
        /** Stop right motor.
         */
        void stopRight();
        
        /** Stop both motors at the same time. Different to disable.
         */
        void stopAll();
        
        // Need to do something to do with detected line...
        
        /** Gives an indication of the data given by the reflectivity sensors.
         */
        float line_position();
        
        int getCentreSensor();
        int getRightSensor();
        int getInRightSensor();
        int getLeftSensor();
        int getInLeftSensor();


        DigitalIn rightSensor;
        DigitalIn inRightSensor;
        DigitalIn centreSensor;
        DigitalIn inLeftSensor;
        DigitalIn leftSensor;
        
    private:
        PwmOut motor1A;
        DigitalOut motor1B;
        DigitalOut motor1En;
        
        PwmOut motor2A;
        DigitalOut motor2B;
        DigitalOut motor2En;
};
