#include "myModule.h"
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <iostream>
#include <deque>
#include <set>
#include <math.h>
#include <algorithm>
#include <sys/time.h>
#include <ros/ros.h>

// MoveIt!
#include <moveit/move_group_interface/move_group.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

using namespace std;

class ModuleAlgorithm
{
  private:

    static ModuleAlgorithm* instance_;

    ros::NodeHandle* nh_;
    moveit::planning_interface::MoveGroup* group_;
    moveit::planning_interface::MoveGroup::Plan cached_plan_;
    ros::AsyncSpinner spinner;

    ModuleAlgorithm(int argc, char* argv[]) : spinner(1)
    {
      nh_ = new ros::NodeHandle();
      group_ = new moveit::planning_interface::MoveGroup("arm");
      group_->setPlannerId("RRTConnectkConfigDefault");
      group_->setPoseReferenceFrame("iri_wam_link_base");
      group_->setPlanningTime(0.4);
      spinner.start();
    }

  public:

    static void init(int argc, char* argv[])
    {
      if (instance_ == NULL)
      {
        instance_ = new ModuleAlgorithm(argc, argv);
      }
    }

    static void cleanup()
    {
      if (instance_ != NULL)
      {
        delete instance_;
        instance_ = NULL;
      }
    }

    inline static ModuleAlgorithm* instance() { return instance_; }

    bool canMove(const std::vector<double>& joints,
        const geometry_msgs::Pose& pose)
    {
      robot_state::RobotState start_state(*group_->getCurrentState());
      start_state.setJointGroupPositions(group_->getName(), joints);
      group_->setStartState(start_state);
      group_->setPoseTarget(pose);
      //return true;
      return group_->plan(cached_plan_);
    }

    double planDuration() const
    {
      ros::Duration duration = cached_plan_.trajectory_.joint_trajectory.points.back().time_from_start;
      return duration.toSec();
    }

    void move(std::vector<double>& joints,
        const geometry_msgs::Pose& pose)
    {
      // big assumption is made here: the joints that the robot must adopt are
      // in the last position of the cached plan's trajectory.
      
      canMove(joints, pose);
      joints = cached_plan_.trajectory_.joint_trajectory.points.back().positions;
    }


    ~ModuleAlgorithm()
    {
      spinner.stop();
      delete nh_;
      delete group_;
    }

};

ModuleAlgorithm* ModuleAlgorithm::instance_ = NULL;

#define DEBUG_MOD (0)


double can_move(const ParameterList & parameterList,
       predicateCallbackType predicateCallback,
       numericalFluentCallbackType numericalFluentCallback,
       int relaxed)
{
  // Receives a pose as a parameter
  printf("Calling %s module...\n", __func__);
  //ROS_INFO("Calling %s module...", __func__);
  
  //if (relaxed) return 0.01;

  NumericalFluentList* nfl = new NumericalFluentList(14);
  nfl->at(0).name = "j0";
  nfl->at(1).name = "j1";
  nfl->at(2).name = "j2";
  nfl->at(3).name = "j3";
  nfl->at(4).name = "j4";
  nfl->at(5).name = "j5";
  nfl->at(6).name = "j6";

  nfl->at(7).name = "x";
  nfl->at(8).name = "y";
  nfl->at(9).name = "z";
  nfl->at(10).name = "qx";
  nfl->at(11).name = "qy";
  nfl->at(12).name = "qz";
  nfl->at(13).name = "qw";

  for (int idx = 7; idx < 14; ++idx)
  {
    // the first (and only) parameter of this condition checker is the
    // symbolic pose identifier.
    nfl->at(idx).parameters.push_back(parameterList.front());
  }

  numericalFluentCallback(nfl);
  cout << *nfl << std::endl;

  std::vector<double> joints(7);
  for (int idx = 0; idx < 7; ++idx)
  {
    joints[idx] = nfl->at(idx).value;
  }

  geometry_msgs::Pose pose;
  pose.position.x = nfl->at(7).value;
  pose.position.y = nfl->at(8).value;
  pose.position.z = nfl->at(9).value;

  pose.orientation.x = nfl->at(10).value;
  pose.orientation.y = nfl->at(11).value;
  pose.orientation.z = nfl->at(12).value;
  pose.orientation.w = nfl->at(13).value;

  // Important! Seems like the other modules' writers do not care too much
  // about memory leaks, but the memory should be freed after its usage.
  delete nfl;

  bool can = ModuleAlgorithm::instance()->canMove(joints, pose);

  return can? ModuleAlgorithm::instance()->planDuration() : INFINITE_COST;
}

int move(const ParameterList & parameterList,
    predicateCallbackType predicateCallback,
    numericalFluentCallbackType numericalFluentCallback,
    int relaxed,
    vector<double>& writtenVars)
{

  printf("Calling %s module", __func__);

  if (relaxed) return 0;
  
  NumericalFluentList* nfl = new NumericalFluentList(7);
  nfl->at(0).name = "x";
  nfl->at(1).name = "y";
  nfl->at(2).name = "z";
  nfl->at(3).name = "qx";
  nfl->at(4).name = "qy";
  nfl->at(5).name = "qz";
  nfl->at(6).name = "qw";

  geometry_msgs::Pose pose;
  pose.position.x = nfl->at(0).value;
  pose.position.y = nfl->at(1).value;
  pose.position.z = nfl->at(2).value;

  pose.orientation.x = nfl->at(3).value;
  pose.orientation.y = nfl->at(4).value;
  pose.orientation.z = nfl->at(5).value;
  pose.orientation.w = nfl->at(6).value;

  delete nfl;

  ModuleAlgorithm::instance()->move(writtenVars, pose);

  cout << writtenVars.size() << std::endl;

  return 1;
}


void exit_module(const RawPlan& plan, int argc, char* argv[],
    predicateCallbackType predicateCallback,
    numericalFluentCallbackType numericalFluentCallback)
{
  ModuleAlgorithm::instance()->cleanup();

  NumericalFluentList* nfl = new NumericalFluentList(7);
  nfl->at(0).name = "j0";
  nfl->at(1).name = "j1";
  nfl->at(2).name = "j2";
  nfl->at(3).name = "j3";
  nfl->at(4).name = "j4";
  nfl->at(5).name = "j5";
  nfl->at(6).name = "j6";

  numericalFluentCallback(nfl);
  cout << *nfl << std::endl;

  delete nfl;
}

void init(int argc, char** argv)
{
   printf("Initilizing MyModule: ");
   for(int i = 0; i < argc; i++)
   {
      printf("%s ", argv[i]);
   }
   printf("\n");
   ModuleAlgorithm::init(argc, argv);
}

subplanType genSubplan(const string & operatorName, const ParameterList & parameterList,
        predicateCallbackType predicateCallback, numericalFluentCallbackType numericalFluentCallback, int heuristic)
{
   printf("Generating subplan for %s\n", operatorName.c_str());
   return strdup(operatorName.c_str());
}

/// For final plan output: Convert a subplan into a string.
string outputSubplan(subplanType sp)
{
   char* str = static_cast<char*>(sp);
   return str;
}

void execSubplan(modulePlanType modulePlan)
{
   printf("Executing subplan:\n");
   for(modulePlanType::iterator it = modulePlan.begin(); it != modulePlan.end(); it++) {
      string sps = outputSubplan(*it);
      printf("%s\n", sps.c_str());
   }
   printf("\n");
}

