#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from ros_hubo_ach.msg import *
import hubo_ach as hubo
import ach
import sys
import time

stateChan = ach.Channel(hubo.HUBO_CHAN_STATE_NAME)
stateStruct=Hubo_state();


def callback(data):
    rospy.loginfo(rospy.get_name() + ": I heard " +str(data))
    stateAchStruct = data
    

def listenerRef():
    rospy.init_node('listenerState', anonymous=True)
    rospy.Subscriber("state", Hubo_state, callback)
    stateChan.flush()
    rospy.spin()


if __name__ == '__main__':
    listenerRef()
