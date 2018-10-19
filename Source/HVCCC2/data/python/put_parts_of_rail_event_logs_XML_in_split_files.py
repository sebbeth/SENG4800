# Created by Nicholas Hendry
# This script was created to fix the problem of the entity-split versions of RailEventsLog.xml file (eg. RailEventsLog_Onlytrk_KCT_InitialEvents.xml)
# not having the actual root element of "<railLog>" included in them, since the "split_schedule_file_into_one_for_each_unique_entity.py" script
# used to generate the entity-split XMLs can only account for one root element from the original file.

# This script prepends and appends the missing contents from RailEventsLog.xml into the entity-split versions of RailEventsLog.xml.

import argparse
import os
import re


# This procedure was copied from martineau's answer on this Stack Overflow question:
# https://stackoverflow.com/questions/5914627/prepend-line-to-beginning-of-a-file
def line_prepender(directory, fileName, stringToPrepend):
    with open(directory + fileName, '+r') as f:
        # Read the entire contents of the filename passed in:
        content = f.read()
        # Move to the start of the file and paste the contents read above, then add in the new content:
        f.seek(0, 0)
        f.write(stringToPrepend.rstrip('\r\n') + '\n' + content)


# A function to neatly store the entire string to be prepended to the file.
# It doesn't serve much purpose at the moment,
# but it would if the entire contents of "<networkData>" was prepended to each entity-split XML file.
def getStringToPlaceAtStart():
    return '<' + rootXMLElementName + '>'


# This was copied and slightly modified from "mick barry"'s Stack Overflow answer in this question:
# https://stackoverflow.com/questions/7167008/efficiently-finding-the-last-line-in-a-text-file
def getLastLineInFile(directory, fileName):
    with open(directory + fileName, 'r') as f:
        lines = f.read().splitlines()
        last_line = lines[-1]
        return last_line


# Use argparser to easily handle the command line arguments we needed to use for this script:
parser = argparse.ArgumentParser(description='A simple script to add back in parts of the RailEventLogs.xml file back into the split versions of this file, since the original splitting script can\'t handle RailEventsLog.xml\'s unique format.')
parser.add_argument('-s', '--source-directory', type=str, required=True)
# Even though this script was developed just for RailEventsLog.xml, the filename and root element is required from the user:
parser.add_argument('-f', '--file-name', type=str, required=True)
parser.add_argument('-r', '--root-element', type=str, required=True)

# Some example parameters:
#     -s ../../../../XMLs/
#     -f RailEventLog.xml
#     -r railLog

args = parser.parse_args()

# Extract the command line parameters:
outputFilesDirectory = args.source_directory
filename = args.file_name
rootXMLElementName = args.root_element

# This regex is used to find out the filename without the ".xml" portion of it:
matchedString = re.search('(.*)(.xml)', filename)
filenameWithoutFileExtension = matchedString.group(1)

# Iterate through all of the files in the directory specified:
for filename in os.listdir(outputFilesDirectory):
    # This regex matches with any XML files with "RailEventsLog" in its filename:
    matchedString = re.search('(.*)(' + filenameWithoutFileExtension + ')(.*)(.xml)', filename)

    if matchedString:
        # It's made sure that the third capture group (the one after "RailEventsLog") has a length greater than 0,
        # since that makes it so that only files such as "RailEventsLog_Onlytrk_KCT_InitialEvents.xml" have lines added to them
        # and the original schedule file (RailEventsLog.xml) is untouched:
        if len(matchedString.group(3)) > 0:
            with open(outputFilesDirectory + filename, 'a') as fd:
                # Prepend everything that's needed before the original contents of the file:
                line_prepender(outputFilesDirectory, filename, getStringToPlaceAtStart())

                # Find out what the very last line of the file is:
                lastLine = getLastLineInFile(outputFilesDirectory, filename)

                # Append the closing root tag for the final line:
                if lastLine.isspace():
                    # If the last line only holds whitespace, place the closing root tag at the end of the line:
                    fd.write('</' + rootXMLElementName + '>')
                else:
                    # If the last line is not purely whitespace, place the closing root tag on a new line:
                    fd.write('\n</' + rootXMLElementName + '>')