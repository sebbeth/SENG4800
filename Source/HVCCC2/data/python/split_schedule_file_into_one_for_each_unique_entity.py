# Created by Nicholas Hendry
# The purpose of this script is to split up a schedule XML file (eg. NCTStockPileLog.xml),
# into one XML file for each of the entities present in the file
# (eg. NCTStockPileLog_OnlyNCT1836.1Events.xml, NCTStockPileLog_OnlyNCT1837.1Events.xml, etc.).
# These split up XML files were used to make the debugging process for the entity schedules at lot easier.

import argparse
import re

# Use argparser to easily handle the command line arguments we needed to use for this script:
parser = argparse.ArgumentParser(description='A simple script to separate the whole schedule XML files (eg. NCTStockPileLog.xml), into one XML file for each unique entity inside the the file (eg. NCTStockPileLog_OnlyNCT1836.1Events.xml).')
parser.add_argument('-s', '--source-directory', type=str, required=True)
parser.add_argument('-f', '--file-name', type=str, required=True)
parser.add_argument('-r', '--root-element', type=str, required=True)
parser.add_argument('-i', '--id-name', type=str, required=True)
parser.add_argument('-o', '--output-directory', type=str)

# Some example parameters:
#     -s ../../../../XMLs/
#     -f CCTDumpLog.xml
#     -r events
#     -i dumpstationID
#     -o .

args = parser.parse_args()

outputFilesDirectory = args.source_directory + '/'

# If the user specified the output directory parameter, use it instead of the source directory value:
if args.output_directory:
    outputFilesDirectory = args.output_directory + '/'

# This dictionary's keys are the entity IDs (eg. NCT1837.1)
# and the values are lists holding all of the lines which represent events that were carried out on the entity:
entityLines = {}

# Iterate through the entire file, separating lines with different entity ID values into their own separate list:
with open(args.source_directory + args.file_name) as openFile:
    for line in openFile:
        # This regex is used to find out the entity ID value held inside the current line.
            # eg. <SpStackStart stockpileID="NCT1836.1" vesselID="1836" time="28.702386" padID="Pad H" machineID="SR04"/>
            # would have just "NCT1836.1" stripped out.
        matchedString = re.search('(.*)(' + args.id_name + '=")([^"]*)(")(.*)', line)

        if matchedString:
            # This capturing group is the contents of the entity ID XML attribute:
            entityID = matchedString.group(3)

            # If the entity ID already exists as a key inside the dictionary, place the new line inside the corresponding list.
            # If not, create a new list and place that and the new entity ID key in the dictionary.
            if entityID in entityLines:
                listForKey = entityLines.get(entityID)
                listForKey.append(line)
                entityLines.update({entityID: listForKey})
            else:
                listForKey = [line]
                entityLines.update({entityID: listForKey})

# Creates a new XML file for each unique entity ID value, making sure to print out all of the lines in its list inside the file:
for entityID in entityLines:
    # Creates the new filename, which appends things to the end so people can see in the file explorer what exactly the contents of the file are.
    # An example of a filename generated by the line below is : NCTStockPileLog_OnlyNCT1836.1Events.xml.
    newFileName = args.file_name[:len(args.file_name) - 4] + "_Only" + entityID + "Events.xml"

    # Use write mode for the very first line of the new file:
    with open(outputFilesDirectory + newFileName, 'w') as newFile:
        # Write the opening tag of the root element from the full schedule file (eg. "<events>"):
        newFile.write('\t<' + args.root_element + '>\n')

    # For all of the following lines in the file, use append mode:
    with open(outputFilesDirectory + newFileName, 'a') as newFile:
        # Add in each line stored in the list for this entity ID:
        for line in entityLines.get(entityID):
            newFile.write(line)
        # Add in the closing tag for the root element:
        newFile.write('\t</' + args.root_element + '>')