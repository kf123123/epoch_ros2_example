#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/string.hpp>

#include "interfaces/msg/num.hpp"

using namespace std::chrono_literals;

namespace pubsub_example
{

  /* class SubscriberExample //{ */

  class SubscriberExample : public rclcpp::Node
  {
  private:

  public:
    SubscriberExample(rclcpp::NodeOptions options);

  private:
    // | ----------------------- subscribers ---------------------- |

    rclcpp::Subscription<interfaces::msg::Num>::SharedPtr subscriber_;
    // | ------------------------- methods ------------------------ |
    
    void callback(const interfaces::msg::Num::SharedPtr msg);

  };

  //}

  /* SubscriberExample() //{ */

  SubscriberExample::SubscriberExample(rclcpp::NodeOptions options) : Node("subscriber_example", options)
  {

    RCLCPP_INFO(get_logger(), "[SubscriberExample]: initializing");

    subscriber_ = this->create_subscription<interfaces::msg::Num>(
      "~/topic_subscriber", 10, std::bind(&SubscriberExample::callback, this, std::placeholders::_1));
  
    // | --------------------- finish the init -------------------- |

    RCLCPP_INFO(get_logger(), "[SubscriberExample]: initialized");
  }

  //}

  // | ------------------------ callbacks ----------------------- |

  /* callback_subscriber() //{ */

  void SubscriberExample::callback( interfaces::msg::Num::SharedPtr msg)
  {

   
    msg->sum = msg->a + msg->b;
   RCLCPP_INFO_STREAM(this->get_logger(), "I heard: '" << msg->sum << "'");


  }

}  // namespace pubsub_example

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(pubsub_example::SubscriberExample)