#!/usr/bin/env python3
import rospy
from std_msgs.msg import String

def calculator():
    pub = rospy.Publisher('calc_result', String, queue_size=10)
    rospy.init_node('calculator_pub', anonymous=True)
    rate = rospy.Rate(1)

    print("Welcome to the Simple ROS Calculator!")
    print("Select operation:")
    print("1. Addition (+)")
    print("2. Subtraction (-)")
    print("3. Multiplication (*)")
    print("4. Division (/)")
    print("5. Percentage (%)")

    while not rospy.is_shutdown():
        choice = input("Enter choice (1/2/3/4/5): ")
        num1 = float(input("Enter first number: "))
        num2 = float(input("Enter second number: "))

        if choice == '1':
            result = num1 + num2
            operation = "Addition"
        elif choice == '2':
            result = num1 - num2
            operation = "Subtraction"
        elif choice == '3':
            result = num1 * num2
            operation = "Multiplication"
        elif choice == '4':
            if num2 != 0:
                result = num1 / num2
                operation = "Division"
            else:
                result = "Error: Division by zero"
                operation = "Division"
        elif choice == '5':
            result = (num1 / num2) * 100
            operation = "Percentage"
        else:
            print("Invalid input. Try again!")
            continue

        msg = f"{operation} result of {num1} and {num2} is: {result}"
        rospy.loginfo(msg)
        pub.publish(msg)
        rate.sleep()

if __name__ == '__main__':
    try:
        calculator()
    except rospy.ROSInterruptException:
        pass

