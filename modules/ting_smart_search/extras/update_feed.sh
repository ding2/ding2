#!/bin/bash
#
# A script to download the webtrekk search data files from kpiindex and parse them. 
# This is handled with a command line cron job because of the size of the files.
#

wget -O search_feed.csv http://www.kpiindex.com/index2/search_feed.csv

php -d memory_limit=2G  parse_feed_data.php
