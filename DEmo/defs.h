#pragma once
#ifndef DEFS_H
#define DEFS_H

const char* PLAYER_FILE = "resource/player.png";
const int PLAYER_CLIPS[][4] = {
	{ 0, 0, 32, 32},
	{ 32, 0, 32, 32},
	{ 64, 0, 32, 32},
	{ 96, 0, 32, 32},

};

const int PLAYER_FRAMES = sizeof(PLAYER_CLIPS) / sizeof(int) / 4;
#endif // DEFS_H
