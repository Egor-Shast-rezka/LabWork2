/*
    Egor Shastin st129457@student.spbu.ru
    
*/


#include "music.h"


// ========== SoundGenerator ==========
SoundGenerator::SoundGenerator() : amplitude(0.5), frequency(440.0) {}
SoundGenerator::~SoundGenerator() {}
    
void SoundGenerator::setAmplitude(double amp) {

    amplitude = amp;
}
void SoundGenerator::setFrequency(double freq) {

    frequency = freq;
}
double SoundGenerator::getAmplitude() const {

    return amplitude;
}
double SoundGenerator::getFrequency() const {

    return frequency;
}


// ========== SineWaveGenerator ==========
double SineWaveGenerator::generateSample(double time) const override {
    return amplitude * sin(2.0 * M_PI * frequency * time);
}


// ========== SquareWaveGenerator ==========
double SquareWaveGenerator::generateSample(double time) const override {
    return (sin(2.0 * M_PI * frequency * time) >= 0) ? amplitude : -amplitude;
}


// ========== SawWaveGenerator ==========
double SawWaveGenerator::generateSample(double time) const override {
    return 2.0 * amplitude * (time * frequency - floor(time * frequency + 0.5));
}


// ========== TriangleWaveGenerator ==========
double TriangleWaveGenerator::generateSample(double time) const override {
    double period = 1.0 / frequency; // Period of the wave
    double normalizedTime = fmod(time, period); // Normalize the time

    // Triangle wave formula
    return amplitude * (2.0 * fabs(2.0 * normalizedTime / period - 1.0) - 1.0);
}


// ========== NoiseGenerator ==========
NoiseGenerator::NoiseGenerator() : rng(std::random_device{}()), dist(-1.0, 1.0) {}
    
double NoiseGenerator::generateSample(double) const override {
    return amplitude * dist(rng);
}


// ========== AudioEngine ==========
static int AudioEngine::audioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData) {
    
    AudioEngine *engine = static_cast<AudioEngine*>(userData);
    float *buffer = static_cast<float*>(outputBuffer);

    // Error handling for underrun or overflow
    if (status == RTAUDIO_INPUT_OVERFLOW || status == RTAUDIO_OUTPUT_UNDERFLOW) {
        
        std::fill(buffer, buffer + nBufferFrames, 0.0f);
    }

    // Generate audio samples
    for (unsigned int i = 0; i < nBufferFrames; i++) {
        
        buffer[i] = engine->generator->generateSample(engine->time);
        engine->time += 1.0 / 44100.0;  // Increment time based on sample rate (44100 Hz)
    }

    return 0;
}

AudioEngine::AudioEngine() : generator(nullptr), time(0.0) {
    
    if (rtAudio.getDeviceCount() < 1) {
        
        throw std::runtime_error("No audio devices found!");
    }
}

void AudioEngine::setGenerator(SoundGenerator* gen) {
    
    generator = gen;
}

void AudioEngine::start(double duration) {
    
    if (!generator) {
        
        throw std::runtime_error("No sound generator set!");
    }

    RtAudio::StreamParameters parameters;
    parameters.deviceId = rtAudio.getDefaultOutputDevice();
    parameters.nChannels = 1;
    parameters.firstChannel = 0;
    unsigned int bufferFrames = 2048;

    try {
        
        rtAudio.openStream(&parameters, nullptr, RTAUDIO_FLOAT32, 44100, &bufferFrames, &audioCallback, this);
        rtAudio.startStream();
            
        // Run for the specified duration
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(duration * 1000)));

        rtAudio.stopStream();
        rtAudio.closeStream();
    }
    catch (...) {
        
        std::cerr << "Unknown error in RtAudio!" << std::endl;
    }
}


// ========== RandomMelodyGenerator ==========
RandomMelodyGenerator::RandomMelodyGenerator() : tempo(120.0) {
    
    rng.seed(std::random_device{}());
}
    
void RandomMelodyGenerator::setScale(const std::vector<double>& newScale) {
    
    scale = newScale;
    distribution = std::uniform_int_distribution<size_t>(0, scale.size() - 1);
}
    
void RandomMelodyGenerator::setTempo(double bpm) {
    
    tempo = bpm;
}
    
double RandomMelodyGenerator::getTempo() const {
    
    return tempo;
}
    
double RandomMelodyGenerator::getNextFrequency() {
    
    if (scale.empty()) {
        
        return 440.0; // Default to A4 if no scale is set
    }
    return scale[distribution(rng)];
}


// ========== InfiniteMelodyPlayer ========== 
InfiniteMelodyPlayer::InfiniteMelodyPlayer(AudioEngine& eng, RandomMelodyGenerator& melodyGen) : engine(eng), melodyGenerator(melodyGen) {}

// Set available generators (Lite version)
void InfiniteMelodyPlayer::setGenerators(const std::vector<SoundGenerator*>& genList) {
    
    generators = genList;
}

// Add predefined music parts (sequences of notes) for playback
void InfiniteMelodyPlayer::setMelodyParts(const std::vector<std::vector<double>>& parts) {
    
    melodyParts = parts;
}

// Infinite random melody with randomly chosen sound generators (Lite version)
void InfiniteMelodyPlayer::startInfinite_Lite() {
    
    while (true) {
        
        SoundGenerator* currentGenerator = generators[std::rand() % generators.size()];
        engine.setGenerator(currentGenerator);
        double frequency = melodyGenerator.getNextFrequency();
        currentGenerator->setFrequency(frequency);
        engine.start(0.05);  // Play each note for 0.05 seconds
        std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Wait for the note to finish
    }
}

// Infinite playback of predefined melody parts
void InfiniteMelodyPlayer::startInfinite_Part() {
    
    size_t partIndex = 0; // Index for cycling through parts
        
    while (true) {
        
        // Get the current part sequence from melodyParts
        std::vector<double> part = melodyParts[partIndex];

        for (double frequency : part) {
            
            // Select a random generator for each note
            SoundGenerator* currentGenerator = generators[std::rand() % generators.size()];
            engine.setGenerator(currentGenerator);
            currentGenerator->setFrequency(frequency);
            engine.start(0.1); // Play each note for 0.2 seconds
            std::this_thread::sleep_for(std::chrono::milliseconds(250)); // Wait for the note to finish
        }

        // Cycle through the parts (there are 4 parts)
        partIndex = (partIndex + 1) % melodyParts.size();
    }
}

// Infinite playback of "In the grass sat the grasshopper" melody
void InfiniteMelodyPlayer::startInfinite_Melody_1() {

    // "In the grass sat the grasshopper" melody
    std::vector<double> melody = {
    293.66, 330.00, 349.23, 349.23, 330.00, 293.66, 330.00, 349.23, 349.23, 330.00, 293.66, // "In the grass"
        440.00, 493.88, 523.25, 523.25, 493.88, 440.00, 493.88, 523.25, 523.25, 493.88, 440.00, // "sat the grasshopper"
        466.16, 440.00, 466.16, 440.00, 466.16, 440.00, 466.16, 440.00
    };

    while (true) {
        
        for (double frequency : melody) {
            
            // Select a random generator for each note
            SoundGenerator* currentGenerator = generators[std::rand() % generators.size()];
            engine.setGenerator(currentGenerator);
            currentGenerator->setFrequency(frequency);
            engine.start(0.3);  // Play each note for 0.3 seconds
            std::this_thread::sleep_for(std::chrono::milliseconds(350));  // Wait for the note to finish
        }
    }
}
