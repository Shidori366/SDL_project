/**
 * @author Dominik Milián
 * @Date 30.12.2023
 * @brief File containing all timer callbacks.
 */

#ifndef SDL_PROJECT_TIMER_CALLBACKS_H
#define SDL_PROJECT_TIMER_CALLBACKS_H

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_types.h>

/**
 * Callback for timer, which controls,
 * when new shape should fall by one block.
 * @param interval Time passed.
 * @param param Additional parameters.
 * @return Next interval for timer.
 */
Uint32 fallTimerCallback(Uint32 interval, void *param);

#endif //SDL_PROJECT_TIMER_CALLBACKS_C
