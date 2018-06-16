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

## Audio Output approaches
Problem: The teensy can not reliably play more than 2 audio clips at a time.
Play an audio clip only after enter was pressed.
Play synth sounds before hand.
Play audio clips from a raspberry pii via midi from teensy.
I can use puredata or there might be a simpler approach.
Play really short percussive type sounds.

## Plan of action
test playing any wave sounds and synth sounds out of the teensy audio shield
