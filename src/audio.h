static Janet cfun_InitAudioDevice(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    InitAudioDevice();
    return janet_wrap_nil();
}

static Janet cfun_CloseAudioDevice(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    CloseAudioDevice();
    return janet_wrap_nil();
}

static Janet cfun_IsAudioDeviceReady(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_boolean(IsAudioDeviceReady());
}

static Janet cfun_SetMasterVolume(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    float volume = (float) janet_getnumber(argv, 0);
    SetMasterVolume(volume);
    return janet_wrap_nil();
}


/*
// Wave/Sound loading/unloading functions
[ ] Wave LoadWaveEx(void *data, int sampleCount, int sampleRate, int sampleSize, int channels)
[ ] void UpdateSound(Sound sound, const void *data, int samplesCount)

// Wave/Sound management functions
[ ] void WaveFormat(Wave *wave, int sampleRate, int sampleSize, int channels)
[ ] void WaveCrop(Wave *wave, int initSample, int finalSample)
[ ] float *GetWaveData(Wave wave)
*/

static Janet cfun_LoadWave(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const char *fileName = janet_getcstring(argv, 0);
    Wave *wave = janet_abstract(&AT_Wave, sizeof(Wave));
    *wave = LoadWave(fileName);
    return janet_wrap_abstract(wave);
}

static Janet cfun_LoadSound(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const char *fileName = janet_getcstring(argv, 0);
    Sound *sound = janet_abstract(&AT_Sound, sizeof(Sound));
    *sound = LoadSound(fileName);
    return janet_wrap_abstract(sound);
}

static Janet cfun_LoadSoundFromWave(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Wave wave = *jaylib_getwave(argv, 0);
    Sound *sound = janet_abstract(&AT_Sound, sizeof(Sound));
    *sound = LoadSoundFromWave(wave);
    return janet_wrap_abstract(sound);
}

static Janet cfun_UnloadWave(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Wave wave = *jaylib_getwave(argv, 0);
    UnloadWave(wave);
    return janet_wrap_nil();
}

static Janet cfun_UnloadSound(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Sound sound = *jaylib_getsound(argv, 0);
    UnloadSound(sound);
    return janet_wrap_nil();
}

static Janet cfun_ExportWave(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Wave wave = *jaylib_getwave(argv, 0);
    const char *fileName = janet_getcstring(argv, 1);
    ExportWave(wave, fileName);
    return janet_wrap_nil();
}

static Janet cfun_ExportWaveAsCode(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Wave wave = *jaylib_getwave(argv, 0);
    const char *fileName = janet_getcstring(argv, 1);
    ExportWaveAsCode(wave, fileName);
    return janet_wrap_nil();
}

static Janet cfun_PlaySound(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Sound sound = *jaylib_getsound(argv, 0);
    PlaySound(sound);
    return janet_wrap_nil();
}

static Janet cfun_PauseSound(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Sound sound = *jaylib_getsound(argv, 0);
    PauseSound(sound);
    return janet_wrap_nil();
}

static Janet cfun_StopSound(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Sound sound = *jaylib_getsound(argv, 0);
    StopSound(sound);
    return janet_wrap_nil();
}

static Janet cfun_ResumeSound(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Sound sound = *jaylib_getsound(argv, 0);
    ResumeSound(sound);
    return janet_wrap_nil();
}

static Janet cfun_IsSoundPlaying(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Sound sound = *jaylib_getsound(argv, 0);
    return janet_wrap_boolean(IsSoundPlaying(sound));
}

static Janet cfun_SetSoundVolume(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Sound sound = *jaylib_getsound(argv, 0);
    float volume = (float) janet_getnumber(argv, 1);
    SetSoundVolume(sound, volume);
    return janet_wrap_nil();
}

static Janet cfun_SetSoundPitch(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Sound sound = *jaylib_getsound(argv, 0);
    float pitch = (float) janet_getnumber(argv, 1);
    SetSoundPitch(sound, pitch);
    return janet_wrap_nil();
}

static Janet cfun_WaveCopy(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Wave wave = *jaylib_getwave(argv, 0);
    Wave *copy = janet_abstract(&AT_Wave, sizeof(Wave));
    *copy = WaveCopy(wave);
    return janet_wrap_abstract(copy);
}

