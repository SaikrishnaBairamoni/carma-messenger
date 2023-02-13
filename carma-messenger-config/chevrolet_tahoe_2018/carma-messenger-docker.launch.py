# Copyright (C) 2022 LEIDOS.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

from ament_index_python import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    """
    Launch CARMA Messenger System.
    """

    #Declare the route file folder launch argument
    route_file_folder = LaunchConfiguration('route_file_folder')
    declare_route_file_folder = DeclareLaunchArgument(
        name = 'route_file_folder',
        default_value='/opt/carma/routes/',
        description = 'Path of folder on host PC containing route CSV file(s) that can be accessed by plugins; currently only used by emergency_response_vehicle_plugin'
    )

    # Launch the core carma launch file
    core_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([ get_package_share_directory('carma-messenger'), '/launch/carma-messenger.launch.py']),
        launch_arguments = {
            'route_file_folder' : route_file_folder
        }.items()
    )

    return LaunchDescription([
        declare_route_file_folder,
        core_launch
    ])
