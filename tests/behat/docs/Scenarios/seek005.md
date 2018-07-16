# Scenario: Seek005

Search using typing of enter

and

Search using click search button

Attempting searching as a user will perform the search
by typing in and either clicking the search button with the mouse or 
by pressing enter on the keyboard.

The test is split in 2 scenarios.

## Method

To test it starts by placing the browser on the start page
(base url), and then it types characters one by one into
the søg-field. The field is identified using a user-friendly alias,
which is translated to a CSS search string using a hard-coded procedure.
_(This would be better to be placed in a file or database)_.

The code then scrolls to the CSS search string object and clicks on it.
This resembles what the user will do - clicking into
the field. (The code does not resemble tabbing).

The string given in the gherkin script will then be typed in, character
by character, but with special keys preceded by a \.
\n is newline. \t is tab. More could be added, but aren't at the time being.

The script ends with "Then the paging allows to get all the results".
This basically reads in the search result, and by doing so it will
notify the user if no search was performed.

## Notes
