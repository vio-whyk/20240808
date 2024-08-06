from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='turtlesim',
            namespace='turtlesim1',
            executable='turtlesim_node',
            name='sim'
        ),
        Node(
            package='turtlesim',
            namespace='turtlesim2',
            executable='turtlesim_node',
            name='sim'
        ),
        Node(
            package='circling_turtle',
            executable='circling_turtle',
            name='circling_turtle',
            namespace= 'turtlesim1'
        ),       
        Node(
            package='circling_turtle',
            executable='nemo_turtle',
            name='nemo_turtle',
            namespace= 'turtlesim2'
        )
    ])
