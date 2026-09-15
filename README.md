# Autonomous Robot

This project is an autonomous line-following robot developed for the INF1900 engineering course.

The robot uses infrared line sensors, a distance sensor, motors, LEDs, buttons, and sound to navigate a predefined course. Its software controls the robot's movement, detects intersections and obstacles, and selects the appropriate path during the run.

The source code is organized in `projet/app/`, with the embedded support library in `projet/lib/`. Robot demonstration videos are stored in `videos/`.

This project does not compile in a general-purpose environment. It targets a specific AVR microcontroller and requires the matching AVR toolchain, programmer, and robot hardware. Without that exact environment, compilation and execution are not expected to work.

## Team

- Giovanni Marven Alcena
- Adam Azrou
- Elliot Gareau
- Anis Feteh Benabderrahmane