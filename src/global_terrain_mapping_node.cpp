/*
 * global_terrain_mapping_node.cpp
 *
 *  Created on: Aug 17, 2023
 *      Author: Ikhyeon Cho
 *	 Institute: Korea Univ. ISR (Intelligent Systems & Robotics) Lab
 *       Email: tre0430@korea.ac.kr
 */

#include <ros/ros.h>
#include "terrain_mapping/GlobalTerrainMapping.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "global_terrain_mapping_node");
  ros::NodeHandle nh("~");

  ros::GlobalTerrainMapping node;

  ros::spin();

  return 0;
}