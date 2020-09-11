//
// Created by zigen on 2020/09/09.
//

#include "SimpleSound.h"

SimpleSound::SimpleSound(const BigInteger &notes, const BigInteger &channels) : midiNotes(notes), midiChannels(channels) {}

SimpleSound::~SimpleSound() {}

bool SimpleSound::appliesToNote(int midiNoteNumber) { return midiNotes[midiNoteNumber]; }

bool SimpleSound::appliesToChannel(int midiChannel) { return midiChannels[midiChannel]; }