#include "ros/ros.h"
#include "robot_info_class.cpp"
#include "hydraulic_system_monitor.cpp" 
#include "robotinfo_msgs/RobotInfo10Fields.h" 
#include <string>


class AGVRobotInfo : public RobotInfo {
private:
    std::string maximum_payload;
    HydraulicSystemMonitor hydraulicMonitor;

public:
    AGVRobotInfo(ros::NodeHandle* nh, const std::string& robot_description, const std::string& serial_number,
                 const std::string& ip_address, const std::string& firmware_version, const std::string& maximum_payload,
                 const std::string& hydraulic_temp, const std::string& hydraulic_fill_level, const std::string& hydraulic_pressure)
        : RobotInfo(nh, robot_description, serial_number, ip_address, firmware_version),
          maximum_payload(maximum_payload),
          hydraulicMonitor(hydraulic_temp, hydraulic_fill_level, hydraulic_pressure) {}

    void publish_data() override {
        robotinfo_msgs::RobotInfo10Fields msg;
        msg.data_field_01 = "robot_description: " + robot_description;
        msg.data_field_02 = "serial_number: " + serial_number;
        msg.data_field_03 = "ip_address: " + ip_address;
        msg.data_field_04 = "firmware_version: " + firmware_version;
        msg.data_field_05 = "maximum_payload: " + maximum_payload;
        msg.data_field_06 = "hydraulic_oil_temperature: " + hydraulicMonitor.getTemperature();
        msg.data_field_07 = "hydraulic_oil_tank_fill_level: " + hydraulicMonitor.getFillLevel();
        msg.data_field_08 = "hydraulic_oil_pressure: " + hydraulicMonitor.getPressure();
        
        publisher.publish(msg);
    }
};


int main(int argc, char** argv) {
    ros::init(argc, argv, "agv_robot_info_node");
    ros::NodeHandle nh;

    
    AGVRobotInfo agvRobotInfo(&nh, "Mir100", "567A359", "169.254.5.180", "3.5.8", "100 Kg", "45C", "100%", "250 bar");

    ros::Rate loop_rate(10); 
    while (ros::ok()) {
        agvRobotInfo.publish_data();
        ros::spinOnce();
        ros::Duration(0.5).sleep();
    }

    return 0;
}
