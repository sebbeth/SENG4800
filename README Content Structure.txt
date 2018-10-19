Key Folders to focus on

CONTENT (Contains all the engine assets and blueprints which have be added to create the project)
SOURCE (All the C++ and Python code)
XMLS (data to run the simulation)
PACKAGED (Use this to run the simulation without setting up Unreal Engine)

1. Content
	- The project was created from a template project, hence why some of the folder names are not fitting to the project
		e.g. Flying, FlyingBP. We were not able to rename these folders without it completely breaking all references in
		the engine.
	- Folders within the Content folder and what they contain
	
	- Blueprints (contains all the blueprints for displaying various visual components such as coal stacks, stackers, etc)
	- Flying (is the UI folder, this contains all the menu blueprints, and HUD blueprints. It also contains the images which
		are a part of the UI)
	- FlyingBP (contains the gamemode, game instance and the character blueprints. The gamemode and game instance is used
		to pass variables to and from other blueprints)
	- Geometry (Contains all the meshes and textures for the main components)
	- Map (Contains the level blueprints for the simulation, main menu and options screen)
	- Materials (Various materials and textures for the project)
	- Source (link to the C++ files)
	
2. Source (Main classes and brief description)
	- Coal Stack (Used to change the size of the coal stack)
	- Conveyer Belt (Used to set the material based on what the state is)
	- File Dialog (Used to generate a file dialog)
	- Level Controller (MAIN CLASS OF THE SYSTEM)
	- Open Dialog (Used to open a dialog and set the path chosen by the user)
	- Ship (Used to set a ship hidden if the ship is not at the terminal)
	- Ship loader (Used to change the direction and the material colour based on the state)
	- Stacker reclaimer (Moves the stacker /reclaimer to the certain position, rotates model, sets material based on state)
	- Time converter (Used to convert the provided float value into a time value)
	- Train (used to set position of trains, spawn them in, spawn carriages)
	- Train Track Spline (creates the railway)
	
	