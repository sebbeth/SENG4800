import argparse
import os
import re

# This procedure was copied from martineau's answer on this Stack Overflow question:
# https://stackoverflow.com/questions/5914627/prepend-line-to-beginning-of-a-file
def line_prepender(directory, fileName, stringToPrepend):
    with open(directory + fileName, '+r') as f:
        content = f.read()
        f.seek(0,0)
        f.write(stringToPrepend.rstrip('\r\n') + '\n' + content)

def getStringToPlaceAtStart():
    # If I wanted these split files to be like the original file, I'd place the contents of the networkData tag at the top.
    # The contents of the split files were going to be used for debugging, so I left them out.
    return '<' + rootXMLElementName + '>'

parser = argparse.ArgumentParser(description='A simple script to add back in parts of the RailEventLogs.xml file back into the split versions of this file, since the original splitting script can\'t handle RailEventsLog.xml\'s unique format.')
parser.add_argument('-s', '--source-directory', type=str, required=True)
parser.add_argument('-f', '--file-name', type=str, required=True)

# Some example parameters:
#     -s ../../../../XMLs/
#     -f RailEventLog.xml

args = parser.parse_args()

outputFilesDirectory = args.source_directory
filename = args.file_name

matchedString = re.search('(.*)(.xml)', filename)
filenameWithoutFileExtension = matchedString.group(1)

rootXMLElementName = 'railLog'

for filename in os.listdir(outputFilesDirectory):
    matchedString = re.search('(.*)(' + filenameWithoutFileExtension + ')(.*)(.xml)', filename)

    if matchedString:
        # Only add the string segments to the files which aren't the original RailEventsLog.xml:
        if len(matchedString.group(3)) > 0:
            with open(outputFilesDirectory + filename, 'a') as fd:
                line_prepender(outputFilesDirectory, filename, getStringToPlaceAtStart())
                fd.write('</' + rootXMLElementName + '>')
