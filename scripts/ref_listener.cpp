/*Created by Debasmit Das
This node should be running inside the Hubo
*/


/*Standard Stuff*/
#include <string>
#include <stdio.h> 
#include <iostream>

/* Required Hubo Headers */
#include <hubo.h>

/* Required for ROS */
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/String.h>
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

double posHNP,posLSP,posLSR,posLSY,posLEBP,posLWY,posLWP,posRSP,posRSR,posRSY,posREBP,posRWY,posRWP,posHPY,posLHY,posLHR,posLHP,posLKNP,posLAP,posLAR,posRHY,posRHR,posRHP;
double posRKNP,posRAP,posRAR;
int r;
ach_channel_t chan_hubo_ref; // Feed-Forward (Reference)
struct hubo_ref H_ref;
int i;


void callback(const sensor_msgs::JointState & msg) 
{ 


for(i=0;i<msg.name.size();i++)
{

if(msg.name[i]=="LSP"){
H_ref.ref[LSP] = msg.position[i];}
else if(msg.name[i]=="LSR"){
H_ref.ref[LSR] = msg.position[i];}
else if(msg.name[i]=="LSY"){
H_ref.ref[LSY] = msg.position[i];}
else if(msg.name[i]=="LEB"){
H_ref.ref[LEB] = msg.position[i];}
else if(msg.name[i]=="LWY"){
H_ref.ref[LWY] = msg.position[i];}
else if(msg.name[i]=="LWP"){
H_ref.ref[LWP] = msg.position[i];}
else if(msg.name[i]=="RSP"){
H_ref.ref[RSP] = msg.position[i];}
else if(msg.name[i]=="RSR"){
H_ref.ref[RSR] = msg.position[i];}
else if(msg.name[i]=="RSY"){
H_ref.ref[RSY] = msg.position[i];}
else if(msg.name[i]=="REB"){
H_ref.ref[REB] = msg.position[i];}
else if(msg.name[i]=="RWY"){
H_ref.ref[RWY] = msg.position[i];}
else if(msg.name[i]=="RWP"){
H_ref.ref[RWP] = msg.position[i];}
else if(msg.name[i]=="LHY"){
H_ref.ref[LHY] = msg.position[i];}
else if(msg.name[i]=="LHR"){
H_ref.ref[LHR] = msg.position[i];}
else if(msg.name[i]=="LHP"){
H_ref.ref[LHP] = msg.position[i];}
else if(msg.name[i]=="LKN"){
H_ref.ref[LKN] = msg.position[i];}
else if(msg.name[i]=="LAP"){
H_ref.ref[LAP] = msg.position[i];}
else if(msg.name[i]=="LAR"){
H_ref.ref[LAR] = msg.position[i];}
else if(msg.name[i]=="RHY"){
H_ref.ref[RHY] = msg.position[i];}
else if(msg.name[i]=="RHR"){
H_ref.ref[RHR] = msg.position[i];}
else if(msg.name[i]=="RHP"){
H_ref.ref[RHP] = msg.position[i];}
else if(msg.name[i]=="RKN"){
H_ref.ref[RKN] = msg.position[i];}
else if(msg.name[i]=="RAP"){
H_ref.ref[RAP] = msg.position[i];}
else {
H_ref.ref[RAR] = msg.position[i];}
}
ach_put( &chan_hubo_ref, &H_ref, sizeof(H_ref));
} 




int main(int argc, char** argv) {

    /* Open Ach - Reference Channels */
    r = ach_open(&chan_hubo_ref, HUBO_CHAN_REF_NAME , NULL);
    assert( ACH_OK == r );
    
    memset( &H_ref,   0, sizeof(H_ref));
    /* Create initial structures to read and write from */
    
    ros::init(argc, argv, "ref_listener");
    ros::NodeHandle n;


    //H_ref.ref[LEB] = -0.1;
	//ach_put( &chan_hubo_ref, &H_ref, sizeof(H_ref));

	
    ros::Subscriber sub = n.subscribe("joint_references", 10, callback);;
    ros::Rate loop_rate(30);
       
    

    
    
    ros::spin();
    return 0;
}
