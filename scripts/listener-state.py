#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from ros_hubo_ach.msg import *
import hubo_ach as hubo
import ach
import sys
import time

refChan = ach.Channel(hubo.HUBO_CHAN_REF_NAME)

def callback(data):
    rospy.loginfo(rospy.get_name() + ": I heard " +str(data))
    refAchStruct = hubo.HUBO_REF()
    for i in range(0,hubo.HUBO_JOINT_COUNT):
    	refAchStruct.ref[i]=data.ref[i]
    	refAchStruct.mode[i]=int(data.mode[i])
    	refAchStruct.comply[i]= int(data.comply[i])
    refChan.put(refAchStruct)


def listenerRef():
    rospy.init_node('listenerRef', anonymous=True)
    rospy.Subscriber("ref", Hubo_ref, callback)
    refChan.flush()
    rospy.spin()


if __name__ == '__main__':
    listenerRef()
