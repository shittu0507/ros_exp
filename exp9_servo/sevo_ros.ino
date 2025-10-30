#include <Servo.h>
#include <ros.h>
#include <std_msgs/Int16.h>

Servo myservo;
ros::NodeHandle nh;

void servo_cb(const std_msgs::Int16 &cmd_msg)
{
  int angle = cmd_msg.data;
  if (angle < 0) angle = 0;
  if (angle > 180) angle = 180;
  myservo.write(angle);
}

ros::Subscriber<std_msgs::Int16> sub("servo", servo_cb);

void setup()
{
  myservo.attach(9);   // Servo signal pin
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  delay(10);  // Small delay for stability
}

