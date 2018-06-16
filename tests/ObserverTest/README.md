# Daniels Teensy Observer Tutorial
## Goal is to make a game like input->led->audio interactive installation

In this project I am learning the observer design pattern.
Although this might not be the best use case for this pattern I am interested
in applying it to what I am working on now to see how it can help decouple
my problems with user input, audio, and led light patterns.

The plan is to have the inputs class inherit from a subject class and the
led light patterns be observers. Then the light patterns would register with
the inputs class to receive notifications from it when buttons are pressed.

An audioPlayer class could also subscribe to the inputs to begin play audio
clips when certain inputs are pressed.

The inputs class will use just regular buttons for now. Then get upgraded to
use a MCP23017 port expender. If the tests are satisfactory this can be used
with the Analog inputs for the ctrlH ToorCamp installation.
