
# Project Report: Vertical Neon Pong Game using Raylib

## Project Title
**Vertical Neon Pong Game using Raylib**

### Group Members:
- Syed Mustafa Bukhari (24K-0682)
- Taaha Syed (24K-0534)
- Khizar Rashid (24K-0523)

### Submission Date:
11/5/25

---

## 1. Executive Summary

### Overview:
This project is a visually enhanced version of the classic Pong game, built using the Raylib graphics library in C++. The game features a vertical playfield, neon-themed visuals, and a player vs CPU gameplay mode.

### Key Findings:
The project effectively demonstrates class design in C++, real-time rendering with Raylib, and simple game physics, while incorporating clean UI and visually engaging elements using custom neon color schemes.

---

## 2. Introduction

### Background:
Pong is one of the earliest arcade video games. This modern version is redesigned to run in a vertical orientation, with a glowing, cyberpunk-style color scheme using Raylib—a lightweight and user-friendly game programming library.

### Project Objectives:
- Design a playable and visually appealing Pong game.
- Implement object-oriented programming principles like inheritance.
- Apply collision detection, score tracking, and real-time updates.

---

## 3. Project Description

### System Description:
The game includes three core components:
- **Ball**: Moves and bounces within screen bounds.
- **Player Paddle**: Controlled with arrow keys.
- **CPU Paddle**: Automatically tracks the ball.

### Tools/Technologies Used:
- C++ for logic and structure.
- Raylib for graphics and input handling.
- Windows OS for execution and testing.

---

## 4. Methodology

### Approach:
The project followed a top-down design approach:
- Implemented ball and paddle as classes.
- Used Raylib for rendering.
- Added collision logic and score system.

### Roles and Responsibilities:
- **Mustafa**: Implemented game logic, ball mechanics.
- **Taaha**: Designed UI, handled rendering, and coordinated class structures.
- **Khizar**: Coordinated class structures and implemented CPU AI.

---

## 5. Project Implementation

### Design and Structure:
- **Classes**: Ball, Paddle, CpuPaddle
- Paddle inherits movement logic; CPU paddle extends it with basic AI.
- Neon-themed color palette defined using Color structures.

### Functionalities Developed:
- Smooth ball movement and bouncing mechanics.
- CPU paddle automatically adjusts to ball position.
- Real-time score tracking and game reset after point loss.

---

## 6. Challenges Faced
- **AI Tuning**: Making the CPU paddle balanced—not too hard or too easy.
- **Collision Detection**: Required fine-tuning to respond correctly to edge cases.
- **Design Polish**: Aligning visuals with the neon aesthetic using RGB color codes.

---

## 7. Results

### Project Outcomes:
- A fully functional vertical Pong game with polished UI and dynamic gameplay.

### Screenshots and Illustrations:
Include screenshots showing:
- Game startup screen
- Player scoring
- CPU scoring
- Mid-game action

### Testing and Validation:
The game was tested at 60 FPS with consistent behavior across different runs. Score tracking, paddle movements, and collision mechanics were validated through multiple test cases.

---

## 8. Conclusion

### Summary of Findings:
The project successfully recreated Pong in a new visual style while reinforcing core C++ concepts such as OOP, inheritance, and graphical programming.

### Future Work:
- Add sound effects and music.
- Include multiple difficulty levels.
- Enable two-player mode with customizable settings.
