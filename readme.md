# macOS Date & Time

In macOS, TODO

## Running

`make`

## Results

There are two options for configuring date and time in macOS:

### System Preferences > Date & Time > Clock > Show date and time in menu bar

There are these two settings:

- Use a 24-hour clock
- Show AM/PM

**These settings only apply to the menu bar!**

### System Preferences > Languages & Region > General

There is the **24-Hour Time** setting.

Wherever the program here is ran with or without this switch toggled, the
results always seem to indicate the `a` token in the time format strings
if it is included in the System Preferences > Language & Region > General >
Advanced > Times. If the AM/PM (`a`) token is removed in these fields, then
it doesn't appear in the output anymore.

## To-Do

### Find out why the `a` token doesn't get removed when the toggle is switched off
