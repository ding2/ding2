#!/bin/bash
#
# A script to download the webtrekk auto data files from kpiindex and parse them. 
# This is handled with a command line cron job because of the size of the files.
#

wget -O autodatayear.csv http://www.kpiindex.com/index2/Smartsearch1y.csv

wget -O autodatamonth.csv http://www.kpiindex.com/index2/Smartsearch1m.csv

php -d memory_limit=2G  parse_auto_data.php
