/*
 * TerrainMapping.h
 *
 *  Created on: Aug 17, 2023
 *      Author: Ikhyeon Cho
 *	 Institute: Korea Univ. ISR (Intelligent Systems & Robotics) Lab
 *       Email: tre0430@korea.ac.kr
 */

#ifndef ROS_TERRAIN_MAPPING_H
#define ROS_TERRAIN_MAPPING_H

#include <ros/ros.h>

#include <isr_ros_utils/core/core.h>
#include <isr_ros_utils/tools/tools.h>

#include <sensor_msgs/PointCloud2.h>
#include <grid_map_ros/GridMapRosConverter.hpp>

#include <pcl_conversions/pcl_conversions.h>

#include "terrain_mapping/ElevationMap.h"

namespace ros
{
class TerrainMapping
{
public:
  TerrainMapping();

  void pointcloudCallback(const sensor_msgs::PointCloud2ConstPtr& msg);

  void processPointcloud(const pcl::PointCloud<pcl::PointXYZI>& pointcloud);

  void updatePose(const ros::TimerEvent& event);

public:
  // ROS Parameters: Node
  roscpp::Parameter<std::string> pointcloud_topic{ "terrain_mapping/SubscribedTopic/pointcloud", "/velodyne_points" };
  roscpp::Parameter<std::string> elevation_map_topic{ "terrain_mapping/PublishingTopic/elevation_map", "map" };

  // ROS Parameters : Framd Ids
  roscpp::Parameter<std::string> frameId_robot{ "frameId_robot", "base_link" };
  roscpp::Parameter<std::string> frameId_map{ "frameId_map", "map" };

  // Elevation Map
  roscpp::Subscriber<sensor_msgs::PointCloud2> pointcloud_subscriber{ pointcloud_topic.param(),
                                                                      &TerrainMapping::pointcloudCallback, this };
  roscpp::Publisher<grid_map_msgs::GridMap> elevation_map_publisher{ elevation_map_topic.param() };

  roscpp::Parameter<double> grid_resolution{ "terrain_mapping/ElevationMap/grid_resolution", 0.1 };
  roscpp::Parameter<double> map_length_x{ "terrain_mapping/ElevationMap/map_length_x", 12 };
  roscpp::Parameter<double> map_length_y{ "terrain_mapping/ElevationMap/map_length_y", 12 };

  // Pose update
  roscpp::Parameter<double> pose_update_duration{ "terrain_mapping/Transform/pose_update_duration",
                                                  0.05 };  // expect 20Hz
  roscpp::Timer pose_update_timer{ pose_update_duration.param(), &TerrainMapping::updatePose, this };

private:
  ElevationMap map_{ map_length_x.param(), map_length_y.param(), grid_resolution.param() };
  
  TransformHandler transform_handler_;
  PointcloudProcessor<pcl::PointXYZI> pointcloud_processor_;
};

}  // namespace ros

#endif