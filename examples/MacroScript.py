import pyHook
from SendKeys import SendKeys
from time import time

def LogPrint(printstr):
    print(printstr)
    return

mykc = 3
def tripplee():
    global mykc
    if mykc < 3:
        mykc += 1
        return True
    else:
        mykc = 0
        SendKeys("""
        eee
""")
        return False

def OnKeyboardEvent(event):
    l = "Ascii: %s , Key: %s , KeyID: %s ." % \
    (event.Ascii, event.Key, event.KeyID) 
    LogPrint(l)
    if event.Key is "E":
        return tripplee();
    #returning true allows to keepress through.
    #false will hide keypress from other programs, mostly.
    return True

def main():
    """ MacroScript a windows keyboard macro
    written in python useing the pyHook and SendKeys
    Python libraries. It Lets you triple tap the
    the e key by pressing the v key.
	MacroScript requires PyHook to capture keyboard input."""
    print "MacroScript Started"
    
    hm = pyHook.HookManager()
    hm.KeyDown = OnKeyboardEvent
    hm.HookKeyboard()
    
    #del log  #no need :D

if __name__ == '__main__':
    main()
    import pythoncom
    pythoncom.PumpMessages()
    