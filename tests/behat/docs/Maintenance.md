# Maintenance procedures

This document describes how the suite is to be maintained to continue to work.

## After update of the data well

The data in the test versions of the well ('brønden') are refreshed from time
to time, and as the current suite depends on known data, these needs to be
refreshed too.

### Detection and recognising the need

Once the scenarios depending on files (containing "Given I use file..") 
starts to fail, and the screendump generated shows that no data is found,
then it is likely the well has been refreshed. 

Do a check on the date of the *.dat files in the behat root dir 
to compare with the latest refresh of well data to be certain if the need is there.

Note that refresh doesn't necessarily mean that all tests will fail, since
some data may still be in the refreshed well data set. 

### Procedure to refresh

There is a maintenance scenario in 99-maintanance.feature: Update files after well is refreshed.
This scenario extracts data from the test webservice. This is currently hard coded in the "ICreateFilesForRelationChunk" 
function in LibContext.php, so that reference needs to be updated (variable $url) to the new
test service, if the endpoint changes.

It creates 8 files in the behat root dir (same as where the features-directory is) when run - which does take a while. It's best started and checked upon after an hour or so.
The files are generated as a base name + _Positive.dat|_Negative.dat.
Basenames are found in the scenario, but should be 'aim', 'credesc', 'onlacc' and 'hasrev'. These are short names for AccessInfoMedia, CreatorDescription, onlineAccess and hasReview. 
The following shell script can pick out the first 100 of each of these files, and overwrites the existing .dat-files. It's assumed well understood, but basically copy this into a shell terminal, where the current directory is the behat root dir.

```sh
cat <<EOF reduceFileSize.sh
head -n100 aim_Positive.dat > accessMedia.dat
head -n100 aim_Negative.dat > accessMediaNot.dat
head -n100 credesc_Positive.dat > creator.dat
head -n100 credesc_Negative.dat > creatorNot.dat
head -n100 onlacc_Positive.dat > onlineAccess.dat
head -n100 onlacc_Negative.dat > onlineAccessNot.dat
head -n100 hasrev_Positive.dat > hasReview.dat
head -n100 hasrev_Negative.dat > hasReviewNot.dat
EOF
chmod +x reduceFileSize.sh
```



After this update, test run the suite. If data is now found, then these new files can be checked into git, and the maintanance is complete.
Run the @specialtests in the 99-maintanance.feature to check that the files are valid.
