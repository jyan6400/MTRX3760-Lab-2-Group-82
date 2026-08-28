# MTRX3760-Lab-2-Group-82


# MTRX3760 Lab 2 - Robot Simulator

## Overview

This repository contains the group implementation for **MTRX3760 Lab 2: Robot Simulator**.

The lab is completed in two major stages:

- **A1 - Wall Follower**
  - Build a robot that follows the wall on its right-hand side around `SimpleWalls.map`.
  - The robot uses exactly two range sensors:
    - one directly to the right at 90 degrees;
    - one forward-right at 45 degrees.
  - The robot uses two independently controlled wheels.
  - The simulation uses a fixed timestep.
  - The robot must leave a trail for the entire run.
  - Collisions must be reported to the console.
  - The final console summary must include update count and collision count.

- **A2 - Line Follower**
  - Extend A1 by adding a second robot to the same simulation.
  - The second robot follows the line in `SimpleLine.map`.
  - It uses exactly two line sensors instead of range sensors.
  - Both robots operate at the same time but do not interact.

The project should follow the unit's **"encapsulate everything"** approach and use only concepts and language features taught in Weeks 1-4.

All direct raylib access must remain behind the `CRender` class.

---

# Design Goals

The implementation should aim for:

- clear separation of responsibilities;
- private member data;
- small and meaningful class interfaces;
- correct use of composition and inheritance;
- low coupling between classes;
- no substantial logic in `main()`;
- no unnecessary global functions or variables;
- encapsulation of constants and related state;
- reusable A1 design that extends cleanly into A2;
- consistent coding style;
- readable and maintainable source files;
- minimal duplicated code.

---

# Folder Structure

```text
MTRX3760-Lab-2/
│
├── A1.WallFollower/
│   │
│   ├── main.cpp
│   │
│   ├── Geometry.h
│   │
│   ├── CSimulation.h
│   ├── CSimulation.cpp
│   │
│   ├── CWorld.h
│   ├── CWorld.cpp
│   │
│   ├── CRobot.h
│   ├── CRobot.cpp
│   │
│   ├── CWallFollower.h
│   ├── CWallFollower.cpp
│   │
│   ├── CWheel.h
│   ├── CWheel.cpp
│   │
│   ├── CRangeSensor.h
│   ├── CRangeSensor.cpp
│   │
│   ├── CTrail.h
│   ├── CTrail.cpp
│   │
│   ├── CRender.h
│   ├── CRender.cpp
│   │
│   ├── CLoopReader.h
│   ├── CLoopReader.cpp
│   │
│   └── SimpleWalls.map
│
├── A2.LineFollower/
│   │
│   ├── common A1 files
│   ├── CLineFollower.h
│   ├── CLineFollower.cpp
│   ├── CLineSensor.h
│   ├── CLineSensor.cpp
│   └── SimpleLine.map
│
└── README.md


----

**# UML Diagram**

@startuml
skinparam classAttributeIconSize 0
skinparam style strictuml

class CSimulation
class CRender
class CWorld
class CLoopReader

class CRobot
class CWallFollower

class CWheel
class CRangeSensor
class CTrail

CRobot <|-- CWallFollower

CSimulation *-- CRender
CSimulation *-- CWorld
CSimulation *-- CWallFollower

CRobot *-- CWheel
CRobot *-- CTrail

CWallFollower *-- CRangeSensor

CWorld *-- CLoopReader

CWallFollower --> CWorld
CRangeSensor --> CWorld

CRobot --> CRender
CWorld --> CRender
CTrail --> CRender

@enduml

**## Team Responsibilities**

| Area | Person 1 - Robot, Control & Simulation | Person 2 - World, Sensors & Rendering |
|---|---|---|
| Main focus | Robot behaviour, movement, control logic and top-level simulation | Environment geometry, sensing, collision detection and visualisation |
| Main files | `main.cpp`, `CSimulation.h/.cpp`, `CRobot.h/.cpp`, `CWallFollower.h/.cpp`, `CWheel.h/.cpp` | `Geometry.h`, `CWorld.h/.cpp`, `CRangeSensor.h/.cpp`, `CTrail.h/.cpp`, `CRender.h/.cpp`, `CLoopReader.h/.cpp` |
| Simulation | Implement fixed-timestep update loop and overall simulation flow | Support world state and rendering used by the simulation |
| Robot model | Implement common robot pose, differential-drive motion and wheel behaviour | Provide geometry/world queries needed by the robot |
| Control | Implement wall-following control logic and convert sensor readings into wheel commands | Provide accurate range-sensor measurements to the controller |
| Wheels | Implement and manage the two independently controlled wheels | — |
| World geometry | Use the world interface for collision and sensing | Load and represent `SimpleWalls.map`, wall segments and room geometry |
| Range sensors | Use the two sensor readings in the wall-following controller | Implement the 90° right sensor and 45° front-right sensor |
| Collision detection | Integrate collision checks, count collisions and report them | Implement robot-to-wall collision detection |
| Trail | Trigger trail updates during robot movement | Implement trail storage and trail rendering |
| Rendering | Coordinate when drawing occurs | Maintain `CRender`, ensure all raylib calls stay inside it, draw walls/trails and assist with robot drawing |
| Map reader | Use starting pose/world data | Adapt and maintain `CLoopReader` |
| Console output | Track update count and print final summary | Provide any geometry/sensor data needed for debugging |
| A2 extension | Lead `CLineFollower`, line-following control and second-robot simulation integration | Lead `CLineSensor`, line geometry and `SimpleLine.map` support |
| Integration | Integrate Person 2's world/sensor interfaces into robot logic | Integrate Person 1's robot/controller interfaces into world/rendering logic |
| Testing | Tune controller and verify both robots complete their loops | Verify sensing, collision detection, map loading and drawing |
| Shared | UML review, interface agreement, code review, integration testing, report, A3 post-mortem, final submission | UML review, interface agreement, code review, integration testing, report, A3 post-mortem, final submission |


