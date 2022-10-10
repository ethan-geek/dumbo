//
//  SPBAudio.h
//  SuperPowerPuzzle
//
//  Created by insanity on 2013. 11. 13..
//
//

#ifndef __SuperPowerPuzzle__SPBAudio__
#define __SuperPowerPuzzle__SPBAudio__

#define IS_MUSIC_OFF    "isMusicOff"
#define IS_SOUND_OFF    "isSoundOff"

#define IS_VIBE_OFF		"isVibeOff"

#define MUSIC_VOLUME    0.5
#define SOUND_VOLUME    0.15



#include "SimpleAudioEngine.h"
#include <iostream>
#include <map>
#include "cocos2d.h"
using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class HiHighAudio
{
public:
    static HiHighAudio* sharedAudio();
    HiHighAudio();
    void muteSound();
    void unmuteSound();
    void muteMusic();
    void unmuteMusic();
    
    void playMusic(string name);
    void stopMusic();
    void pauseMusic();
    void resumeMusic();
    void playEffect(string name);
    void stopEffect();
    void playEffectLoop(string name);
	void vibrate(long time = 300);

    map<string, string> musics;
    map<string, string> sounds;
    string _lastPlayedMusicName;
    unsigned int currentLoopSound;
};


#endif /* defined(__SuperPowerPuzzle__SPBAudio__) */
