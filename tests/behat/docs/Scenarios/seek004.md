# Scenario: seek004

Show openscan suggestions in search field.

Requires openscan to be enabled for the target site, and will check 
that suggestions are being made.

## Method

It will open the target site on the main page and type in three
hard coded letters in the search field.
It does this by entering each letter by itself, mimicking keyboard
use.
Then it pauses a bit to enable the openscan to run (it normally
takes a second or two).
After that it lists out the given suggestions. 
Because it is configurable it cannot test if the suggestions are right, only
if suggestions are given. It also cannot test if the number of
suggestions are correct.

## Notes
This is disabled on CircleCI because there seems to be no way
the openscan configuration can be enabled on the test site.