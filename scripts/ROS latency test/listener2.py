#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from ros_hubo_ach.msg import Hubo_joint_state
from datetime import datetime

def callback(data):
    rospy.loginfo(rospy.get_name() + ": I heard %s" % data.lname + 'at ' + str(datetime.time(datetime.now())))


def listener():
    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber("chatter", Hubo_joint_state, callback)
    rospy.spin()


if __name__ == '__main__':
    listener()
