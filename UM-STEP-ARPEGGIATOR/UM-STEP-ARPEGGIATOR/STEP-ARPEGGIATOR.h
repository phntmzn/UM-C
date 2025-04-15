#ifndef STEP_SEQUENCER_ENGINE_h
#define STEP_SEQUENCER_ENGINE_h

#include <CoreMIDI/CoreMIDI.h>
#include <stdio.h>

#define NOTE_DURATION_MS 250
#define ARP_BPM 120

void initialize_arpeggiator(void);
void run_arpeggiator(void);
void send_arp_note_on(int note);
void send_arp_note_off(int note);

extern MIDIClientRef arpeggiatorClient;
extern MIDIPortRef arpeggiatorOutPort;
extern MIDIEndpointRef arpeggiatorDest;
extern int arpeggioNotes[];
extern int numNotes;

#endif /* STEP_SEQUENCER_ENGINE_h */
