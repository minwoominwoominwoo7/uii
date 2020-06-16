#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
#include <ros.h>
#include <ros/time.h>
#include <std_msgs/UInt16.h>
#include <sensor_msgs/Range.h>
#include <SoftwareSerial.h>



PulseSensorPlayground pulseSensor; // Creates an instance of the PulseSensorPlayground object called "pulseSensor"
SoftwareSerial BTSerial(3,2);
void heart_cb( const std_msgs::UInt16& cmd_msg);

const int PulseWire = 1;
const int LED13 = 13;
int Threshold = 550;

int lof_pin = 10;
int rof_pin = 11;
int sound_pin = 9;
int led_pin = 8;
int beat_pulse = 0;
int threshold = 500;
std_msgs::UInt16 msg;

ros::NodeHandle nh;
sensor_msgs::Range range_msg;
ros::Publisher pub_range( "/ecg", &range_msg);
ros::Subscriber<std_msgs::UInt16> sub("/heartrate", heart_cb);

void heart_cb( const std_msgs::UInt16& cmd_msg)
{
msg = cmd_msg;
}

void setup() {

nh.initNode();
nh.advertise(pub_range);
// initialize the serial communication:
Serial.begin(9600);
BTSerial.begin(9600);
pinMode(lof_pin, INPUT); // Setup for leads off detection LO +
pinMode(rof_pin, INPUT); // Setup for leads off detection LO -
pinMode(sound_pin, OUTPUT);
pinMode(led_pin, OUTPUT);

pulseSensor.analogInput(PulseWire);
pulseSensor.blinkOnPulse(LED13); //auto-magically blink Arduino's LED with heartbeat.
pulseSensor.setThreshold(Threshold);

// Double-check the "pulseSensor" object was created and "began" seeing a signal.
if (pulseSensor.begin()) {
//Serial.println("We created a pulseSensor Object !"); //This prints one time at Arduino power-up, or on Arduino reset.
}
}


void loop() {

//read sensor value and publish
range_msg.range = analogRead(A0);
pub_range.publish( &range_msg );

if ((digitalRead(lof_pin) == 1) || (digitalRead(rof_pin) == 1)) {
//Serial.println('!');
}
else {
// send the value of analog input 0:
if (beat_pulse >= threshold) {
digitalWrite(sound_pin, HIGH);
digitalWrite(led_pin, HIGH);
}
else {
digitalWrite(sound_pin, LOW);
digitalWrite(led_pin, LOW);
}
}

if(msg.data == 0) {
BTSerial.println("위험:심장박동이 정지되었습니다");
}
nh.spinOnce();
}
