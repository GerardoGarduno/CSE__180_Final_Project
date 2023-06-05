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
