//
//  PATTERN-MUTATION.h
//  UM-PATTERN-MUTATION
//
//  Created by bRx86 on 4/15/25.
//

#ifndef PATTERN_MUTATION_h
#define PATTERN_MUTATION_h

#include <stdint.h>
#include <CoreMIDI/CoreMIDI.h>

#define MAX_PATTERN_LENGTH 128

// MIDI note structure
typedef struct {
    uint8_t note;
    uint8_t velocity;
    uint64_t delay_ms;
} MIDINote;

// Pattern structure
typedef struct {
    MIDINote notes[MAX_PATTERN_LENGTH];
    int length;
} MIDIPattern;

// Initialize a pattern with random notes
void generateRandomPattern(MIDIPattern *pattern, int length);

// Apply mutation to an existing pattern
void mutatePattern(MIDIPattern *pattern, float mutation_rate);

// Print and send pattern using CoreMIDI
void printPattern(const MIDIPattern *pattern);

#endif /* PATTERN_MUTATION_h */
