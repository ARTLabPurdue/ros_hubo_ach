#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from ros_hubo_ach.msg import *
import hubo_ach as hubo
import ach
import sys
import time


def talkerRef():
    pub=[]
    pub = rospy.Publisher('ref', Hubo_ref)
    rospy.init_node('talkerRef')
    refStruct=Hubo_ref();
    refStruct.ref = [];
    refStruct.mode = [];
    refStruct.comply = [];
    for i in xrange(0,hubo.HUBO_JOINT_COUNT):
    	refStruct.ref.append(0);
    	refStruct.mode.append(0);
    	refStruct.comply.append(0);
    i=0.0
    increase=1;
    while not rospy.is_shutdown():
	if (increase==1):
        	i=i+1.0
	else:
		i=i-1.0
        refStruct.ref[hubo.LEB]=-i/50
	rospy.loginfo(refStruct)
        pub.publish(refStruct)
        rospy.sleep(1)
        if i>10:
		increase=0
	if i<0:
		increase=1


if __name__ == '__main__':
    try:
        talkerRef()
    except rospy.ROSInterruptException:
        pass
