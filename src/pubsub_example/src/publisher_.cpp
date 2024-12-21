#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/string.hpp>

#include "interfaces/msg/num.hpp"
using namespace std::chrono_literals;

namespace pubsub_example  //使用命名空间
{

/* class PublisherExample //{ */

class PublisherExample : public rclcpp::Node
{
public:
  PublisherExample(rclcpp::NodeOptions options);

private:
  // | -------------------- member variables -------------------- |
  rclcpp::Subscription<rcl_interfaces::msg::ParameterEvent>::SharedPtr parameter_event_sub_;
  rclcpp::AsyncParametersClient::SharedPtr parameters_client_;
  void update_parameter();

  int64_t b_;
  int64_t a_; 
  int64_t sum_; 

  // | ----------------------- publishers ----------------------- |

  rclcpp::Publisher<interfaces::msg::Num>::SharedPtr publisher_;


  // | ------------------------- timers ------------------------- |

  rclcpp::TimerBase::SharedPtr timer_;

  // | ------------------------- methods ------------------------ |
  void callback();//一定记得声明回调函数
};

//}

/* PublisherExample() //{ */

PublisherExample::PublisherExample(rclcpp::NodeOptions options)
: Node("publisher_example", options)
{
  RCLCPP_INFO(get_logger(), "[PublisherExample]: initializing");

  // | ------------------------ publisher ----------------------- |
                            
  this->declare_parameter("a", 10);
  a_ = this->get_parameter("a").get_value<int64_t>();
  this->declare_parameter("b", 0);
  b_ = this->get_parameter("b").get_value<int64_t>();
  this->declare_parameter("sum", 0);
  sum_ = this->get_parameter("sum").get_value<int64_t>();
   this->update_parameter();

  publisher_ = create_publisher<interfaces::msg::Num>("~/topic_publisher", 10);


  // | -------------------------- timer ------------------------- |

  timer_ =
    create_wall_timer(
    1000ms,
    std::bind(&PublisherExample::callback, this));//1000ms 执行一次回调函数


  // | --------------------- finish the init -------------------- |

  RCLCPP_INFO(get_logger(), "[PublisherExample]: initialized=======完成初始化");
}


void PublisherExample::update_parameter()
{
  parameters_client_ = std::make_shared<rclcpp::AsyncParametersClient>(this);
  while (!parameters_client_->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for the service. Exiting.");
      return;
    }
    RCLCPP_INFO(this->get_logger(), "service not available, waiting again...");
  }

  auto param_event_callback =
    [this](const rcl_interfaces::msg::ParameterEvent::SharedPtr event) -> void
    {
      for (auto & changed_parameter : event->changed_parameters) {
        if (changed_parameter.name == "a") {
          auto value = rclcpp::Parameter::from_parameter_msg(changed_parameter);
          a_ = value.get_value<int64_t>(); // 使用 get_value 方法

        } else if (changed_parameter.name == "b") {
          auto value = rclcpp::Parameter::from_parameter_msg(changed_parameter);
         b_ = value.get_value<int64_t>(); // 使用 get_value 方法
        }
      }
    };

  parameter_event_sub_ = parameters_client_->on_parameter_event(param_event_callback);
}
// | ------------------------ callbacks ----------------------- |



void PublisherExample::callback()
{
   auto message = interfaces::msg::Num();     
   message.a = a_;
   message.b = b_;
   message.sum = sum_;
    RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: '" << message.a << "'");    // CHANGE
    RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: '" << message.b << "'");    // CHANGE
    publisher_->publish(message);
}


 // namespace pubsub_example
}
#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(pubsub_example::PublisherExample)
