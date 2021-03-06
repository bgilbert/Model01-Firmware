// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 01's firmware
 */


// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for "Numlock" mode, which is mostly just the Numlock specific LED mode
#include "Kaleidoscope-Numlock.h"

// Support shifted characters
#include <Kaleidoscope-TopsyTurvy.h>

// Support for an "LED off mode"
#include "LED-Off.h"

// Support for the "Boot greeting" effect, which pulses the 'LED' button for 10s
// when the keyboard is connected to a computer (or that computer is powered on)
#include "Kaleidoscope-LEDEffect-BootGreeting.h"

// Support for LED modes that set all LEDs to a single color
#include "Kaleidoscope-LEDEffect-SolidColor.h"

// Support for an LED mode that lights up the keys as you press them
#include "Kaleidoscope-LED-Stalker.h"

// Support for Keyboardio's internal keyboard testing mode
#include "Kaleidoscope-Model01-TestMode.h"


/** This 'enum' is a list of all the macros used by the Model 01's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

enum { MACRO_VERSION_INFO,
     };



/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   the special nature of the PROG key
  *   keeping NUM and FN consistent and accessible on all layers
  *
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  */

enum { QWERTY, FUNCTION, ARROWS, NUMPAD }; // layers

/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

const Key keymaps[][ROWS][COLS] PROGMEM = {

  [QWERTY] = KEYMAP_STACKED
  (Key_Escape,        Key_1, Key_2, Key_3, Key_4, Key_5, Key_Backtick,
   ___,               Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Delete,
   ___,               Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_LEDEffectNext, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_LeftGui,
   Key_Backspace, Key_LeftShift, Key_LeftControl, Key_LeftAlt,
   ShiftToLayer(FUNCTION),

   Key_KeypadNumLock, Key_6, Key_7, Key_8,     Key_9,         Key_0,         Key_Home,
   Key_Tab,           Key_Y, Key_U, Key_I,     Key_O,         Key_P,         Key_PageUp,
                      Key_H, Key_J, Key_K,     Key_L,         Key_Semicolon, Key_PageDown,
   ___,               Key_N, Key_M, Key_Comma, Key_Period,    Key_Slash,     Key_End,
   ___, Key_Enter, Key_Spacebar, ShiftToLayer(ARROWS),
   ShiftToLayer(FUNCTION)),

  [FUNCTION] =  KEYMAP_STACKED
  (___,      Key_F1,        Key_F2,           Key_F3,    Key_F4,           Key_F5,          XXX,
   Key_Tab,  TOPSY(1),      TOPSY(2),         TOPSY(3),  TOPSY(4),         TOPSY(5),        ___,
   Key_Home, TOPSY(6),      TOPSY(7),         TOPSY(8),  TOPSY(Semicolon), TOPSY(Backtick),
   Key_End,  Key_Backslash, TOPSY(Backslash), Key_Quote, TOPSY(Quote),     TOPSY(Slash),    ___,
   Key_Delete, ___, ___, ___,
   ___,

   ___, Key_F6, Key_F7,             Key_F8,              Key_F9,          Key_F10,          Key_F11,
   ___, ___,    Key_Equals,         Key_Minus,           TOPSY(Minus),    TOPSY(Equals),    Key_F12,
        ___,    TOPSY(9),           TOPSY(0),            Key_LeftBracket, Key_RightBracket, ___,
   ___, ___,    TOPSY(LeftBracket), TOPSY(RightBracket), TOPSY(Comma),    TOPSY(Period),    ___,
   ___, ___,    Key_Enter, ___,
   ___),


  [ARROWS] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   ___, ___, ___,           ___,           ___,            ___, ___,
   ___, ___, ___,           Key_UpArrow,   ___,            ___, ___,
        ___, Key_LeftArrow, Key_DownArrow, Key_RightArrow, ___, ___,
   ___, ___, ___, ___,      ___,           ___,            ___,
   ___, ___, ___, ___,
   ___),

  [NUMPAD] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   ___,                    ___, Key_Keypad7, Key_Keypad8,   Key_Keypad9,     Key_KeypadDivide,   ___,
   ___,                    ___, Key_Keypad4, Key_Keypad5,   Key_Keypad6,     Key_KeypadMultiply, ___,
                           ___, Key_Keypad1, Key_Keypad2,   Key_Keypad3,     Key_KeypadSubtract, ___,
   M(MACRO_VERSION_INFO),  ___, Key_Keypad0, Key_KeypadDot, Key_KeypadEnter, Key_KeypadAdd,      Key_KeypadEquals,
   ___, ___, ___, ___,
   ___)
};

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

  case MACRO_VERSION_INFO:
    versionInfoMacro(keyState);
    break;
  }
  return MACRO_NONE;
}



// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 01.


static kaleidoscope::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::LEDSolidColor solidBlue(0, 70, 130);
static kaleidoscope::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::LEDSolidColor solidViolet(130, 0, 120);



/** The 'setup' function is one of the two standard Arduino sketch functions.
  * It's called when your keyboard first powers up. This is where you set up
  * Kaleidoscope and any plugins.
  */

void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // Next, tell Kaleidoscope which plugins you want to use.
  // The order can be important. For example, LED effects are
  // added in the order they're listed here.
  Kaleidoscope.use(
    // The boot greeting effect pulses the LED button for 10 seconds after the keyboard is first connected
    &BootGreetingEffect,

    // The hardware test mode, which can be invoked by tapping Prog, LED and the left Fn button at the same time.
    &TestMode,

    // LEDControl provides support for other LED modes
    &LEDControl,

    // We start with the LED effect that turns off all the LEDs.
    &LEDOff,

    // These static effects turn your keyboard's LEDs a variety of colors
    //&solidRed, &solidOrange, &solidYellow, &solidGreen, &solidBlue, &solidIndigo, &solidViolet,

    // The stalker effect lights up the keys you've pressed recently
    &StalkerEffect,

    // Support shifted characters
    &TopsyTurvy,

    // The numlock plugin is responsible for lighting up the 'numpad' mode
    // with a custom LED effect
    &NumLock,

    // The macros plugin adds support for macros
    &Macros
  );

  // While we hope to improve this in the future, the NumLock plugin
  // needs to be explicitly told which keymap layer is your numpad layer
  NumLock.numPadLayer = NUMPAD;

  // The LED Stalker mode has a few effects. The one we like is
  // called 'BlazingTrail'. For details on other options,
  // see https://github.com/keyboardio/Kaleidoscope-LED-Stalker
  StalkerEffect.variant = STALKER(Haunt, (CRGB(0, 70, 130)));

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}
