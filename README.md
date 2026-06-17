# ✨ Particle System

A real-time **multi-mode particle system** built with **C++ and SFML 3.0**, featuring 5 stunning visual effects with interactive controls.

![Particle System](https://raw.githubusercontent.com/snehal-thombare08/-Particle-System/main/Screenshot%202026-06-17%20170800.png)

## ✨ Features

- **5 Particle Modes** — Fire, Snow, Explosion, Galaxy, Firework
- **Interactive emission** — drag mouse to emit particles
- **Gravity toggle** — enable/disable physics gravity
- **5000+ simultaneous particles** with smooth rendering
- Real-time circle-based particle rendering at 1200×800

## 🎮 Controls

| Key / Button | Action |
|---|---|
| `1` | 🔥 Fire mode |
| `2` | ❄️ Snow mode (auto) |
| `3` | 💥 Explosion mode |
| `4` | 🌌 Galaxy mode |
| `5` | 🎆 Firework mode |
| LMB (drag) | Emit particles |
| RMB (click) | Burst (Explosion/Firework) |
| `G` | Toggle gravity |
| `Space` | Clear all particles |
| `Esc` | Quit |

## 🚀 How to Run

1. Download **ParticleSystem-v1.0-Windows.zip**
2. Extract all files to a folder
3. Run **ParticleSystem.exe**

> No installation required. All DLLs included.

## 🛠️ Build from Source

**Requirements:**
- C++17 compiler (MinGW-w64)
- SFML 3.0 (via vcpkg)
- CMake 3.16+

```bash
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -G "MinGW Makefiles"
mingw32-make
```

## 🔬 Physics

- **Verlet-style integration** for smooth motion
- **Per-type gravity** — fire rises, snow drifts, galaxy orbits
- **Alpha fade** based on remaining lifetime
- **Size scaling** as particles age

## 📁 Project Structure

```
Particle System/
├── src/
│   └── main.cpp
├── CMakeLists.txt
└── .gitignore
```

## 🧰 Tech Stack

- **Language:** C++17
- **Graphics:** SFML 3.0
- **Build:** CMake + MinGW
- **Rendering:** Circle-based particles with alpha blending

---
*Part of a C++ graphics & simulation portfolio*
