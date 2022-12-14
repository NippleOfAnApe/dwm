/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 6;       	/* border pixel of windows */
static const unsigned int gappx     = 10;     	/* gaps between windows */
static const unsigned int snap      = 3;       	/* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "Fira Mono Medium:size=13"};
static const char dmenufont[]       = "Fira Mono Medium:size=13";
static const char col_gray1[]       = "#264653";
static const char col_gray2[]       = "#264653";
static const char col_gray3[]       = "#F4A261";
static const char col_gray4[]       = "#E9C46A";
static const char col_gray5[]       = "#E76F51";
static const char col_cyan[]        = "#2A9D8F";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_gray5 },
};

/* tagging */
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    	title      	tags mask   isfloating   monitor */
	{ "firefox",     NULL,   	NULL,  		0,         	0,           -1 }
};

/* layout(s) */
static const float mfact     	= 0.5; 	/* factor of master area size [0.05..0.95] */
static const int nmaster     	= 1;    /* number of clients in master area */
static const int resizehints 	= 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; 	/* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]",      tile },    /* first entry is default */
	{ "[]",      NULL },
	{ "[]",      monocle},    /* no layout function means floating behavior */
};

//static const char *upvol[]   = { "/home/george/.local/bin/volumePlus",     NULL };
//static const char *downvol[] = { "/home/george/.local/bin/volumeMinus",     NULL };
//static const char *mutevol[] = { "/usr/bin/amixer", "sset",   "Master", "toggle",  NULL };
//static const char *light_up[] = {"/home/george/.local/bin/brightnessUp", NULL};
//static const char *light_down[] = {"/home/george/.local/bin/brightnessDown", NULL};
//static const char *prtScFull[] = { "/usr/bin/flameshot", "full", "-c", "-p", "/W/Media", NULL};
//static const char *prtScGUI[] = { "/usr/bin/flameshot", "gui", NULL};
//static const char *dmenuemoji[]  = { "/home/george/.local/bin/dmenuunicode", NULL };
//static const char *clipmenu[] = { "/usr/bin/clipmenu", NULL};
//static const char *spawnSlock[] = { "/usr/local/bin/slock", NULL};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/zsh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[] = { "st", NULL };
static const char *browsercmd[] = { "firefox", NULL };
//static const char *codiumcmd[] = { "/usr/bin/codium", NULL };
//static const char *telegram[] = { "telegram-desktop", NULL };
//static const char *pcmanfm[] = { "pcmanfm", NULL };

#include "movestack.c"
#include <X11/XF86keysym.h>	//https://github.com/freedesktop/xorg-x11proto/blob/master/XF86keysym.h

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             			XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,             			XK_F2, 	   spawn,          {.v = browsercmd } },
	//{ MODKEY,             			XK_F3, 	   spawn,          {.v = codiumcmd } },
	//{ MODKEY,             			XK_F4, 	   spawn,          {.v = telegram } },
	//{ MODKEY,             			XK_F1, 	   spawn,          {.v = pcmanfm } },
	//{ MODKEY|ShiftMask,             XK_f, 	   spawn,          {.v = dmenuemoji } },
	//{ MODKEY|ShiftMask,             XK_d, 	   spawn,          {.v = clipmenu } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_a,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_d,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_q,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_e,      setmfact,       {.f = +0.05} },
	{ MODKEY,             			XK_z,      setcfact,       {.f = +0.25} },
	{ MODKEY,             			XK_c,      setcfact,       {.f = -0.25} },
	{ MODKEY,             			XK_x,      setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,             XK_a,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,             			XK_w,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
    //{ MODKEY,						XK_Print,   spawn,		   {.v = prtScGUI}},
    //{ 0,						    XK_Print,   spawn,		   {.v = prtScFull}},
    //{ MODKEY,					    XK_BackSpace,   spawn,		   {.v = spawnSlock}},
	//{ 0,     		XF86XK_AudioLowerVolume,   spawn, 		   {.v = downvol } },
	//{ 0,         	XF86XK_AudioMute, 		   spawn,          {.v = mutevol } },
	//{ 0,         	XF86XK_AudioRaiseVolume,   spawn, 		   {.v = upvol   } },
	//{ 0,			XF86XK_MonBrightnessUp,	   spawn,		   {.v = light_up}},
	//{ 0,			XF86XK_MonBrightnessDown,  spawn,	  	   {.v = light_down}},
//	{ 0,			XF86XK_AudioStop,  		   spawn,	  	   {.v = spawnSlock}},
//	{ 0,							XK_Print,	   spawn,		   {.v = prtScFull}},
//	{ MODKEY,						XK_Print,	   spawn,		   {.v = prtScGUI}},
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
//	{ ClkStatusText,        0,              Button2,        spawn,          {.v = nmtuicmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

