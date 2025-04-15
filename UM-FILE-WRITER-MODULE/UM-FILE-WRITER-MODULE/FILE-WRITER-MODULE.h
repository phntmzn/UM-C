//
//  FILE-WRITER-MODULE.h
//  12. MIDI file writer module   UM-FILE-WRITER-MODULE
//
//  Created by bRx86 on 4/15/25.
//

#ifndef FILE_WRITER_MODULE_h
#define FILE_WRITER_MODULE_h

#include <stdio.h>
#include <AudioToolbox/AudioToolbox.h>
#include <CoreMIDI/CoreMIDI.h>

void write_midi_file(const char *filename);

#endif /* FILE_WRITER_MODULE_h */
