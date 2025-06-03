/*
    Egor Shastin st129457@student.spbu.ru
    
    Implementation of classes from music.h: audio stream management, random note generation,
*/


#include "music.h"


// ========== Envelope ==========

Envelope::Envelope() : attack(0.02), decay(0.1), sustain(0.7), release(0.2) {}

double Envelope::getAmplitude(double t) const {
    if (t < attack) {

        return 1.0 - exp(-t / attack * 5);
    }
    else if (t < attack + decay) {

        double decayTime = t - attack;
        double decayProgress = decayTime / decay;
        return sustain + (1.0 - sustain) * exp(-decayProgress * 4);
    }
    else if (t < noteLength - release) {

        return sustain;
    }
    else {

        double releaseTime = t - (noteLength - release);
        double releaseProgress = releaseTime / release;
        return sustain * exp(-releaseProgress * 5);
    }
}

void Envelope::setNoteLength(double length) {
    noteLength = length;
}


// ========== SoundGenerator ==========

SoundGenerator::SoundGenerator() : amplitude(0.5), frequency(440.0) {}
SoundGenerator::~SoundGenerator() {}

void SoundGenerator::setNoteStart(double t) {

    noteStartTime = t;
}

void SoundGenerator::setNoteLength(double seconds) {

    envelope.setNoteLength(seconds);
}

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


// ========== SquareWaveGenerator ==========

double SquareWaveGenerator::generateSample(double time) const {

    double t = time - noteStartTime;
    double phase = fmod(time * frequency, 1.0);
    double wave = (phase < 0.5) ? 1.0 : -1.0;
    
    double smoothing = 0.05;
    double smoothed = tanh(wave / smoothing);
    
    return amplitude * envelope.getAmplitude(t) * smoothed;
}


// ========== SawWaveGenerator ==========

double SawWaveGenerator::generateSample(double time) const {

    double t = time - noteStartTime;
    double phase = fmod(time * frequency, 1.0);
    double wave = 2.0 * (phase - 0.5);
    
    double smoothing = 0.1;
    double smoothed = tanh(wave / smoothing);
    
    return amplitude * envelope.getAmplitude(t) * smoothed;
}



// ========== TriangleWaveGenerator ==========

double TriangleWaveGenerator::generateSample(double time) const {

    double t = time - noteStartTime;
    double phase = fmod(time * frequency, 1.0);
    double wave = 4.0 * fabs(phase - 0.5) - 1.0;
    return amplitude * envelope.getAmplitude(t) * wave;
}

// ========== SineWaveGenerator ==========

double SineWaveGenerator::generateSample(double time) const {

    double t = time - noteStartTime;
    double wave = sin(2.0 * M_PI * frequency * time);
    
    double smoothing = 0.8;
    double smoothed = tanh(wave / smoothing);
    
    return amplitude * envelope.getAmplitude(t) * smoothed;
}

// ========== AudioEngine ==========

AudioEngine::AudioEngine() : generator(nullptr), time(0.0) {
    
    if (rtAudio.getDeviceCount() < 1) {
        
        throw std::runtime_error("No audio devices found!");
    }
}

double AudioEngine::getTime() const {
    return time;
}

int AudioEngine::audioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData) {
    
    AudioEngine *engine = static_cast<AudioEngine*>(userData);
    float *buffer = static_cast<float*>(outputBuffer);

    // Error handling for underrun or overflow
    if (status == RTAUDIO_INPUT_OVERFLOW || status == RTAUDIO_OUTPUT_UNDERFLOW) {
        
        std::fill(buffer, buffer + nBufferFrames, 0.0f);
    }

    // Generate audio samples
    for (unsigned int i = 0; i < nBufferFrames; i++) {
        
        buffer[i] = engine->generator->generateSample(engine->time);
        engine->time += 1.0 / 44100.0; // Increment time based on sample rate (44100 Hz)
    }

    return 0;
}

void AudioEngine::setGenerator(SoundGenerator* gen) {
    
    generator = gen;
}

void AudioEngine::start() {
    if (!generator) {
        throw std::runtime_error("No sound generator set!");
    }

    if (rtAudio.isStreamOpen()) return;

    RtAudio::StreamParameters parameters;
    parameters.deviceId = rtAudio.getDefaultOutputDevice();
    parameters.nChannels = 1;
    parameters.firstChannel = 0;
    unsigned int bufferFrames = 1024;

    try {
        rtAudio.openStream(&parameters, nullptr, RTAUDIO_FLOAT32, 44100, &bufferFrames, &audioCallback, this);
        rtAudio.startStream();
    } catch (...) {
        std::cerr << "Unknown error in RtAudio.\n";
    }
}

bool AudioEngine::isStreamRunning() const {
    return rtAudio.isStreamRunning();
}

