# SENG4800
Repository for SENG4800 HVCCC Group 2018

This is the Unreal Engine project that is set up to be the base of our project.

This is a C++ project setup for version 4.19.2 of Unreal Engine 4

Visual Studio must be installed for this project to compile.

# Project Setup:

Pull the project down from GitHub, or access using the provided USB

Install Unreal Engine version 4.19.* preferably 4.19.2 (https://docs.unrealengine.com/en-US/GettingStarted/Installation)

Install Visual Studio 2017, community version is fine.

When VS is installed, add the following packages to it using Visual Studio Installer (a separate program to Visual Studio)
- https://drive.google.com/file/d/1ASWWaXu223DRYypJaPbyuzRmzA0YW2S7/view?usp=sharing
- https://drive.google.com/file/d/1hrIddU0KsTgE-sJ6vBuA4Z0bfNSqkNvy/view?usp=sharing
- https://drive.google.com/open?id=1e2UrahadnAju7gm7VgEZvP-PO4ovVQ0P 

- Text Version
	- In the Windows section, ensure that '.NET desktop development' and 'Desktop development with C++' is enabled.
	- Scroll down to Mobile and Gaming and enable 'Game development with C++'
		- Ensure you enable the following optional packages within the 'Game development with c++' packages	
			- C++ profiling tools
			- Windows 10 SDK (10.0.17134.0)
			- Windows 8.1 SDK and UCRT SDK

	

After all these packages are installed, right click on the project (HVCCC2.uproject) and then select 'Generate Visual Studio Project Files'
This will generate the solution required to compile the game.
Once you have generated the project files you can now open HVCCC2.uproject and you will be prompted to recompile the project. If you have installed the required packages successfully, it will work from here and you will be able to edit the project. If there were errors it will probably fail to compile.

Before running the game in the engine, ensure you compile once again (using the editors compile button) to ensure that everything is compiled.

Once the project is open you can access the C++ files in VS and modify them there.

# Reasons why your project may not be running:
1. If you are getting over 100 compilation errors in Visual Studio, you can try opening a file explorer outside of UE Editor and Visual Studio and double clicking on "HVCCC2.uproject". You have to then open up the same folder in a file explorer, right click on "HVCCC2uproject" and click on "Generate Visual Studio project files".
2. If you are getting the getting the error "Unable to start program '...\UE4.exe'. The system cannot find the file specified.", you have to right click on "HVCCC2" in the Solution Explorer inside Visual Studio. After that, you need to select "Set as StartUp Project", then recompile.
3. If you are debugging using Visual Studio code and you are getting errors related to not having Unreal Engine .pdb files loaded, you can try:
- Downloading the editor symbols for debugging:

  - Open up the Unreal Engine program
  - Go to Unreal Engine>Library>right click the dropdown next to "Launch" for whichever version of the engine you have installed>Options>check "Editor symbols for debugging"
- Making sure these debugging symbols are being searched for:

  - Launch the project in Visual Studio
  - Tools>Options>Debugging>Symbols
  - In the top section, add the root Unreal Engine folder (eg. C:\Program Files\Epic Games\UE_4.19)
  - Click "OK" to close the window
4. You may have to force shader re-compilation:
- Delete the DerivedDataCache folder in AppData\Local\UnrealEngine\Common
- Relaunch the project in the UE editor and wait for the shaders to be recompiled

# Blender model import procedure:

1. Export the model from blender as a .obj file ensuring that export options forward = 'X Forward' and Up = 'Z Up' are set.
2. Navigate to the folder in the UE4 Content Browser you want to import the model to or make a new folder.
3. Click import and select the model file. In the import menu, set the value of Import Uniform Scale if nessesary. This can be changed later by 're-importing' the asset.
4. Click 'Import' the model should now be imported as a static mesh and any textures made in Blender should have been converted into UE4 Materials as well. 

---------------------
# TinyXML2Testing Information

## Instructions for generating cpp code from Python
Assumming you have python3 installed, run the generate_python.py script located at python/generate_python.py.
Running it with with the -h/--help flag (i.e. `python3 python/generate_python.py -h`) will print out a list of required parameters.
Explanation of StateInfo.json:
The general format of json file is something like:
```
{
    "entities": {
        "{AnEntityName e.g. Stockpile}": {
            "tagPrefix": "{prefix, e.g. sp for Stockpile}",
            "initial": "{e.g. Idle"},
            "hasTerminal": true,
            "identifier": "anEntityNameID",
            "transitions": {
                "{FromStateName}": {
                    "{AnEventName}": "{ToStateName}",
                    ...
                    "{AnotherEventName}": "{AnotherToStateName}"
                }
                ...
                "{AnotherFromStateName}": {
                    "{AnEventName}": "{ToStateName}",
                    ...
                    "{AnotherEventName}": "{AnotherToStateName}"
                }
            }
        },
        ...
        "{AnEntityWhichEncodesStatesName}": {
            "tagPrefix": "{prefix, e.g. sp for Stockpile}",
            "initial": "{e.g. Idle"},
            "hasTerminal": false,
            "identifier": "anEntityWhichEncodesStatesNameID",
            "stateCodes": {
                "ASTATECODE": "ACorrespondingStateName",
                ...
                "AnotherSTATECODE": "AnotherCorrespondingStateName"
            }
            "events": [
                "AnEventName",
                ...
                "AnotherEventName"
            ]
        }
    },
    "terminals": [
      "ABC",
      "EFG",
      "HIJ"
    ],
    "merges": {
		"AnEntityAnotherEntity": ["AnEntity", "AnotherEntity"]
	}
}
```
There are two types of entities, with different attribute sets in the JSON:
- Standard entities like the first in the above example. These have initial states ('initial') and state transitions ('transitions'), specified as a destination-staet per event type per start state.
- Entities whose state is included in the event data, like the second entity in the above example. These have maps for determining the state-name from the code in the event data ('stateCodes'), and a list of valid event codes ('events')

The following is common to both types of entities:
- The 'identifier' attribute, which should match the XML attribute used to uniquely identify instances of the entity (e.g. tell one stacker apart from another)
- The 'tagPrefix' attribute, which is used to identify the tags relating to that entity.
- The 'hasTerminal' attribute, indicating whether or not the entity relates to a specific terminal (e.g. Stackers do, Vessels don't)
