#include <chrono>
#include <functional>
#include <memory>


#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

class CommunicationTest : public rclcpp::Node
{
  public:
    CommunicationTest()
    : Node("communication_test")
    {
      subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
      "turtle1/rotate_absolute/_action/feedback", 10, std::bind(&CommunicationTest::topic_callback, this, std::placeholders::_1));
    }

  private:
    void topic_callback(const geometry_msgs::msg::Twist & msg) const
    {
      RCLCPP_INFO(this->get_logger(), "'%f', '%f'", msg.linear.x, msg.angular.z);
    }
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CommunicationTest>());
  rclcpp::shutdown();
  return 0;
}