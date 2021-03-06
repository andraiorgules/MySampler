# Andrada Iorgulescu
## MEDI 481 - The Sonic Experience
## Final Project : MySampler
A Sampler VST that I made using the JUCE framework. This is the first VST I have ever created, as well as my first time using JUCE and C++.

[![MySampler](https://github.com/andraiorgules/MySampler/blob/main/assets/MySampler/MySamplerThumbnail.png)](https://youtu.be/LtkMCZv4_aw)
###### Please Click The Image To Watch A Demo On Youtube

## Description 
This Sampler plugin is very easy to use. First, locate the sound files you would like to use and "drag and drop" them onto the box. You can use ".wav", ".aif", or ".mp3" files. Once the sound file is loaded, the text will disappear and be replaced with a purple background. The waveform for your sound file will be drawn on top of the purple background, and the name of your sound file will be displayed in the upper right corner. If you would like to use a different sound file, simply "drag and drop" it on top of the old one. The waveform and sound file name will also update to reflect the new sound file. The ADSR Envelope is quite simple to use: simply drag the knobs upwards to increase the value and downwards to decrease the value. You can also double-click on the boxes underneath the knobs to manually put in the value you would like to use. As you play your sound file, a playhead will follow along and give you a visual representation of what part of the file is currently playing. The playhead will also slightly darken the areas that have already been played. 

## Download and Install
[Google Drive: Download Link](https://drive.google.com/file/d/1RhdmNlnnTT37AvRakJWsa4VxlDlk6S2X/view?usp=sharing)

Clicking on the link above will take you to my Google Drive, where you can download a .zip file containing the "MySampler" installation folder. 

#### MAC
After you unzip the file, go into the "build" folder and click on the "MySampler.pkg" file. This will install the necessary components into the correct directories on your computer so that the VST can be used in your DAW. Going into the "Release" folder will lead you to an application called "MySampler" - this is the standalone plugin which you can use outside of your DAW.
#### WINDOWS
After you unzip the file, go into the "Release" folder and look for the 'MySampler.component", "MySampler.vst3", and "libMySampler.a" files. Move these files into C:\Program Files\Common Files\VST3 for use in your DAW. The "MySampler" application is the standalone plugin. 
#### I have also included the complete JUCE project folder titled "MySampler", which you can run in the Projucer to compile the project locally on your own computer.


## Sources Used
###### [1] [JUCE Documentation](https://docs.juce.com/master/index.html)
###### [2] [JUCE Value Tree Class Reference](https://docs.juce.com/master/classValueTree.html)
###### [3] [JUCE ValueTree::Listener Class Reference](https://docs.juce.com/master/classValueTree_1_1Listener.html)
###### [4] [JUCE AudioProcessorValueTreeState Class Reference](https://docs.juce.com/master/classAudioProcessorValueTreeState.html)
###### [5] [JUCE AudioParameterFloat Class Reference](https://docs.juce.com/master/classAudioParameterFloat.html)
###### [6] [JUCE AudioProcessorValueTreeState::SliderAttachment Class Reference](https://docs.juce.com/master/classAudioProcessorValueTreeState_1_1SliderAttachment.html)
###### [7] [JUCE Slider::Listener Class Reference](https://docs.juce.com/master/classSlider_1_1Listener.html)
###### [8] [JUCE SamplerSound Class Reference](https://docs.juce.com/master/classSamplerSound.html)
###### [9] [JUCE Synthesiser Class Reference](https://docs.juce.com/master/classSynthesiser.html)
###### [10] [JUCE FileChooser Class Reference](https://docs.juce.com/master/classFileChooser.html)
###### [11] [JUCE Slider Class Reference](https://docs.juce.com/master/classSlider.html)
###### [12] [Youtube Build A Sampler VST Tutorials by TheAudioProgrammer](https://youtube.com/playlist?list=PLrACIjSt9ge-SH78GmExKiDBMsAlhKLWc)
###### [13] [JUCE Tutorials](https://juce.com/learn/tutorials)
