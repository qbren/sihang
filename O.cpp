#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#define PI 3.14159265358979323846

int main(int argc, char **argv)
{
	ros::init(argc, argv, "velocity_publisher");

	ros::NodeHandle n;

	ros::Publisher turtle_vel_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

	ros::Rate loop_rate(10);

	int count = 0;
	while (ros::ok())
	{
		geometry_msgs::Twist vel_msg;
		vel_msg.linear.x = 2;
		vel_msg.angular.z = 0.5;
		count ++;
		while(count==3){
			count=0;
			vel_msg.angular.z = 2*PI;
		}

		turtle_vel_pub.publish(vel_msg);
		ROS_INFO("Publsh turtle velocity command[%0.2f m/s, %0.2f rad/s]", 
				vel_msg.linear.x, vel_msg.angular.z);

	    loop_rate.sleep();
	}

	return 0;
}