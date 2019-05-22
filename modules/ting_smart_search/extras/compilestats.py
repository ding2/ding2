#!/usr/bin/env python
import sys, glob, csv, operator, itertools, collections

import inspect, os, ntpath
print inspect.getfile(inspect.currentframe()) # script filename (usually with path)
print os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe()))) # script director

def getKey(item):
    return item[1]

paths = []
strings = []
hitpaths = []
hitscores = []
rows = []
stringdict = {}

# compilepath = 'C:\Users\DQ28514\Documents\Udvikling\projekter\stats\compile\*.csv'
# outpath = 'C:\Users\DQ28514\Documents\Udvikling\projekter\stats\compile\log.txt'
compilepath = '/var/www/drupal7vm/drupal/web/sites/default/files/compile/*.csv'
outpath = '/var/www/drupal7vm/drupal/web/sites/default/files/compile/log.txt'

files = glob.glob(compilepath)
with open(outpath, 'w') as outfile:
    for fname in files:
        print ntpath.basename(fname)
        with open(fname) as infile:
            for line in infile:
                outfile.write(line)
        #TODO - move files to oldfiles
print 'inside l.22'
with open(outpath,'r') as csvfile:
    readCSV = csv.reader(csvfile, delimiter=',')
    # sortedCSV = sorted(readCSV, key=getKey)
    # # Write hitpaths to sitemap.txt and hitscores to file
    # # with open("C:\Users\DQ28514\Documents\Udvikling\projekter\stats\compile\sitemap_new.txt", "wb") as hpf:
    # with open("/var/www/drupal7vm/drupal/web/sites/default/files/compile/sorted.csv", "w") as hps:
    #     writer = csv.writer(hps)
    #     for sortedrow in sortedCSV:
    #         writer.writerow(sortedrow)

    for row in readCSV:
        path = row[0]
        string = row[1].lower()

        if '"' not in string:
            stringdict.setdefault(string, []).append(path)

    for key in stringdict:
        # calculate hitscore
        ctotal = len(stringdict[key])
        scount = stringdict[key].count('search')
        score = float((ctotal - scount)) / float(ctotal)
        hitscore = [key, score]
        hitscores.append(hitscore)

        #extract hitpaths
        for pathindex in stringdict[key]:
            if pathindex != 'search':
                #print pathindex + ' ' + key, score
                hitpaths.append(pathindex)
    # remove duplicates from hitpaths
    hitpaths = list(set(hitpaths))

# Write hitpaths to sitemap.txt and hitscores to file
#with open("C:\Users\DQ28514\Documents\Udvikling\projekter\stats\compile\sitemap_new.txt", "wb") as hpf:
with open("/var/www/drupal7vm/drupal/web/sites/default/files/compile/sitemap_new.txt", "w") as hpf:
    writer = csv.writer(hpf)
    for val in hitpaths:
        fullpath = 'https://www.randersbib.dk/'+val
        writer.writerow([fullpath])
        #hpf.write(fullpath)
#with open("C:\Users\DQ28514\Documents\Udvikling\projekter\stats\compile\hitscores_new.csv", "wb") as hsf:
with open("/var/www/drupal7vm/drupal/web/sites/default/files/compile/hitscores_new.csv", "w") as hsf:
    writer = csv.writer(hsf)
    hitscores.sort(reverse=True, key=lambda elem: elem[1])
    writer.writerows(hitscores)
    #hsf.write(hitscores)
print 'Kapeew!'
