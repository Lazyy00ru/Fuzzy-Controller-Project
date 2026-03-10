# Fuzzy Logic Controller for Inverted Pendulum System

**Course:** Artificial Intelligence 159302  

---

## Introduction

This project presents the design, implementation, and evaluation of a **Fuzzy Logic Controller (FLC)** for stabilising an inverted pendulum system. The inverted pendulum is a classical nonlinear, inherently unstable control problem widely used to evaluate sophisticated control strategies. A fuzzy logic approach is adopted for its robustness, ability to handle nonlinear dynamics, and reduced dependence on a precise mathematical model.

---

## System Description

The inverted pendulum system consists of a cart on a track with an inverted pole attached to a pivot. The control objective is to apply a suitable horizontal force to the cart so that the pole remains stationary in the upright position without the cart exceeding its physical track limits.

The four system states are:
- Pole angle (θ)
- Pole angular velocity (θ̇)
- Cart position (x)
- Cart velocity (ẋ)

---

## Controller Design

### Combined Inputs (Yamakawa Approach)

A Sugeno-type fuzzy inference system is applied using the combined-input method introduced by Yamakawa. The four system states are reduced to two fuzzy inputs:

```
INPUT_X = (A × θ) + (B × θ̇)      ← pole control channel
INPUT_Y = (C × x) + (D × ẋ)       ← cart control channel
```

| Coefficient | Value | Role |
|---|---|---|
| A | 18.0 | Pole angle weight |
| B | 9.5 | Pole angular velocity weight |
| C | 5.0 | Cart position weight |
| D | 4.0 | Cart velocity weight |

These coefficients prioritise pole stabilisation while maintaining adequate cart position control.

### Fuzzy Rule Base

The controller uses **25 fuzzy rules** covering all 5×5 combinations of INPUT_X and INPUT_Y. Each input is described by five linguistic terms:

| Symbol | Meaning |
|---|---|
| NL | Negative Large |
| NS | Negative Small |
| ZE | Zero |
| PS | Positive Small |
| PL | Positive Large |

Rule structure:
```
IF X is Xi AND Y is Yi THEN Force is Fi
```

This provides complete coverage of the operational space with a compact and manageable rule base.

### Sugeno Output Singletons

Each rule produces a fixed crisp force value (zero-order Sugeno inference):

| Label | Symbol | Force (N) |
|---|---|---|
| Negative Very Large | out_nvl | −145 |
| Negative Large | out_nl | −105 |
| Negative Medium | out_nm | −68 |
| Negative Small | out_ns | −32 |
| Zero | out_ze | 0 |
| Positive Small | out_ps | +32 |
| Positive Medium | out_pm | +68 |
| Positive Large | out_pl | +105 |
| Positive Very Large | out_pvl | +145 |

### Defuzzification

Weighted average defuzzification is used to compute the final control force:

```
F = Σ(μᵢ · fᵢ) / Σμᵢ
```

where μᵢ is the firing strength of rule i and fᵢ is its singleton output. This produces a continuous, smooth control action.

---

## Fuzzy Membership Functions

All membership functions are trapezoidal, providing smooth transitions between linguistic regions.

### Input X — Pole Control

| Set | a | b | c | d |
|---|---|---|---|---|
| NL | −40 | −8 | −8 | −4 |
| NS | −10 | −5 | −2 | −0.5 |
| ZE | −3 | −0.6 | 0.6 | 3 |
| PS | 0.5 | 2 | 5 | 10 |
| PL | 8 | 40 | 40 | 40 |

### Input Y — Cart Control

| Set | a | b | c | d |
|---|---|---|---|---|
| NL | −10 | −1.2 | −1.2 | −0.6 |
| NS | −1.5 | −0.7 | −0.2 | 0 |
| ZE | −0.4 | −0.08 | 0.08 | 0.4 |
| PS | 0 | 0.2 | 0.7 | 1.5 |
| PL | 1.2 | 10 | 10 | 10 |

---

## Project Structure

| File | Description |
|---|---|
| `main.cpp` | Entry point; physics simulation loop, rendering, control surface generation |
| `fuzzylogic.cpp / .h` | Fuzzy system: membership functions, rule base, inference engine |
| `sprites.cpp / .h` | `Cart` and `Rod` classes for animated pendulum rendering |
| `transform.cpp / .h` | World-to-device coordinate transformation |
| `graphics.cpp / .h` | BGI graphics API wrapper (SDL_BGI / WinBGI) |
| `CMakeLists.txt` | CMake build configuration |

---

## Build Instructions

### Prerequisites

- CMake ≥ 4.1
- C++14-compatible compiler (GCC, Clang, MSVC)
- **Unix/macOS:** SDL_BGI graphics library
- **Windows:** WinBGI or compatible graphics library

### Build & Run

```bash
mkdir build && cd build
cmake ..
make
./Assignment2
```

On startup, a graphical window opens and prompts you to enter an initial pole angle via the terminal.

---

## Output

After the simulation, a control surface data file is saved:

```
data_angle_vs_angle_dot.txt
```

This is a 100×100 CSV grid of fuzzy output forces sampled over:
- **Angle range:** −40° to +40°
- **Angular velocity range:** −3.0 to +3.0 rad/s

The file can be imported into MATLAB, Python (Matplotlib), or Excel to plot a 3D control surface.

---

## Results

The simulation shows that the fuzzy logic controller successfully stabilises the inverted pendulum for **initial pole angles of up to approximately ±25 degrees**. Within this range, the system responds smoothly with minimal oscillation around the upright equilibrium, and the cart remains within its physical track limits throughout. The generated control surface confirms nonlinear but well-structured behaviour, verifying correct rule design and tuning.

---

## Conclusion

A fuzzy logic controller based on a Sugeno inference system and the Yamakawa combined-input approach has been successfully designed and implemented for the inverted pendulum problem. By reducing the four system states to two composite inputs, the rule base is kept compact while maintaining stable and robust performance. The results confirm that fuzzy logic control is a viable and practical approach for nonlinear, unstable systems such as the inverted pendulum.
