#include "mbed.h"

/**  Parallax Robot Shield Control Class
 */
class ParallaxRobotShield
{
    public:
    
        /** Create a new ParallaxRobotShield object on any mbed pin
        *
        * @param leftServoPin Left Servomotor Signal pin - default D10
        * @param rightServoPin Right Servomotor Signal pin - default D11
        * @param leftWhiskerPin Left Whisker digital pin connection
        * @param rightWhiskerPin Right Whisker digital pin connection
        * @param leftServoCenter Center pulsewidth for the Left servomotor - default 1500 (us)
        * @param rightServoCenter Center pulsewidth for the Right servomotor - default 1500 (us)
        * @param leftServoClockwiseOffset Range of clockwise pulsewidth for the Left servomotor - default 2.0 (eg: if speed is 100, range is 100 * 2 = ±200 us)
        * @param rightServoClockwiseOffset Range of clockwise pulsewidth for the Right servomotor - default 2.0
        * @param leftServoAntiClockwiseOffset Range of anticlockwise pulsewidth for the Left servomotor - default 2.0
        * @param rightServoAntiClockwiseOffset Range of anticlockwise pulsewidth for the Right servomotor - default 2.0
        */
        ParallaxRobotShield(PinName leftServoPin = D10, PinName rightServoPin = D11, PinName leftWhiskerPin = NC, PinName rightWhiskerPin = NC, int leftServoCenter = 1500, int rightServoCenter = 1500,
                            double leftServoClockwiseOffset = 2.0, double rightServoClockwiseOffset = 2.0, double leftServoAntiClockwiseOffset = 2.0, double rightServoAntiClockwiseOffset = 2.0);
        

        /** Switch on the left servo at the given speed. Can be used with loops to run the left servomotor.
         *  @param speed The speed, from 0 to 100 at which to spin the servomotor. - 100 by default
         */
        void left_servo(int speed = 100);       // Just for internal functions
        
        
        /** Switch on the right servo at the given speed. Can be used with loops to run the right servomotor.
         *  @param speed The speed, from 0 to 100 at which to spin the servomotor. - 100 by default
         */
        void right_servo(int speed = 100);      // Just for internal functions
        
        
        /** Switch on both servomotors, forwards at the given speed.
         *  @param speed The speed, from 0 to 100 at which to spin the servomotors. - 100 by default
         */
        void forward(int speed = 100);

        
        /** Switch on both servomotors, backwards at the given speed.
         *  @param speed The speed, from 0 to 100 at which to spin the servomotors. - 100 by default
         */
        void backward(int speed = 100);
        
        
        /** Switch on both servomotors at the given speed, in opposite directions so as to turn left.
         *  @param speed The speed, from 0 to 100 at which to spin the servomotors. - 100 by default
         */
        void left(int speed = 100);
                
        
        /** Switch on both servomotors at the given speed, in opposite directions so as to turn right.
         *  @param speed The speed, from 0 to 100 at which to spin the servomotors. - 100 by default
         */
        void right(int speed = 100);
               
        
        /** Turns left by switching the right servo off and running the left servo.
         *  @param speed The speed, from 0 to 100 at which to spin the left servomotor. - 100 by default
         */
        void turn_left(int speed = 100);
               
        
        /** Turns right by switching the left servo off and running the right servo.
         *  @param speed The speed, from 0 to 100 at which to spin the right servomotor. - 100 by default
         */
        void turn_right(int speed = 100);
               

        /** Enable the left servomotor
         */
        void enable_left_motor();
        
        
        /** Enable the right servomotor
         */
        void enable_right_motor();
        
        
        /** Stop left servomotor.
         */
        void stopLeft();
        
        
        /** Stop right servomotor.
         */
        void stopRight();
        
        
        /** Stop both servomotors at the same time.
         */
        void stopAll();
        
        
        /** Returns an integer corresponding to the state of the left whisker.
         *  @return 1 if the Left whisker is in contact, 0 otherwise.
         */
        int leftWhiskerContact();
        
        
        /** Returns an integer corresponding to the state of the right whisker.
         *  @return 1 if the Right whisker is in contact, 0 otherwise.
         */
        int rightWhiskerContact();
        
        
        /** Returns an integer correspondingly if there is a black color is detected.
         *  Uses the QTR-1RC Light sensor
         *  @param lightSensor the QTR-1RC signal pin
         *  @return 1 if Black color is detected, 0 otherwise.
         */
        int lightSensor(PinName lightSensor);
        
        
        /** Returns an integer correspondingly if an object is detected within 10cm.
         *  Uses the Sharp GP2Y0D810Z0F Digital Distance Sensor - 10cm
         *  @param bumpSensor the pin the bump sensor is connected to.
         *  @return 1 if something is detected, 0 otherwise.
         */
        int bumpSensor(PinName bumpSensor);
        
        
        /** Returns the distance of the nearest object.
         *  Uses the HC-SR04 Distance Sensor.
         *  @param trigPin the pin to which the trig pin is connected
         *  @param echoPin the pin to which the echo pin is connected
         *  @return the distance in cm.
         */
        double distanceSensor(PinName trigPin, PinName echoPin);
        
        
        /** Optional implementation for future use
         *  Turns on the corresponding LED to indicate if the whisker came into contact.
         *  @param left_LED the pin to which the left LED is connected to
         *  @param right_LED the pin to which the right LED is connected to
         *
         *  void whiskersLED(PinName left_LED, PinName right_LED);
         */
        
        
    private:
    
        int leftCenter;
        int rightCenter;
        double leftClockwiseOffset;
        double rightClockwiseOffset;
        double leftAntiClockwiseOffset;
        double rightAntiClockwiseOffset;

        PwmOut leftServo;
        PwmOut rightServo;
        
        DigitalIn leftWhisker;      // for the left Whisker
        DigitalIn rightWhisker;     // for the right Whisker

};
