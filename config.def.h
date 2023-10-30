/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 1;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const int smartborders              = 1;
static const unsigned int borderpx         = 3;  /* border pixel of windows */
static const float bordercolor[]           = COLOR(0x00000000);
static const float focuscolor[]            = COLOR(0x7aa6daff);
static const float urgentcolor[]           = COLOR(0xd54e53ff);
/* To conform the xdg-protocol, set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.1, 0.1, 0.1, 1.0}; /* You can also use glsl colors */

/* Autostart */
static const char *const autostart[] = {
	"/home/korei/.config/dwl/dwlinit.sh", NULL,
	NULL /* terminate */
};

/* tagging - TAGCOUNT must be no greater than 31 */
#define TAGCOUNT (10)

/* logging */
static int log_level = WLR_ERROR;

/* keyboard layout change notification for status bar */
static const char  kblayout_file[] = "/tmp/dwl-keymap";
static const char *kblayout_cmd[]  = {"pkill", "-RTMIN+1", "someblocks", NULL};
static const int   kblayout_perclient = 0;

static const Rule rules[] = {
	/* app_id      title       tags mask  isfloating opacity          monitor */
	{ "corectrl",  NULL,       0 << 0,       0,           -1 },
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "[M]",      monocle },
	{ "|v|",      vertile },
	{ "><>",      NULL }    /* no layout function means floating behavior */
};

