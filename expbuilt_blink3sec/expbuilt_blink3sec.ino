#include <ros.h>
#include <std_msgs/Bool.h>

ros::NodeHandle nh;
std_msgs::Bool led_state;
ros::Publisher led_pub("led_status", &led_state);

const int LED_PIN = 13;

void setup() {
  nh.initNode();
  nh.advertise(led_pub);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // LED ON for 3 seconds
  digitalWrite(LED_PIN, HIGH);
  led_state.data = true;
  led_pub.publish(&led_state);
  nh.spinOnce();
  delay(3000);

  // LED OFF for 3 seconds
  digitalWrite(LED_PIN, LOW);
  led_state.data = false;
  led_pub.publish(&led_state);
  nh.spinOnce();
  delay(3000);
}

