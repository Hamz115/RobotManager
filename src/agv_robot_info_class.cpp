#include "ros/ros.h"
#include "robot_info_class.cpp"
#include "robotinfo_msgs/RobotInfo10Fields.h" 
#include <string>


class AGVRobotInfo : public RobotInfo {
private:
    std::string maximum_payload; 

public:
    // Constructor
    AGVRobotInfo(ros::NodeHandle* nh, const std::string& robot_description, const std::string& serial_number, 
                 const std::string& ip_address, const std::string& firmware_version, const std::string& maximum_payload)
        : RobotInfo(nh, robot_description, serial_number, ip_address, firmware_version),
          maximum_payload(maximum_payload) {}

    
    virtual void publish_data() override {
        robotinfo_msgs::RobotInfo10Fields msg;
        msg.data_field_01 = "robot_description: " + robot_description;
        msg.data_field_02 = "serial_number: " + serial_number;
        msg.data_field_03 = "ip_address: " + ip_address;
        msg.data_field_04 = "firmware_version: " + firmware_version;
        msg.data_field_05 = "maximum_payload: " + maximum_payload;
    
        publisher.publish(msg);
    }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "agv_robot_info_node");
    ros::NodeHandle nh;

   
    AGVRobotInfo agvRobotInfo(&nh, "Mir100", "567A359", "169.254.5.180", "3.5.8", "100 Kg");

    ros::Rate loop_rate(10); 
    while (ros::ok()) {
        agvRobotInfo.publish_data();
        ros::spinOnce();
        ros::Duration(0.5).sleep();
    }

    return 0;
}
