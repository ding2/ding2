# Ting smart search

This is a module that allows configuration of the search results coming from the
well. You can use different searches, boost certain materials. As default the
module puts up to 5 off the most required materials in the top off the search
results.

To work optimally the module uses data from Webtrekk. The data feed from 
Webtrekk is very large so Randers Bibliotek hosts an intermediary webservice 
which parses the files.

The code for the webservice is included in the extras folder.

On install you need to run a cron job to get a list off the most popular 
searches.

The module uses a 20 MB data file to put the most relevant materials first in 
search results. In order to have top performance the data file is saved as php 
array anduse the include statement to read it. For optimal performance a 20 MB 
increase to your opcode cache maybe required.

