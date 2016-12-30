#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <iterator>

#include <ros/ros.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <tf/transform_listener.h>
#include "pcl_ros/transforms.h"

typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;

using namespace std;

ofstream pcl_map;


void point_cloud_callback( const sensor_msgs::PointCloud2ConstPtr& cloud2_msg ) {
    pcl::PCLPointCloud2 cloud2;
    pcl_conversions::toPCL(*cloud2_msg, cloud2);


    PointCloud* cloud (new PointCloud);
    pcl::fromPCLPointCloud2(cloud2,*cloud);

    pcl_map.open ("point_cloud.ply");
    pcl_map << "ply\n";
    pcl_map << "format ascii 1.0\n";
    pcl_map << "comment RFAL @Stevens Bona\n";

    int valid_counter = 0;
    for (int j = 1; j< cloud2.width; j++)
    {
        if(isnan(cloud->at(j).x))
            continue;
        valid_counter++;
    }

    pcl_map << "element vertex " << valid_counter << "\n";
    pcl_map << "property float32 x\n";
    pcl_map << "property float32 y\n";
    pcl_map << "property float32 z\n";
    pcl_map << "end_header\n";

    cout << "height : " << cloud2.height << "  , width :" << cloud2.width << endl;
        for (int j = 1; j< cloud2.width; j++)
        {
            if(isnan(cloud->at(j).x))
                continue;
            pcl_map << cloud->at(j).x << " " << cloud->at(j).y << " " << cloud->at(j).z << "\n";
            // cout << cloud->at(j).x << "   ;   x is ..." << endl;
        }
    pcl_map.close();
}



int main(int argc, char **argv) {
    ros::init(argc, argv, "save_ply");
    ros::NodeHandle nh;

    ros::Subscriber point_map_sub;
    point_map_sub = nh.subscribe<sensor_msgs::PointCloud2>("/velodyne_points", 1, point_cloud_callback);
    ros::spin();

    return 0;
}