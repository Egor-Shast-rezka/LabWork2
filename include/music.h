/*
    Egor Shastin st129457@student.spbu.ru
    
*/


#include <iostream>
#include <cmath>
#include <rtaudio/RtAudio.h>
#include <random>
#include <thread>
#include <chrono>
#include <vector>


#ifndef MUSIC_H
#define MUSIC_H


// ========== SoundGenerator ==========
// Base class for sound generation
class SoundGenerator {
protected:
    double amplitude; // Amplitude of the wave (0 to 1)
    double frequency; // Frequency in Hz

public:

    SoundGenerator();
    virtual ~SoundGenerator();
    
    void setAmplitude(double amp);
    
    void setFrequency(double freq);
    
    double getAmplitude() const;
    
    double getFrequency() const;
    
    virtual double generateSample(double time) const = 0;
};


// ========== SineWaveGenerator ==========
// Derived class for sine wave generation
class SineWaveGenerator : public SoundGenerator {
public:

    double generateSample(double time) const override;
};


// ========== SquareWaveGenerator ==========
// Square Wave Generator
class SquareWaveGenerator : public SoundGenerator {
public:

    double generateSample(double time) const override;
};


// ========== SawWaveGenerator ==========
// Sawtooth Wave Generator
class SawWaveGenerator : public SoundGenerator {
public:

    double generateSample(double time) const override;
};


// ========== TriangleWaveGenerator ==========
// Triangle Wave Generator
class TriangleWaveGenerator : public SoundGenerator {
public:

    double generateSample(double time) const override;
};


// ========== NoiseGenerator ==========
// Noise Generator
class NoiseGenerator : public SoundGenerator {
private:

    mutable std::mt19937 rng;
    mutable std::uniform_real_distribution<double> dist;

public:

    NoiseGenerator();
    
    double generateSample(double) const override;
};


// ========== AudioEngine ==========
// Audio Engine for playback
class AudioEngine {
private:

    RtAudio rtAudio;
    SoundGenerator* generator;
    double time;

    static int audioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData);

public:

    AudioEngine();

    void setGenerator(SoundGenerator* gen);

    void start(double duration);
};

// ========== RandomMelodyGenerator ==========
// Random Melody Generator
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
// Class to play infinite random melody, parts, or specific melody
class InfiniteMelodyPlayer {
private:

    AudioEngine& engine;
    RandomMelodyGenerator& melodyGenerator;
    std::vector<SoundGenerator*> generators;
    std::vector<std::vector<double>> melodyParts; // Store melody parts

public:

    InfiniteMelodyPlayer(AudioEngine& eng, RandomMelodyGenerator& melodyGen);

    // Set available generators
    void setGenerators(const std::vector<SoundGenerator*>& genList);

    // Add predefined music parts (sequences of notes) for playback
    void setMelodyParts(const std::vector<std::vector<double>>& parts);

    // Infinite random melody with randomly chosen sound generators
    void startInfinite_Lite();

    // Infinite playback of predefined melody parts
    void startInfinite_Part();

    // Infinite playback of "In the grass sat the grasshopper" melody
    void startInfinite_Melody_1();
};

#endif
