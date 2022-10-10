//
//  HiHighAudio.cpp
//  SuperPowerPuzzle
//
//  Created by insanity on 2013. 11. 13..
//
//

#include "HiHighAudio.h"
#include "../helper/AndroidHelper.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
#import <AudioToolbox/AudioToolbox.h>
#endif


HiHighAudio* g_Audio = NULL;

HiHighAudio* HiHighAudio::sharedAudio()
{
    if(g_Audio == NULL) {
        g_Audio = new HiHighAudio();
    }
    return g_Audio;
}

HiHighAudio::HiHighAudio()
{
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(SOUND_VOLUME);
}


void HiHighAudio::muteSound()
{
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(0);
}

void HiHighAudio::unmuteSound()
{
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(SOUND_VOLUME);
}

void HiHighAudio::muteMusic()
{
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
}

void HiHighAudio::unmuteMusic()
{
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(MUSIC_VOLUME);
    
    string musicName;
    if(_lastPlayedMusicName == "") {
        musicName = "Menu";
    } else {
        musicName = _lastPlayedMusicName;
    }
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(musics[musicName].c_str(), true);
}

void HiHighAudio::playEffect(string name)
{
    bool isOff = CCUserDefault::sharedUserDefault()->getBoolForKey(IS_SOUND_OFF);
    if (isOff) {
        return;
    }
    SimpleAudioEngine::sharedEngine()->playEffect(sounds[name].c_str());
}

void HiHighAudio::playEffectLoop(string name)
{
    bool isOff = CCUserDefault::sharedUserDefault()->getBoolForKey(IS_SOUND_OFF);
    if (isOff) {
        return;
    }
    currentLoopSound = SimpleAudioEngine::sharedEngine()->playEffect(sounds[name].c_str(),true);
}

void HiHighAudio::stopEffect() {
    SimpleAudioEngine::sharedEngine()->stopEffect(currentLoopSound);
}


void HiHighAudio::playMusic(string name)
{
    bool isOff = CCUserDefault::sharedUserDefault()->getBoolForKey(IS_MUSIC_OFF);
    if (isOff) {
        return;
    }
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(musics[name].c_str(), true);
    _lastPlayedMusicName = name;
}

void HiHighAudio::stopMusic()
{
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void HiHighAudio::pauseMusic()
{
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void HiHighAudio::resumeMusic()
{
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
void HiHighAudio::vibrate(long time) {

	 bool isOff = CCUserDefault::sharedUserDefault()->getBoolForKey(IS_VIBE_OFF);
    if (isOff) {
        return;
    }


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    android_viberate(time);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
	AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
#endif


}
