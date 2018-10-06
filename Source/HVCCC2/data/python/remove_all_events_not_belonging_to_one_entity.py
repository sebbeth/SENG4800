xmlFilesDirectory = '../../../../XMLs/'
xmlFileName = 'CCTDumpLog.xml'
rootElement = 'events'
idName = 'dumpstationID'
entityID = 'CCT.RR1'
outputFilesDirectory = '../../../../XMLs/'

with open(xmlFilesDirectory + xmlFileName) as fd:
    firstLine = True

    newFileName = xmlFileName[:len(xmlFileName) - 4] + "_Only" + entityID + "Events.xml"

    for line in fd:
        modeUsed = 'a'

        if firstLine:
            modeUsed = 'w'
            firstLine = False

        with open(outputFilesDirectory + newFileName, modeUsed) as newFile:
            if line == ("<" + rootElement + ">\n") or line == ("</" + rootElement + ">") or (idName + "=\"" + entityID + "\"") in line:
                newFile.write(line)