static Janet cfun_LoadMusicStream(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const char *fileName = janet_getcstring(argv, 0);
    Music *music = janet_abstract(&AT_Music, sizeof(Music));
    *music = LoadMusicStream(fileName);
    return janet_wrap_abstract(music);
}

static Janet cfun_UnloadMusicStream(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Music music = *jaylib_getmusic(argv, 0);
    UnloadMusicStream(music);
    return janet_wrap_nil();
}

static Janet cfun_PlayMusicStream(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Music music = *jaylib_getmusic(argv, 0);
    PlayMusicStream(music);
    return janet_wrap_nil();
}

static Janet cfun_UpdateMusicStream(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Music music = *jaylib_getmusic(argv, 0);
    UpdateMusicStream(music);
    return janet_wrap_nil();
}

static Janet cfun_StopMusicStream(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Music music = *jaylib_getmusic(argv, 0);
    StopMusicStream(music);
    return janet_wrap_nil();
}

static Janet cfun_PauseMusicStream(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Music music = *jaylib_getmusic(argv, 0);
    PauseMusicStream(music);
    return janet_wrap_nil();
}

static Janet cfun_ResumeMusicStream(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Music music = *jaylib_getmusic(argv, 0);
    ResumeMusicStream(music);
    return janet_wrap_nil();
}

static Janet cfun_IsMusicStreamPlaying(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Music music = *jaylib_getmusic(argv, 0);
    return janet_wrap_boolean(IsMusicStreamPlaying(music));
}

static Janet cfun_SetMusicVolume(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Music music = *jaylib_getmusic(argv, 0);
    float volume = (float) janet_getnumber(argv, 1);
    SetMusicVolume(music, volume);
    return janet_wrap_nil();
}

static Janet cfun_SetMusicPitch(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Music music = *jaylib_getmusic(argv, 0);
    float pitch = (float) janet_getnumber(argv, 1);
    SetMusicPitch(music, pitch);
    return janet_wrap_nil();
}

static Janet cfun_GetMusicTimeLength(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Music music = *jaylib_getmusic(argv, 0);
    return janet_wrap_number((double) GetMusicTimeLength(music));
}

static Janet cfun_GetMusicTimePlayed(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Music music = *jaylib_getmusic(argv, 0);
    return janet_wrap_number((double) GetMusicTimePlayed(music));
}

static Janet cfun_LoadAudioStream(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    unsigned int sampleRate = (unsigned) janet_getinteger(argv, 0);
    unsigned int sampleSize = (unsigned) janet_getinteger(argv, 1);
    unsigned int channels = (unsigned) janet_getinteger(argv, 2);
    AudioStream *audioStream = janet_abstract(&AT_AudioStream, sizeof(AudioStream));
    *audioStream = LoadAudioStream(sampleRate, sampleSize, channels);
    return janet_wrap_abstract(audioStream);
}

static Janet cfun_UpdateAudioStream(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    AudioStream stream = *jaylib_getaudiostream(argv, 0);
    JanetBuffer *data = janet_getbuffer(argv, 1);
    int samples = data->count / (stream.sampleSize >> 3);
    UpdateAudioStream(stream, data->data, samples);
    return janet_wrap_nil();
}

static Janet cfun_UnloadAudioStream(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    AudioStream stream = *jaylib_getaudiostream(argv, 0);
    UnloadAudioStream(stream);
    return janet_wrap_nil();
}

static Janet cfun_IsAudioStreamProcessed(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    AudioStream stream = *jaylib_getaudiostream(argv, 0);
    return janet_wrap_boolean(IsAudioStreamProcessed(stream));
}

static Janet cfun_PlayAudioStream(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    AudioStream stream = *jaylib_getaudiostream(argv, 0);
    PlayAudioStream(stream);
    return janet_wrap_nil();
}

static Janet cfun_PauseAudioStream(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    AudioStream stream = *jaylib_getaudiostream(argv, 0);
    PauseAudioStream(stream);
    return janet_wrap_nil();
}

