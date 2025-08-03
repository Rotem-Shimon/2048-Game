# 2048 Game – C Project

![Gameplay](./assets/2048.PNG)

This project is an implementation of the classic **2048 game** written in **C**, developed as part of my coursework at **Afeka College (2024)**.  
The project is organized with a clean structure and includes support for **Visual Studio** for easy building and debugging.

## Features
- Full implementation of the **2048 game logic** in C.  
- Clear **modular structure** – separate header and source files (`.h` / `.c`).  
- **Configurable board size** and **winning score**.  
- **Per-user High Score system** – each player has their own high score file, named with their username and timestamp.  
- **Player identification in menu** – the game displays the current player's name alongside their best score.  
- Designed to run on **Windows** using Visual Studio.  

## Project Structure
```
.
├── include/                      # Header files
├── src/                          # Source files
├── 2048-Game.sln                 # Visual Studio solution file
├── 2048-Game.vcxproj             # Visual Studio project file
├── 2048-Game.vcxproj.filters     # Visual Studio filters
├── .gitignore                    # Ignored files for Git
├── .gitattributes                # Git configuration
└── README.md                     # Project description
```

## How to Run
1. Clone this repository:
   ```bash
   git clone https://github.com/Rotem-Shimon/2048-Game.git
   ```
2. Open `2048-Game.sln` in **Visual Studio**.  
3. Build and run the project (press **F5**).  
4. When prompted, enter your **username** – the game will create a personalized high score file for you.

## Future Improvements
- Adding **graphical interface** (currently console-based).  
- Saving and loading **game progress** between sessions.  

## License
This project is released under the **MIT License** – feel free to use or modify it.  