void AudioEngine::stop() {
    if (rtAudio.isStreamRunning()) {
        try {
            rtAudio.stopStream();
        } catch (...) {
            std::cerr << "Error stopping stream.\n";
        }
    }
}

void AudioEngine::cleanup() {
    if (rtAudio.isStreamOpen()) {
        try {
        
            rtAudio.stopStream();
            rtAudio.closeStream();
            
        } catch (...) {
            std::cerr << "Error cleaning up audio stream.\n";
       }
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
        
        return 440.0;
    }
    return scale[distribution(rng)];
}


// ========== InfiniteMelodyPlayer ========== 

InfiniteMelodyPlayer::InfiniteMelodyPlayer(AudioEngine& eng, RandomMelodyGenerator& melodyGen) : engine(eng), melodyGenerator(melodyGen) {}

// Set available generators (Lite version)
void InfiniteMelodyPlayer::setGenerators(std::vector<std::unique_ptr<SoundGenerator>> genList) {

    generators = std::move(genList);
}

// Add predefined music parts (sequences of notes) for playback
void InfiniteMelodyPlayer::setMelodyParts(const std::vector<std::vector<double>>& parts) {
    
    melodyParts = parts;
}

// Infinite random melody with randomly chosen sound generators
void InfiniteMelodyPlayer::startInfinite_Lite() {
    while (true) {
        if (generators.empty()) {
            std::cerr << "ERROR: Generator list is empty!\n";
            return;
        }

        SoundGenerator* currentGenerator = generators[rand() % generators.size()].get();
        engine.setGenerator(currentGenerator);
        engine.start();

        double frequency = melodyGenerator.getNextFrequency();
        double duration = 0.5 + (rand() % 100) / 200.0;

        currentGenerator->setFrequency(frequency);
        currentGenerator->setNoteStart(engine.getTime());
        currentGenerator->setNoteLength(duration);

        std::this_thread::sleep_for(std::chrono::milliseconds(int(duration * 1000)));
    }
}

// Infinite playback of predefined melody parts
void InfiniteMelodyPlayer::startInfinite_Part() {
    size_t partIndex = 0;

    while (true) {
        if (melodyParts.empty() || generators.empty()) {
            std::cerr << "ERROR: Melody parts or generator list is empty!\n";
            return;
        }

        const std::vector<double>& part = melodyParts[partIndex];

        for (double frequency : part) {

            SoundGenerator* currentGenerator = generators[rand() % generators.size()].get();
            engine.setGenerator(currentGenerator);
            engine.start();

            double duration = 0.4 + (rand() % 100) / 200.0;

            currentGenerator->setFrequency(frequency);
            currentGenerator->setNoteStart(engine.getTime());
            currentGenerator->setNoteLength(duration);

            std::this_thread::sleep_for(std::chrono::milliseconds(int(duration * 1000)));
        }

        partIndex = (partIndex + 1) % melodyParts.size();
    }
}

// Infinite playback of "In the grass sat the grasshopper" melody
void InfiniteMelodyPlayer::startInfinite_Melody_1() {
    // "In the grass sat the grasshopper" melody
    std::vector<double> melody = { 
        293.66, 330.00, 349.23, 349.23, 330.00, 293.66, 330.00, 349.23, 349.23, 330.00, 293.66, // "In the grass"
        440.00, 493.88, 523.25, 523.25, 493.88, 440.00, 493.88, 523.25, 523.25, 493.88, 440.00, // "sat the grasshopper"
        466.16, 440.00, 466.16, 440.00, 466.16, 440.00, 466.16, 440.00,                         // hopping motif
        392.00, 440.00, 392.00, 349.23, 392.00, 440.00,                                         // "Just like a cucumber"
        349.23, 329.63, 293.66, 329.63, 349.23, 293.66                                          // "He was green."
    };

    std::vector<double> durations = {
        0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.8,  // "In the grass"
        0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.8,  // "sat the grasshopper"
        0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.8,                 // hopping motif
        0.4, 0.4, 0.4, 0.4, 0.4, 0.8,                           // "Just like a cucumber"
        0.4, 0.4, 0.4, 0.4, 0.4, 0.8                            // "He was green."
    };

    while (true) {
        for (size_t i = 0; i < melody.size(); ++i) {
            if (generators.empty()) {
                std::cerr << "ERROR: Generator list is empty!\n";
                return;
            }

            SoundGenerator* currentGenerator = generators[1].get();
            engine.setGenerator(currentGenerator);
            engine.start();

            double frequency = melody[i];
            double duration = durations[i];

            currentGenerator->setFrequency(frequency);
            currentGenerator->setNoteStart(engine.getTime());
            currentGenerator->setNoteLength(duration);

            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(duration * 1000)));
        }
    }
}


void InfiniteMelodyPlayer::stop() {
    if (engine.isStreamRunning()) {
        engine.stop();
    }
}






