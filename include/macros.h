#pragma once

#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include "Resources.h"

constexpr auto WINDOW_WIDTH = 1600;
constexpr auto WINDOW_HEIGHT = 800;
constexpr int WALL_SIZE = 100;
constexpr int STAGE_TIME = 15;
enum _entity {
    WALL = 0x0001,
    BALL = 0x0002,
    WEAPON = 0x0004,
};