Description
-----------
The module provides D!ng-integration of the ticket booking service Place2Book.
 
Events created on a Ding-site is automatically exported to Place2book. Furthermore, Place2Book can be made to send event data to Kultunaut. This way events only have to be created, updated and deleted in one place for the data is used in 3 places, so the module saves a lot of time when handling events for the library.

Event that has tickets will include a "Book your ticket"-link. The module checks if any tickets are left on that event. If yes, the booking link is presented to the user. If the event is closed for admissions or if no tickets are available, the user instead sees an appropriate message.


Installation
------------

1. Get in touch with Place2book (www.place2book.com) and get your accounts (preferably 2 accounts, one for production and one for test).
2. Login to the respective Place2Book account(s) and copy API-key(s) from the page [https://www.place2book.com/da/event_makers#tab4](https://www.place2book.com/da/event_makers#tab4).
3. Configure the ding_place2book module at Administration > Site Configuration > Ding! > Place2book settings.


Configuration of the module
---------------------------

### Settings in the administration section (/admin/settings/ding/place2book)

* "Place2Book service URL": must point to the event api at Place2Book. Currently, this is  [https://www.place2book.com/da/event_api](https://www.place2book.com/da/event_api).

* "Place2Book base API key": contains the generic API key when connecting to the  Place2book API. It is possible to have separate API keys for each library on the ding site - see below. For more information on the Place2Book API, see [https://github.com/place2book/place2book-api/wiki](https://github.com/place2book/place2book-api/wiki).

* "API key {LIBRARY NAME}": One of these is provided for each library set up on the ding site. When an API key is provided for a specific library, this key will override the generic key when editing events related to that library.
 
* "Place2Book event node defaults": The values set here will be the standard values applied to every new event created on the site. Their meaning is explained in the section below. 

### Setting at Event Node edit pages (/node/add/event + /node/#/edit)

Most of the fields on the add/edit event form are mapped directly to corresponding values on the related events created at Place2Book. 

A few fields and/or settings specific to Place2Book have been added to the form. These are:

* **Ekstra information for Event price**: Text reminding the user how event price connects to a ticket on Place2Book.

* **"Event capacity"**: Amount of tickets available at this event. This can be set to 0 for unlimited capacity/number of tickets.

* **"Place2book"**: The Place2Book settings specific to this event (found at the bottom of the form). These take standard values from the settings set at /admin/settings/ding/place2book. They include:

    **Maintain copy**: The event is created and updated at Place2Book. It can be set after the ding event has been created - this will create the related Place2Book event and keep it updated thereafter. It can also be unset at a later date, in which case the corresponding Place2Book event will be deleted (what could be called "severing the link to Place2Book"). Deleting a ding event will also delete the related Place2Book event.

    **Place2Book ID**: This number is the ID of the related event at Place2Book. It is made as a link for easy access to the more elaborate settings at the Place2Book event.

    **Kultunaut Export**: If set, the ding event will also be sent to Kultunaut for exposing the event at that site. 

    **Passive Event**: If set, there will be no ticket sale at Place2Book. Furthermore, the ding site will not display a "Book Ticket"-link for that event.

### Presenting ticket information at Event Node view page (/node/#)

There are 2 options for showing the order link button/ticket information box on the page:

* **Inside the node content (default)**. The module has inserted a placeholder field inside the node content. When viewing the event, this placeholder is filled with ticket information pulled real-time from www.place2book.com. However, node content i normally cached - therefore, enabling this module turns off caching inside the Node Template->Event Variant's node content panel pane. 

* **As a panel pane**. In order for administrators to place the ticket information where they want on the event pages, a pane named "Place2book ticket info" is provided with the module (it can be found in the group "Ding!" among the panel panes). Remember to never put any caching on this pane - it shows real-time information!

Modifying the standard ding2 caching for events (as with the default option above) may NOT be what the site administrator wants.
If so, you WILL have to use the second option, as the "Place2book ticket info" pane has its own
cache settings separate from the node content pane.

To use the second option instead of the default above, do the following:
1. Go to the Node Template under Pages (/admin/structure/pages/edit/node_view) and open the Event variant's Content.
2. Add content to the area of the panel you want. The "Place2book ticket info" pane is found under the group "Ding!". Now, you have 2 places where ticket info is shown
3. Click on settings for the "Node being viewed" content pane. Under "Caching", click "Change". Set it back to "Rules-based cache" - the specific settings here are Granularity: "Context" and "Cache per language" ON. You have now restored the original cache settings for the node content.    
4. Go to manage the display for the Event Node content type (/admin/structure/types/manage/ding-event/display). Move the field "Place2book Tickets" into the Hidden area, and save. You should now have event pages that only show ticket information once (via the pane you placed in step 2).

Usage and Tips
--------------

### Place2Book accounts

Each library on the ding site can have their own account/event maker at Place2Book. Be sure to ask for your accounts to be set up accordingly when contacting Place2Book. 

### Place2Book as a one-place list of event attendance

Some libraries have events they do not wish to connect to Place2Book because they cannot see any benefit in selling tickets. However, using Place2Book for keeping record of event attendance regardless of ticket sale can be beneficial (for the library statistics, for instance). The setting *Passive event* can be used for this purpose. For an event, set *Maintain Copy* AND *Passive Event*.  

### Kultunaut

In effect, Place2Book keeps event information and relays it to Kultunaut. An image is sent to Kultunaut for the event. The list image on the event node is reused for this. The ding2-specific taxonomy *Category* is reused for Kultunauts *Age Group*. For Kultunauts *Category*, a new field has been added to the Ding Event insert/update form. 

In most cases, Kultunauts values for *Age Group* (Alle, Børn, Unge, Voksne og Ældre) will not be the same at the terms set up by a library in its taxonomy *Category*. *Category* is therefore mapped to the correct kultunaut categories - the settings for this is found at Configuration -> Ding -> Place2book settings -> Kultunaut (admin/config/ding/place2book/kultunaut). Be sure to apply your mappings here where applicable.    

The module can be used solely for transmitting event data to Kultunaut (in effect only using the Place2book service for relaying data). At the settings for an event, set Maintain copy, Kultunaut Export AND Passive Event. The event will not have ticket sale on Place2Book nor a booking link on the ding site, but information will be sent to Kultunaut.


Version information
-------------------

Version-specific information can be seen in connection with the available downloads (tagged versions) at:

https://github.com/ding2/ding_place2book/tags

