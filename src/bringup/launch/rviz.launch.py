import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition


def generate_launch_description():

    package_path = get_package_share_directory('r2bot_bringup')

    default_rviz_config_path = os.path.join(package_path, 'rviz', 'r2bot_nav2.rviz')
    rviz_cfg = LaunchConfiguration('rviz_cfg')
    rviz_use = LaunchConfiguration('rviz')

    declare_rviz_cmd = DeclareLaunchArgument(
        'rviz', default_value='true',
        description='Use RViz to monitor results'
    )
    declare_rviz_config_path_cmd = DeclareLaunchArgument(
        'rviz_cfg', default_value=default_rviz_config_path,
        description='RViz config file path'
    )

    ld = LaunchDescription()
	
  
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        arguments=['-d', rviz_cfg],
        condition=IfCondition(rviz_use)
    )
   
    ld.add_action(declare_rviz_cmd)
    ld.add_action(declare_rviz_config_path_cmd)

    ld.add_action(rviz_node)

    return ld
