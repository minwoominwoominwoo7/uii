if false; then
#if true; then
else
  alias eb='nano ~/.bashrc'
  alias sb='source ~/.bashrc'
  alias gs='git status'
  alias gp='git pull'
  alias cw='cd ~/turtlebot3_ws'
  alias cs='cd ~/turtlebot3_ws/src'
  alias cm='cd ~/turtlebot3_ws && colcon build --symlink-install'

  source /opt/ros/dashing/setup.bash
  #source ~/ros2_dashing/install/setup.bash
  source ~/turtlebot3_ws/install/setup.bash
  export GAZEBO_MODEL_PATH=$GAZEBO_MODEL_PATH:~/turtlebot3_ws/src/turtlebot3/turtlebot3_simulations/turtlebot3$
  export ROS_DOMAIN_ID=30 #TURTLEBOT3
fi
