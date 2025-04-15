#ifndef MARKOV_CHAIN_GENERATOR_h
#define MARKOV_CHAIN_GENERATOR_h

#include <CoreMIDI/CoreMIDI.h>
#include <stdio.h>

#define NUM_NOTES 5
#define NOTE_DURATION_MS 300

void initialize_markov_generator(void);
void run_markov_melody(void);
void send_markov_note_on(int note);
void send_markov_note_off(int note);
int choose_next_note(int current);

extern MIDIClientRef markovClient;
extern MIDIPortRef markovOutPort;
extern MIDIEndpointRef markovDest;
extern int notes[NUM_NOTES];
extern float transition[NUM_NOTES][NUM_NOTES];

#endif /* MARKOV_CHAIN_GENERATOR_h */
