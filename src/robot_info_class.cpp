#include "ros/ros.h"
#include "robotinfo_msgs/RobotInfo10Fields.h"
#include <string>

class RobotInfo {
protected:
    std::string robot_description;
    std::string serial_number;
    std::string ip_address;
    std::string firmware_version;
    ros::Publisher publisher;

public:
    RobotInfo(ros::NodeHandle* nh, const std::string& robot_description, const std::string& serial_number, 
              const std::string& ip_address, const std::string& firmware_version)
        : robot_description(robot_description), serial_number(serial_number), 
          ip_address(ip_address), firmware_version(firmware_version) {
        publisher = nh->advertise<robotinfo_msgs::RobotInfo10Fields>("robot_info", 10);
    }

    virtual void publish_data() {
        robotinfo_msgs::RobotInfo10Fields msg;
        msg.data_field_01 = "robot_description: " + robot_description;
        msg.data_field_02 = "serial_number: " + serial_number;
        msg.data_field_03 = "ip_address: " + ip_address;
        msg.data_field_04 = "firmware_version: " + firmware_version;
        publisher.publish(msg);
    }
};
