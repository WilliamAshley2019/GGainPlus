GGainPlus is a professional aspirant audio plugin designed for precise gain control and psychoacoustic enhancement, 
featuring age-based loudness modeling and tactile "feel" sub-harmonic generation. Developed by William Ashley, 
this plugin is perfect for audio engineers, music producers, and developers looking to enhance their audio processing
workflows with a versatile VST3 plugin built using JUCE 8. Keywords: Audio Plugin, VST3, JUCE 8, Psychoacoustic Processing,
Gain Control, Sub-Harmonic Generation, Music Production, Audio Engineering, William AshleyTable of ContentsFeatures (#features)

Features GGGain's Gain Control: Smooth, high-quality gain adjustment from -36 dB to +24 dB; as well as,
Age-Based Loudness Modeling: Simulates age-related hearing loss with low-frequency boost and high-frequency cut,
adjustable from 0 to 100 years. Also, Tactile Feel Enhancement: Adds a 40Hz sub-harmonic for enhanced tactile sensation, 
ideal for immersive audio experiences.

Additionaly it adds,
Un-Age Processing: Reverses the age-based curve to restore high frequencies and attenuate lows for a "younger" sound perception.
VST3 Compatibility: Built with the Steinberg VST3 SDK for seamless integration with major DAWs (e.g., Ableton Live, FL Studio, Reaper).
Cross-Platform: Supports Windows, macOS, and Linux, built with JUCE 8.

Relatively Low CPU Usage: Optimized for real-time audio processing with smoothed parameter changes to avoid clicks.

"GGainPlus brings a unique blend of psychoacoustic modeling and tactile enhancement to your audio projects." — William Ashley :)
InstallationDownload the Plugin:Visit the Releases page to download the latest VST3 plugin for your platform.

Alternatively, build from source (see Building from Source (#building-from-source)). The four JUCE files for JUCE 8.09 are provided.
It was built using Visual Studio Community 2022 ~ V17 on windows 11 24h2.

Install the Plugin:
Windows: Copy the .vst3 file to C:\Program Files\Common Files\VST3\.

Duh,
Load in Your DAW:Open your DAW (e.g., Ableton Live, FL Studio) and scan for new plugins. (Only Tested in FL Studio)
Add GGainPlus is an audio effect so add  to your audio track or bus such as in FL Studio's mixer.

UsageLoad the Plugin: Insert GGainPlus on an audio track / mixer track in your DAW.

Adjust Parameters:Gain: Set the overall level (-36 dB to +24 dB).
Age: Adjust the age-based loudness curve (0–100 years) to simulate hearing loss.
Un-Age: Counteract the age curve (0–100%) to restore high frequencies and reduce lows.
Feel: Add sub-harmonic enhancement (0–1) for tactile sensation.

Experiment: Combine settings to balance psychoacoustic effects and gain for your mix.

Example:markdown

- For a vocal track: Set `Age` to 25 yrs, `Un-Age` to 50%, and `Feel` to 0.3 for a balanced, vibrant sound.
- For bass-heavy tracks: Increase `Feel` to 0.8 and reduce `Un-Age` to 0% for enhanced low-end presence.

Building from SourceTo build GGGain from source, you need:PrerequisitesJUCE 8: Download from juce.com or clone the JUCE GitHub repository.
Steinberg VST3 SDK: Obtain from Steinberg Developer.
CMake: For project configuration.
A C++ Compiler: Visual Studio (Windows), Xcode (macOS), or GCC (Linux).
Git: To clone the repository.

StepsClone the Repository:bash

git clone https://github.com/williamashley2019/GGainPlus.git
 
The projucer .jucer files have not been provided however you can easily set up a default build plugin basics with dsp module additonally
copy and paste the code in or drag and drop the provide source files into the source directory and link them if required.

Install the Plugin:Copy the generated .vst3 file to your DAW’s VST3 folder (see Installation (#installation)).
This plugin should work with just the vst3 file put in your vst3 folder under commonfiles as is normal for all vst3 plugins on windows.

LicenseGGGain is licensed under multiple licenses due to its dependencies:GPLv3 LicenseThis project is licensed under the GNU General Public License v3.0. You are free to use, modify, and distribute this software, provided all derivative works are also licensed under GPLv3.markdown

GNU General Public License v3.0
Permissions: Commercial use, modification, distribution, private use
Conditions: Disclose source, same license, state changes
Limitations: Liability, warranty - full disclaimer is intended this is Alpha software use at your own risk it has been tested on my own
computer with no noticable ill effects but no warranty or fitness of the software is implied.

See the LICENSE file for full details.
JUCE 8 LicenseGGGain uses the JUCE 8 framework, which is licensed under the JUCE End-User License Agreement. 
For open-source projects under GPLv3, JUCE 8 is free to use, provided the project complies with GPLv3 terms. 
For commercial use, a separate JUCE license may be required from juce.com.

Steinberg VST3 SDK License
The VST3 functionality is provided by the Steinberg VST3 SDK, licensed under the Steinberg VST3 License under open source GPLv3 license. 
The SDK is free for use in VST3 plugin development, but you must comply with Steinberg’s terms, including not modifying the SDK itself.

Contributing
Contributions are welcome! To contribute to GGainPlus:Fork the repository.
Create a new branch: git checkout -b feature/your-feature.
Make your changes and commit: git commit -m "Add your feature".
Push to your fork: git push origin feature/your-feature.
Open a pull request on GitHub.

Please include:A clear description of your changes.
Tests or examples demonstrating functionality.
Compliance with the GPLv3 license.

ContactGitHub: williamashley2019

About the DeveloperWilliam Ashley is a passionate audio plugin developer and music technology enthusiast. 
With expertise in C++, JUCE, and audio DSP, William creates innovative tools for music production. 
Follow his work on:GitHub for open-source projects.  https://github.com/williamashley2019
Portfolio https://12264447666william.wixsite.com/williamashley for professional showcases.
Medium  https://medium.com/@12264447666.williamashley for audio programming insights.
YouTube https://www.youtube.com/@WilliamAshleyOnline  for tutorials and demos.
You can support me and my audio projects through https://buymeacoffee.com/williamashley  or getting involved in development.
Feel free to provide any suggestions for upgrades to the plugins or just provide feedback on your experiences with them


 Star this repository to support the project and stay updated!

Future updates
better audio brightening methods. such as hearing aid methods to boost audio. 
text lables for gui knobs explaining what they are for.
