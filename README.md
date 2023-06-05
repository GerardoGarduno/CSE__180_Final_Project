## Project Name: robotpatrol


## Description
This project involves running the `testnavigator.cpp` file alongside Gazebo to explore an environment and identify the location of an unknown pillar.

## Getting Started
- Windows: WSL (Windows Subsystem for Linux), VBox, Native
- Mac: VBox (recommended)
- Linux: Ubuntu 20.4

## Prerequisites
- MRTP folder
- ROS2
- Gazebo
- Colcon
- Robot patrol folder

## Installation
1. Ensure that you have the latest version of MRTP from Stefano Carpin's Github: [https://github.com/stefanocarpin/MRTP/](https://github.com/stefanocarpin/MRTP/)
2. Install ROS2 and Gazebo packages by following the instructions provided in the MRTP repository: [https://github.com/stefanocarpin/MRTP/wiki/Installation-Intructions](https://github.com/stefanocarpin/MRTP/wiki/Installation-Intructions)
3. Install COLCON by referring to the official documentation: [https://colcon.readthedocs.io/en/released/user/installation.html](https://colcon.readthedocs.io/en/released/user/installation.html)
4. Once the packages are installed, open a new terminal and navigate to the directory where the MRTP folder is located (e.g., `cd /Desktop/MRTP/MRTP`). It is recommended to source the MRTP folder inside your home directory.
5. Inside the MRTP/MRTP folder, run the command `colcon build`.
6. Source the folder by running the command: `source install/local_setup.bash` or `. install/local_setup.bash`.
7. The `colcon` command will build the necessary folders inside the MRTP folder.
8. Run the environment (still inside the MRTP folder):
   - export TURTLEBOT3_MODEL=waffle
   - export GAZEBO_MODEL_PATH=$GAZEBO_MODEL_PATH:~/MRTP/MRTP/src/gazeboenvs/models
   - . install/local_setup.bash
   - ros2 launch gazeboenvs tb3_simulation.launch.py
9. This will launch Gazebo, and you should see an environment with 10 pillars and a gazebo robot.
10. The next step is to run the navigation node. Follow these steps:
   - Clone the repository: `git clone https://github.com/GerardoGarduno/CSE_Final_Project`
   - Build the project (inside the `/src` directory): `colcon build`
   - Source the project: `. install/local_setup.bash`
   - Run the `testnavigator.cpp` file: `ros2 run robotpatrol testnavigator.cpp`
11. You should now have two terminals: one running Gazebo and another running the testnavigation node. Wait until the Gazebo robot finishes its path to obtain the estimated position of the unknown pillar.

**Note**: Sometimes the Gazebo application may crash, in which case it is recommended to rerun step 9 to start with a fresh Gazebo instance for testing the application.

## Authors:
- Alan Barajas
- Gerardo Garduno
- Angel Monroy
- Professor Carpin

## CSE 180 Project One Page Report

Our implementation of the project works not with lasers and point clouds, but by comparing an original map (before moving) to another map (after the robot has finished moving) and then finding discrepancies or anomalies between them. That anomaly returned is (roughly) the location of the 10th column.

We first started with the `testnavigator.cpp` provided to us by the professor. We then modified it moderately by first getting the global cost map and assigning it to a variable prior to giving the robot the commands to start moving. This assigns the current map without the 10th cylinder to that variable. As the robot moved, we modified the rate at which it executes to 10 Hz, have the rate sleep inside the while loop, have the condition include less than 300 of that variable that gets incremented by 1 each iteration so the robot gets stuck for less time, and spin it so it can adjust itself and decrease the chances of the robot getting stuck.

Then, once the robot finished the path we assigned it, the program stores the most recent global cost map and assigns it to a separate variable. Now the goal is to subtract the two cost maps which should reveal the location of the 10th cylinder. If visualized, it would look like a singular blob on the map.

To do this, we assign variables to store our data for x, y, and weight that we calculate inside a nested for loop. The nested for loop goes through all of the rows and columns. The weight is necessary to compute the weighted average. The pixel values are only added to the weight if it is greater than 50, to reduce noise as values are typically closer to 0 and closer to 100.

Then, outside the loops, we assign the x and y as equal to themselves divided by the same variable for that weight. We then initialize two new variables h and k which multiply the x and y values respectively with the resolution and add the origin position as it is not (0, 0) but rather (-10, -10).

We then print h and k which provides an approximation of the location of the 10th cylinder. This is a singular approximation of the cylinder’s location. Increasing or decreasing the threshold in the nested for loop seems to have the most influence on the accuracy of the 10th cylinder’s location as it determines how much noise is in the resulting cost map.

