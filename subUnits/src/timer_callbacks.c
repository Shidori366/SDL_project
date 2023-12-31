/**
 * @author Dominik Milián
 * @Date 30.12.2023
 */

#include <timer_callbacks.h>

Uint32 fallTimerCallback(Uint32 interval, void *param) {
    SDL_Event event;
    SDL_UserEvent userEvent;

    userEvent.type = SDL_USEREVENT;
    userEvent.code = 0;
    userEvent.data1 = NULL;
    userEvent.data2 = NULL;

    event.type = SDL_USEREVENT;
    event.user = userEvent;

    SDL_PushEvent(&event);

    return interval;
}