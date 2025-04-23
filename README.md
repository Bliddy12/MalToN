# MalToN

**MalToN** is a playful homage to the legendary **MEMZ** virus — a pure **visual-only** chaos simulator.  
It’s **harmless**, **safe to run locally**, and designed purely for fun and experimentation.  
Expect screen glitches, screen recursive moves, and a nostalgic touch of sounds and popups.


# Usage

Make sure you're on **Windows** with **MinGW** or a C++ compiler that supports `-lgdi32` and `-lwinmm`.

Compile the code with 
```
g++ MalToN.cpp -o MalToN.exe -mwindows -lgdi32 -lwinmm
