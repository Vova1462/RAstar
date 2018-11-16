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

#include "rastar_node.h"

using namespace RAstar_planner;
namespace PathPlanner{
    void PathPlanner::init(){
        tfListener.reset(new  tf2_ros::TransformListener(tf_buffer));
        robot_name = "ump";
        ros::Subscriber map_sub = n.subscribe("map", 10, &PathPlanner::mapCallback, this);
        ros::Subscriber goal_sub = n.subscribe("move_base_simple/goal", 1, &PathPlanner::goalCallback, this);
        ros::Subscriber cost_map_sub = n.subscribe("costmap_node/costmap/costmap", 10, &PathPlanner::costmapCallback, this);
        costmap_2d::Costmap2DROS::Costmap2DROS costmap("map", tf_buffer);
        
    }

    void PathPlanner::mapCallback(const nav_msgs::OccupancyGrid::ConstPtr& map_msg){
        nav_msgs::MapMetaData info = map_msg->info;
        std::vector<std::vector<int>> map(info.width, vector<int> (info.height, 0));
        // Map map(info.width, info.height);
        int i = 0;
        ROS_INFO("Got map %d %d", info.width, info.height);
        for (unsigned int x=0; x < info.width; x++)
           for(unsigned int y=0; y < info.height; y++){
               map[x][y] = map_msg->data[i];
               i++;
           }
        // planner.initialize(robot_name, map);
    }

    // void PathPlanner::costmapCallback(costmap_2d::Costmap2DROS *costmap_msg){

    // }

    void PathPlanner::goalCallback(const geometry_msgs::PoseStamped::ConstPtr& goal_msg){
        std::vector<int> goal_position(2);
        goal_position[0] = goal_msg -> pose.position.x;
        goal_position[1] = goal_msg -> pose.position.y;
    }

    void PathPlanner::update_coords(){
        try{
            transformStamped = tf_buffer.lookupTransform("map", robot_name, ros::Time(0));
            robot_position[0] = transformStamped.transform.translation.x;
            robot_position[1] = transformStamped.transform.translation.y;            
        } catch (tf2::TransformException &ex) {
            ROS_WARN("Could not lookup pathplanner to tf2.");
        }
    }
}

int main(int argc, char const *argv[])
{
    PathPlanner::PathPlanner Astar;
    Astar.init();
    ros::spin();
    return 0;
}
