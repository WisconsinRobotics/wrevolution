#include "ZeroPowerBehaviorServiceAction.h"
#include "ControlGroup.h"
#include "ros-handler-core/ControlGroupRosServiceAction.h"
#include "wrevolution/ZeroPowerBehavior.h"

namespace RosHandler {

using RosHandlerCore::ControlGroupRosServiceAction;
using wrevolution::ZeroPowerBehavior;

ZeroPowerBehaviorServiceAction::ZeroPowerBehaviorServiceAction(const ros::NodeHandle &node,
                                                               std::shared_ptr<ControlGroup> controlGroup)
    : ControlGroupRosServiceAction<ZeroPowerBehavior>{node,
                                                      std::move(controlGroup),
                                                      "zero_power_behavior",
                                                      ros::Duration{ZERO_POWER_MAX_RESPONSE_DELAY_SECONDS}} {}

auto ZeroPowerBehaviorServiceAction::onServiceRequest(ZeroPowerBehavior::Request &req,
                                                      ZeroPowerBehavior::Response &resp) -> bool {
    switch (req.behavior) {
    case ZeroPowerBehavior::Request::ZERO_POWER_BEHAVIOR_BRAKE:
        controlGroup->setZeroPowerBehavior(Hardware::ZeroPowerBehavior::BRAKE);
        break;
    case ZeroPowerBehavior::Request::ZERO_POWER_BEHAVIOR_COAST:
        controlGroup->setZeroPowerBehavior(Hardware::ZeroPowerBehavior::COAST);
        break;
    default:
        return false;
    }
    resp.success = 1U; // Not explicit bool due to how ROS autogenerates bool msgs
    return true;
}

} // namespace RosHandler