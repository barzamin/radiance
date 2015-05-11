#ifndef __FILTERS_AUDIO_H__
#define __FILTERS_AUDIO_H__

#include "core/audio.h"

#include <SDL/SDL.h>

#define WAVEFORM_HISTORY_SIZE 4096

struct waveform_bin {
    SDL_Color color;
    float history[WAVEFORM_HISTORY_SIZE];
};

enum freq_bin_i {
    WF_HIGH,
    WF_MID,
    WF_LOW,

    N_WF_BINS
};

extern struct waveform_bin waveform_bins[];

void waveform_init();
void waveform_update(chunk_pt chunk);
void waveform_del();


#endif