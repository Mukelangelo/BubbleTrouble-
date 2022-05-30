#pragma once

#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include "Resources.h"

constexpr auto WINDOW_WIDTH = 1600.f;
constexpr auto WINDOW_HEIGHT = 800.f;
constexpr auto WALL_SIZE = 100.f;
constexpr auto PLAYER_WIDTH = 48.f;
constexpr auto STAGE_TIME = 60.f;
constexpr auto BAR_SIZE = 100.f;
constexpr auto SHOT_WIDTH = 5.f;
constexpr auto SHOT_HEIGHT = -50;

enum _entity {
    WALL = 0x0001,
    BALL = 0x0002,
    WEAPON = 0x0004,
    PLAYER = 0x0008,
};

enum _game_objects {
    PLAYER_GO = 0,
    BALL_GO = 1,
    WALL_GO = 2,
    HELP = 3
};

enum _ball_radius {
    MEGA_BIG = 100,
    BIG = 50,
    MEDIUM = 25,
    SMALL = 12,
};