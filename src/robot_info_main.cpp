#include "ros/ros.h"
#include "robot_info_class.cpp"

int main(int argc, char **argv) {
    ros::init(argc, argv, "robot_info_node");
    ros::NodeHandle nh;
    RobotInfo robotInfo(&nh, "Mir100", "567A359", "169.254.5.180", "3.5.8");

    ros::Rate loop_rate(10);
    while (ros::ok()) {
        robotInfo.publish_data();
        ros::spinOnce();
        ros::Duration(0.5).sleep();
    }

    return 0;
}
