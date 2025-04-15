//
//  STEP-SEQUENCER-ENGINE.h
//  UM-STEP-SEQUNCER-ENGINE
//
//  Created by bRx86 on 4/15/25.
//

#ifndef STEP_SEQUENCER_ENGINE_h
#define STEP_SEQUENCER_ENGINE_h

#include <stdio.h>
#include <CoreMIDI/CoreMIDI.h>

#define NUM_STEPS 16
#define TEMPO_BPM 120
#define TICKS_PER_BEAT 24

void initialize_sequencer(void);
void run_sequencer(void);
void send_note_on(int note);
void send_note_off(int note);

extern int steps[NUM_STEPS];
extern MIDIClientRef midiClient;
extern MIDIPortRef midiOutPort;
extern MIDIEndpointRef dest;

#endif /* STEP_SEQUENCER_ENGINE_h */
