/*
  ==============================================================================

    PlayerPool.h
    Created: 3 Mar 2022 6:10:18pm
    Author:  Anna

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
using namespace juce;

#include "DJAudioPlayer.h"

class PlayerPool {
public:
    // constructors & destructors
    /******************************************
    * Name:
    *  PlayerPool
    * Description:
    *  constructor of the PlayerPool class. Used to create 
    *  instance of the DJAudioPlayer and store them.
    * Parameters:
    *  formatManager: reference to global AudioFormatManager
    * Output:
    *  N/A
    *******************************************/
    PlayerPool(AudioFormatManager &formatManager);

    // getters & setters
    /******************************************
    * Name:
    *  getPlayer
    * Description:
    *  getter to get DJAudioPlayer by id
    * Parameters:
    *  id
    * Output:
    *  pointer to DJAudioPlayer represented by id
    *******************************************/
    DJAudioPlayer* getPlayer(int id);

    /******************************************
    * Name:
    *  getAvailablePlayer
    * Description:
    *  get an available player, by getting a id from the queue.
    *  Return nullptr if no players are available.
    * Parameters:
    *  N/A
    * Output:
    *  pointer to available DJAudioPlayer
    *******************************************/
    DJAudioPlayer* getAvailablePlayer();

    // methods
    /******************************************
    * Name:
    *  size
    * Description:
    *  returns the number of players that exist in the pool.
    * Parameters:
    *  N/A
    * Output:
    *  no. of ALL DJAudioPlayers in the pool
    *******************************************/
    int size();

    /******************************************
    * Name:
    *  releasePlayer
    * Description:
    *  Add a released player back to the available pool
    *  by inserting its id into the queue.
    * Parameters:
    *  id: id of player released
    * Output:
    *  N/A
    *******************************************/
    void releasePlayer(int id);

    // public constants
    static const int N = 16;    // total number of players in the pool

private:
    // functionality members
    OwnedArray<DJAudioPlayer> players;  // pointer array to all players
    std::queue<int> availablePlayers;   // queue used to control the pool
};