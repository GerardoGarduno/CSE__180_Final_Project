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
//CSE CENTER 

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
//   (-2, -0.5)
// (-2, 0.5)
// (-1, 1.5)
// (-0.5, 0.5)
// (-0.5, 0)
// (-0.5, -1)
// (0, -1.5)
// (0.5, -1)
// (0.5, 0)
// (0.5, 1.5)
// (2, 1.5)
// (2, -1)
  rclcpp::Rate rate(10);
  // goal_pos->position.x = -1.5;
  // goal_pos->position.y = 0.5;
  // goal_pos->orientation.w = 1;
  // // move to new pose
  // navigator.GoToPose(goal_pos);
  // //cancel if the tick hits 100 -> go to next pose
  int tick = 0;
  // while ( ! navigator.IsTaskComplete() && tick < 100) {
  //   tick++;
  //   rate.sleep();
  // }

  // goal_pos->position.x = -1;
  // goal_pos->position.y = 1.5;
  // goal_pos->orientation.w = 1;
  goal_pos->position.x = 2;
  goal_pos->position.y = 1;
  goal_pos->orientation.w = 1;
  // move to new pose
  navigator.GoToPose(goal_pos);
  tick = 0;
  while ( ! navigator.IsTaskComplete() && tick < 300) {
    tick++;
    rate.sleep();
  }
  navigator.Spin();
  while ( ! navigator.IsTaskComplete() ) {
    // busy waiting for task to be completed
  }
  
  // goal_pos->position.x = 0;
  // goal_pos->position.y = -1.5;
  // goal_pos->orientation.w = 1;
  goal_pos->position.x = 2;
  goal_pos->position.y = -1;
  goal_pos->orientation.w = 1;
  // move to new pose
  navigator.GoToPose(goal_pos);
  tick = 0;
  while ( ! navigator.IsTaskComplete() && tick < 300) {
    tick++;
    rate.sleep();
  }
  navigator.Spin();
  while ( ! navigator.IsTaskComplete() ) {
    // busy waiting for task to be completed
  }
  // goal_pos->position.x = 0.5;
  // goal_pos->position.y = -1;
  // goal_pos->orientation.w = 1;
  // // move to new pose
  // navigator.GoToPose(goal_pos);
  // tick = 0;
  // while ( ! navigator.IsTaskComplete() && tick < 100) {
  //   tick++;
  //   rate.sleep();
  // } 
  // goal_pos->position.x = 0.5;
  // goal_pos->position.y = 0;
  // goal_pos->orientation.w = 1;
  // // move to new pose
  // navigator.GoToPose(goal_pos);
  // tick = 0;
  // while ( ! navigator.IsTaskComplete() && tick < 100) {
  //   tick++;
  //   rate.sleep();
  // }
  
  // goal_pos->position.x = 0.5;
  // goal_pos->position.y = 1.5;
  // goal_pos->orientation.w = 1;
  goal_pos->position.x = -2;
  goal_pos->position.y = -0.5;
  goal_pos->orientation.w = 1;
  // move to new pose
  navigator.GoToPose(goal_pos);
  tick = 0;
  while ( ! navigator.IsTaskComplete() && tick < 300) {
    tick++;
    rate.sleep();
  }
  navigator.Spin();
  while ( ! navigator.IsTaskComplete() ) {
    // busy waiting for task to be completed
  }
  // goal_pos->position.x = 2;
  // goal_pos->position.y = 1.5;
  // goal_pos->orientation.w = 1;
  // // move to new pose
  // navigator.GoToPose(goal_pos);
  // tick = 0;
  // while ( ! navigator.IsTaskComplete() && tick < 100) {
  //   tick++;
  //   rate.sleep();
  // }
  // goal_pos->position.x = 2;
  // goal_pos->position.y = -1;
  // goal_pos->orientation.w = 1;
  // // move to new pose
  // navigator.GoToPose(goal_pos);
  // tick = 0;
  // while ( ! navigator.IsTaskComplete() && tick < 300) {
  //   tick++;
  //   rate.sleep();
  // }
  // navigator.Spin();
  // while ( ! navigator.IsTaskComplete() ) {
  //   // busy waiting for task to be completed
  // }
  // goal_pos->position.x = -2;
  // goal_pos->position.y = -0.5;
  // goal_pos->orientation.w = 1;
  // // move to new pose
  // navigator.GoToPose(goal_pos);
  // tick = 0;
  // while ( ! navigator.IsTaskComplete() && tick < 300) {
  //   tick++;
  //   rate.sleep();
  // }
  // navigator.Spin();
  // while ( ! navigator.IsTaskComplete() ) {
  //   // busy waiting for task to be completed
  // }
  // goal_pos->position.x = 2;
  // goal_pos->position.y = 1;
  // goal_pos->orientation.w = 1;
  // // move to new pose
  // navigator.GoToPose(goal_pos);
  // while ( ! navigator.IsTaskComplete() ) {
    
  // }
  // goal_pos->position.x = 2;
  // goal_pos->position.y = -1;
  // goal_pos->orientation.w = 1;
  // navigator.GoToPose(goal_pos);
  // // move to new pose
  // while ( ! navigator.IsTaskComplete() ) {
    
  // }
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
  float orig_weights=0;
  float final_wieght=0;
  RCLCPP_INFO(navigator.get_logger(), "x: %d, y: %d, res: %f", orig_map->metadata.size_x,  orig_map->metadata.size_y,  orig_map->metadata.resolution);

  RCLCPP_INFO(navigator.get_logger(), "x: %d, y: %d, res: %f", latest_map->metadata.size_x,  latest_map->metadata.size_y,  latest_map->metadata.resolution);
  //iterate through the map data and grab the pixels from old map and new map
  for (uint j = 0; j < latest_map->metadata.size_y; j++){
    for(uint i = 0; i < latest_map->metadata.size_x; i++){
      int index = i + j * latest_map->metadata.size_x;
      //subtract the differences -> compare ->visually laying each map on top of each other and seeing
      //the differences
      int pixel = latest_map->data[index] - orig_map->data[index]; // subtracteed 
      //debug stuff
      orig_weights +=  orig_map->data[index]; // subtracteed 
      final_wieght += latest_map->data[index] ; // subtracteed 


      //give higher values to the differences in pixel (first map pixels - new map pixels) 
      //increase the difference more by squaring also making it postive
      // pixel = abs(pixel)* abs(pixel)*abs(pixel)*abs(pixel);

      pixel = abs(pixel);
      //increasing the threshold decreases the accuracy
      if (abs(pixel) > 50){
        x += pixel * i;
        y += pixel * j;
        weights += pixel;
      }

      
      // if(pixel > 50){
      //   RCLCPP_INFO(navigator.get_logger(), "i: %d, j: %d, pixel: %d", i,j,pixel);
      // }
      //RCLCPP_INFO(navigator.get_logger(), "string", format....);
    }
  }
  RCLCPP_INFO(navigator.get_logger(),"x %f y: %f weights: %f Iweights: %f fweights: %f" , x,y,weights,orig_weights,final_wieght);
  //use the calculated wieght to convert to cordinates in the map
  x = x / weights;
  y = y / weights;
  //0.5 is the resultion of the map... "pixels in the image"
  //h = 0.5 * (calcuated(x/wieght).....
  float h = latest_map->metadata.resolution * x + latest_map->metadata.origin.position.x;
  float k = latest_map->metadata.resolution * y + latest_map->metadata.origin.position.y;
  RCLCPP_INFO(navigator.get_logger(), "h: %.2f, k: %.2f", h,k);

  
  rclcpp::shutdown(); // shutdown ROS
  return 0;
}
