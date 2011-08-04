/*
 UNIVERSIDADE ESTADUAL DO PIAUÍ - UESPI
 Bac. em Ciências da Computação - CTU

 AJ Alves.

 aj.alves@live.com;
 aj.zerokol@gmail.com;

 zerokol.com
 */

/********************************************************************
 * INCLUDES
 ********************************************************************/
//C headers
#include <inttypes.h>
//Arduino headers
#include <WProgram.h> //Header to work with native proprietes from Arduino plataform "http://www.arduino.cc"
#include <Servo.h> //Header do work with Servo Engines "http://www.arduino.cc/en/Reference/Servo"

/********************************************************************
 * CONSTANTS
 ********************************************************************/
// helpers value
#define MILI 1000 //value for 1 second in milliseconds
#define STOPED 90 //Value in which the continuous Servo motors is stopped, its variation is between 0 to 180
#define PI 3.14159265 //Math PI value
#define RAD 0.017453292 //Math RADIANS value
//machine wheels reference
#define RIGHTWHEEL 1 //right wheel
#define LEFTWHEEL 2 //left wheel
//machine motion state
#define IDLE 0 //It sight the machine is stopped
#define FORWARD 1 //It sight the machine is moving to forward
#define BACKWARD 2 //It sight the machine is moving to backward

/********************************************************************
 * DECLARATIONS
 ********************************************************************/
class Continuous2Wheels {
public:
	int _speed; //Holds the actual machine' speed
	int _direction; //Holds the actual motion direction of machine
	double _resistence = 0; //Holds the resistance from middle into the wheels, in a ideal scenery it is zero
	bool _debug; //Holds the mode of log messages from this header
	long _serialPortBaud = 9600; //Holds the baud value for the serial port communication, by default 9600

	/*Both constructors needs: the Arduino's pin in which the right Servo is plugged in,
	 the Arduino's pin in which the left Servo is plugged in,
	 The Radius of machine's wheels,
	 The Bend Radius, Bend radius is the length value from one wheel to another, the machine shaft length

	 The first constructor to work in a ideal scenery, without resistance, the second needs to set a resistance value
	 */
	Continuous2Wheels(int rightWhreelPin, int leftWhreelPin,
			double wheellRadius, double bendRadius);
	Continuous2Wheels(int rightWhreelPin, int leftWhreelPin,
			double wheellRadius, double bendRadius, double resistence);

	/*
	 speed* must be higher or equal to 0 and lower or equal to 90
	 distance** is a value in centimeter
	 degree*** is a value positive or negative different of 0, the sigh determines the direction
	 degree**** is a value higher then 0

	 Ps:. Every time you use one of the motion methods the value of _speed and _direction are dynamically changed
	*/

	//Motion methods
	void stop(); //Method to stop the machine
	void forward(int speed); //Method to move the machine forward in a certain speed*
	void forward(int speed, double distance); //Method to move the machine forward in a certain speed* to a distance*
	void backward(int speed); //Method to move the machine backward in a certain speed*
	void backward(int speed, double distance); //Method to move the machine backward in a certain speed* to a distance*
	void bend(int degree); //Method to make a bend with the passed degree*** value, the degree sigh will determine the bend side
	void rigthBend(int degree); //Method to make a right bend with the passed degree**** value
	void leftBend(int degree); //Method to make a left bend with the passed degree**** value
	void spin(int degree); //Method to spin the machine in its own axis, the sign of param will determine the spin direction
	void spin(int degree, int speed); //Method to spin the machine in its own axis, the sign of param will determine the spin direction and in a certain speed*
	//Auxiliary methods
	bool getDebugMode(); //Method to get the Debug mode value
	void setDebugMode(bool mode); //Method to set the Debug Mode of this lib
	int getSpeed(); //Method to get the speed value
	int getDirection(); //Method to get direction value
	long getSerialPortBaud(); //Method to get the baud value of serial port communication
	void setSerialPortBaud(long baud); //Method to set the baud value of serial port communication

private:
	Servo _rightWheel; //Holds the Servo object which will work with the right wheel
	Servo _leftWheel; //Holds the Servo object which will work with the left wheel
	double _wheelRadius; //Holds the wheel radios value
	double _bendRadius; //Holds the bend radius value

	int getWheelSpeed(int speed, int wheel); //Private method used to calculate the speed value to a specific wheel
	double degreeToRadian(int degree); //Method to convert degrees to radians
	double getCircleDisplacement(double radians, double radius); //Method to calculate the circle "for wheels" displacement
	double getWalkDisplacement(double distance); //Method to calculate the machine distance displacement
	double circleLength(double radius); //Method to calculate the length  for an circle
	unsigned long getWaitValue(double desplacement, int speed); //Method to calculate among of time to wait until the displacement is walked
	int speedFormater(int speed); //Method to format the speed to a valid speed value
};
