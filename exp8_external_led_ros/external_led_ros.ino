#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle nh;
int ledPin = 8;

void ledCallback(const std_msgs::String& msg) {
  if (msg.data == "ON") digitalWrite(ledPin, HIGH);
  else if (msg.data == "OFF") digitalWrite(ledPin, LOW);
}

ros::Subscriber<std_msgs::String> sub("ext_led", &ledCallback);

void setup() {
  pinMode(ledPin, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
  delay(10);
}

