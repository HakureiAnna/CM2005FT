/*
  ==============================================================================

    PlayerPool.cpp
    Created: 3 Mar 2022 6:10:18pm
    Author:  Anna

  ==============================================================================
*/

#include "PlayerPool.h"

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
PlayerPool::PlayerPool(AudioFormatManager &formatManager) {
    // create new dynamically allocated players and add them to the pointer array
    for (auto i = 0; i < N; ++i) {
        players.add(new DJAudioPlayer(formatManager, i));
        availablePlayers.push(i);
    }
}

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
DJAudioPlayer* PlayerPool::getPlayer(int id) {
    return players[id];
}

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
DJAudioPlayer* PlayerPool::getAvailablePlayer() {
    // if no more players available, return nullptr
    if (availablePlayers.empty()) {
        return nullptr;
    }
    // dequeue a id and return the associated player
    auto id = availablePlayers.front();
    availablePlayers.pop();
    return players[id];
}

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
int PlayerPool::size() {
    return players.size();
}

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
void PlayerPool::releasePlayer(int id) {
    // enqueue a returned player's id to make it available
    availablePlayers.push(id);
}
