/*
  ==============================================================================

    ConfigManager.h
    Created: 4 Mar 2022 4:46:32pm
    Author:  Anna

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
using namespace juce;

class ConfigManager {
public:
    // public constants
    static const String PATH_CONFIG;    // config file relative path

    // methods
    /******************************************
    * Name:
    *  save
    * Description:
    *  function used during program termination to save the current track 
    *  list to the config file.
    * Parameters:
    *  config: the JSON formatted configuration to save
    * Output:
    *  N/A
    *******************************************/
    static void save(const var& config);

    /******************************************
    * Name:
    *  load
    * Description:
    *  function used during program startup to load saved track list
    *  from the config file
    * Parameters:
    *  N/A
    * Output:
    *  JSON formatted config to initialize track list from
    *******************************************/
    static const var load();

};