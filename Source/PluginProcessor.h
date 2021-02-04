/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "gen_exported.h" //genのコードをインクルード

//==============================================================================
/**
*/
class OtverbAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    OtverbAudioProcessor();
    ~OtverbAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;
    
    //==============================================================================
    //追加する関数群
    int getNumParameters() override; // hostから呼ばれる、
    float getParameter(int index) override; // host, guiへパラメーターの値を渡す
    void setParameter(int index, float newValue) override; // host, guiから値をセットする

    const juce::String getParameterName(int index) override; // hostがパラメーターの名前を入手する
    const juce::String getParameterText(int index) override; //　hostがパラメーターの表記を入手する

    const juce::String getInputChannelName(int channelIndex) const override; //
    const juce::String getOutputChannelName(int channelIndex) const override; //
    bool isInputChannelStereoPair(int index) const override; //
    bool isOutputChannelStereoPair(int index) const override; //
    //追加する関数群
    //==============================================================================
    
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

protected:
    //==============================================================================
    // c74: since Juce does float sample processing and Gen offers double sample
    // processing, we need to go through input and output buffers
    void assureBufferSize(long bufferSize); //added
    
private:
    //==============================================================================
    CommonState* m_C74PluginState; //genに必要な渡す構造体（サンプルレートやパラメーターなど）
    long m_CurrentBufferSize; //ブロックサイズ
    t_sample** m_InputBuffers; //genのコードに合わせた入力バッファ
    t_sample** m_OutputBuffers; //genのコードに合わせた出力バッファ

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OtverbAudioProcessor)
};
