/*
Copyright 2023 Stefano Carpin

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <rclcpp/rclcpp.hpp> 
#include <navigation/navigation.hpp>
//need to print
#include <std_msgs/msg/float32.hpp>
//need to print
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <iostream>
#include <sensor_msgs/msg/laser_scan.hpp>
 //include map info when starting ??
// void mapCallback(const nav_msgs::msg::OccupancyGrid::SharedPtr msg){
//         RCLCPP_INFO("Size of Map: %d", msg->data.size());
//         // RCLCPP_INFO( "Resolution: %f", msg->info.resolution());
//         // RCLCPP_INFO( "Width: %d", msg->info.width());
//         // RCLCPP_INFO( "Height: %d", msg->info.height());
//         uint counter = 0;
//         for (uint i = 0; i < msg->data.size(); i++) {
//             if (-1 != msg->data[i]) {
//                 counter++;
//             }
//         }
// }
// void mapCallBack(const nav_msgs::msg::OccupancyGrid::SharedPtr msg) {
//   // Get map info
//   int map_width = msg->info.width;
//   int map_height = msg->info.height;
//   float map_resolution = msg->info.resolution;

//   // Print map info to console
//   //RCLCPP_INFO(rclcpp::get_logger("mapCallback"), "Received map with width: %d, height: %d, and resolution: %f", map_width, map_height, map_resolution);
//   // std::cout<<msg->info.map_width<<std::endl;
//   //std::cout<< "map dimensions:" << "width: " << map_width << " hieght:" << map_height << "resolution" << map_resolution << std::endl;

// }
//ppose printer
void pathCallBack(const nav_msgs::msg::Path::SharedPtr msg) {
  for (const auto& pose : msg->poses) {
    std::cout <<"Currently Iam at: "<< "x: " << pose.pose.position.x << " y: " << pose.pose.position.y << std::endl;
  }
}

//laser printer
class FindClosest : public rclcpp::Node {
  public:
    FindClosest() : Node("pubsubstl") {
    pubf = this->create_publisher<std_msgs::msg::Float32>("closest", 1000);
    sub = this->create_subscription<sensor_msgs::msg::LaserScan>(
    "scan", 10, std::bind(&FindClosest::processScan, this, std::placeholders::_1));
  }

  private:
    void processScan(const sensor_msgs::msg::LaserScan::SharedPtr msg) {
      std::vector<float>::const_iterator minval = min(msg->ranges.begin(), msg->ranges.end());
      std_msgs::msg::Float32 msgToSend;
      msgToSend.data = *minval;
      pubf->publish(msgToSend); // publish result
      for (size_t i = 0; i < msg->ranges.size(); i++) {
        RCLCPP_INFO(rclcpp::get_logger("laser_scan"), "Values %d: %f", i, msg->ranges[i]);
      }
    }
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr pubf;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr sub;
};


int main(int argc,char **argv) {
  rclcpp::init(argc,argv); // initialize ROS 
  Navigator navigator(true,false); // create node with debug info but not verbose
  //RCLCPP_INFO(rclcpp::get_logger(navigator),"--------------TEST-------------");

  // first: it is mandatory to initialize the pose of the robot
  geometry_msgs::msg::Pose::SharedPtr init = std::make_shared<geometry_msgs::msg::Pose>();
  init->position.x = -2;
  init->position.y = -0.5;
  init->orientation.w = 1;
  navigator.SetInitialPose(init);
  
  // wait for navigation stack to become operationale
  navigator.WaitUntilNav2Active();
  
  // subscribe to map topic
  //auto map_sub = navigator.create_subscription<nav_msgs::msg::OccupancyGrid>("map", 10, mapCallBack);


  // subscribe to plan topic and set callback to pathCallBack
  auto path_sub = navigator.create_subscription<nav_msgs::msg::Path>("plan", 10, pathCallBack);
  
  

  // spin in place of 90 degrees (default parameter)
  navigator.Spin();
  while ( ! navigator.IsTaskComplete() ) {
    // busy waiting for task to be completed
  }
  // move to the poses in the arrays
  //double arrayx[] ={-2,-0.5,-0.5,-0.5,0.5,0.5,0.5,2,2};
  //double arrayy[] ={1,2,0,-2,-1.5,0,2,1,-1};
  //attempts
  double arrayx[] ={-2, -0.5,0.5,2,2,2,2,0.5,-0.5,-2};
  double arrayy[] ={0,0,0,0,0.5,1,2,2,2,2};
  int arraySize = sizeof(arrayy)/sizeof(double);
  for (int i = 0; i < arraySize; i++) {
    // set goal pose
    geometry_msgs::msg::Pose::SharedPtr goal_pos = std::make_shared<geometry_msgs::msg::Pose>();
    goal_pos->position.x = arrayx[i];
    goal_pos->position.y = arrayy[i];
    goal_pos->orientation.w = 1;

    // send goal pose to navigator and wait for task completion
    navigator.GoToPose(goal_pos);
    //call the laser
    while (!navigator.IsTaskComplete()) {
        rclcpp::spin(std::make_shared<FindClosest>());

      // busy waiting for task to be completed
    }
  }
  //prints path that it follows can be usful to find other path .....
  rclcpp::shutdown(); // shutdown ROS
  return 0;
}
