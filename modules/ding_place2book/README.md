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

### Settings in the administration section (/admin/config/ding/place2book)
Represents form for defining URLs to p2b service. On current moment module works with second version of p2b service.
Additional info can be found - http://developer.place2book.com.

* "Place2Book service URL" - point to P2b service [https://apitest.place2book.com].

* "Place2Book authorisation token" - contains the generic API key when connecting to the  Place2book API. It is possible to have separate API keys for each library on the ding site - see below.

* "Place2Book event makers URL" -  point for getting all available event makers[https://apitest.place2book.com/event_makers].

* "Place2Book get event URL" - point for getting event from P2b service [https://apitest.place2book.com/event_makers/:event_maker_id/events/:event_id].

* "Place2Book update event URL" - point for updating event on P2b service [https://apitest.place2book.com/event_makers/:event_maker_id/events/:event_id].

* "Place2Book delete event URL" - point for deleting event on P2b service [https://apitest.place2book.com/event_makers/:event_maker_id/events/:event_id].

* "Place2Book create event URL" - point for creating event on P2b service [https://apitest.place2book.com/event_makers/:event_maker_id/events].

* "Place2Book create price URL" - point for creating price on P2b service [https://apitest.place2book.com/event_makers/:event_maker_id/events/:event_id/prices].

* "Place2Book get prices of event URL"  - point for getting all prices of event [https://apitest.place2book.com//event_makers/:event_maker_id/events/:event_id/prices].

* "Place2Book get price URL" - point for getting price of event by id from P2b service [https://apitest.place2book.com//event_makers/:event_maker_id/events/:event_id/prices/:price_id].

* "Place2Book update price URL" - point for updating price of event by id on P2b service [https://apitest.place2book.com//event_makers/:event_maker_id/events/:event_id/prices/:price_id].

* "Place2Book delete price URL" - point for deleting price of event by id on P2b service [https://apitest.place2book.com//event_makers/:event_maker_id/events/:event_id/prices/:price_id].


### Settings of default values (/admin/config/ding/place2book/defaults)

This form represents settings for configuration defaults values for different options.

* "Default event maker: - Represents default event maker for creating events in P2b. It will be used in case when mapping for some library will be missed or event will be created without reference to some library.

* "Maintain copy" - If it will be checked, then by defualt on creating event, checkbox "Mantain copy" will be checked and event will be created on P2b.

* "Kultunaut export" - If it will be checked, then by defualt on creating event, checkbox " Kultunaut export" will be checked and event will be exported to Kultuanut.

* "Passive event" - If it will be checked, then by default on creating event, checkbox Passive will be checked and event will be marked as Passive. It means that event can doesnt have any price.

* "Capacity" -  Default value of price. If 0 - it means unlimited.

* "Ticket type" - Type of price. E. g. Adult, Child or Standard. Adgang is the default ticket type.


### Settings of mappings (admin/config/ding/place2book/mappings)

Represents mappings for terms of events. It means what here you can map each category of event to some value on p2b.

And when user will choose a category automatically will be add some info to event on P2b.

* "EVENT MAKERS" - Associate each library with some event maker.

* "KULTUNAUT AGE GROUP" - Associate each event target with kultunaut age group.

* "KULTUNAUT EXPORT CATEGORY" - Associate each event target with kultunaut age group.

### Presenting ticket information at Event Node view page (/node/#)

There are 1 options for showing the order link button/ticket information box on the page:

* **Inside the node content (default)**. The module has inserted a placeholder field inside the node content. When viewing the event, this placeholder is filled with ticket information pulled real-time from www.place2book.com. However, node content i normally cached - therefore, enabling this module turns off caching inside the Node Template->Event Variant's node content panel pane.

Modifying the standard ding2 caching for events (as with the default option above) may NOT be what the site administrator wants.

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


