#!/usr/bin/env python
import sys, glob, csv, operator, itertools, collections

import inspect, os
print inspect.getfile(inspect.currentframe()) # script filename (usually with path)
print os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe()))) # script director

def getKey(item):
    return item[1]

paths = []
strings = []
hitpaths = []
placing = []
rows = []
stringdict = {}

# compilepath = 'C:\Users\DQ28514\Documents\Udvikling\projekter\stats\compile\*.csv'
# outpath = 'C:\Users\DQ28514\Documents\Udvikling\projekter\stats\log.txt'
# compilepath = '/var/www/drupal7vm/drupal/web/sites/default/files/compile/*.csv'
outpath = '/var/www/drupal7vm/drupal/web/sites/default/files/compile/log.txt'

# files = glob.glob(compilepath)
# with open(outpath, 'w') as outfile:
#     for fname in files:
#         with open(fname) as infile:
#             for line in infile:
#                 outfile.write(line)
# print 'inside l.22'
with open(outpath,'r') as csvfile:
    readCSV = csv.reader(csvfile, delimiter=',')
    sortedCSV = sorted(readCSV, key=getKey)

    for row in sortedCSV:
        path = row[0]
        string = row[1].lower()
        place = row[2]

        if '"' not in string and 'search' not in path:
            stringdict.setdefault(string, []).append([path, place])
    #print stringdict
    for key in stringdict:
        # calculate hitscore
        placing.append([key])
        for collection in stringdict[key]:
            placing.append(collection)
    #print placing
#         #extract hitpaths
#         for pathindex in stringdict[key]:
#             if pathindex != 'search':
#                 #print pathindex + ' ' + key, score
#                 hitpaths.append(pathindex)
#     # remove duplicates from hitpaths
#     hitpaths = list(set(hitpaths))
#
# Write placings to placings.txt
#with open("C:\Users\DQ28514\Documents\Udvikling\projekter\stats\placings.txt", "wb") as hpf:
with open("/var/www/drupal7vm/drupal/web/sites/default/files/compile/placings.txt", "w") as hpf:
    writer = csv.writer(hpf)
    for val in placing:
        writer.writerow(val)
        #hpf.write(fullpath)
# #with open("C:\Users\DQ28514\Documents\Udvikling\projekter\stats\compile\hitscores_new.csv", "wb") as hsf:
# with open("/var/www/drupal7vm/drupal/web/sites/default/files/compile/hitscores_new.csv", "w") as hsf:
#     writer = csv.writer(hsf)
#     hitscores.sort(reverse=True, key=lambda elem: elem[1])
#     writer.writerows(hitscores)
#     #hsf.write(hitscores)
print 'Kapeew!'
