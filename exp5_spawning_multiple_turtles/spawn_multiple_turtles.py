#!/usr/bin/env python3
import rospy
from turtlesim.srv import Spawn

def spawn_turtle(name, x, y):
    rospy.wait_for_service('spawn')
    try:
        spawner = rospy.ServiceProxy('spawn', Spawn)
        spawner(x, y, 0, name)
        rospy.loginfo(f"{name} spawned at ({x}, {y})")
    except rospy.ServiceException as e:
        rospy.logerr("Service call failed: %s" % e)

if __name__ == "__main__":
    rospy.init_node("spawn_multiple_turtles")

    # spawn turtles at different positions
    spawn_turtle("turtle2", 2, 2)
    spawn_turtle("turtle3", 5, 5)
    spawn_turtle("turtle4", 8, 8)

    rospy.loginfo("All turtles spawned successfully!")

