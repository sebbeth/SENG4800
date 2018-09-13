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

---------------------
# TinyXML2Testing Information
========================================================================
    CONSOLE APPLICATION : TinyXML2Testing Project Overview
========================================================================

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