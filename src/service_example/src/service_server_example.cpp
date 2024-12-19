#include <rclcpp/rclcpp.hpp>

#include <std_srvs/srv/set_bool.hpp>

using namespace std::chrono_literals;

namespace service_example
{

  /* class ServiceServerExample //{ */

  class ServiceServerExample : public rclcpp::Node
  {
  public:
    ServiceServerExample(rclcpp::NodeOptions options);

  private:
    // | --------------------- service servers -------------------- |

    rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr service_server_;

    void callback_set_bool(const std::shared_ptr<std_srvs::srv::SetBool::Request> request, std::shared_ptr<std_srvs::srv::SetBool::Response> response);
  };

  //}

  /* ServiceServerExample() //{ */

  ServiceServerExample::ServiceServerExample(rclcpp::NodeOptions options) : Node("service_server_example", options)
  {

    RCLCPP_INFO(get_logger(), "[ServiceServerExample]: initializing");

    // | --------------------- service server --------------------- |

    service_server_ = create_service<std_srvs::srv::SetBool>(
        "~/set_bool_in", std::bind(&ServiceServerExample::callback_set_bool, this, std::placeholders::_1, std::placeholders::_2));

    RCLCPP_INFO(get_logger(), "[ServiceServerExample]: initialized");
  }

  //}

  // | ------------------------ callbacks ----------------------- |

  /* callback_set_bool() //{ */

  void ServiceServerExample::callback_set_bool(const std::shared_ptr<std_srvs::srv::SetBool::Request> request,
                                               std::shared_ptr<std_srvs::srv::SetBool::Response> response)
  {
    RCLCPP_INFO(get_logger(), "[ServiceServerExample]: received service call: %s", request->data ? "TRUE" : "FALSE");

    response->message = "succeeded";
    response->success = true;
  }

  //}

}  // namespace service_example

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(service_example::ServiceServerExample)
