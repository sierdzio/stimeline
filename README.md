## Intro

sTimeline application helps in creating and maintaining records of historical or
fictional events.

It is especially suited for writers, but can also be used by historians, or
anybody who wants to (for example) write a family chronicle.

Apart from events arranged in a timeline, the app allows to specify accompanying
information, background descriptions, biographies of people and objects.

sTimeline supports arbitrary time systems (you can define your own calendar and
time rules), which can be especially useful for science fiction and fantasy
authors.

This is Free Software, for details see LICENSE.md file.

## File support

sTimeline supports 2 major file saving "architectures":
 - compressed saves (.tmln)
 - uncompressed (open) saves (.json)

Both are very alike. In fact, a TMLN file is just a simple ZIP archive made from
the JSON type + all aditional artifacts (pictures).

## Compiling

sTimeline requires Qt 5.8 and QUazip library. You can build it by simply running
qmake and make, or you can use Qt Creator.
