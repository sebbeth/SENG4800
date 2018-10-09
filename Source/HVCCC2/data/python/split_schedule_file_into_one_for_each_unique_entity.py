import argparse
import re

parser = argparse.ArgumentParser(description='A simple script to strip all of the events not belonging to the entity specified, from the XML file selected.')
parser.add_argument('-s', '--source-directory', type=str, required=True)
parser.add_argument('-f', '--file-name', type=str, required=True)
parser.add_argument('-r', '--root-element', type=str, required=True)
parser.add_argument('-i', '--id-name', type=str, required=True)
# parser.add_argument('-e', '--entity-id', type=str, required=True)
parser.add_argument('-o', '--output-directory', type=str)

# Some example parameters:
#     -s ../../../../XMLs/
#     -f CCTDumpLog.xml
#     -r events
#     -i dumpstationID

# Used before:
#     -e CCT.RR1 I changed the script to split the schedule script into one XML file per unique entity,
# so that's why this command line param isn't used any more

args = parser.parse_args()

outputFilesDirectory = args.source_directory

if args.output_directory:
    outputFilesDirectory = args.output_directory

uniqueEntityIDs = []
numUniqueEntityIDs = 0

# Find out all of the individual entities in the file:
with open(args.source_directory + args.file_name) as fd:
    for line in fd:
        matchedString = re.search('(.*)(' + args.id_name + '=\")([^\"]*)(.*)', line)

        if matchedString:
            entityIDAlreadyInArray = False

            for index in uniqueEntityIDs:
                if index == matchedString.group(3):
                    entityIDAlreadyInArray = True

            if not entityIDAlreadyInArray:
                uniqueEntityIDs.append(matchedString.group(3))

for entityID in uniqueEntityIDs:
    with open(args.source_directory + args.file_name) as fd:
        firstLine = True

        # newFileName = args.file_name[:len(args.file_name) - 4] + "_Only" + args.entity_id + "Events.xml"
        newFileName = args.file_name[:len(args.file_name) - 4] + "_Only" + entityID + "Events.xml"

        for line in fd:
            modeUsed = 'a'

            if firstLine:
                modeUsed = 'w'
                firstLine = False

            with open(outputFilesDirectory + newFileName, modeUsed) as newFile:
                # if ("<" + args.root_element + ">\n") in line or ("</" + args.root_element + ">") in line or ("</" + args.root_element + ">\n") in line or (args.id_name + "=\"" + args.entity_id + "\"") in line:
                if ("<" + args.root_element + ">\n") in line or ("</" + args.root_element + ">") in line or ("</" + args.root_element + ">\n") in line or (args.id_name + "=\"" + entityID + "\"") in line:
                    newFile.write(line)