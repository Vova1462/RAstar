
//include c++ libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

//include ros libraries
#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include <geometry_msgs/PoseStamped.h>

#include <tf/tf.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>

#include <tf2_ros/transform_listener.h>

#include <std_msgs/String.h>

//
#include "RAstar_ros.h"


namespace PathPlanner{
    class PathPlanner{
        public:
            void init();
            void mapCallback(const nav_msgs::OccupancyGrid::ConstPtr& map_msg);
            void goalCallback(const geometry_msgs::PoseStamped::ConstPtr& goal_msg);
            void update_coords();

            ros::NodeHandle n;
            
            std::vector<double> robot_position = std::vector<double>(2);

            tf2_ros::Buffer tf_buffer;
            geometry_msgs::TransformStamped transformStamped;
            boost::shared_ptr <tf2_ros::TransformListener> tfListener;

            RAstar_planner::RAstarPlannerROS planner;

            std::string robot_name;


    };
}; 