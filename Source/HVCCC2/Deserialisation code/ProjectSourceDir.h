#include <string>

//This file contains a string, which represents the file path for the source files folder of the project (actual string in ProjectSourceDir.cpp).
	//We need to do this, since std::experimental::filesystem does not support wildcards (*) in its file paths.
	//(ie. we can't use a filecard to make the filepath work on most people's machines)

//Please open up ProjectSourceDir.cpp, and type out the proper string to point it to where you
//currently have your project soure files.

class ProjectSourceDir {
	public:
		ProjectSourceDir();
		std::string filePath;
};