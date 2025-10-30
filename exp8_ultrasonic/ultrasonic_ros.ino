#include <ros.h>
#include <std_msgs/Float32.h>

ros::NodeHandle nh;
std_msgs::Float32 distance_msg;
ros::Publisher pub_distance("ultrasonic_distance", &distance_msg);

// Define pins for HC-SR04
const int trigPin = 9;
const int echoPin = 10;

void setup() {
  nh.initNode();
  nh.advertise(pub_distance);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Send a 10 microsecond pulse to trigger the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance (in cm)
  float distance = duration * 0.0343 / 2;

  // Publish distance to ROS topic
  distance_msg.data = distance;
  pub_distance.publish(&distance_msg);

  nh.spinOnce();
  delay(1000);   // 1 second delay between readings
}

