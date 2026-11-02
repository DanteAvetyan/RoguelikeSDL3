Roguelike/
│
├── CMakeLists.txt
├── CMakePresets.json
│
├── assets/
│   ├── fonts/
│   ├── textures/
│   ├── audio/
│   └── maps/
│
├── src/
│   ├── main.cpp
│   │
│   ├── engine/
│   │   ├── Game.cpp
│   │   ├── Game.h
│   │   ├── Renderer.cpp
│   │   ├── Renderer.h
│   │   ├── Input.cpp
│   │   └── Input.h
│   │
│   ├── world/
│   │   ├── Map.cpp
│   │   ├── Map.h
│   │   ├── Tile.h
│   │   ├── DungeonGenerator.cpp
│   │   └── DungeonGenerator.h
│   │
│   ├── entities/
│   │   ├── Entity.h
│   │   ├── Player.h
│   │   ├── Monster.h
│   │   └── Item.h
│   │
│   ├── systems/
│   │   ├── Combat.cpp
│   │   ├── Pathfinding.cpp
│   │   ├── FieldOfView.cpp
│   │   └── Inventory.cpp
│   │
│   └── ui/
│       ├── HUD.cpp
│       └── MessageLog.cpp
│
└── tests/
├── MapTests.cpp
├── CombatTests.cpp
└── GenerationTests.cpp