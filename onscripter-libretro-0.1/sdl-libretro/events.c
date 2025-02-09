#include <SDL_libretro.h>
#include <sdl/src/events/SDL_events_c.h>
#include <sdl/src/video/dummy/SDL_nullevents_c.h>
#define USE_EVTEST 0
#if USE_EVTEST
#include <linux/input.h> //EVIOCGRAB
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <linux/input.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>

#include <SDL_libretro.h>
#include <sdl/src/events/SDL_events_c.h>
//#include <sdl/src/video/dummy/SDL_nullevents_c.h>

static int do_capture(const char *device, int grab_flag);
#endif

static void PumpKeyboardEvents(void)
{
  static int16_t keys[RETROK_LAST] = {0};
  static SDL_keysym sym;
  for (int i = 0; i < RETROK_LAST; ++i) {
    int16_t state = SDL_libretro_input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0, i);
    if (keys[i] != state) {
      keys[i] = state;
      sym.scancode = i;
      sym.sym = i;
      SDL_PrivateKeyboard(state ? SDL_PRESSED : SDL_RELEASED, &sym);
    }
  }

#if 0
//github.com/minexew/GA330-libretro
//src/libretro-main.cpp
	{	
		int16_t state = SDL_libretro_input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A);
		SDL_keysym sym;
		sym.scancode = SDLK_RETURN;
		sym.sym = SDLK_RETURN;
		SDL_PrivateKeyboard(state ? SDL_PRESSED : SDL_RELEASED, &sym);
	}
#else
//see github.com/madcock/libretro-onscripter

  static int16_t buttons[16] = {0};
  static const int bkeys[16] = {
    [RETRO_DEVICE_ID_JOYPAD_B]      = SDLK_SPACE,
    [RETRO_DEVICE_ID_JOYPAD_Y]      = SDLK_RCTRL,
    [RETRO_DEVICE_ID_JOYPAD_SELECT] = SDLK_0,
    [RETRO_DEVICE_ID_JOYPAD_START]  = SDLK_a,
    [RETRO_DEVICE_ID_JOYPAD_UP]     = SDLK_UP,
    [RETRO_DEVICE_ID_JOYPAD_DOWN]   = SDLK_DOWN,
    [RETRO_DEVICE_ID_JOYPAD_LEFT]   = SDLK_LEFT,
    [RETRO_DEVICE_ID_JOYPAD_RIGHT]  = SDLK_RIGHT,
    [RETRO_DEVICE_ID_JOYPAD_A]      = SDLK_RETURN,
    [RETRO_DEVICE_ID_JOYPAD_X]      = SDLK_ESCAPE,
    [RETRO_DEVICE_ID_JOYPAD_L]      = SDLK_o,
    [RETRO_DEVICE_ID_JOYPAD_R]      = SDLK_s,
    [RETRO_DEVICE_ID_JOYPAD_L2]     = SDLK_PAGEUP,
    [RETRO_DEVICE_ID_JOYPAD_R2]     = SDLK_PAGEDOWN,
    [RETRO_DEVICE_ID_JOYPAD_L3]     = SDLK_TAB,
    [RETRO_DEVICE_ID_JOYPAD_R3]     = SDLK_q,
  };
  for (int i = 0; i < 16; ++i) {
    int16_t state = SDL_libretro_input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i);
    int k = bkeys[i];
    if (k && buttons[i] != state) {
      buttons[i] = state;
      sym.scancode = k;
      sym.sym = k;
      SDL_PrivateKeyboard(state ? SDL_PRESSED : SDL_RELEASED, &sym);
    }
  }
#endif
}

static Uint8 to_button(int16_t pressed)
{
  if (pressed == 1)
    return SDL_BUTTON_LEFT;
  if (pressed == 2)
    return SDL_BUTTON_RIGHT;
  return 0;
}

static void PumpMouseEvents(void)
{
#if 0
//no mouse move
  static Sint16 x = 0;
  static Sint16 y = 0;
  static Uint8 btn = 0;
  static int16_t pressed = 0;

  SDL_Surface *screen = SDL_GetVideoSurface();
  int16_t _x = SDL_libretro_input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_X);
  int16_t _y = SDL_libretro_input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_Y);
  int16_t _pressed = 0;

  while (SDL_libretro_input_state_cb(0, RETRO_DEVICE_POINTER, _pressed, RETRO_DEVICE_ID_POINTER_PRESSED)) {
    _pressed += 1;
  }

  if (SDL_libretro_input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_LEFT)) {
    _pressed = 1;
  }
  if (SDL_libretro_input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_RIGHT)) {
    _pressed = 2;
  }

  if (pressed) {
    if (!_pressed) {
      btn = to_button(pressed);
      SDL_PrivateMouseButton(SDL_RELEASED, btn, x, y);
      pressed = 0;
    }
  } else {
    if (_pressed) {
      x = screen->w * (_x + 0x7fff) / 0xffff;
      y = screen->h * (_y + 0x7fff) / 0xffff;
      btn = to_button(_pressed);
      SDL_WarpMouse(x, y);
      SDL_PrivateMouseButton(SDL_PRESSED, btn, 0, 0);
      pressed = _pressed;
    }
  }
