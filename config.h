/* See LICENSE file for copyright and license details. */

/* appearance */
#include <X11/Xlib.h>
static       char font[]        = "monospace:size=9";
static       char* selbgcolor   = "#2c323b";
static       char* selfgcolor   = "#61afef";
static       char* normbgcolor  = "#2c323b";
static       char* normfgcolor  = "#bbbbbb";
static       char* urgbgcolor   = "#111111";
static       char* urgfgcolor   = "#cc0000";
static const char before[]      = "<";
static const char after[]       = ">";
static const char titletrim[]   = "...";
#if AWESOMEBAR_PATCH
static       int  tabwidth      = 200;
#else
static const int  tabwidth      = 200;
#endif // AWESOMEBAR_PATCH
static const Bool foreground    = True;
static       Bool urgentswitch  = False;
static const Bool tabcycle      = True;

#if BAR_HEIGHT_PATCH
static const int barheight = 30;  /* 0 means derive by font (default), otherwise absolute height */
#endif // BAR_HEIGHT_PATCH

/*
 * Where to place a new tab when it is opened. When npisrelative is True,
 * then the current position is changed + newposition. If npisrelative
 * is False, then newposition is an absolute position.
 */
static int  newposition   = 99;
static Bool npisrelative  = True;

#define SETPROP(p) { \
        .v = (char *[]){ "/bin/sh", "-c", \
                "prop=\"`xwininfo -children -id $1 | grep '^     0x' |" \
                "sed -e's@^ *\\(0x[0-9a-f]*\\) \"\\([^\"]*\\)\".*@\\1 \\2@' |" \
                "xargs -0 printf %b | dmenu -l 10 -w $1`\" &&" \
                "xprop -id $1 -f $0 8s -set $0 \"$prop\"", \
                p, winid, NULL \
        } \
}

#define MODKEY Mod1Mask
static const Key keys[] = {
	/* modifier             key           function     argument */
	// embed tabbed in the config of st now.
    // { MODKEY,               XK_n,    focusonce,   { 0 } },
	// { MODKEY,               XK_n,    spawn,       { 0 } },

    { MODKEY,               XK_bracketleft,rotate,     { .i = -1 } },
    { MODKEY,               XK_bracketright,rotate,    { .i = +1 } },
    { MODKEY|ShiftMask,     XK_bracketleft,movetab,    { .i = -1 } },
    { MODKEY|ShiftMask,     XK_bracketright,movetab,   { .i = +1 } },
	// Focus last tab.
	{ MODKEY,               XK_Tab,       rotate,      { .i = 0 } },
	{ 0,                    XK_Prior,     rotate,      { .i = -1 } },
	{ 0,                    XK_Next,      rotate,      { .i = +1 } },
	{ 0,                    XK_End,       rotate,      { .i = +99 } },
	{ 0,                    XK_Home,      rotate,      { .i = -99 } },
	{ MODKEY,               XK_1,         move,        { .i = 0 } },
	{ MODKEY,               XK_2,         move,        { .i = 1 } },
	{ MODKEY,               XK_3,         move,        { .i = 2 } },
	{ MODKEY,               XK_4,         move,        { .i = 3 } },
	{ MODKEY,               XK_5,         move,        { .i = 4 } },
	{ MODKEY,               XK_6,         move,        { .i = 5 } },
	{ MODKEY,               XK_7,         move,        { .i = 6 } },
	{ MODKEY,               XK_8,         move,        { .i = 7 } },
	{ MODKEY,               XK_9,         move,        { .i = 8 } },
	{ MODKEY,               XK_0,         move,        { .i = 9 } },

	{ MODKEY,               XK_w,         killclient,  { 0 } },
};
