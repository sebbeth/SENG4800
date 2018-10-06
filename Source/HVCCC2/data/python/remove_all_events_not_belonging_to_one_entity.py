import argparse

parser = argparse.ArgumentParser(description='A simple script to strip all of the events not belonging to the entity specified, from the XML file selected.')
parser.add_argument('-s', '--source-directory', type=str, required=True)
parser.add_argument('-f', '--file-name', type=str, required=True)
parser.add_argument('-r', '--root-element', type=str, required=True)
parser.add_argument('-i', '--id-name', type=str, required=True)
parser.add_argument('-e', '--entity-id', type=str, required=True)
parser.add_argument('-o', '--output-directory', type=str)

# Some example parameters:
#     -s ../../../../XMLs/
#     -f CCTDumpLog.xml
#     -r events
#     -i dumpstationID
#     -e CCT.RR1

args = parser.parse_args()

outputFilesDirectory = args.source_directory

if args.output_directory:
    outputFilesDirectory = args.output_directory

with open(args.source_directory + args.file_name) as fd:
    firstLine = True

    newFileName = args.file_name[:len(args.file_name) - 4] + "_Only" + args.entity_id + "Events.xml"

    for line in fd:
        modeUsed = 'a'

        if firstLine:
            modeUsed = 'w'
            firstLine = False

        with open(outputFilesDirectory + newFileName, modeUsed) as newFile:
            if line == ("<" + args.root_element + ">\n") or line == ("</" + args.root_element + ">") or (args.id_name + "=\"" + args.entity_id + "\"") in line:
                newFile.write(line)