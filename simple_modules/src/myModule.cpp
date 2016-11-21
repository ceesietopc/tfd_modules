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

using namespace std;

#define DEBUG_MOD (0)

double can_move(const ParameterList & parameterList,
       predicateCallbackType predicateCallback,
       numericalFluentCallbackType numericalFluentCallback,
       int /* relaxed */)
{
  printf("Calling %s module\n", __func__);
  ROS_INFO("Calling %s module", __func__);
  return 0;
}

int move(const ParameterList & parameterList,
    predicateCallbackType predicateCallback,
    numericalFluentCallbackType numericalFluentCallback,
    int /* relaxed */,
    vector<double>& writtenVars)
{
  ROS_INFO("Calling %s module", __func__);
  return 0;
}

void init(int argc, char** argv)
{
   printf("Initilizing Transport Module: ");
   for(int i = 0; i < argc; i++) {
      printf("%s ", argv[i]);
   }
   printf("\n");
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

