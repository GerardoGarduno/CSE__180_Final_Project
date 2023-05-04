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
#include <iostream>

bool has_orig_map = false;

int main(int argc,char **argv) {
 
  rclcpp::init(argc,argv); // initialize ROS 

  Navigator navigator(true,false); // create node with debug info but not verbose

  // first: it is mandatory to initialize the pose of the robot
  geometry_msgs::msg::Pose::SharedPtr init = std::make_shared<geometry_msgs::msg::Pose>();
  init->position.x = -2;
  init->position.y = -0.5;
  init->orientation.w = 1;
  navigator.SetInitialPose(init);
  // wait for navigation stack to become operationale


//s1 wait

//s2 get global costmap and create a subscription
  auto orig_map = navigator.get_costmap();

//s3 start movement

  navigator.WaitUntilNav2Active();
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


  //s4

  auto latest_map = navigator.get_costmap();

  // s5 somehow subtract img (and s6)
  float x = 0; 
  float y = 0;
  float weights = 0;
  for(int j){
    for(int i){
      int index = i + j*latest_map.metadata.size_x;
      int pixel = latest_map.data[index] - orig_map.data[index]; // subtracteed
      // subtract
      // also x += pixel (subtracted) * x (weighted sum)
      // also y += pixel (subtracted) * y (weighted sum)
      // weights += pixel (subtraced)

    }
  }
  x = x / weights;
  y = y / weights;

  //s7
  float h = latest_map.metadata.resolution * x + latest_map.metadata.origin.x
  float k = latest_map.metadata.resolution * y + latest_map.metadata.origin.y

  print(h,k)



  // complete here....
  
  rclcpp::shutdown(); // shutdown ROS
  return 0;
}