#!/usr/bin/env python
import rospy
from std_msgs.msg import String
#from Hubo_joint_state.msg 
from ros_hubo_ach.msg import LargeData#Hubo_joint_state
from datetime import datetime

def talker():
    pub=[]
    pub = rospy.Publisher('chatter', LargeData)
    rospy.init_node('talker4')
    msg= LargeData();
    while not rospy.is_shutdown():
        #str = "hello world %s" % rospy.get_time()
	#print str
        msg.fname2= 'Manas'
        msg.lname= str(datetime.time(datetime.now())) 
	rospy.loginfo(msg)
        pub.publish(msg)
        rospy.sleep(0.005)


if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
