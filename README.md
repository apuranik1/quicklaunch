Liftoff
===========

A minimal lightweight application launcher for Linux

The goal of this project is to create a convenient and desktop-independent app-launcher for my Arch Linux system (with Openbox) while also teaching myself C++. This launcher should be compatible with Freedesktop-compliant operating systems, but it only gets tested on Arch Linux.

Features
--------
+ App suggestions that are continuously refined as you type
+ Fully keyboard-oriented UI
+ Extremely minimal interface - exactly zero (0) buttons, very little eye-candy
+ Ability to execute any command by prefixing it with "!"
+ Memory of most commonly used applications to provide better suggestions

Future Features
---------------
+ Tab completion for arbitrary commands

Note to anyone who used this while it was named quicklaunch
-----------------------------------------------------------

Move the directory .local/share/quicklaunch to .local/share/liftoff to avoid
losing history. Also delete the old executable.
