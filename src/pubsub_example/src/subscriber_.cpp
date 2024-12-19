#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/string.hpp>


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

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_;
    // | ------------------------- methods ------------------------ |
    
    void callback(const std_msgs::msg::String::SharedPtr msg);

  };

  //}

  /* SubscriberExample() //{ */

  SubscriberExample::SubscriberExample(rclcpp::NodeOptions options) : Node("subscriber_example", options)
  {

    RCLCPP_INFO(get_logger(), "[SubscriberExample]: initializing");

    subscriber_ = this->create_subscription<std_msgs::msg::String>(
      "~/topic_subscriber", 10, std::bind(&SubscriberExample::callback, this, std::placeholders::_1));
  
    // | --------------------- finish the init -------------------- |

    RCLCPP_INFO(get_logger(), "[SubscriberExample]: initialized");
  }

  //}

  // | ------------------------ callbacks ----------------------- |

  /* callback_subscriber() //{ */

  void SubscriberExample::callback(const std_msgs::msg::String::SharedPtr msg)
  {

    RCLCPP_INFO(get_logger(), "[SubscriberExample]: receiving string message '%s'", msg->data.c_str());
  }


  

}  // namespace pubsub_example

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(pubsub_example::SubscriberExample)