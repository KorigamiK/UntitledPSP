#pragma once

#define BACKGROUND 53, 58, 71
#define BACKGROUND_ALT 87, 99, 84
#define HEADING 192, 216, 203
#define TEXT 255, 255, 255
#define ACCENT 35, 17, 35
#define ACCENT_ALT 173, 40, 49
#define FOREGROUND 249, 212, 187
#define SCORE 194, 141, 115

#define PLAYER_COLOR 142, 184, 229
#define PLAYER_VIEW_COLOR 226, 207, 234

#define RAY_PRIMARY 10, 45, 34
#define RAY_SECONDARY 27, 168, 155

#define FLOOR 107, 163, 104
#define SKY 230, 250, 252
#define HORIZON SKY

#define TARGET_MISS 255, 0, 0
#define TARGET_HIT 0, 255, 0

#define COLOR_BACKGROUND(x) SDL_SetRenderDrawColor(x, BACKGROUND, 255)
#define COLOR_HEADING(x) SDL_SetRenderDrawColor(x, HEADING, 255)
#define COLOR_TEXT(x) SDL_SetRenderDrawColor(x, TEXT, 255)
#define COLOR_ACCENT(x) SDL_SetRenderDrawColor(x, ACCENT, 255)
#define COLOR_FOREGROUND(x) SDL_SetRenderDrawColor(x, FOREGROUND, 255)

#define COLOR_RAY_PRIMARY(x) SDL_SetRenderDrawColor(x, RAY_PRIMARY, 255)
#define COLOR_RAY_SECONDARY(x) SDL_SetRenderDrawColor(x, RAY_SECONDARY, 255)

#define COLOR_FLOOR(x) SDL_SetRenderDrawColor(x, FLOOR, 255)
#define COLOR_SKY(x) SDL_SetRenderDrawColor(x, SKY, 255)
#define COLOR_HORIZON(x) SDL_SetRenderDrawColor(x, HORIZON, 255)

#define COLOR_TARGET_HIT(x) SDL_SetRenderDrawColor(x, TARGET_HIT, 255)
#define COLOR_TARGET_MISS(x) SDL_SetRenderDrawColor(x, TARGET_MISS, 255)

#define COLOR_WHITE(x) SDL_SetRenderDrawColor(x, 255, 255, 255, 255)
#define COLOR_BLACK(x) SDL_SetRenderDrawColor(x, 0, 0, 0, 255)
#define COLOR_RED(x) SDL_SetRenderDrawColor(x, 255, 0, 0, 255)
#define COLOR_GREEN(x) SDL_SetRenderDrawColor(x, 0, 255, 0, 255)
#define COLOR_BLUE(x) SDL_SetRenderDrawColor(x, 0, 0, 255, 255)