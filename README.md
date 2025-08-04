# 🎮 2048 Game – Enhanced C Version

![C](https://img.shields.io/badge/Language-C-blue?logo=c)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey)
![Visual Studio](https://img.shields.io/badge/IDE-Visual%20Studio-purple?logo=visualstudio)

An **enhanced version of the classic 2048 game** written in **C**, with a polished interface, leaderboard tracking, and a user-friendly console experience.  
Designed to demonstrate clean C programming, file handling, and simple UI/UX for console applications.

---

## ✨ Features
- **Color-coded board** with smooth in-place refresh on every move.
- **Main menu**: Start Game, View Leaderboard, Exit.
- **Leaderboard**: Top 10 scores saved with **player names** and **timestamps**.
- **In-game controls hint** for better user experience.
- **Cross-platform support**: Runs on Windows (Visual Studio) and Linux (via Makefile).

---

## 📸 Screenshots
### Game Board  
![Game Screenshot](assets/screenshot.png)  

### Leaderboard  
![Leaderboard Screenshot](assets/leaderboard.png)  

*(Coming soon: **GIF** showing gameplay in action!)*

---

## 🎮 Controls
- **R** – Move Right  
- **L** – Move Left  
- **U** – Move Up  
- **D** – Move Down  
- **E** – Exit  

---

## 🛠️ Tech Stack
- **Language:** C  
- **Platform:** Windows Console App (Visual Studio), Makefile for Linux  
- **File Handling:** Highscore and leaderboard persistence  
- **Assets:** Screenshots & data files  

---

## 📂 Project Structure
```
2048-Game/
├─ src/                # Source code (.c files)
├─ include/            # Header files (.h)
├─ assets/             # Screenshots, gameplay GIF & highscore data
│   ├─ screenshot.png
│   ├─ leaderboard.png
│   ├─ gameplay.gif
│   ├─ highscore.txt
│   ├─ leaderboard.txt
│   └─ other highscore_* files
├─ Makefile            # Build script for Linux
├─ 2048-Game.sln       # Visual Studio solution
├─ 2048-Game.vcxproj   # Visual Studio project file
└─ README.md           # Project documentation
```

---

## 🚀 How to Build & Run

### **Windows (Visual Studio)**
1. Open `2048-Game.sln` in **Visual Studio**.
2. Build and run the project (Ctrl + F5).

### **Linux**
1. Open a terminal in the project folder.
2. Run:
   ```bash
   make
   ./game
   ```

---

## 📜 Author
**Rotem Shimon**  
2nd-year Computer Science student at Afeka Academic College of Engineering.  
Passionate about system programming and building fun, interactive projects.
