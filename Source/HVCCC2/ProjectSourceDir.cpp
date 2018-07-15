#include "ProjectSourceDir.h"
#include "stdafx.h"

//This file contains a string, which represents the file path for the source files folder of the project.
	//We need to do this, since std::experimental::filesystem does not support wildcards (*) in its file paths.
	//(ie. we can't use a filecard to make the filepath work on most people's machines)

//Please type out the proper string for "filePath"'s value, to point it to where you currently have your project soure files.
	//eg. std::string ProjectSourceDir::filePath = "C:/Users/Nick/Documents/Unreal Projects/SENG4800/Source/HVCCC2/";

ProjectSourceDir::ProjectSourceDir() {
	filePath = "";
}