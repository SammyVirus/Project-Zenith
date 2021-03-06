#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "stdio.h"
#include "sensor_msgs/NavSatFix.h"
//using namespace std


std_msgs::Int8 obj_found_1=0,obj_found_2=0,obj_found_3=0; 
sensor_msgs::NavSatFix gps1, gps2, gps3;
std::float64 lat_offset = 26.192, lon_offset=91.69;    // coordinates for guwahati
std::vector<std::pair<int,int> > gps_coordinates;


void obj_number_cb1(const std_msgs::Int8::ConstPtr& msg1)
{
  obj_found_1=*msg1;
}

void obj_number_cb2(const std_msgs::Int8::ConstPtr& msg2)
{
   obj_found_2=*msg2;
}

void obj_number_cb3(const std_msgs::Int8::ConstPtr& msg3)
{
   obj_found_3=*msg3;
}

void gps_cb1(const sensor_msgs::NavSatFix::ConstPtr& msg4)
{
	gps1=*msg4;
	if (obj_found_1==1)
	{
		//append the vector with current gps coordinates
		gps_coordinates.push_back(int((gps1.latitude-lat_offset)*10000000),int((gps1.longitude-lon_offset)*1000000));
	}
}

void gps_cb2(const sensor_msgs::NavSatFix::ConstPtr& msg5)
{
	gps2=*msg5;
	if (obj_found_2==1)
	{
		//append the vector with current gps coordinates
		gps_coordinates.push_back(int((gps2.latitude-lat_offset)*10000000),int((gps2.longitude-lon_offset)*1000000));
	}
}

void gps_cb3(const sensor_msgs::NavSatFix::ConstPtr& msg6)
{
	gps3=*msg6;
	if (obj_found_3==1)
	{
		//append the vector with current gps coordinates
		gps_coordinates.push_back(int((gps3.latitude-lat_offset)*10000000),int((gps3.longitude-lon_offset)*1000000));
	}
}




int main(int argc, char **argv)
{
   ros::init(argc, argv, "gps_clustering_node");
   ros::NodeHandle nh;
   ros::Subscriber obj_sub1 = nh.subscribe<std_msgs::Int8>("/uav1/object_found", 100, obj_number_cb1);
   ros::Subscriber obj_sub2 = nh.subscribe<std_msgs::Int8>("/uav2/object_found", 100, obj_number_cb2);
   ros::Subscriber obj_sub3 = nh.subscribe<std_msgs::Int8>("/uav3/object_found", 100, obj_number_cb3);
   ros::Subscriber gps_sub1 = nh.subscribe<sensor_msgs::NavSatFix>("/uav1/mavros/global_position/global", 100, gps_cb1);
   ros::Subscriber gps_sub2 = nh.subscribe<sensor_msgs::NavSatFix>("/uav2/mavros/global_position/global", 100, gps_cb2);
   ros::Subscriber gps_sub3 = nh.subscribe<sensor_msgs::NavSatFix>("/uav3/mavros/global_position/global", 100, gps_cb3);
   

   ros::spin();
   return 0;
 }


