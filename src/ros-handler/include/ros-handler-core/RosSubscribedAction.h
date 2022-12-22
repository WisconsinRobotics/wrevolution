#ifndef ROS_SUBSCRIBED_ACTION_H
#define ROS_SUBSCRIBED_ACTION_H

#include "RosConcepts.h" // IWYU pragma: keep; Concept defintion
#include "ros/node_handle.h"
#include <iostream>

namespace RosHandler::RosHandlerCore {

template <RosMessage T>
class RosSubscribedAction {
public:
    RosSubscribedAction(ros::NodeHandle &node, const std::string &topicName, uint32_t queue_size, const ros::Duration &maxResponseTime)
        : server{node.subscribe(topicName, queue_size, &RosSubscribedAction<T>::subscriberCallback, this)},
          maxResponseTime{maxResponseTime} {}

    virtual ~RosSubscribedAction() = default;
    RosSubscribedAction(const RosSubscribedAction &) = delete;
    auto operator=(const RosSubscribedAction &) -> RosSubscribedAction & = delete;
    RosSubscribedAction(RosSubscribedAction &&) = delete;
    auto operator=(RosSubscribedAction &&) = delete;

private:
    void subscriberCallback(const ros::MessageEvent<T const> &event) {
        std::cout << "Heard something!" << std::endl;
        onMessageReceived(event.getConstMessage());
    }

    virtual void onMessageReceived(const typename T::ConstPtr &msg) = 0;

    const ros::Subscriber server;
    const ros::Duration maxResponseTime;
};
} // namespace RosHandler::RosHandlerCore

#endif