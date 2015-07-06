/*Standard Stuff*/
#include <string>
#include <stdio.h> 
#include <iostream>

/* Required Hubo Headers */
#include <hubo.h>

/* Required for ROS */
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>

/* For Ach IPC */
#include <errno.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <inttypes.h>
#include "ach.h"

using namespace std;
ach_channel_t chan_hubo_state; // Feed-back (State)



int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
    ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
    tf::TransformBroadcaster broadcaster;
    ros::Rate loop_rate(30);

    /* Open Ach Channel */

    int r = ach_open(&chan_hubo_state, HUBO_CHAN_STATE_NAME , NULL);
    assert( ACH_OK == r );

    const double degree = M_PI/180;

    /* Create initial structures to read and write from */
    //struct hubo_ref H_ref;
    struct hubo_state H_state;
    //memset( &H_ref,   0, sizeof(H_ref));
    memset( &H_state, 0, sizeof(H_state));

    /* for size check */
    size_t fs;

    /* Get the current feed-forward (state) */
    r = ach_get( &chan_hubo_state, &H_state, sizeof(H_state), &fs, NULL, ACH_O_LAST );
    if(ACH_OK != r) 
    {
        assert( sizeof(H_state) == fs );
    }


    //double posLEB = H_state.joint[LEB].pos;
    //cout<<posLEB<<endl;
    
    double angle=0;

    /* robot joints set manually
    double HNP=0, LSP=0, LSR=0, LSY=0, LEP=0, LWY=0, LWP=0, RSP=0, RSR=0, RSY=0, REP=0, RWY=0;    
    double RWP=0, HPY=0, LHY=0;       
    double LHR=0,LHP=0, LKP=0, LAP=0, LAR=0, RHY=0, RHR=0, RHP=0, RKP=0, RAP=0, RAR=0, angle=0;
    */

    // message declarations
    geometry_msgs::TransformStamped odom_trans;
    sensor_msgs::JointState joint_state;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "axis";

    while (ros::ok()) {

        /* Get the current feed-forward (state) */
        r = ach_get( &chan_hubo_state, &H_state, sizeof(H_state), &fs, NULL, ACH_O_LAST );
        if(ACH_OK != r) 
          {
           assert( sizeof(H_state) == fs );
          }


        //update joint_state
        joint_state.header.stamp = ros::Time::now();
        joint_state.name.resize(26);
        joint_state.position.resize(26);
        joint_state.name[0] ="HNP";
        joint_state.position[0] = 0;
        joint_state.name[1] ="LSP";
        joint_state.position[1] = H_state.joint[LSP].pos;
        joint_state.name[2] ="LSR";
        joint_state.position[2] = H_state.joint[LSR].pos;
        joint_state.name[3] ="LSY";
        joint_state.position[3] = H_state.joint[LSY].pos;
        joint_state.name[4] ="LEP";
        joint_state.position[4] = H_state.joint[LEB].pos;
        joint_state.name[5] ="LWY";
        joint_state.position[5] = H_state.joint[LWY].pos;
        joint_state.name[6] ="LWP";
        joint_state.position[6] = H_state.joint[LWP].pos;
        joint_state.name[7] ="RSP";
        joint_state.position[7] = H_state.joint[RSP].pos;
        joint_state.name[8] ="RSR";
        joint_state.position[8] = H_state.joint[RSR].pos;
        joint_state.name[9] ="RSY";
        joint_state.position[9] = H_state.joint[RSY].pos;
        joint_state.name[10] ="REP";
        joint_state.position[10] = H_state.joint[REB].pos;
        joint_state.name[11] ="RWY";
        joint_state.position[11] = H_state.joint[RWY].pos;
        joint_state.name[12] ="RWP";
        joint_state.position[12] = H_state.joint[RWP].pos;
        joint_state.name[13] ="HPY";
        joint_state.position[13] = 0;
        joint_state.name[14] ="LHY";
        joint_state.position[14] = H_state.joint[LHY].pos;
        joint_state.name[15] ="LHR";
        joint_state.position[15] = H_state.joint[LHR].pos;
        joint_state.name[16] ="LHP";
        joint_state.position[16] = H_state.joint[LHP].pos;
        joint_state.name[17] ="LKP";
        joint_state.position[17] = H_state.joint[LKN].pos;
        joint_state.name[18] ="LAP";
        joint_state.position[18] = H_state.joint[LAP].pos;
        joint_state.name[19] ="LAR";
        joint_state.position[19] = H_state.joint[LAR].pos;
        joint_state.name[20] ="RHY";
        joint_state.position[20] = H_state.joint[RHY].pos;
        joint_state.name[21] ="RHR";
        joint_state.position[21] = H_state.joint[RHR].pos;
        joint_state.name[22] ="RHP";
        joint_state.position[22] = H_state.joint[RHP].pos;
        joint_state.name[23] ="RKP";
        joint_state.position[23] = H_state.joint[RKN].pos;
        joint_state.name[24] ="RAP";
        joint_state.position[24] = H_state.joint[RAP].pos;
        joint_state.name[25] ="RAR";
        joint_state.position[25] = H_state.joint[RAR].pos;
       

        // update transform
        // (moving in a circle with radius=2)
        odom_trans.header.stamp = ros::Time::now();
        odom_trans.transform.translation.x = cos(angle)*2;
        odom_trans.transform.translation.y = sin(angle)*2;
        odom_trans.transform.translation.z = .7;
        odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(angle+M_PI/2);

        //send the joint state and transform
        joint_pub.publish(joint_state);
        broadcaster.sendTransform(odom_trans);

        // Create new robot state
        //tilt += tinc;
        //if (tilt<-.5 || tilt>0) tinc *= -1;
        //height += hinc;
        //if (height>.2 || height<0) hinc *= -1;
        //swivel += degree;
        //angle += degree/4;

        // This will adjust as needed per iteration
        loop_rate.sleep();
    }


    return 0;
}
