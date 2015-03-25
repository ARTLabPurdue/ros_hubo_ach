# ros_hubo_ach

This project was developed to interface hubo-ach with ROS.
talker-state.py reads the current hubo-state and publishes it ROS Message.
listener-state.py reads the current state.

talker-ref.py publishes some desired hubo-ref commands
listener-ref.py listens to the ROS messages to move the hubo and sends them to the robot, thus moving it.
