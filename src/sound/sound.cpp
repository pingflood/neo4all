/*  gngeo a neogeo emulator
 *  Copyright (C) 2001 Peponas Mathieu
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "../neo4all.h"
#include "streams.h"

static unsigned char sound_muted=0x3;

#include "sound.h"

#define MUSIC_VOLUME 96

#define NB_SAMPLES 1024 /* normal resolution */

#ifdef AES
#define MUSIC_MOD "aes.mod"
#else
#define MUSIC_MOD "cd.mod"
#endif

#include <SDL_mixer.h>

#ifdef MENU_MUSIC
enum{
	SAMPLE_BEEP,
	SAMPLE_ERROR,
	SAMPLE_LOADING,
	SAMPLE_SAVING,
	SAMPLE_MENU,
	SAMPLE_BYE,
	NUM_SAMPLES
};

static char *sample_filename[NUM_SAMPLES]={
	DATA_PREFIX "beep.wav",
	DATA_PREFIX "error.wav",
	DATA_PREFIX "loading.wav",
	DATA_PREFIX "saving.wav",
	DATA_PREFIX "menu.wav",
	DATA_PREFIX "goodbye.wav",
};

static Mix_Chunk *sample[NUM_SAMPLES];

#define play_sample(NSAMPLE) Mix_PlayChannel(0,sample[(NSAMPLE)],0)

#endif


#define printf

unsigned sound_emulating=0;

void update_sdl_stream(void *userdata, Uint8 * stream, int len)
{
    extern Uint16 play_buffer[];
#ifdef Z80_EMULATED
    if ((!sound_muted)&&(neogeo_sound_enable)&&(neogeo_emulating))
    {
		neo4all_prof_start(NEO4ALL_PROFILER_SOUND);
    	streamupdate(len);
    	SDL_MixAudio(stream, (Uint8*)play_buffer, len, MUSIC_VOLUME);
    	// memcpy(stream, (Uint8 *) play_buffer, len);
		neo4all_prof_end(NEO4ALL_PROFILER_SOUND);
    }
#endif
}

int init_sdl_audio(void)
{
	printf("%s:%d %s\n", __FILE__, __LINE__, __func__);
#ifdef Z80_EMULATED
    unsigned i;
    Mix_OpenAudio(SAMPLE_RATE, AUDIO_S16SYS, 2, NB_SAMPLES);

	SDL_PauseAudio(0);
	Mix_VolumeMusic(96);

#ifdef MENU_MUSIC
    for(i=0;i<NUM_SAMPLES;i++) {
	    sample[i]=Mix_LoadWAV(sample_filename[i]);
    }
#endif

    sound_reset();
#endif
    return 1;
}


void sound_play_menu_music(void)
{
	printf("%s:%d %s\n", __FILE__, __LINE__, __func__);
#ifdef MENU_MUSIC
    Mix_PlayMusic(Mix_LoadMUS(DATA_PREFIX MUSIC_MOD),-1);
    sound_mute();
#endif
}

void sound_play_loading(void)
{
	printf("%s:%d %s\n", __FILE__, __LINE__, __func__);
#ifdef MENU_MUSIC
	play_sample(SAMPLE_LOADING);
#endif
}

void sound_play_saving(void)
{
	printf("%s:%d %s\n", __FILE__, __LINE__, __func__);
#ifdef MENU_MUSIC
	play_sample(SAMPLE_SAVING);
#endif
}

void sound_play_menu(void)
{
	printf("%s:%d %s\n", __FILE__, __LINE__, __func__);
#ifdef MENU_MUSIC
	play_sample(SAMPLE_MENU);
#endif
}

void sound_play_bye(void)
{
	printf("%s:%d %s\n", __FILE__, __LINE__, __func__);
#ifdef MENU_MUSIC
	play_sample(SAMPLE_BYE);
#endif
}

void sound_play_beep(void)
{
	printf("%s:%d %s\n", __FILE__, __LINE__, __func__);
#ifdef MENU_MUSIC
	play_sample(SAMPLE_BEEP);
#endif
}

void sound_play_error(void)
{
	printf("%s:%d %s\n", __FILE__, __LINE__, __func__);
#ifdef MENU_MUSIC
	play_sample(SAMPLE_ERROR);
#endif
}

void sound_enable(void) {
	printf("%s:%d %s\n", __FILE__, __LINE__, __func__);
	SDL_PauseAudio(0);
	sound_muted&=0xFE;
}

void sound_disable(void) {
	printf("%s:%d %s\n", __FILE__, __LINE__, __func__);
	SDL_PauseAudio(1);
	sound_muted|=0x1;
}

void sound_toggle(void) {
	printf("%s:%d %s\n", __FILE__, __LINE__, __func__);
#ifdef Z80_EMULATED
	if (!(sound_muted&0x2))
	{
		if (sound_muted&0x1)
			sound_enable();
		else
			sound_disable();
	}
#endif
}

void sound_shutdown(void) {
	printf("%s:%d %s\n", __FILE__, __LINE__, __func__);
#ifdef Z80_EMULATED
    sound_stop();
    streams_sh_stop();
    YM2610_sh_stop();
    SDL_CloseAudio();
#endif
}

void sound_emulate_stop(void) {
	printf("%s:%d %s\n", __FILE__, __LINE__, __func__);
#ifdef Z80_EMULATED
    YM2610_sh_reset();
    AY8910_reset();
#endif
}

void sound_stop(void) {
	printf("%s:%d %s\n", __FILE__, __LINE__, __func__);
#ifdef Z80_EMULATED
    sound_mute();
    sound_emulate_stop();
    SDL_Delay(100);
#endif
}

void sound_emulate_start(void) {
	printf("%s:%d %s\n", __FILE__, __LINE__, __func__);
#ifdef Z80_EMULATED
    YM2610_sh_start();
    YM2610_sh_reset();
    AY8910_reset();
#endif
}

void sound_reset(void) {
	printf("%s:%d %s\n", __FILE__, __LINE__, __func__);
#ifdef Z80_EMULATED
    streams_sh_start();
    sound_emulate_start();
    sound_unmute();
#endif
}

void sound_mute(void){
	printf("%s:%d %s\n", __FILE__, __LINE__, __func__);
	sound_muted=0x3;
}

void sound_unmute(void){
	printf("%s:%d %s\n", __FILE__, __LINE__, __func__);
	sound_muted=0;
}
