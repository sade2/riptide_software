#ifndef GOLD_CHIP_H
#define GOLD_CHIP_H

#include "ros/ros.h"
#include <vector>
#include "geometry_msgs/Vector3.h"
#include "riptide_msgs/Constants.h"
#include "riptide_msgs/ControlStatusAngular.h"
#include "riptide_msgs/ControlStatusLinear.h"
#include "riptide_msgs/AttitudeCommand.h"
#include "riptide_msgs/AlignmentCommand.h"
#include "riptide_msgs/Pneumatics.h"
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "darknet_ros_msgs/BoundingBox.h"
#include "riptide_autonomy/be_autonomous.h"
#include "riptide_autonomy/validators.h"

#include <cmath>
using namespace std;
typedef riptide_msgs::Constants rc;

class BeAutonomous;

class GoldChip
{

private:
  ros::Subscriber task_bbox_sub, alignment_status_sub, attitude_status_sub;
  vector<ros::Subscriber> active_subs;

  darknet_ros_msgs::BoundingBoxes task_bboxes;
  riptide_msgs::AlignmentCommand align_cmd;

  // Mission variables
  int mission_state;

  // Alignment variables
  int alignment_state;
  bool align_timer_started;
  ros::Time align_start;
  ros::Duration aligned_duration;
  double aligned_duration_thresh;

  DetectionValidator chip_detector;
  ErrorValidator x_validator;
  ErrorValidator y_validator;
  ErrorValidator bbox_validator;

  // Reference to master
  BeAutonomous* master;

public:

  Slots(BeAutonomous* master);
  void Initialize();
  void Start();
  void Identify(const darknet_ros_msgs::BoundingBoxes::ConstPtr& bbox_msg);
  void AlignmentStatusCB(const riptide_msgs::ControlStatusLinear::ConstPtr& status_msg);
  void AttitudeStatusCB(const riptide_msgs::ControlStatusAngular::ConstPtr& status_msg);
  void Abort();
};

#endif