/* monitors */
static const MonitorRule monrules[] = {
	/* name       mfact nmaster scale layout       rotate/reflect                x    y */
	/* example of a HiDPI laptop monitor:
	{ "eDP-1",    0.5,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	*/
	/* defaults */
	{ NULL,       0.55, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
  /* can specify fields: rules, model, layout, variant, options */
  /* example:
  .options = "ctrl:nocaps",
  */
  .layout = "us,ua",
  .options = "grp:win_space_toggle,caps:escape",
};

static const int repeat_rate = 60;
static const int repeat_delay = 170;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 1;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT;
static const double accel_speed = -0.5;
static const int cursor_timeout = 2;

/* separate values for trackpad */
static const enum libinput_config_accel_profile accel_profile_trackpad = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed_trackpad = 0.0;
/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_LOGO
#define SHIFT WLR_MODIFIER_SHIFT
#define ALT WLR_MODIFIER_ALT
#define CTRL WLR_MODIFIER_CTRL
#define SUPER WLR_MODIFIER_LOGO

#define TAGKEYS(KEY,TAG) \
	{ SUPER,       KEY,            view,            {.ui = 1 << TAG} }, \
	{ SUPER|ALT,   KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ SUPER|SHIFT, KEY,            tag,             {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char* Term[] = { "footclient", NULL };
static const char* TermAlt[] = { "foot", NULL };
static const char* Menu[] = { "fuzzel", NULL };
static const char* PowerMenu[] = { "powermenu.sh", NULL };
static const char* AudioUpdate[] = { "pkill", "-RTMIN+12", "someblocks", NULL };
static const char* AudioLower[] = { "wpctl", "set-volume", "-l", "1", "@DEFAULT_AUDIO_SINK@", "3%-", NULL };
static const char* AudioRaise[] = { "wpctl", "set-volume", "-l", "1", "@DEFAULT_AUDIO_SINK@", "3%+", NULL };
static const char* AudioMute[] = { "wpctl", "set-mute", "@DEFAULT_AUDIO_SINK@", "toggle", NULL };
static const char* MuteMic[] = { "MuteMic.sh", NULL };
static const char* AudioPlayPause[] = { "playerctl", "play-pause", NULL };
static const char* AudioPause[] = { "playerctl", "pause", NULL };
static const char* AudioNext[] = { "playerctl", "next", NULL };
static const char* AudioPrev[] = { "playerctl", "previous", NULL };
static const char* Mako[] = { "mako.sh", NULL };
static const char* Mixer[] = { "footclient", "pulsemixer", NULL };
static const char* Emoji[] = { "emoji.sh", NULL };
static const char* Calc[] = { "footclient", "-e", "qalc", NULL };
static const char* Print[] = { "PrintDwl.sh", NULL };
static const char* PrintSel[] = { "PrintDwl.sh", "Select", NULL };
static const char* PrintSave[] = { "PrintDwl.sh", "Save", NULL };
static const char* PrintSelSave[] = { "PrintDwl.sh", "SelectSave", NULL };
static const char* BMonUp[] = { "light", "-T", "1.4", NULL };
static const char* BMonDown[] = { "light", "-T", "0.72", NULL };
static const char* BufferSave[] = { "buffer-save.sh", NULL };
static const char* BufferToggle[] = { "buffer-toggle.sh", NULL };
static const char* RecToggle[] = { "rec-toggle.sh", NULL };
static const char* ScreenLock[] = { "Lock.sh", "lock", NULL };
static const char* Swayidle[] = { "Lock.sh", "toggle", NULL };
static const char* Thunar[] = { "Thunar", NULL };

#include "keys.h"
static const Key keys[] = {
  /* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
  /* modifier		key				function		argument */
  { SUPER,                                Key_b,                     togglebar,        { 0 }                       },
  { 0,                                    Key_XF86AudioPlay,         spawn,            { .v = AudioPlayPause }     },
  { 0,                                    Key_XF86AudioPause,        spawn,            { .v = AudioPause }         },
  { 0,                                    Key_XF86AudioNext,         spawn,            { .v = AudioNext }          },
  { 0,                                    Key_XF86AudioPrev,         spawn,            { .v = AudioPrev }          },
  { 0,                                    Key_XF86AudioLowerVolume,  spawn,            { .v = AudioLower }         },
  { 0,                                    Key_XF86AudioRaiseVolume,  spawn,            { .v = AudioRaise }         },
  { 0,                                    Key_XF86AudioMute,         spawn,            { .v = AudioMute }          },
  { 0,                                    Key_XF86AudioMicMute,      spawn,            { .v = MuteMic }            },
  { SUPER,                                Key_n,                     spawn,            { .v = MuteMic }            },
  { 0,                                    Key_XF86AudioLowerVolume,  spawn,            { .v = AudioUpdate }        },
  { 0,                                    Key_XF86AudioRaiseVolume,  spawn,            { .v = AudioUpdate }        },
  { 0,                                    Key_XF86AudioMute,         spawn,            { .v = AudioUpdate }        },
  { 0,                                    Key_XF86MonBrightnessUp,   spawn,            { .v = BMonUp }             },
  { 0,                                    Key_XF86MonBrightnessDown, spawn,            { .v = BMonDown }           },
  { 0,                                    Key_Print,                 spawn,            { .v = Print }              },
  { SUPER,                                Key_Print,                 spawn,            { .v = PrintSave }          },
  { SHIFT,                                Key_Print,                 spawn,            { .v = PrintSel }           },
  { SUPER | SHIFT,                        Key_Print,                 spawn,            { .v = PrintSelSave }       },
  { SUPER | SHIFT,                        Key_Insert,                spawn,            { .v = Mako }               },
  { SUPER,                                Key_Insert,                spawn,            { .v = Mixer }              },
  { SUPER | CTRL,                         Key_Insert,                spawn,            { .v = Swayidle }           },
  { SUPER,                                Key_e,                     spawn,            { .v = Calc }               },
  { SUPER,                                Key_t,                     spawn,            { .v = Thunar }             },
  { SUPER,                                Key_p,                     spawn,            { .v = Menu }               },
  { SUPER | CTRL,                         Key_p,                     spawn,            { .v = Emoji }              },
  { SUPER,                                Key_Return,                spawn,            { .v = Term }               },
  { SUPER | SHIFT,                        Key_Return,                spawn,            { .v = TermAlt }            },
  { SUPER,                                Key_p,                     spawn,            { .v = Menu }               },
  { SUPER,                                Key_j,                     focusstack,       { .i = +1 }                 },
  { SUPER,                                Key_k,                     focusstack,       { .i = -1 }                 },
  { SUPER,                                Key_z,                     focusstack,       { .i = +1 }                 },
  { SUPER,                                Key_x,                     focusstack,       { .i = -1 }                 },
  { SUPER,                                Key_i,                     incnmaster,       { .i = +1 }                 },
  { SUPER | SHIFT,                        Key_i,                     incnmaster,       { .i = -1 }                 },
  { SUPER,                                Key_h,                     setmfact,         { .f = -0.05 }              },
  { SUPER,                                Key_l,                     setmfact,         { .f = +0.05 }              },
  { SUPER,                                Key_c,                     setlayout,        { .v = &layouts[0] }        },
  { SUPER,                                Key_s,                     setlayout,        { .v = &layouts[1] }        },
  { SUPER,                                Key_v,                     setlayout,        { .v = &layouts[2] }        },
  { SUPER,                                Key_grave,                 togglefloating,   { 0 }                       },
  { SUPER | SHIFT,                        Key_s,                     togglesticky,     { 0 }                       },
  { SUPER,                                Key_f,                     togglefullscreen, { 0 }                       },
  { SUPER,                                Key_g,                     zoom,             { 0 }                       },
  { SUPER,                                Key_Tab,                   view,             { 0 }                       },
  { SUPER,                                Key_a,                     rotatetags,       { .i = -1 }                 },
  { SUPER,                                Key_d,                     rotatetags,       { .i = 1 }                  },
  { SUPER | SHIFT,                        Key_a,                     rotatetags,       { .i = -2 }                 },
  { SUPER | SHIFT,                        Key_d,                     rotatetags,       { .i = 2 }                  },
  { SUPER,                                Key_w,                     killclient,       { 0 }                       },
  { ALT,                                  Key_Escape,                spawn,            { .v = PowerMenu }          },
  { ALT,                                  Key_Caps_Lock,             spawn,            { .v = PowerMenu }          },
  { SUPER,                                Key_Home,                  spawn,            { .v = BufferToggle }       },
  { SUPER,                                Key_End,                   spawn,            { .v = BufferSave }         },
  { SUPER,                                Key_F12,                   spawn,            { .v = RecToggle }          },
  { SUPER | SHIFT,                        Key_BackSpace,             spawn,            { .v = ScreenLock }         },
  { SUPER,                                Key_comma,                 focusmon,         { .i = WLR_DIRECTION_LEFT } },
  { SUPER,                                Key_period,                focusmon,         { .i = WLR_DIRECTION_RIGHT }},
  { SUPER | SHIFT,                        Key_comma,                 tagmon,           { .i = WLR_DIRECTION_LEFT } },
  { SUPER | SHIFT,                        Key_period,                tagmon,           { .i = WLR_DIRECTION_RIGHT }},
  TAGKEYS(Key_1, 0),
  TAGKEYS(Key_2, 1),
  TAGKEYS(Key_3, 2),
  TAGKEYS(Key_4, 3),
  TAGKEYS(Key_5, 4),
  TAGKEYS(Key_6, 5),
  TAGKEYS(Key_7, 6),
  TAGKEYS(Key_8, 7),
  TAGKEYS(Key_9, 8),
  TAGKEYS(Key_0, 9),
  { SUPER | SHIFT,                        Key_q,                     quit,             { 0 }                       },
 /* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
  { WLR_MODIFIER_CTRL | WLR_MODIFIER_ALT, XKB_KEY_Terminate_Server,  quit,             { 0 }                       },
#define CHVT(KEY, n)                                               \
  {                                                                \
    WLR_MODIFIER_CTRL | WLR_MODIFIER_ALT, KEY, chvt, { .ui = (n) } \
  }
  CHVT(Key_F1, 1),
  CHVT(Key_F2, 2),
  CHVT(Key_F3, 3),
  CHVT(Key_F4, 4),
  CHVT(Key_F5, 5),
  CHVT(Key_F6, 6),
  CHVT(Key_F7, 7),
  CHVT(Key_F8, 8),
  CHVT(Key_F9, 9),
  CHVT(Key_F10, 10),
  CHVT(Key_F11, 11),
  CHVT(Key_F12, 12),
};

static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};
