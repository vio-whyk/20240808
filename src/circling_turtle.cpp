#include <chrono>
#include <functional>
#include <memory>


#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

class CirclingTurtle : public rclcpp::Node
{
  public:
    CirclingTurtle()
    : Node("circling_turtle"), count_(0)
    {
      publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
      timer_ = this->create_wall_timer(
      500ms, std::bind(&CirclingTurtle::timer_callback, this));
    }

  private:
    void timer_callback()
    {
      auto message = geometry_msgs::msg::Twist();
      message.linear.x = 2.0;
      message.angular.z = 1.8;
      publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    int count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CirclingTurtle>());
  rclcpp::shutdown();
  return 0;
}

