# -------- External LED Blink for 3 Seconds Continuously (Arduino + ROS Noetic) --------

# Step 1: Source ROS environment
source /opt/ros/noetic/setup.bash

# Step 2: Install rosserial packages (if not already installed)
sudo apt install ros-noetic-rosserial ros-noetic-rosserial-arduino

# Step 3: Go to Arduino libraries folder
cd ~/Arduino/libraries

# Step 4: Clone rosserial library
git clone https://github.com/ros-drivers/rosserial.git

# Step 5: Generate ROS library for Arduino
cd ~/Arduino/libraries/rosserial/rosserial_arduino
make_libraries.py ~/Arduino/libraries


# Step 6: Hardware Connections
# - LED anode (+) → Arduino digital pin 8
# - LED cathode (–) → 220Ω resistor → GND
# If no 220Ω available, use 330Ω or 1kΩ (LED will be dimmer but safe)

# Step 7: Open Arduino IDE and upload the below code as external_led_ros.ino
# -------------------------------------------------------------------------

#include <ros.h>
#include <std_msgs/Bool.h>

ros::NodeHandle nh;

int ledPin = 8;
bool ledState = false;
unsigned long previousMillis = 0;
const long interval = 3000;  // 3 seconds ON/OFF

void ledCallback(const std_msgs::Bool& msg) {
  ledState = msg.data;  // true = start blinking, false = stop
}

ros::Subscriber<std_msgs::Bool> sub("led_topic", ledCallback);

void setup() {
  pinMode(ledPin, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();

  if (ledState) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(ledPin, !digitalRead(ledPin));  // Toggle LED every 3s
    }
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(10);
}

# -------------------------------------------------------------------------

# Step 8: Run these terminals

# Terminal 1:
roscore

# Terminal 2:
rosrun rosserial_python serial_node.py /dev/ttyACM0
# (Check port using: ls /dev/tty*)

# Terminal 3:
# To start continuous blink:
rostopic pub /led_topic std_msgs/Bool "data: true"

# To stop blinking:
rostopic pub /led_topic std_msgs/Bool "data: false"

# -------------------------------------------------------------------------
# Expected Output:
# - When "data: true" is published → LED blinks ON for 3s → OFF for 3s repeatedly.
# - When "data: false" is published → LED stops blinking and remains OFF. 



----If Arduino/libraries shows ‘No such file or directory’----
Run:
mkdir -p ~/Arduino/libraries
cd ~/Arduino/libraries

Then continue with:
git clone https://github.com/ros-drivers/rosserial.git
cd rosserial/rosserial_arduino
python make_libraries.py ~/Arduino/libraries

