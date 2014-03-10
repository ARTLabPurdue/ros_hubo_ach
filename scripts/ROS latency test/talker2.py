#!/usr/bin/env python
import rospy
from std_msgs.msg import String
#from Hubo_joint_state.msg 
from ros_hubo_ach.msg import Hubo_joint_state
from datetime import datetime

def talker():
    pub=[]
    pub = rospy.Publisher('chatter', Hubo_joint_state)
    rospy.init_node('talker2')
    msg= Hubo_joint_state('Manas', 'Paldhe');
    while not rospy.is_shutdown():
        #str = "hello world %s" % rospy.get_time()
	#print str
        msg= Hubo_joint_state('Manas', str(datetime.time(datetime.now()))) 
	rospy.loginfo(msg)
        pub.publish(msg)
        rospy.sleep(1.0)


if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
