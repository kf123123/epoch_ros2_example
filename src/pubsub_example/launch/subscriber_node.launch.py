import launch
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode
import os

def generate_launch_description():

    ld = launch.LaunchDescription()

    pkg_name = "pubsub_example"
    pkg_share_path = get_package_share_directory(pkg_name)

    namespace='epoch'
    ld.add_action(ComposableNodeContainer(
        namespace='',
        name=namespace+'_subscriber_example',
        package='rclcpp_components',
        executable='component_container_mt',
        composable_node_descriptions=[
            ComposableNode(
                package=pkg_name,
                plugin='pubsub_example::SubscriberExample',
                namespace=namespace,
                name='subscriber_',
                # parameters=[
                #     pkg_share_path + '/config/subscriber_example.yaml',
                # ],
                remappings=[
                    # topics
                    ("~/topic_subscriber", "/epoch/publisher_/topic_publisher_out"),
                   
                ],
            )
        ],
        output='screen',
    ))

    return ld
