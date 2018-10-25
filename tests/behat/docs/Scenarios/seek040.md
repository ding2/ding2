# Scenario: Seek040

Creator Descriptions show and no show.

Using known data, objects are shown and it's determined that creator descriptions are shown (and not) when expected.

## Method
This test uses the data manager module, and sets the filename. These files are actually created 
using an extract from opensearch, automatically. 
There's a documentation entry on the data manager class in the guideline document and data files.

This test is divided into two scenarios.

Both sets the filename to be used, and then displays a random object from that file. Notice that some objects takes a long time to display, if they've not been selected recently from the opensearch service. This can be due to a test service limitation?

**Then a 'hasCreatorDescription' entry is shown** 

will check if the creator description is shown by looking for the class being present. hasCreatorDescription is translated to the technical term, meaning the css class. 



## Notes
The conversion to technical terms should probably 'live' in the data manager object, instead of being hard coded.

This is currently excluded from CCI because the dataset there cannot be determined.