#include "ros/ros.h"
#include "arktask1/board_pose.h"
#include "arktask1/limit_crossed.h"
#include <bits/stdc++.h>
void chatterCallback(const arktask1::borad_pose::ConstPtr& msg)
{
  ROS_INFO("I heard: [%d] [%d]", msg->x,msg->y);
}
bool add(arktask1::limit_crossed::Request &req,
          arktask1::limit_crossed::Response &res)
{
  std::stringstream ss;
  ss << "hello world ";
  res.out = ss.str();
  ROS_INFO("request: %d", (int)req.a);
  ROS_INFO("sending back response: [%s]", res.out.data());
  return true;
}
int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::ServiceServer service = n.advertiseService("limit_crossed",add);
  ros::Subscriber sub = n.subscribe("check_pose", 100, chatterCallback);
  ros::spin();
  return 0;
}
