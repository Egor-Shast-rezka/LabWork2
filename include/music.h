/*
    Egor Shastin st129457@student.spbu.ru
    
    Header file containing classes and interfaces for generating and playing melodies.
*/


#include <iostream>
#include <cmath>
#include <memory>
#include <RtAudio.h>
#include <random>
#include <thread>
#include <chrono>
#include <vector>


#ifndef MUSIC_H
#define MUSIC_H


// ========== Envelope ==========

class Envelope {
private:
    double attack;
    double decay;
    double sustain;
    double release;
    double noteLength;

public:
    Envelope();
    double getAmplitude(double t) const;
    void setNoteLength(double length);
};


// ========== SoundGenerator ==========

class SoundGenerator {
protected:

    Envelope envelope;
    double noteStartTime;
    double amplitude;
    double frequency;

public:

    SoundGenerator();
    virtual ~SoundGenerator();
    
    void setNoteStart(double t);
    void setNoteLength(double seconds);
    void setAmplitude(double amp);
    void setFrequency(double freq);
    double getAmplitude() const;
    double getFrequency() const;
    virtual double generateSample(double time) const = 0;
};


// ========== SquareWaveGenerator ==========

class SquareWaveGenerator : public SoundGenerator {
public:

    double generateSample(double time) const override;
};


// ========== SawWaveGenerator ==========

class SawWaveGenerator : public SoundGenerator {
public:

    double generateSample(double time) const override;
};


// ========== TriangleWaveGenerator ==========

class TriangleWaveGenerator : public SoundGenerator {
public:

    double generateSample(double time) const override;
};


// ========== SineWaveGenerator ==========

class SineWaveGenerator : public SoundGenerator {
public:

    double generateSample(double time) const override;
};


// ========== AudioEngine ==========

class AudioEngine {
private:

    RtAudio rtAudio;
    SoundGenerator* generator;
    double time;

public:

    AudioEngine();
    
    double getTime() const;

    static int audioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData);

    void setGenerator(SoundGenerator* gen);

    void start();
    
    bool isStreamRunning() const;
    
    void stop();

    void cleanup();
};


// ========== RandomMelodyGenerator ==========

class RandomMelodyGenerator {
private:

    std::vector<double> scale; // List of allowed frequencies (notes)
    std::mt19937 rng; // Random number generator
    std::uniform_int_distribution<size_t> distribution;
    double tempo; // Beats per minute (BPM)

public:

    RandomMelodyGenerator();
    
    void setScale(const std::vector<double>& newScale);
    
    void setTempo(double bpm);
    
    double getTempo() const;
    
    double getNextFrequency();
};


// ========== InfiniteMelodyPlayer ========== 

class InfiniteMelodyPlayer {
private:

    AudioEngine& engine;
    RandomMelodyGenerator& melodyGenerator;
    std::vector<std::unique_ptr<SoundGenerator>> generators;
    std::vector<std::vector<double>> melodyParts; // Store melody parts

public:

    InfiniteMelodyPlayer(AudioEngine& eng, RandomMelodyGenerator& melodyGen);
    
    // Set available generators
    void setGenerators(std::vector<std::unique_ptr<SoundGenerator>> genList);

    // Add predefined music parts (sequences of notes) for playback
    void setMelodyParts(const std::vector<std::vector<double>>& parts);
    
    void setAudioEngine(const AudioEngine engine);
    
    void setRandomMelodyGenerator(const RandomMelodyGenerator melodyGenerator);

    // Infinite random melody with randomly chosen sound generators
    void startInfinite_Lite();

    // Infinite playback of predefined melody parts
    void startInfinite_Part();

    // Infinite playback of "In the grass sat the grasshopper" melody
    void startInfinite_Melody_1();
    
    void stop();
};


#endif
