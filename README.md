sudo apt-get install ros-humble-std-srvs

rosdep install -i --from-path src --rosdistro $ROS_DISTRO -y

sudo apt update
sudo apt install ros-humble-tf2-ros ros-humble-tf2-geometry-msgs

ros2 param set /epoch/publisher_ b 30
