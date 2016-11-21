#ifndef TRANSPORT_MODULE_H
#define TRANSPORT_MODULE_H

#include "tfd_modules/module_api/pddlModuleTypes.h"

using namespace modules;

#ifdef __cplusplus
extern "C" {
#endif

void init(int argc, char** argv);
VERIFY_INIT_MODULE_DEF(init);



double can_move(const ParameterList & parameterList,
        predicateCallbackType predicateCallback,
        numericalFluentCallbackType numericalFluentCallback,
        int relaxed);
VERIFY_CONDITIONCHECKER_DEF(can_move);

int move(const ParameterList & parameterList,
    predicateCallbackType predicateCallback,
    numericalFluentCallbackType numericalFluentCallback,
    int relaxed,
    vector<double>& writtenVars);
VERIFY_APPLYEFFECT_DEF(move);

void exit_module(const RawPlan& plan, int argc, char* argv[],
    predicateCallbackType predicateCallback,
    numericalFluentCallbackType numericalFluentCallback);
VERIFY_EXIT_MODULE_DEF(exit_module);

subplanType genSubplan(const string & operatorName,
    const ParameterList & parameterList,
    predicateCallbackType predicateCallback,
    numericalFluentCallbackType numericalFluentCallback,
    int heuristic);
VERIFY_SUBPLANGENERATOR_DEF(genSubplan);

/// For final plan output: Convert a subplan into a string.
string outputSubplan(subplanType sp);

void execSubplan(modulePlanType modulePlan);


#ifdef __cplusplus
}
#endif

#endif

