#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GGGainAudioProcessor::GGGainAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    )
#endif
{
}

GGGainAudioProcessor::~GGGainAudioProcessor() = default;

//==============================================================================
void GGGainAudioProcessor::prepareToPlay(double sampleRate, int)
{
    currentSampleRate = sampleRate;
    gainLin.reset(sampleRate, 0.005);
    gainLin.setTargetValue(1.0f);

    // Reset phase to avoid clicks
    feel.phase = 0.0f;

    // Initialize un-age smoother
    unAgeAmount.reset(sampleRate, 0.005f);
    unAgeAmount.setCurrentAndTargetValue(0.0f);
}

void GGGainAudioProcessor::releaseResources() {}

void GGGainAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;

    // Clear unused output channels
    for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // Get parameter values
    const float ageParam = apvts.getRawParameterValue("age")->load();
    const float feelParam = apvts.getRawParameterValue("feel")->load();
    const float gainParam = apvts.getRawParameterValue("gain")->load();
    const float unAgeAmt = apvts.getRawParameterValue("unAge")->load() * 0.01f;

    gainLin.setTargetValue(juce::Decibels::decibelsToGain(gainParam));

    // Age-based psychoacoustic modeling
    // As age increases: boost low frequencies (presbycusis compensation)
    // and reduce high frequency sensitivity
    const float normalizedAge = ageParam / 100.0f;
    curve.lfBoost = 1.0f + 0.6f * std::pow(normalizedAge, 2.0f);
    curve.hfCut = 1.0f - 0.9f * normalizedAge;

    // Un-Age inverse curve
    unAgeAmount.setTargetValue(unAgeAmt);
    unAgeCurve.lfCut = 1.0f / curve.lfBoost;
    unAgeCurve.hfBoost = 1.0f / curve.hfCut;

    // Feel parameter controls sub-harmonic generation intensity
    feel.subLevel = feelParam * 0.25f;

    // Calculate phase increment for 40Hz sub-harmonic (tactile frequency range)
    const float subPhaseInc = 2.0f * juce::MathConstants<float>::pi * 40.0f / static_cast<float>(currentSampleRate);

    // Process each channel
    for (int ch = 0; ch < getTotalNumInputChannels(); ++ch)
    {
        float* channelData = buffer.getWritePointer(ch);
        const int numSamples = buffer.getNumSamples();

        for (int sample = 0; sample < numSamples; ++sample)
        {
            float signal = channelData[sample];

            // Apply age-based loudness curve (low frequency boost)
            signal *= curve.lfBoost;

            // ----- Un-Age section -----
            const float amt = unAgeAmount.getNextValue();
            signal *= (1.0f - amt) + amt * unAgeCurve.lfCut;   // lows
            signal *= (1.0f - amt) + amt * unAgeCurve.hfBoost; // highs

            // Soft clipping to prevent harsh distortion
            signal = std::tanh(signal * 0.7f) / 0.7f;
            signal = std::clamp(signal, -0.9999f, 0.9999f);

            // Add sub-harmonic "feel" enhancement
            if (feel.subLevel > 0.0f)
            {
                // Envelope follower for dynamic sub-harmonic generation
                const float envelope = std::abs(signal) * 0.2f;

                // Generate 40Hz sub-harmonic (optimal for tactile sensation)
                feel.phase += subPhaseInc;
                if (feel.phase > juce::MathConstants<float>::pi * 2.0f)
                    feel.phase -= juce::MathConstants<float>::pi * 2.0f;

                const float subHarmonic = feel.subLevel * envelope * std::sin(feel.phase);
                signal += subHarmonic;
            }

            // Apply high-frequency cut (age-based hearing loss simulation)
            signal *= curve.hfCut;

            // Apply final gain with smoothing
            signal *= gainLin.getNextValue();

            channelData[sample] = signal;
        }
    }
}

//==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout
GGGainAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    // Main gain control
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID("gain", 1), "Gain",
        juce::NormalisableRange<float>(-36.0f, 24.0f, 0.1f), 0.0f, "dB"));

    // Age-based psychoacoustic modeling (0-100 years)
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID("age", 1), "Age",
        juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f), 25.0f, "yrs"));

    // Feel enhancement (tactile frequency boost)
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID("feel", 1), "Feel",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f));

    // Un-Age parameter (inverse of age curve)
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID("unAge", 1), "Un-Age",
        juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f), 0.0f, "%"));

    return layout;
}

//==============================================================================
bool GGGainAudioProcessor::hasEditor() const { return true; }
juce::AudioProcessorEditor* GGGainAudioProcessor::createEditor()
{
    return new GGGainAudioProcessorEditor(*this);
}

//==============================================================================
const juce::String GGGainAudioProcessor::getName() const { return JucePlugin_Name; }
bool GGGainAudioProcessor::acceptsMidi() const { return false; }
bool GGGainAudioProcessor::producesMidi() const { return false; }
bool GGGainAudioProcessor::isMidiEffect() const { return false; }
double GGGainAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int GGGainAudioProcessor::getNumPrograms() { return 1; }
int GGGainAudioProcessor::getCurrentProgram() { return 0; }
void GGGainAudioProcessor::setCurrentProgram(int) {}
const juce::String GGGainAudioProcessor::getProgramName(int) { return {}; }
void GGGainAudioProcessor::changeProgramName(int, const juce::String&) {}

//==============================================================================
void GGGainAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void GGGainAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(apvts.state.getType()))
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GGGainAudioProcessor();
}