#include <ros/ros.h>   
#include <geometry_msgs/Twist.h> 
#define PI 3.1415926897932384626
 
int main(int argc, char **argv){
  ros::init(argc, argv, "sudolab");  
  std::string topic = "/xu/cmd_vel";  
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
    if(count == 15 || count == 17 || count == 29 )//左拐圆角
      speed.angular.z = PI/2;
    if(count == 9 || count == 23)//往回走
    {  
      speed.linear.x = 0;
      speed.angular.z = PI; 
    }        
    if(count == 3 )//左拐直角
    {  
      speed.linear.x = 0;
      speed.angular.z = PI/2;
    }    
           
    if(count == 30)
      ros::shutdown();
   
    cmdVelPub.publish(speed); 
    //ros::spinOnce();
    loopRate.sleep();
  }
  return 0;
}