#else
//with mouse move
//see github.com/madcock/libretro-onscripter
  static Sint16 x = 0;
  static Sint16 y = 0;
  static Uint8 btn = 0;
  static int16_t pressed = 0;

  SDL_Surface *screen = SDL_GetVideoSurface();
  int16_t _x = SDL_libretro_input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_X);
  int16_t _y = SDL_libretro_input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_Y);
  int16_t _pressed = 0;

  _x = screen->w * (_x + 0x7fff) / 0xffff;
  _y = screen->h * (_y + 0x7fff) / 0xffff;
  if (x != _x || y != _y) {
    x = _x;
    y = _y;
    SDL_PrivateMouseMotion(0, 0, x, y);
  }

  while (SDL_libretro_input_state_cb(0, RETRO_DEVICE_POINTER, _pressed, RETRO_DEVICE_ID_POINTER_PRESSED)) {
    _pressed += 1;
  }

  if (SDL_libretro_input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_LEFT)) {
    _pressed = 1;
  }
  if (SDL_libretro_input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_RIGHT)) {
    _pressed = 2;
  }

  if (pressed) {
    if (!_pressed) {
      btn = to_button(pressed);
      SDL_PrivateMouseButton(SDL_RELEASED, btn, x, y);
      pressed = 0;
    }
  } else {
    if (_pressed) {
      btn = to_button(_pressed);
      SDL_PrivateMouseButton(SDL_PRESSED, btn, x, y);
      pressed = _pressed;
    }
  }
#endif
}

void DUMMY_PumpEvents(_THIS)
{
  PumpKeyboardEvents();
  PumpMouseEvents();
  SDL_libretro_co_yield();
}

void DUMMY_InitOSKeymap(_THIS)
{
#if USE_EVTEST
        //do_capture("/dev/input/event1", 1);
#endif
}



#if USE_EVTEST
static unsigned int joypad = 0;

static volatile sig_atomic_t stop = 0;
static void interrupt_handler(int sig)
{
    stop = 1;
}




