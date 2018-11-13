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

#include "RAstar_ros.h"

using namespace RAstar_planner;
bool mapCallback(const nav_msgs::OccupancyGrid::ConstPtr& map_msg){
    nav_msgs::MapMetaData info = map_msg->info;
    int data = map_msgs->data;
    Map map(info.width, info.height);
    ROS_INFO('Got map', info.width, info.height);
    for (unsigned int x=0; x < info.width; x++)
        for(unsigned int y=0; y < info.height; y++){
            

        }


    return true;
}

int main(int argc, char const *argv[])
{
    
    return 0;
}
