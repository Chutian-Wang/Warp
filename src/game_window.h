#ifdef WINDOW_PROPERTIES
static_assert(false, "[compile time] Redefinition of window properties.")
#endif

#define WINDOW_PROPERTIES

// Same as DOOM 1993 window size.
#define SCREEN_X 320
#define SCREEN_Y 200
#define PIXEL_UPSCALE 3
#define WINDOW_X (SCREEN_X * PIXEL_UPSCALE)
#define WINDOW_Y (SCREEN_Y * PIXEL_UPSCALE)