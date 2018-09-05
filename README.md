# SENG4800
Repository for SENG4800 HVCCC Group 2018

This is the Unreal Engine project that is set up to be the base of our project.

This is a C++ project setup for version 1.19.3 of Unreal Engine 4

Visual Studio must be installed for this project to compile.

# Project Setup:

Pull the project down from GitHub.

Install Unreal Engine version 4.19.* preferably 4.19.2 (https://docs.unrealengine.com/en-US/GettingStarted/Installation)

Install Visual Studio 2017, community version is fine.

When VS is installed, add the following packages to it using VS Installer
- https://drive.google.com/file/d/1ASWWaXu223DRYypJaPbyuzRmzA0YW2S7/view?usp=sharing
- https://drive.google.com/file/d/1hrIddU0KsTgE-sJ6vBuA4Z0bfNSqkNvy/view?usp=sharing
- https://drive.google.com/open?id=1e2UrahadnAju7gm7VgEZvP-PO4ovVQ0P

After all these packages are installed, Open the project, you will be prompted to recompile the project, if you have installed the required packages successfully it will work from here and you will be able to edit the project, if there were errors it will probably fail to compile.

In a file explorer outside of UE Editor and Visual Studio, right click on "HVCCC2.uproject" and click on "Generate Visual Studio project files" to stop the over 100 compilation errors in Visual Studio.

Once the project is open you can access the C++ files in VS and modify them there.

# Blender model import procedure:

1. Export the model from blender as a .obj file ensuring that export options forward = 'X Forward' and Up = 'Z Up' are set.
2. Navigate to the folder in the UE4 Content Browser you want to import the model to or make a new folder.
3. Click import and select the model file. In the import menu, set the value of Import Uniform Scale if nessesary. This can be changed later by 're-importing' the asset.
4. Click 'Import' the model should now be imported as a static mesh and any textures made in Blender should have been converted into UE4 Materials as well. 