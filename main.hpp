#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <windows.h>
#include <limits>

void get_player_symbols();
void reset_board();
void print_board();
void player_input();
void computer_input();
char evaluate_win_conditions();
void print_winner(char winner);
bool get_continue();
int get_remaining_spaces();