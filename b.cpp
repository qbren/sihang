#include <ros/ros.h>   
#include <geometry_msgs/Twist.h> 
#define PI 3.1415926897932384626
 
int main(int argc, char **argv){
  ros::init(argc, argv, "sudolab");  
  std::string topic = "/xb/cmd_vel";  
  ros::NodeHandle n; 
  ros::Publisher cmdVelPub = n.advertise<geometry_msgs::Twist>(topic, 10);  
  ros::Rate loopRate(1);  
  ROS_INFO("sudolab start...");
  geometry_msgs::Twist speed;  
  int count = 0;
  while (ros::ok()){
    speed.linear.x = 0.2;  // 线速度 0.3m/s, 
    speed.angular.z = 0;  //角速度0.
    count++;
    if(count == 3 || count == 5 )//左拐圆角
      speed.angular.z = PI/2;
    if(count == 11)//往回走
    {  
      speed.linear.x = 0;
      speed.angular.z = PI; 
     }
      if(count == 7)//右拐直角
    {  
      speed.linear.x = 0;
     speed.angular.z = -PI/2;
    }        
    if(count == 17)
      ros::shutdown();
   
    cmdVelPub.publish(speed); 
    //ros::spinOnce();
    loopRate.sleep();
  }
  return 0;
}
