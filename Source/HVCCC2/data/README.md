========================================================================
    CONSOLE APPLICATION : TinyXML2Testing Project Overview
========================================================================

AppWizard has created this TinyXML2Testing application for you.

This file contains a summary of what you will find in each of the files that
make up your TinyXML2Testing application.


TinyXML2Testing.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

TinyXML2Testing.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

TinyXML2Testing.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named TinyXML2Testing.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////

#Instructions for generating cpp code from Python
Assuming you have python3 installed, run the generate_code.py script located at python/generate_code.py.
Running it with  the -h/--help flag (i.e. `python3 python/generate_code.py -h`) will print out a list of required parameters.

**depending how you use python you may only need to use the word "python" not python3 **

first navigate your command line to SENG4800\Source\HVCCC2\data
Then you will need to supply 3 points of data when running the python command:
-j StateInfo.json
-x the path to the xml root folder e.g. SENG4800\XML
-o the path of the output file preferably SENG4800\Source\HVCCC2\data\extraction

e.g. python python/generate_code.py -j  StateInfo.json -x SENG4800\XML -o SENG4800\Source\HVCCC2\data\extraction



Explanation of StateInfo.json:
The general format of json file is something like:
```
{
	"{AnEntityName e.g. Stockpile}": {
		"tagPrefix": "{prefix, e.g. sp for Stockpile}",
		"initial": "{e.g. Idle"},
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
}
```
There are two types of entities, with different attribute sets in the JSON:
- Standard entities like the first in the above example. These have initial states ('initial') and state transitions ('transitions'), specified as a destination-staet per event type per start state.
- Entities whose state is included in the event data, like the second entity in the above example. These have maps for determining the state-name from the code in the event data ('stateCodes'), and a list of valid event codes ('events')

Note: Both types of entities also have a 'tagPrefix' attribute, which is used to identify the tags relating to that entity.
