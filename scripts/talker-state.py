#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from ros_hubo_ach.msg import *
import hubo_ach as hubo
import ach
import sys
import time

stateChan = ach.Channel(hubo.HUBO_CHAN_STATE_NAME)


def getJointName(joint_number):
     if (joint_number==0):
	return 'WST'
     if (joint_number==1):
	return 'NKY'
     if (joint_number==2):
	return 'NK1'
     if (joint_number==3):
	return 'NK2'
     if (joint_number==4):
	return 'LSP'
     if (joint_number==5):
	return 'LSR'
     if (joint_number==6):
	return 'LSY'
     if (joint_number==7):
	return 'LEB'
     if (joint_number==8):
	return 'LWY'
     if (joint_number==9):
	return 'LWR'
     if (joint_number==10):
	return 'LWP'
     if (joint_number==11):
	return 'RSP'
     if (joint_number==12):
	return 'RSR'
     if (joint_number==13):
	return 'RSY'
     if (joint_number==14):
	return 'REB'
     if (joint_number==15):
	return 'RWY'
     if (joint_number==16):
	return 'RWR'
     if (joint_number==17):
	return 'RWP'
     if (joint_number==18):
	return ''
     if (joint_number==19):
	return 'LHY'
     if (joint_number==20):
	return 'LHR'
     if (joint_number==21):
	return 'LHP'
     if (joint_number==22):
	return 'LKN'
     if (joint_number==23):
	return 'LAP'
     if (joint_number==24):
	return 'LAR'
     if (joint_number==25):
	return ''
     if (joint_number==26):
	return 'RHY'
     if (joint_number==27):
	return 'RHR'
     if (joint_number==28):
	return 'RHP'
     if (joint_number==29):
	return 'RKN'
     if (joint_number==30):
	return 'RAP'
     if (joint_number==31):
	return 'RAR'
     if (joint_number==32):
	return 'RF1'
     if (joint_number==33):
	return 'RF2'
     if (joint_number==34):
	return 'RF3'
     if (joint_number==35):
	return 'RF4'
     if (joint_number==36):
	return 'RF5'
     if (joint_number==37):
	return 'LF1'
     if (joint_number==38):
	return 'LF2'
     if (joint_number==39):
	return 'LF3'
     if (joint_number==40):
	return 'LF4'
     if (joint_number==41):
	return 'LF5'
     else:
	return 'Invalid Joint'


def talkerState():
    pub=[]
    pub = rospy.Publisher('state', Hubo_state)
    rospy.init_node('talkerState')
    stateStruct=Hubo_state();
    stateStruct.joint_state = [];
    stateStruct.ft_sensors = [];
    stateStruct.imu_sensors = [];
    #initialize state to zeros
    for i in range(0,hubo.HUBO_JOINT_COUNT):
    	stateStruct.joint_state.append(Hubo_joint_state(getJointName(i), 0, 0, 0, 0, 0, 0, 0)) 
    for i in range(0,hubo.HUBO_IMU_COUNT):
	stateStruct.imu_sensors.append(Hubo_imu(0,0,0,0,0,0))
    for i in range(0,3): #4 FT sensors
	stateStruct.ft_sensors.append(Hubo_ft(0,0,0))
  
    latestData = hubo.HUBO_STATE() #stores the latest sensor data

    while not rospy.is_shutdown():
	#Get the latest State from hubo-ach
	[statuss, framesizes] = stateChan.get(latestData, wait=False, last=False)
        for i in range(0,hubo.HUBO_JOINT_COUNT):
    		stateStruct.joint_state[i].name=getJointName(i)
    		stateStruct.joint_state[i].commanded= latestData.joint[i].ref 
    		stateStruct.joint_state[i].position=  latestData.joint[i].pos
    		stateStruct.joint_state[i].velocity=  latestData.joint[i].vel
    		stateStruct.joint_state[i].current=  latestData.joint[i].cur
    		stateStruct.joint_state[i].temperature=  latestData.joint[i].tmp
    		stateStruct.joint_state[i].active=  latestData.joint[i].active
    		stateStruct.joint_state[i].zeroed=  latestData.joint[i].zeroed

        for i in range(0,hubo.HUBO_IMU_COUNT):
		stateStruct.imu_sensors[i].x_acc=latestData.imu[i].a_x
		stateStruct.imu_sensors[i].y_acc=latestData.imu[i].a_y
		stateStruct.imu_sensors[i].z_acc=latestData.imu[i].a_z
		stateStruct.imu_sensors[i].x_rot=latestData.imu[i].w_x
		stateStruct.imu_sensors[i].y_rot=latestData.imu[i].w_y
		stateStruct.imu_sensors[i].z_rot=latestData.imu[i].w_z

        for i in range(0,3): #4 FT sensors
		stateStruct.ft_sensors[i].Mx=latestData.ft[i].m_x
		stateStruct.ft_sensors[i].My=latestData.ft[i].m_y
		stateStruct.ft_sensors[i].Fz=latestData.ft[i].f_z
 
	rospy.loginfo(stateStruct)
        pub.publish(stateStruct)
        rospy.sleep(0.005) #200Hz for Hubo2+


if __name__ == '__main__':
    try:
        talkerState()
    except rospy.ROSInterruptException:
        pass
