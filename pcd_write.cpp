#include <iostream>
#include <pcl/io/pcd_io.h> 
#include <pcl/point_types.h>
#include <pcl/common/common.h>
#include <pcl/io/obj_io.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/visualization/pcl_visualizer.h> 

int
main (int argc, char** argv)
{
	pcl::TextureMesh mesh7;
	//pcl::io::loadPolygonFileOBJ("BlueSaltCube_5k_tex.obj", mesh7); // no texture

	//pcl::io::loadOBJFile("../obj2/cubfox4-e.obj", mesh7); 
	pcl::io::loadOBJFile("../obj2/rectanglebox.obj", mesh7);

	pcl::visualization::PCLVisualizer viewer_pre7("PCL Viewer_pre7");
	viewer_pre7.addTextureMesh(mesh7, "texture", 0);
	viewer_pre7.spin();
 
return (0);
}