static int print_events(int fd)
{
static SDL_keysym sym;

	struct input_event ev[64];
	int i, rd;
	fd_set rdfs;

	FD_ZERO(&rdfs);
	FD_SET(fd, &rdfs);

	while (!stop) {
	    select(fd + 1, &rdfs, NULL, NULL, NULL);
	    if (stop)
		break;
	    rd = read(fd, ev, sizeof(ev));

	    if (rd < (int) sizeof(struct input_event)) {
		fprintf(stderr, "expected %d bytes, got %d\n", (int) sizeof(struct input_event), rd);
		perror("\nevtest: error reading");
		return 1;
	    }

	    for (i = 0; i < rd / sizeof(struct input_event); i++) {
		unsigned int type, code;

		type = ev[i].type;
		code = ev[i].code;


		if (type == EV_KEY) {
		    fprintf(stderr, "Event: time %ld.%06ld, ", ev[i].time.tv_sec, ev[i].time.tv_usec);
		    fprintf(stderr, "type %d, code %d, ", type, code);
		    fprintf(stderr, "value %d\n", ev[i].value);

sym.scancode = (SDLKey)code;
sym.sym = (SDLKey)code;
SDL_PrivateKeyboard(ev[i].value ? SDL_PRESSED : SDL_RELEASED, &sym);

	/*
	evtest, /dev/input/event1
	/dev/input/event0:      sunxi-gpadc0
	/dev/input/event1:      gpio-keys
	Select the device event number [0-1]: 1
	1
	Input driver version is 1.0.1
	Input device ID: bus 0x19 vendor 0x1 product 0x1 version 0x100
	Input device name: "gpio-keys"
	Supported events:
	Event type 0 (EV_SYN)
	Event type 1 (EV_KEY)
	UP, PE0, left up：type 1 (EV_KEY), code 114 (KEY_VOLUMEDOWN), value 1->0
	DOWN, PE7, left down：type 1 (EV_KEY), code 115 (KEY_VOLUMEUP), value 1
	LEFT: PE6, left left：type 1 (EV_KEY), code 116 (KEY_POWER), value 1
	RIGHT: PE4, left right：type 1 (EV_KEY), code 117 (KEY_KPEQUAL), value 1
	X, PE11, right up：type 1 (EV_KEY), code 120 (KEY_SCALE), value 1
	B, PE12, right down：type 1 (EV_KEY), code 119 (KEY_PAUSE), value 1
	Y, PE2, right left：type 1 (EV_KEY), code 118 (KEY_KPPLUSMINUS), value 1
	A, PE13, right right：type 1 (EV_KEY), code 121 (KEY_KPCOMMA), value 1
	SELECT, PE8, left 1：type 1 (EV_KEY), code 122 (KEY_HANGUEL), value 1
	START, PE9, left 2：type 1 (EV_KEY), code 123 (KEY_HANJA), value 1
	MENU, PE3, right 1：type 1 (EV_KEY), code 124 (KEY_YEN), value 1
	L, PE1，left top: Event code 125 (KEY_LEFTMETA)
	R, PE10, right top: Event code 126 (KEY_RIGHTMETA)
	*/

	#define MY_Key_L (121)//space : A
	#define MY_Key_O (119)//B : B
	#define MY_Key_1 (122)//1 : Select
	#define MY_Key_2 (123)//2 : Start
	#define MY_Key_W (114)//Up : up
	#define MY_Key_S (115)//Down : Down
	#define MY_Key_A (116)//Left : Left
	#define MY_Key_D (117)//Right : Right

		    if (ev[i].value == 1) {
		        switch(code)
		        {
		            case MY_Key_L://space : A
		            {
		                joypad &= ~(1);
		                joypad |= 1;
		            }break;
		            case MY_Key_O://B : B
		            {
		                joypad &= ~(1<<1);
		                joypad |= 1<<1;
		            }break;
		            case MY_Key_1://1 : Select
		            {
		                joypad &= ~(1<<2);
		                joypad |= 1<<2;
		            }break;
		            case MY_Key_2://2 : Start
		            {
		                joypad &= ~(1<<3);
		                joypad |= 1<<3;
		            }break;
		            case MY_Key_W://Up : up
		            {
		                joypad &= ~(1<<4);
		                joypad |= 1<<4;
		            }break;
		            case MY_Key_S://Down : Down
		            {
		                joypad &= ~(1<<5);
		                joypad |= 1<<5;
		            }break;
		            case MY_Key_A://Left : Left
		            {
		                joypad &= ~(1<<6);
		                joypad |= 1<<6;
		            }break;
		            case MY_Key_D://Right : Right
		            {
		                joypad &= ~(1<<7);
		                joypad |= 1<<7;
		            }break;
		            default:break;
		        }

		        //qDebug()<<"keyPressEvent:"<<joypad;
		    } else if (ev[i].value == 0) {
		        switch(code)
		        {
		            case MY_Key_L://space : A
		            {
		                joypad &= ~(1);
		            }break;
		            case MY_Key_O://B : B
		            {
		                joypad &= ~(1<<1);
		            }break;
		            case MY_Key_1://1 : Select
		            {
		                joypad &= ~(1<<2);
		            }break;
		            case MY_Key_2://2 : Start
		            {
		                joypad &= ~(1<<3);
		            }break;
		            case MY_Key_W://Up : up
		            {
		                joypad &= ~(1<<4);
		            }break;
		            case MY_Key_S://Down : Down
		            {
		                joypad &= ~(1<<5);
		            }break;
		            case MY_Key_A://Left : Left
		            {
		                joypad &= ~(1<<6);
		            }break;
		            case MY_Key_D://Right : Right
		            {
		                joypad &= ~(1<<7);
		            }break;
		            default:break;
		        }
		        //qDebug()<<"keyReleaseEvent:"<<joypad;
		    }
		}
	    }

	}

	ioctl(fd, EVIOCGRAB, (void*)0);
	return EXIT_SUCCESS;
}
static int test_grab(int fd, int grab_flag)
{
	int rc;

	rc = ioctl(fd, EVIOCGRAB, (void*)1);

	if (rc == 0 && !grab_flag)
	    ioctl(fd, EVIOCGRAB, (void*)0);

	return rc;
}
static int do_capture(const char *device, int grab_flag)
{
	int fd;
	char *filename = NULL;

	filename = strdup(device);

	if (!filename)
	    return EXIT_FAILURE;

	if ((fd = open(filename, O_RDONLY)) < 0) {
	    //QString str = QString("evtest : open %1").arg(filename);
	    perror("evtest");
	    //perror(str.toAscii().constData());
	    if (errno == EACCES && getuid() != 0) {
		fprintf(stderr, "You do not have access to %s. Try "
		        "running as root instead.\n",
		        filename);
	    } else {
		fprintf(stderr, "You do not have access to %s.\n",
		        filename);
	    }
	    fflush(stderr);
	    goto error;
	}

	if (!isatty(fileno(stdout)))
	    setbuf(stdout, NULL);

	if (test_grab(fd, grab_flag))
	{
	    fprintf(stderr, "***********************************************\n");
	    fprintf(stderr, "  This device is grabbed by another process.\n");
	    fprintf(stderr, "  No events are available to evtest while the\n"
		   "  other grab is active.\n");
	    fprintf(stderr, "  In most cases, this is caused by an X driver,\n"
		   "  try VT-switching and re-run evtest again.\n");
	    fprintf(stderr, "  Run the following command to see processes with\n"
		   "  an open fd on this device\n"
		   " \"fuser -v %s\"\n", filename);
	    fprintf(stderr, "***********************************************\n");
	}

	signal(SIGINT, interrupt_handler);
	signal(SIGTERM, interrupt_handler);

	free(filename);

	return print_events(fd);

	error:
	free(filename);
	return EXIT_FAILURE;
}
#endif


