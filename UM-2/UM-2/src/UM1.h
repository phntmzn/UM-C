//
//  UM1.h
//  UM-2
//
//  Created by bRx86 on 4/15/25.
//

#ifndef UM1_h
#define UM1_h

#include <CoreMIDI/CoreMIDI.h>
#include <CoreServices/CoreServices.h>
#include <mach/mach_time.h>
#include <unistd.h>
#include <stdio.h>

// Initialize MIDI client and port
void initializeMIDI(void);

// Send a MIDI note with scheduling
void sendMIDINote(UInt8 note, UInt8 velocity, UInt8 channel, UInt64 delay_ms);

// Tear down MIDI connections
void teardownMIDI(void);

#endif /* UM1_h */