static Janet cfun_ResumeAudioStream(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    AudioStream stream = *jaylib_getaudiostream(argv, 0);
    ResumeAudioStream(stream);
    return janet_wrap_nil();
}

static Janet cfun_StopAudioStream(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    AudioStream stream = *jaylib_getaudiostream(argv, 0);
    StopAudioStream(stream);
    return janet_wrap_nil();
}

static Janet cfun_IsAudioStreamPlaying(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    AudioStream stream = *jaylib_getaudiostream(argv, 0);
    return janet_wrap_boolean(IsAudioStreamPlaying(stream));
}

static Janet cfun_SetAudioStreamVolume(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    AudioStream stream = *jaylib_getaudiostream(argv, 0);
    float volume = (float) janet_getnumber(argv, 1);
    SetAudioStreamVolume(stream, volume);
    return janet_wrap_nil();
}

static Janet cfun_SetAudioStreamPitch(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    AudioStream stream = *jaylib_getaudiostream(argv, 0);
    float pitch = (float) janet_getnumber(argv, 1);
    SetAudioStreamPitch(stream, pitch);
    return janet_wrap_nil();
}

/*
// AudioStream management functions
[ ] void PlayAudioStream(AudioStream stream)
[ ] void PauseAudioStream(AudioStream stream)
[ ] void ResumeAudioStream(AudioStream stream)
[ ] bool IsAudioStreamPlaying(AudioStream stream)
[ ] void StopAudioStream(AudioStream stream)
[ ] void SetAudioStreamVolume(AudioStream stream, float volume)
[ ] void SetAudioStreamPitch(AudioStream stream, float pitch)
*/

