xmlFilesLocation = '../../../../XMLs/'
rootElement = 'events'

with open(xmlFilesLocation + 'CCTDumpLog.xml') as fd:
    firstLine = True

    for line in fd:
        modeUsed = 'a'

        if firstLine:
            modeUsed = 'w'
            firstLine = False

        with open('testing.xml', modeUsed) as newFile:
            if line == ("<" + rootElement + ">\n") or line == ("</" + rootElement + ">") or "CCT.RR1" in line:
                newFile.write(line)