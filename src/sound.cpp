#include "sound.h"
#include <iostream>

Sound::Sound() : filePath("") {
    freopen("../media/LoadGame/volume.txt", "r", stdin);
    std::cin >> volumeLevel;
    setVolume(volumeLevel);
}

Sound::~Sound() {
    freopen("../media/LoadGame/volume.txt", "w", stdout);
    std::cout << volumeLevel * 100;
}

void Sound::setVolume(double volumeLevel_) {
    if (volumeLevel_ < 0 || volumeLevel_ > 100) return;
    volumeLevel = volumeLevel_ / 100;
    DWORD newVolume = static_cast<DWORD>(volumeLevel * 0xFFFF);
    waveOutSetVolume(0, newVolume);
}

void Sound::setFilePath(std::string filePath_) {
    filePath = Path + filePath_;
}

double Sound::getVolume() {
    return volumeLevel * 100;
}

void Sound::play(std::string filePath_) {
    if (filePath == Path + filePath_) return;
    PlaySoundA(NULL, NULL, SND_PURGE);
    setFilePath(filePath_);
    DWORD newVolume = static_cast<DWORD>(volumeLevel * 0xFFFF);
    waveOutSetVolume(0, newVolume);
    PlaySoundA(filePath.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}
