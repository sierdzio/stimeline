Short and incomplete list of what is left to be done here:

- unit tests, especially for SEvent, STimeline, SCalendar and SDateTime classes
- whole GUI, obviously
- support for file attachments
- nice GUI for timeline, with smooth zooming and swiping (EventTimeline)
- use magic macros for Q_OBJECTS
- add null datetime (when it is not set)
- object description - text elide fixes + add ability to expand the item to show
  whole text
- clean up temp dir after using it (save/ load)
- BUG: sometimes it is not possible to edit datetime (Android?)
- BUG: popups do not fit on Android
- make Android Intent use ContentProvider to share files
- prompt for storage permission
- "event folding" into "chapters". Add ability to group events together
  and fold (hide) all these events under single item. User can click "+" button
- add tags for events/ objects
- add searching/ filtering
- close event editor when Enter is pressed
- Check dirty before exiting (do you want to save changes?)
- add undo/ redo
- plots need to have order (because sometimes an author would like to present
  plots in different order than chronologically)
- add "chapters" - special kind of plot, which organizes objects into
  distinctive, chronological parts. Maybe some other name: Eras, Stories, Parts
