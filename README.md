# LiveLinkVoicePlugin_UnrealEngine
An Unreal 5.0.2 plugin to implement audio source capture through **Live Link Plugin**.

## Requirements 
* **Unreal LiveLink Plugin.** 

You can add the plugin to your project by going to *Edit->Plugins* menu entry, then search for "**Live Link**" and set *Enable On*. After reloading the project, go to *Window->Virtual Productuon->Live Link* to open Live Link source window.

## How to install

Download the *LiveLinkVoicePlugin* directory from this repository, then copy it inside your project's Plugins directory. Now **LiveLink Voice Plugin** will be added to the *Edit->Plugins* menu and you just need to set *Enable On* and reload the project.

## Description

**LiveLink Voice Plugin** allows you to use your *default audio input* device as a Live Link source. Record external sounds and reuse them as inputs for your *Unreal Engine* project. 
**Live Link Voice Source** exposes the following data:

* Sound *Duration*.
* Sound *Volume*.
* Sound *Pitch*.

## Example.

Let's try to implement a **LiveLink Voice Source** as a World Light Controller.

* ### Step 1: *Create LiveLink Voice Source*

On Live Link source window, click on *Add* button and select Voice Source on the menu. A LiveLink Voice Source will appear inside the window, automatically linked to the default input audio device of your platform.

* ### Step 2: *Voice Settings*

Together with the creation of the Voice Source a Voice Settings Asset will be generated. Inside, you can set useful parameters about Voice Capture rate anch Pitch Curve implemantation. 

| Name | Description|
|------|------------|
|

