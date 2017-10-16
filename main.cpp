#include <iostream>
#include <vector>
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

using namespace std;

int max_index = 5;
int current_index;//number of item to show
boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
vector<pcl::TextureMesh> mesh_id(5);

pcl::PCLPointCloud2 TransformationPointCloud2(pcl::PCLPointCloud2 in, Eigen::Affine3f transform)
{
	pcl::PCLPointCloud2 pc2;
	pcl::PointCloud<pcl::PointXYZ> cloud, t_cloud;

	pcl::fromPCLPointCloud2(in, cloud);

	pcl::transformPointCloud(cloud, t_cloud, transform);

	pcl::PCLPointCloud2 out;
	pcl::toPCLPointCloud2(t_cloud, out);

	return out;

}

void ShowObject()
{
	viewer->removeAllPointClouds();
	viewer->removeAllShapes();

	//cout << current_index << endl;
	//string t_name = "texture";
	//viewer->addTextureMesh(mesh_id[current_index-1], t_name, 0);

	for (int i = 0; i < current_index; i++)
	{
		string t_name = "texture";
		t_name = t_name + to_string(i);
		//cout << t_name << endl;

		viewer->addTextureMesh(mesh_id[i], t_name, 0);
	}

	viewer->addCoordinateSystem(5.0);
	viewer->spin();

}
void keyboardEventOccurred(const pcl::visualization::KeyboardEvent &event,
	void* viewer_void)
{
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer = *static_cast<boost::shared_ptr<pcl::visualization::PCLVisualizer> *> (viewer_void);
	if (event.getKeySym() == "a" && event.keyDown())
	{
		if (current_index > 1)
		{
			
			current_index--;
			ShowObject();
		}
	}
	else if (event.getKeySym() == "d" && event.keyDown())
	{
		if (current_index < max_index)
		{
			current_index++;
			ShowObject();
		}

	}
}


int main(int argc, char** argv)
{
	current_index = max_index;

	
	/*vector<string> obj_filename(5);
	obj_filename.push_back("../obj2/obj_chocochip.obj");
	obj_filename.push_back("../obj2/obj_colon.obj");
	obj_filename.push_back("../obj2/obj_flan.obj");
	obj_filename.push_back("../obj2/obj_milky.obj");
	obj_filename.push_back("../obj2/obj_teddy.obj");
	*/
	/*obj_filename[1] = "../obj2/obj_chocochip.obj";
	obj_filename[2] = "../obj2/obj_colon.obj";
	obj_filename[3] = "../obj2/obj_flan.obj";
	obj_filename[4] = "../obj2/obj_milky.obj";
	obj_filename[5] = "../obj2/obj_teddy.obj";*/

	/*for (int i = 0; i < 5; i++)
	{
		cout << obj_filename.at(i) << endl;
		pcl::io::loadOBJFile(obj_filename.at(i), mesh_id[i]);
	}*/

	pcl::io::loadOBJFile("../obj2/obj_chocochip.obj", mesh_id[0]);
	pcl::io::loadOBJFile("../obj2/obj_colon.obj", mesh_id[1]);
	pcl::io::loadOBJFile("../obj2/obj_flan.obj", mesh_id[2]);
	pcl::io::loadOBJFile("../obj2/obj_milky.obj", mesh_id[3]);
	pcl::io::loadOBJFile("../obj2/obj_teddy.obj", mesh_id[4]);
	



	float theta = M_PI / 2; // The angle of rotation in radians
	

	//Eigen::Affine3f transform_6 = Eigen::Affine3f::Identity();
	//transform_6.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitZ()));

	Eigen::Affine3f transform = Eigen::Affine3f::Identity();
	transform.translation() << 1.0, 0.5, 0.0;
	mesh_id[0].cloud = TransformationPointCloud2(mesh_id[0].cloud, transform);

	transform.translation() << 1.0, 1.5, 0.0;
	mesh_id[1].cloud = TransformationPointCloud2(mesh_id[1].cloud, transform);

	transform.translation() << 2.5, 1.5, 0.0;
	mesh_id[3].cloud = TransformationPointCloud2(mesh_id[3].cloud, transform);

	transform.translation() << 2.5, 0.5, 0.0;
	mesh_id[4].cloud = TransformationPointCloud2(mesh_id[4].cloud, transform);

	transform.translation() << 1.0, 0.5, 0.5;
	mesh_id[2].cloud = TransformationPointCloud2(mesh_id[2].cloud, transform);
	
	viewer->registerKeyboardCallback(keyboardEventOccurred, (void*)&viewer);
	ShowObject();

 
return (0);
}