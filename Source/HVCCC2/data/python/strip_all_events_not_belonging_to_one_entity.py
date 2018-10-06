from collections import OrderedDict

import xmltodict

with open('../../../../XMLs/CCTDumpLog.xml') as fd:
    doc = xmltodict.parse(fd.read())

    baseElementName = next(iter(doc))

    events = doc[baseElementName]

    eventListIterator = iter(events)

    for i in range(len(events)):
        eventList = events[next(eventListIterator)]

        j = 0
        endIndex = len(eventList)

        # The following code will used to strip all of the events which don't have the dumpstationID of CCT.RR1:
        while j < endIndex:
            if not eventList[j]['@dumpstationID'] == 'CCT.RR1':
                eventList.pop(j)
                j = j - 1
                endIndex = endIndex - 1
            j = j + 1

    print(xmltodict.unparse(doc, pretty=True))
    print()