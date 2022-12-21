#include "EncoderTimedAction.h"
#include "ros-handler-core/RosTimedAction.h"
#include "ros/forwards.h"
#include "ros/node_handle.h"
#include "std_msgs/Float64.h"

namespace RosHandler {
using Hardware::ControlGroup;

EncoderTimedAction::EncoderTimedAction(ros::NodeHandle &node, std::shared_ptr<ControlGroup> controlGroup)
    : RosTimedAction(ros::Rate{ENCODER_PUBLISHING_RATE_HZ}, node, "'" + controlGroup->getName() + "' Encoder Publisher"),
      publisher{node.advertise<std_msgs::Float64>(controlGroup->getName() + "/encoder", ENCODER_PUBLISHING_BUFFER_SIZE)},
      controlGroup{std::move(controlGroup)} {}

void EncoderTimedAction::onTimerEvent(const ros::TimerEvent &event) {
    std_msgs::Float64 msg;
    auto encoderValue = controlGroup->getEncoder();
    if (encoderValue.has_value()) {
        msg.data = *encoderValue;
        publisher.publish(msg);
    }
}

} // namespace RosHandler