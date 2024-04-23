#pragma once
#ifndef _DEFS__H
#define _DEFS__H

const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 800;

const char* PLAYER_FILE = "resource//player.png";
const int IDLE_CLIPS[][4] = {
	{ 0, 0, 32, 32},
	{ 32, 0, 32, 32},
	{ 64, 0, 32, 32},
	{ 96, 0, 32, 32},

};

const int IDLE_FRAMES = sizeof(IDLE_CLIPS) / sizeof(int) / 4;

const int RUNNING_CLIPS[][4] = {
	{ 0, 32, 32, 32},
	{ 32, 32, 32, 32},
	{ 64, 32, 32, 32},
	{ 96, 32, 32, 32},
	{ 128, 32, 32, 32},
	{ 160, 32, 32, 32},

};

const int RUNNING_FRAMES = sizeof(RUNNING_CLIPS) / sizeof(int) / 4;

const int FALL_CLIPS[][4] = {
	{ 0, 128, 32, 32},
	{ 32, 128, 32, 32},

};

const int FALL_FRAMES = sizeof(FALL_CLIPS) / sizeof(int) / 4;

const int READY_CLIPS[][4] = {
	{ 32, 96, 32, 32},
	{ 64, 96, 32, 32},

};

const int READY_FRAMES = sizeof(READY_CLIPS) / sizeof(int) / 4;
#endif
