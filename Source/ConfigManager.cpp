/*
  ==============================================================================

    ConfigManager.cpp
    Created: 4 Mar 2022 4:46:32pm
    Author:  Anna

  ==============================================================================
*/

#include "ConfigManager.h"

// config file relative path
const String ConfigManager::PATH_CONFIG = "config.json";

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
void ConfigManager::save(const var& config) {
    // construct full path
    auto path = File::getCurrentWorkingDirectory().getFullPathName() + File::getSeparatorChar() + PATH_CONFIG;

    // open file
    File f(path);

    // write to file
    f.replaceWithText(JSON::toString(config));
}

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
const var ConfigManager::load() {
    // construct full path
    auto path = File::getCurrentWorkingDirectory().getFullPathName() + File::getSeparatorChar() + PATH_CONFIG;

    // open file
    File f(path);

    if (!f.exists()) {
        return false;
    }
    // parse file content as JSON and return
    var config = JSON::parse(f);



    return config;
}
