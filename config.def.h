/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 6;        /* horizontal padding for statusbar */
static const int vertpadbar         = 7;        /* vertical padding for statusbar */
static const char *fonts[]          = {"Ubuntu:weight=bold:size=8:antialias=true:hinting=true", 
                                       "Hack:size=8:antialias=true:autohint=true" };
static const char dmenufont[]       = "Ubuntu:weight=bold:size=8:antialias=true:hinting=true";

/* tokyonight colorscheme  */
static const char col_1[]           = "#1a1b26"; /* background color of bar */
static const char col_2[]           = "#1a1b26"; /* border color unfocused windows */
static const char col_3[]           = "#d7d7d7";
static const char col_4[]           = "#f7768e"; /* border color focused windows and tags */
static const char col_5[]           = "#7aa2f7"; /* blue */

/* opacity */
static const unsigned int baralpha    = 0xff;
static const unsigned int borderalpha = OPAQUE;

/* color & opacity mapping */
static const char *colors[][3]        = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_3, col_1, col_2 },
	[SchemeSel]  = { col_3, col_4, col_4 },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
// static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
// static const char *tags[] = { "", "", "", "", "", "♫", "⛥", "", "" };
// static const char *tags[] = { "dev", "www", "sys", "org", "chat", "mus", "daw", "sci", "etc"};
static const char *tags[] = { "dev1", "dev2", "www", "chat & mus", "dev3", "zoom", "rec", "etc"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "zoom",     NULL,       NULL,       1 << 5,       1,           -1 },
	{ "obs",      NULL,       NULL,       1 << 6,       0,           -1 },
    { "Brave",    NULL,       NULL,       1 << 2,       0,           -1 }
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "grid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      grid },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask

#define TAGKEYS(KEY,TAG)												\
	{1, {{MODKEY, KEY}},								view,           {.ui = 1 << TAG} },	\
	{1, {{MODKEY|ControlMask, KEY}},					toggleview,     {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ShiftMask, KEY}},						tag,            {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ControlMask|ShiftMask, KEY}},			toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/zsh", "-c", cmd, NULL } }

/* commands */
#define USER_TERMINAL "alacritty"
static const char *dmenucmd[]   = { "dmenu_run", "-fn", dmenufont,
    "-h", "20",
    "-nb", col_1, "-nf", col_3, "-sb", col_4, "-sf", col_3, NULL };
static const char *termcmd[]    = { USER_TERMINAL, NULL };
static const char *browsercmd[] = { "brave", NULL };
static const char *neovimcmd[]  = { USER_TERMINAL, "nvim", NULL };
static const char *emacscmd[]   = { "emacsclient", "-c", "-a=\"\"", NULL };

static Keychord keychords[] = {
	/* Keys                                function        argument */
	{1, {{MODKEY|ShiftMask, XK_Return}},   spawn,          {.v = dmenucmd } },
	{1, {{MODKEY, XK_Return}},             spawn,          {.v = termcmd } },
	{1, {{MODKEY, XK_e}},	                 spawn,          {.v = neovimcmd} },
	{1, {{MODKEY|ShiftMask, XK_e}},	       spawn,          {.v = emacscmd} },
  {1, {{MODKEY, XK_b}},                  spawn,          {.v = browsercmd }},
	{1, {{MODKEY|ShiftMask, XK_b}},	       togglebar,      {0} },
	{1, {{MODKEY, XK_j}},						       focusstack,     {.i = +1 } },
	{1, {{MODKEY, XK_k}},						 	     focusstack,     {.i = -1 } },
	{1, {{MODKEY|ShiftMask, XK_j}},        rotatestack,    {.i = +1 } },
	{1, {{MODKEY|ShiftMask, XK_k}},        rotatestack,    {.i = -1 } },
  {1, {{MODKEY, XK_i}},						 	     incnmaster,     {.i = +1 } },
	{1, {{MODKEY, XK_d}},						 	     incnmaster,     {.i = -1 } },
	{1, {{MODKEY, XK_h}},						 	     setmfact,       {.f = -0.05} },
	{1, {{MODKEY, XK_l}},						 	     setmfact,       {.f = +0.05} },

  /* Screenshot */
  {1, {{MODKEY, XK_s}},                  spawn,          SHCMD("escrotum -s -C") },

  /* Volume & Brightness */
  {1, {{MODKEY, XK_Down}},               spawn,          SHCMD("pamixer -d 5 && pkill -RTMIN+10 dwmblocks") }, /*0x1008ff11*/
  {1, {{MODKEY, XK_Up}},                 spawn,          SHCMD("pamixer -i 5 && pkill -RTMIN+10 dwmblocks") }, /*XF86XK_AudioRaiseVolume*/
  {1, {{MODKEY|ShiftMask, XK_m}},        spawn,          SHCMD("pamixer -t && pkill -RTMIN+10 dwmblocks") }, /*XF86XK_AudioMute*/
  {1, {{MODKEY|ShiftMask, XK_Down}},     spawn,          SHCMD("brightnessctl set 5%-") },
  {1, {{MODKEY|ShiftMask, XK_Up}},       spawn,          SHCMD("brightnessctl set 5%+") },

//	{1, {{MODKEY, XK_Return}},						 zoom,           {0} },
	{1, {{MODKEY, XK_Tab}},							   view,           {0} },
	{1, {{MODKEY|ShiftMask, XK_c}},				 killclient,     {0} },
	{1, {{MODKEY, XK_t}},							     setlayout,      {.v = &layouts[0]} },
	{1, {{MODKEY, XK_f}},							     setlayout,      {.v = &layouts[1]} },
	{1, {{MODKEY, XK_m}},							     setlayout,      {.v = &layouts[2]} },
  {1, {{MODKEY, XK_g}},                  setlayout,      {.v = &layouts[3]} },
	{1, {{MODKEY, XK_space}},						   spawn,          SHCMD("~/.local/bin/statusbar/switch-layout.sh && pkill -RTMIN+11 dwmblocks") },
	{1, {{MODKEY|ShiftMask, XK_space}},		 togglefloating, {0} },
	{1, {{MODKEY, XK_0}},							     view,           {.ui = ~0 } },
	{1, {{MODKEY|ShiftMask, XK_0}},				 tag,            {.ui = ~0 } },
	{1, {{MODKEY, XK_comma}},						   focusmon,       {.i = -1 } },
	{1, {{MODKEY, XK_period}},						 focusmon,       {.i = +1 } },
	{1, {{MODKEY|ShiftMask, XK_comma}},		 tagmon,         {.i = -1 } },
	{1, {{MODKEY|ShiftMask, XK_period}},	 tagmon,         {.i = +1 } },
	{1, {{MODKEY|ControlMask, XK_comma}},  cyclelayout,    {.i = -1 } },
	{1, {{MODKEY|ControlMask, XK_period}}, cyclelayout,    {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{1, {{MODKEY|ShiftMask, XK_q}},				 quit,           {0} }, // Quit DWM
	{1, {{MODKEY|ShiftMask, XK_r}},        quit,           {1} }, // Restart DWM 

  /* volume keys */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

