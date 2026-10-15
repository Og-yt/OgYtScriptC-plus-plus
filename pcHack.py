import time

import pyperclip as clip
import pyautogui as auto

def command_line_setting():
    clip.copy('cd "C:\\MyProject\\TransCompilerEditor"')
    
    auto.hotkey('ctrl', 'v')
    auto.press('enter')

def git_status() -> None:
    auto.press('g'); time.sleep(0.1); auto.press('i'); time.sleep(0.1); auto.press('t'); time.sleep(0.1); auto.press('space')
    auto.press('s'); time.sleep(0.1); auto.press('t'); time.sleep(0.1); auto.press('a'); time.sleep(0.1); auto.press('t'); time.sleep(0.1); auto.press('u'); time.sleep(0.1); auto.press('s')
    
def git_add() -> None:
    auto.press('g'); time.sleep(0.1); auto.press('i'); time.sleep(0.1); auto.press('t'); time.sleep(0.1); auto.press('space')
    auto.press('a'); time.sleep(0.1); auto.press('d'); time.sleep(0.1); auto.press('d'); time.sleep(0.1); auto.press('space'); time.sleep(0.1);
    
    clip.copy('.')
    
    auto.hotkey('ctrl', 'v')
    
def git_commit() -> None:
    auto.press('g'); time.sleep(0.1); auto.press('i'); time.sleep(0.1); auto.press('t'); time.sleep(0.1); auto.press('space')
    auto.press('c'); time.sleep(0.1); auto.press('o'); time.sleep(0.1); auto.press('m'); time.sleep(0.1); auto.press('m'); time.sleep(0.1); auto.press('i'); time.sleep(0.1); auto.press('t'); time.sleep(0.1); auto.press('space'); time.sleep(0.1)
    
    clip.copy('-')
    
    auto.hotkey('ctrl', 'v')
    auto.press('m')
    
    auto.press('space')
    
    clip.copy('"_"')
    auto.hotkey('ctrl', 'v')
    
def git_push() -> None:
    auto.press('g'); time.sleep(0.1); auto.press('i'); time.sleep(0.1); auto.press('t'); time.sleep(0.1); auto.press('space')
    auto.press('p'); time.sleep(0.1); auto.press('u'); time.sleep(0.1); auto.press('s'); time.sleep(0.1); auto.press('h')

auto.hotkey('win', 'r')
time.sleep(0.1)

auto.write('cmd')
auto.press('enter')

time.sleep(0.5)

command_line_setting()
time.sleep(0.5)

git_status()
auto.press('enter')

time.sleep(0.5)

git_add()
auto.press('enter')

time.sleep(0.5)

git_commit()
auto.press('enter')

time.sleep(0.5)

git_push()
auto.press('enter')