#include <iostream>
#include <pcl/io/pcd_io.h> 
#include <pcl/point_types.h>
#include <pcl/common/common.h>
#include <pcl/io/obj_io.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/conversions.h> 
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
//#include <sensor_msgs/PointCloud2.h>
#include <pcl/console/parse.h>
#include <pcl/common/transforms.h>
#include <pcl/visualization/pcl_visualizer.h> 

int
main (int argc, char** argv)
{
	pcl::TextureMesh mesh6,mesh7;
	//pcl::io::loadPolygonFileOBJ("BlueSaltCube_5k_tex.obj", mesh7); // no texture

	pcl::io::loadOBJFile("../obj2/obj_teddy.obj", mesh6); 
	pcl::io::loadOBJFile("../obj2/obj_teddy.obj", mesh7);


	float theta = M_PI / 4; // The angle of rotation in radians
	

	pcl::PCLPointCloud2 pcl_pc6, pcl_pc7;


	pcl::PointCloud<pcl::PointXYZ> cloud6, t_cloud6;
	pcl::PointCloud<pcl::PointXYZ> cloud7, t_cloud7;

	pcl::fromPCLPointCloud2(mesh6.cloud, cloud6);
	pcl::fromPCLPointCloud2(mesh7.cloud, cloud7);

	Eigen::Affine3f transform_6 = Eigen::Affine3f::Identity();
	transform_6.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitZ()));
	pcl::transformPointCloud(cloud6, t_cloud6, transform_6);

	Eigen::Affine3f transform_7 = Eigen::Affine3f::Identity();
	transform_7.translation() << 2.5, 0.0, 0.0;
	pcl::transformPointCloud(cloud7, t_cloud7, transform_7);

	pcl::toPCLPointCloud2(t_cloud6, pcl_pc6); 
	mesh6.cloud = pcl_pc6;

	pcl::toPCLPointCloud2(t_cloud7, pcl_pc7);
	mesh7.cloud = pcl_pc7;

	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer_pre7(new pcl::visualization::PCLVisualizer("3D Viewer"));
	viewer_pre7->addTextureMesh(mesh6, "texture6", 0);
	viewer_pre7->addTextureMesh(mesh7, "texture7", 0);
	viewer_pre7->addCoordinateSystem(5.0);
	//viewer_pre7.initCameraParameters();
	viewer_pre7->spin();
 
return (0);
}