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
    {"init-audio-device", cfun_InitAudioDevice, NULL},
    {"close-audio-device", cfun_CloseAudioDevice, NULL},
    {"audio-device-ready?", cfun_IsAudioDeviceReady, NULL},
    {"set-master-volume", cfun_SetMasterVolume, NULL},
    {"load-wave", cfun_LoadWave, NULL},
    {"load-sound", cfun_LoadSound, NULL},
    {"load-sound-from-wave", cfun_LoadSoundFromWave, NULL},
    {"unload-wave", cfun_UnloadWave, NULL},
    {"unload-sound", cfun_UnloadSound, NULL},
    {"export-wave", cfun_ExportWave, NULL},
    {"export-wave-as-code", cfun_ExportWaveAsCode, NULL},
    {"play-sound", cfun_PlaySound, NULL},
    {"stop-sound", cfun_StopSound, NULL},
    {"resume-sound", cfun_ResumeSound, NULL},
    {"pause-sound", cfun_PauseSound, NULL},
    {"sound-playing?", cfun_IsSoundPlaying, NULL},
    {"set-sound-volume", cfun_SetSoundVolume, NULL},
    {"set-sound-pitch", cfun_SetSoundPitch, NULL},
    {"wave-copy", cfun_WaveCopy, NULL},
    {"load-music-stream", cfun_LoadMusicStream, NULL},
    {"unload-music-stream", cfun_UnloadMusicStream, NULL},
    {"play-music-stream", cfun_PlayMusicStream, NULL},
    {"update-music-stream", cfun_UpdateMusicStream, NULL},
    {"pause-music-stream", cfun_PauseMusicStream, NULL},
    {"stop-music-stream", cfun_StopMusicStream, NULL},
    {"resume-music-stream", cfun_ResumeMusicStream, NULL},
    {"music-stream-playing?", cfun_IsMusicStreamPlaying, NULL},
    {"set-music-volume", cfun_SetMusicVolume, NULL},
    {"set-music-pitch", cfun_SetMusicPitch, NULL},
    {"get-music-time-length", cfun_GetMusicTimeLength, NULL},
    {"get-music-time-played", cfun_GetMusicTimePlayed, NULL},
    {"load-audio-stream", cfun_LoadAudioStream, NULL},
    {"update-audio-stream", cfun_UpdateAudioStream, NULL},
    {"unload-audio-stream", cfun_UnloadAudioStream, NULL},
    {"audio-stream-processed?", cfun_IsAudioStreamProcessed, NULL},
    {"audio-stream-playing?", cfun_IsAudioStreamPlaying, NULL},
    {"play-audio-stream", cfun_PlayAudioStream, NULL},
    {"pause-audio-stream", cfun_PauseAudioStream, NULL},
    {"stop-audio-stream", cfun_StopAudioStream, NULL},
    {"resume-audio-stream", cfun_ResumeAudioStream, NULL},
    {"set-audio-stream-volume", cfun_SetAudioStreamVolume, NULL},
    {"set-audio-stream-pitch", cfun_SetAudioStreamPitch, NULL},
    {NULL, NULL, NULL}
};
