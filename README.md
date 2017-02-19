## Intro

sTimeline application helps in creating and maintaining records of historical or
fictional events. You can record events and all neighbouring pieces of
information, people relevant to the story, maps of the locations, various
important artifacts.

It is especially suited for writers, but can also be used by historians, or
anybody who wants to write a family chronicle or record some information about
some events for future reference.

Apart from events arranged in a timeline, the app allows to specify accompanying
information, background descriptions, biographies of people and objects.

sTimeline supports arbitrary time systems (you can define your own calendar and
time rules), which can be especially useful for science fiction and fantasy
authors.

## Events

Each event has a title, description and a start date. Optionally an end date can
be provided (if given situation took longer), and a picture (JPG, PNG) can be
added as well.

Events can be viewed as a chonological list ("Events" tab) or on a timeline
("Timeline" tab - WIP), which also shows the time between the events and their
duration. The timeline can be zoomed and panned around using mouse (on desktops)
or fingers (on touch screens).

## Calendar systems

The default timeline uses our standard, Gregorian calendar. However, you can
always define your own - completely arbitrary - calendar system. That means you
can define how many months there are (and their names), how many days there are
in each month, length of week etc.

Currently a calendar system can only be defined by modifying a saved JSON
maually (see the "Calendar" tag). A nice GUI for that is in the making.

## File support

sTimeline supports 2 major file saving "architectures":
 - compressed saves (.tmln)
 - uncompressed (open) saves (.json)

Both are very alike. In fact, a TMLN file is just a simple ZIP archive made from
the JSON type + all aditional artifacts (pictures).

## Compiling

sTimeline requires Qt 5.8 and QUazip library. You can build it by simply running
qmake and make, or you can use Qt Creator.

## Licenses

sTimeline is Free Software, for details see LICENSE.md file.

sTimeline depends on Qt Framework and QuaZIP library.
