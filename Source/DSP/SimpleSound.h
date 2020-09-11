//
// Created by zigen on 2020/09/09.
//

#ifndef SIMPLESYNTH_SIMPLESOUND_H
#define SIMPLESYNTH_SIMPLESOUND_H

#include <JuceHeader.h>

class SimpleSound : public SynthesiserSound {
 public:
  SimpleSound(const BigInteger &notes, const BigInteger &channels);

  virtual ~SimpleSound();

  virtual bool appliesToNote(int midiNoteNumber) override;

  virtual bool appliesToChannel(int midiChannel) override;

 private:
  BigInteger midiNotes;
  BigInteger midiChannels;
};

#endif  // SIMPLESYNTH_SIMPLESOUND_H