static JanetReg audio_cfuns[] = {
    {"init-audio-device", cfun_InitAudioDevice, 
        "(init-audio-device)\n\n"
        "Initialize audio device and context"
    },
    {"close-audio-device", cfun_CloseAudioDevice, 
        "(close-audio-device)\n\n"
        "Close the audio device and context"
    },
    {"audio-device-ready?", cfun_IsAudioDeviceReady, 
        "(audio-device-ready?)\n\n"
        "Check if audio device has been initialized successfully"
    },
    {"set-master-volume", cfun_SetMasterVolume, 
        "(set-master-volume volume)\n\n"
        "Set master volume (listener)"
    },
    {"load-wave", cfun_LoadWave, 
        "(load-wave file-name)\n\n"
        "Load wave data from file"
    },
    {"load-sound", cfun_LoadSound, 
        "(load-sound file-name)\n\n"
        "Load sound from file"
    },
    {"load-sound-from-wave", cfun_LoadSoundFromWave, 
        "(load-sound-from-wave wave)\n\n"
        "Load sound from wave data"
    },
    {"unload-wave", cfun_UnloadWave, 
        "(unload-wave wave)\n\n"
        "Unload wave data"
    },
    {"unload-sound", cfun_UnloadSound, 
        "(unload-sound sound)\n\n"
        "Unload sound"
    },
    {"export-wave", cfun_ExportWave, 
        "(export-wave wave file-name)\n\n"
        "Export wave data to file, returns true on success"
    },
    {"export-wave-as-code", cfun_ExportWaveAsCode, 
        "(export-wave-as-code wave file-name)\n\n"
        "Export wave sample data to code (.h), returns true on success"
    },
    {"play-sound", cfun_PlaySound, 
        "(play-sound sound)\n\n"
        "Play a sound"
    },
    {"stop-sound", cfun_StopSound, 
        "(stop-sound sound)\n\n"
        "Stop playing a sound"
    },
    {"resume-sound", cfun_ResumeSound, 
        "(resume-sound sound)\n\n"
        "Resume a paused sound"
    },
    {"pause-sound", cfun_PauseSound, 
        "(pause-sound sound)\n\n"
        "Pause a sound"
    },
    {"sound-playing?", cfun_IsSoundPlaying, 
        "(sound-playing? sound)\n\n"
        "Check if a sound is currently playing"
    },
    {"set-sound-volume", cfun_SetSoundVolume, 
        "(set-sound-volume sound volume)\n\n"
        "Set volume for a sound (1.0 is max level)"
    },
    {"set-sound-pitch", cfun_SetSoundPitch, 
        "(set-sound-pitch sound pitch)\n\n"
        "Set pitch for a sound (1.0 is base level)"
    },
    {"wave-copy", cfun_WaveCopy, 
        "(wave-copy wave)\n\n"
        "Copy a wave to a new wave"
    },
    {"load-music-stream", cfun_LoadMusicStream, 
        "(load-music-stream file-name)\n\n"
        "Load music stream from file"
    },
    {"unload-music-stream", cfun_UnloadMusicStream, 
        "(unload-music-stream music)\n\n"
        "Unload music stream"
    },
    {"play-music-stream", cfun_PlayMusicStream, 
        "(play-music-stream music)\n\n"
        "Start music playing"
    },
    {"update-music-stream", cfun_UpdateMusicStream, 
        "(update-music-stream music)\n\n"
        "Updates buffers for music streaming"
    },
    {"pause-music-stream", cfun_PauseMusicStream, 
        "(pause-music-stream music)\n\n"
        "Pause music playing"
    },
    {"stop-music-stream", cfun_StopMusicStream, 
        "(stop-music-stream music)\n\n"
        "Stop music playing"
    },
    {"resume-music-stream", cfun_ResumeMusicStream, 
        "(resume-music-stream music)\n\n"
        "Resume playing paused music"
    },
    {"music-stream-playing?", cfun_IsMusicStreamPlaying, 
        "(music-stream-playing? music)\n\n"
        "Check if music is playing"
    },
    {"set-music-volume", cfun_SetMusicVolume, 
        "(set-music-volume music volume)\n\n"
        "Set volume for music (1.0 is max level)"
    },
    {"set-music-pitch", cfun_SetMusicPitch, 
        "(set-music-pitch music pitch)\n\n"
        "Set pitch for a music (1.0 is base level)"
    },
    {"get-music-time-length", cfun_GetMusicTimeLength, 
        "(get-music-time-length music)\n\n"
        "Get music time length (in seconds)"
    },
    {"get-music-time-played", cfun_GetMusicTimePlayed, 
        "(get-music-time-played music)\n\n"
        "Get current music time played (in seconds)"
    },
    {"load-audio-stream", cfun_LoadAudioStream, 
        "(load-audio-stream sample-rate sample-size channels)\n\n"
        "Init audio stream (to stream raw audio pcm data)"
    },
    {"update-audio-stream", cfun_UpdateAudioStream, 
        "(update-audio-stream stream)\n\n"
        "Update audio stream buffers with data"
    },
    {"unload-audio-stream", cfun_UnloadAudioStream, 
        "(unload-audio-stream stream)\n\n"
        "Close audio stream and free memory"
    },
    {"audio-stream-processed?", cfun_IsAudioStreamProcessed, 
        "(audio-stream-processed? stream)\n\n"
        "Check if any audio stream buffers requires refill"
    },
    {"audio-stream-playing?", cfun_IsAudioStreamPlaying, 
        "(audio-stream-playing? stream)\n\n"
        "Check if audio stream is playing"
    },
    {"play-audio-stream", cfun_PlayAudioStream, 
        "(play-audio-stream stream)\n\n"
        "Play audio stream"
    },
    {"pause-audio-stream", cfun_PauseAudioStream, 
        "(pause-audio-stream stream)\n\n"
        "Pause audio stream"
    },
    {"stop-audio-stream", cfun_StopAudioStream, 
        "(stop-audio-stream stream)\n\n"
        "Stop audio stream"
    },
    {"resume-audio-stream", cfun_ResumeAudioStream, 
        "(resume-audio-stream stream)\n\n"
        "Resume audio stream"
    },
    {"set-audio-stream-volume", cfun_SetAudioStreamVolume, 
        "(set-audio-stream-volume stream volume)\n\n"
        "Set volume for audio stream (1.0 is max level)"
    },
    {"set-audio-stream-pitch", cfun_SetAudioStreamPitch, 
        "(set-audio-stream-pitch stream pitch)\n\n"
        "Set pitch for audio stream (1.0 is base level)"
    },
    {NULL, NULL, NULL}
};
