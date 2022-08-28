#include <ros/ros.h>   
#include <geometry_msgs/Twist.h> 
#define PI 3.1415926897932384626
 
int main(int argc, char **argv){
  ros::init(argc, argv, "sudolab");  
  std::string topic = "/xa/cmd_vel"; 
  ros::NodeHandle n; 
  ros::Publisher cmdVelPub = n.advertise<geometry_msgs::Twist>(topic, 10);  
  ros::Rate loopRate(1);  
  ROS_INFO("sudolab start...");
  geometry_msgs::Twist speed;  
  int count = 0;
  while (ros::ok()){
    speed.linear.x = 0.2; 
    speed.angular.z = 0;  
    count++;
    if(count == 3 || count == 6 || count == 8 || count == 11  )//左拐圆角
      speed.angular.z = PI/2;
    if(count == 13 )
      speed.angular.z = -PI/2;
    if(count == 15)
      ros::shutdown();
   
    cmdVelPub.publish(speed); 
    loopRate.sleep();
  }
  return 0;
}
