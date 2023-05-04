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
//CSE CENTER HELPED

#include <rclcpp/rclcpp.hpp> 
#include <navigation/navigation.hpp>
//need to print
#include <std_msgs/msg/float32.hpp>
//need to print
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <iostream>
#include <sensor_msgs/msg/laser_scan.hpp>
//convert laser to cordinates
#include <sensor_msgs/msg/point_cloud.hpp>
 //include map info when starting ??

// void mapCallBack(const nav2_msgs::srv::GetCostmap  msg){
//         // RCLCPP_INFO("Size of Map: %d", msg->data.size());
//         // RCLCPP_INFO( "Resolution: %f", msg->info.resolution());
//         // RCLCPP_INFO( "Width: %d", msg->info.width());
//         // RCLCPP_INFO( "Height: %d", msg->info.height());
//         // uint counter = 0;

//         // //free spaces
//         // for (uint i = 0; i < msg->data.size(); i++) {
//         //     if (-1 != msg->data[i]) {
//         //         counter++;
//         //     }
//         // }
// }





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
  //FIRST WAIT ? 

  navigator.WaitUntilNav2Active();

  //MAKE SUBCRIPTION
  auto orig_map = navigator.GetGlobalCostmap();
  
  
  // //s3 start movement
  // navigator.WaitUntilNav2Active();
  // spin in place of 90 degrees (default parameter)
  navigator.Spin();
  while ( ! navigator.IsTaskComplete() ) {
    // busy waiting for task to be completed
  }
  geometry_msgs::msg::Pose::SharedPtr goal_pos = std::make_shared<geometry_msgs::msg::Pose>();
  goal_pos->position.x = 2;
  goal_pos->position.y = 1;
  goal_pos->orientation.w = 1;
  // move to new pose
  navigator.GoToPose(goal_pos);
  while ( ! navigator.IsTaskComplete() ) {
    
  }
  goal_pos->position.x = 2;
  goal_pos->position.y = -1;
  goal_pos->orientation.w = 1;
  navigator.GoToPose(goal_pos);
  // move to new pose
  while ( ! navigator.IsTaskComplete() ) {
    
  }
  // backup of 0.15 m (deafult distance)
  navigator.Backup();
  while ( ! navigator.IsTaskComplete() ) {
    
  }
  //updating the cost map with new explored map... 
  auto latest_map = navigator.GetGlobalCostmap();
  //s5 somehow subtract img (and s6)
  float x = 0; 
  float y = 0;
  float weights = 0;
  RCLCPP_INFO(navigator.get_logger(), "x: %d, y: %d, res: %f", orig_map->metadata.size_x,  orig_map->metadata.size_y,  orig_map->metadata.resolution);

  RCLCPP_INFO(navigator.get_logger(), "x: %d, y: %d, res: %f", latest_map->metadata.size_x,  latest_map->metadata.size_y,  latest_map->metadata.resolution);

  for (uint j = 0; j < latest_map->metadata.size_y; j++){
    for(uint i = 0; i < latest_map->metadata.size_x; i++){
      int index = i + j * latest_map->metadata.size_x;
      int pixel = latest_map->data[index] - orig_map->data[index]; // subtracteed 
      //give higher values to the differences in pixel (first map pixels - new map pixels) 
      //increase the difference more by squaring also making it postive
      pixel = pixel * pixel;
      x += pixel * i;
      y += pixel * j;
      weights += pixel;
      
      // if(pixel > 50){
      //   RCLCPP_INFO(navigator.get_logger(), "i: %d, j: %d, pixel: %d", i,j,pixel);
      // }
      //RCLCPP_INFO(navigator.get_logger(), "string", format....);
    }
  }
  RCLCPP_INFO(navigator.get_logger(),"x %f y: %f weights: %f" , x,y,weights);

  x = x / weights;
  y = y / weights;
  float h = latest_map->metadata.resolution * x + latest_map->metadata.origin.position.x;
  float k = latest_map->metadata.resolution * y + latest_map->metadata.origin.position.y;
  RCLCPP_INFO(navigator.get_logger(), "h: %f, k: %f x %f y: %f", h,k , x,y);

  
  rclcpp::shutdown(); // shutdown ROS
  return 0;
}
