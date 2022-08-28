#include <ros/ros.h>
#include <turtlesim/Spawn.h>
#include <turtlesim/Kill.h>
#include <geometry_msgs/Twist.h> 
#define PI 3.1415926897932384626

#include <string>
#include <iostream>
using namespace std;

int main(int argc,char** argv)
{
    string names[] = {"s","u","d","o","l","a","b"};
    ros::init(argc, argv, "sudolab");
    std::string topic = "/xs/cmd_vel";
    ros::NodeHandle n;
    ros::Publisher cmdVelPub = n.advertise<geometry_msgs::Twist>(topic, 10);  
    ros::service::waitForService("spawn");//等待/spawn服务启动
    ros::ServiceClient client_kill = n.serviceClient<turtlesim::Kill>("kill");//定义一个/kill服务的客户端
    turtlesim::Kill kill_name;
    kill_name.request.name="turtle1";
    client_kill.call(kill_name);//调用/kill服务乌龟
    ros::ServiceClient client = n.serviceClient<turtlesim::Spawn>("spawn");//定义一个/spawn服务的客户端
    turtlesim::Spawn turtle;
    
    for(int i = 0; i < 7;i++)
    {
        turtle.request.name="x"+names[i];
        turtle.request.x = i+1;
        turtle.request.y = 5;
        turtle.request.theta = 0;
        client.call(turtle);//生成乌龟
    }
    ros::Rate loopRate(1);  
    ROS_INFO("sudolab start...");
    geometry_msgs::Twist speed;  
  int count = 0;
  while (ros::ok()){
    speed.linear.x = 0.2;  // 线速度 0.3m/s, 
    speed.angular.z = 0;  //角速度0.
    count++;
    if(count == 3 || count == 6)
    {
        speed.angular.z = PI/2;
    }
    if(count == 8 || count == 11)  //右拐圆角
    {  
      speed.angular.z = -PI/2;
    }
     if(count == 13)
      ros::shutdown();
   
    cmdVelPub.publish(speed); 
    //ros::spinOnce();
    loopRate.sleep();


  }
}
