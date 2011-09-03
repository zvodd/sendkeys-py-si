/*
* _sendkeys module.
*
* This module is used by the SendKeys module.
*
* Copyright (C) 2003 Ollie Rutherfurd <oliver@rutherfurd.net>
*
* Version 0.3 (2003-06-14)
*
* Modified By Zv_oDD 
* Version 0.4?(2011-09-04)
*
* $Id$
*/
#define _WIN32_WINNT 0x501

#include "Python.h"
#include "windows.h"

static void
_sk_key_down(char vk)
{
	/*
	char scan = 0;
	scan = MapVirtualKeyA(vk,0);
	*/
	
	INPUT input[1];
	memset(input, 0, sizeof(input));
	input[0].type = INPUT_KEYBOARD;

	input[0].ki.wVk = vk; // ASCI value of A
	input[0].ki.dwFlags = 0;
	input[0].ki.time = 0;
	input[0].ki.dwExtraInfo = 0;
	
	SendInput(1,input,sizeof(INPUT));
}

/* sends a key released event */
static void
_sk_key_up(char vk)
{
	/*
	char scan = 0;
	scan = MapVirtualKeyA(vk,0);
	*/
	
	INPUT input[1];
	memset(input, 0, sizeof(input));
	input[0].type = INPUT_KEYBOARD;

	input[0].ki.wVk = vk; // ASCI value of A
	input[0].ki.dwFlags = KEYEVENTF_KEYUP;
	input[0].ki.time = 0;
	input[0].ki.dwExtraInfo = 0;
	
	SendInput(1,input,sizeof(INPUT));
}

/*
// sends a key pressed event 
static void
_key_down(char vk)
{
	char scan = 0;
	scan = MapVirtualKeyA(vk,0);

	keybd_event((char)vk,
			scan,
			0, // down 
			0);
}

// sends a key released event 
static void
_key_up(char vk)
{
	char scan = 0;
	scan = MapVirtualKeyA(vk,0);

	keybd_event((char)vk,
			scan,
			KEYEVENTF_KEYUP,
			0);
}
*/

static char char2keycode_docs[] = "\
char2keycode(char) -> int \n\
\n\
Converts character to virtual key code \n\
";

static PyObject*
char2keycode(PyObject* self, PyObject* args)
{
	char c = 0;
	int vk = 0;

	if(!PyArg_ParseTuple(args, "c", &c))
		return NULL;

	vk = VkKeyScanA(c);

	return Py_BuildValue("i", vk);
}

static char toggle_numlock_docs[] = "\
toggle_numlock(int) ->  int \n\
\n\
Turns NUMLOCK on or off and returns whether \n\
it was originally on or off. \n\
";

static PyObject*
toggle_numlock(PyObject* self, PyObject* args)
{
	int is_on = 0;
	int turn_on = 0;
	BYTE keys[256] = {0};

	if(!PyArg_ParseTuple(args, "i", &turn_on))
		return NULL;

	GetKeyboardState((LPBYTE)&keys);
	is_on = keys[VK_NUMLOCK] & 0x1;
	if(is_on != turn_on)
	{
		keybd_event(VK_NUMLOCK, 
			    0x45, 
			    KEYEVENTF_EXTENDEDKEY | 0, 
			    0);
		keybd_event(VK_NUMLOCK, 
			    0x45, 
			    KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 
			    0);

	}

	return Py_BuildValue("i", is_on);
}

static char key_down_docs[] = "\
key_down(int) -> None \n\
\n\
Generates a key pressed event.  Takes a \n\
virtual key code. \n\
";

static PyObject*
key_down(PyObject* self, PyObject* args)
{
	int vk = 0;

	if(!PyArg_ParseTuple(args, "i", &vk))
		return NULL;

	// XXX exception if >= 256
	_sk_key_down((byte)vk);

	return Py_BuildValue("");
}

static char key_up_docs[] = "\
key_up(int) -> None \n\
\n\
Generates a key released event.  Takes a \n\
virtual key code. \n\
";

static PyObject*
key_up(PyObject* self, PyObject* args)
{
	int vk = 0;

	if(!PyArg_ParseTuple(args, "i", &vk))
		return NULL;

	// XXX exception if >= 256
	_sk_key_up((byte)vk);

	return Py_BuildValue("");
}

static PyMethodDef _sendkeys_methods[] = {
	{"char2keycode", char2keycode, METH_VARARGS, char2keycode_docs},
	{"key_down", key_down, METH_VARARGS, key_down_docs},
	{"key_up",   key_up,   METH_VARARGS, key_up_docs},
	{"toggle_numlock", toggle_numlock, METH_VARARGS, toggle_numlock_docs},
	{NULL, NULL}
};

void 
init_sendkeys(void)
{
	Py_InitModule("_sendkeys", _sendkeys_methods);
}

/* :indentSize=8:lineSeparator=\r\n:maxLineLen=76:mode=c:
   :noTabs=false:tabSize=8:wrap=hard: */
