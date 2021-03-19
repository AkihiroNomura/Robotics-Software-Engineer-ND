## Project: Go Chase It!


#### Directory Structure
```
% tree .
.
├── ball_chaser
│   ├── CMakeLists.txt
│   ├── launch
│   │   └── ball_chaser.launch
│   ├── package.xml
│   ├── src
│   │   ├── drive_bot.cpp
│   │   └── process_image.cpp
│   └── srv
│       └── DriveToTarget.srv
└── my_robot
    ├── CMakeLists.txt
    ├── launch
    │   ├── robot_description.launch
    │   └── world.launch
    ├── meshes
    │   └── hokuyo.dae
    ├── package.xml
    ├── urdf
    │   ├── my_robot.gazebo
    │   └── my_robot.xacro
    └── worlds
        └── crayon_office.world
```