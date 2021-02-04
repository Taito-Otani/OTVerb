/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
OtverbAudioProcessor::OtverbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
    , m_CurrentBufferSize(0) //added
{
    //==============================================================================
#pragma region add-region01
    m_C74PluginState = (CommonState*)gen_exported::create(44100, 64);
    gen_exported::reset(m_C74PluginState);

    m_InputBuffers = new t_sample * [gen_exported::num_inputs()];
    m_OutputBuffers = new t_sample * [gen_exported::num_outputs()];

    for (int i = 0; i < gen_exported::num_inputs(); i++)
    {
        m_InputBuffers[i] = 0;
    }
    for (int i = 0; i < gen_exported::num_outputs(); i++)
    {
        m_OutputBuffers[i] = 0;
    }
    
#pragma endregion
    //==============================================================================
}

OtverbAudioProcessor::~OtverbAudioProcessor()
{
    gen_exported::destroy(m_C74PluginState);
}

//==============================================================================
const juce::String OtverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int OtverbAudioProcessor::getNumParameters()
{
    return gen_exported::num_params();
}

float OtverbAudioProcessor::getParameter(int index)
{
    t_param value;
    t_param min = gen_exported::getparametermin(m_C74PluginState, index);
    t_param range   =   fabs(gen_exported::getparametermax(m_C74PluginState, index) - min);
    
    gen_exported::getparameter(m_C74PluginState, index, &value);
    
    value = (value - min) / range;
    return value;
}

void OtverbAudioProcessor::setParameter(int index, float newValue){
    t_param min = gen_exported::getparametermin(m_C74PluginState, index);
    t_param range = fabs(gen_exported::getparametermax(m_C74PluginState, index) - min);
    t_param value = newValue * range + min;

    gen_exported::setparameter(m_C74PluginState, index, value, NULL);
}

const juce::String OtverbAudioProcessor::getParameterName(int index)
{
    return juce::String(gen_exported::getparametername(m_C74PluginState, index));
}

const juce::String OtverbAudioProcessor::getParameterText(int index)
{
    juce::String text = juce::String(getParameter(index));
    text += juce::String(" ");
    text += juce::String(gen_exported::getparameterunits(m_C74PluginState, index));

    return text;
}

const juce::String OtverbAudioProcessor::getInputChannelName(int channelIndex) const
{
    return juce::String(channelIndex + 1);
}

const juce::String OtverbAudioProcessor::getOutputChannelName(int channelIndex) const
{
    return juce::String(channelIndex + 1);
}

bool OtverbAudioProcessor::isInputChannelStereoPair(int index) const
{
    return gen_exported::num_inputs() == 2;
}

bool OtverbAudioProcessor::isOutputChannelStereoPair(int index) const
{
    return gen_exported::num_outputs() == 2;
}


bool OtverbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool OtverbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool OtverbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double OtverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int OtverbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int OtverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void OtverbAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String OtverbAudioProcessor::getProgramName (int index)
{
    return {};
}

void OtverbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void OtverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    // initialize samplerate and vectorsize with the correct values
    m_C74PluginState->sr = sampleRate;
    m_C74PluginState->vs = samplesPerBlock;

    assureBufferSize(samplesPerBlock);
}

void OtverbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool OtverbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void OtverbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    assureBufferSize(buffer.getNumSamples());

    // fill input buffers
    for (int i = 0; i < gen_exported::num_inputs(); i++) {
        if (i < totalNumInputChannels) {
            for (int j = 0; j < m_CurrentBufferSize; j++) {
                m_InputBuffers[i][j] = buffer.getReadPointer(i)[j];
            }
        }
        else {
            memset(m_InputBuffers[i], 0, m_CurrentBufferSize * sizeof(double));
        }
    }

    // process audio
    gen_exported::perform(m_C74PluginState,
        m_InputBuffers,
        gen_exported::num_inputs(),
        m_OutputBuffers,
        gen_exported::num_outputs(),
        buffer.getNumSamples());

    // fill output buffers
    for (int i = 0; i < totalNumOutputChannels; i++) {
        if (i < gen_exported::num_outputs()) {
            for (int j = 0; j < buffer.getNumSamples(); j++) {
                buffer.getWritePointer(i)[j] = m_OutputBuffers[i][j];
            }
        }
        else {
            buffer.clear(i, 0, buffer.getNumSamples());
        }
    }
}

//==============================================================================
bool OtverbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* OtverbAudioProcessor::createEditor()
{
    //SWITCH UI
    return new OtverbAudioProcessorEditor (*this);
//    return new juce::GenericAudioProcessorEditor(this);
}

//==============================================================================
void OtverbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    char* state;
    size_t statesize = gen_exported::getstatesize(m_C74PluginState);
    state = (char*)malloc(sizeof(char) * statesize);

    gen_exported::getstate(m_C74PluginState, state);
    destData.replaceWith(state, sizeof(char) * statesize);

    if (state) free(state);
}

void OtverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    gen_exported::setstate(m_C74PluginState, (const char*)data);
}

void OtverbAudioProcessor::assureBufferSize(long bufferSize)
{
    if (bufferSize > m_CurrentBufferSize) {
        for (int i = 0; i < gen_exported::num_inputs(); i++) {
            if (m_InputBuffers[i]) delete m_InputBuffers[i];
            m_InputBuffers[i] = new t_sample[bufferSize];
        }
        for (int i = 0; i < gen_exported::num_outputs(); i++) {
            if (m_OutputBuffers[i]) delete m_OutputBuffers[i];
            m_OutputBuffers[i] = new t_sample[bufferSize];
        }

        m_CurrentBufferSize = bufferSize;
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new OtverbAudioProcessor();
}
