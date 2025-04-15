//
//  FILE-WRITER-MODULE.c
//  12. MIDI file writer module   UM-FILE-WRITER-MODULE
//
//  Created by bRx86 on 4/15/25.
//

#include "FILE-WRITER-MODULE.h"
#include <AudioToolbox/AudioToolbox.h>
#include <CoreMIDI/CoreMIDI.h>
#include <stdio.h>

void write_midi_file(const char *filename) {
    MusicSequence sequence;
    NewMusicSequence(&sequence);

    MusicTrack track;
    MusicSequenceNewTrack(sequence, &track);

    MIDINoteMessage note = {60, 100, 1, 1.0, 0};
    MusicTimeStamp time = 0;

    for (int i = 0; i < 8; i++) {
        MusicTrackNewMIDINoteEvent(track, time, &note);
        time += 1.0;
    }

    CFURLRef fileURL = CFURLCreateFromFileSystemRepresentation(NULL, (const UInt8 *)filename, (CFIndex)strlen(filename), false);
    MusicSequenceFileCreate(sequence, fileURL, kMusicSequenceFile_MIDIType, kMusicSequenceFileFlags_EraseFile, 480);
    CFRelease(fileURL);
    DisposeMusicSequence(sequence);

    printf("MIDI file written to: %s\n", filename);
}
