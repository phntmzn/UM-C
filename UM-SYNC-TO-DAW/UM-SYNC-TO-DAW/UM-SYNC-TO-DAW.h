//
//  UM-SYNC-TO-DAW.h
//  UM-SYNC-TO-DAW
//
//  Created by bRx86 on 4/15/25.
//

#ifndef UM_SYNC_TO_DAW_h
#define UM_SYNC_TO_DAW_h

#include <CoreMIDI/CoreMIDI.h>
#include <stdio.h>

#define SYNC_BPM 120
#define MIDI_CLOCK_RATE_US (500000 / 24)

void initialize_daw_sync(void);
void send_midi_clock(void);
void send_start_signal(void);
void run_daw_sync_loop(void);

extern MIDIClientRef syncClient;
extern MIDIPortRef syncOutPort;
extern MIDIEndpointRef dawDest;

#endif /* UM_SYNC_TO_DAW_h */
