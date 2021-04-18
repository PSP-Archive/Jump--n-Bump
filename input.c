/*
 * input.c
 * Copyright (C) 1998 Brainchild Design - http://brainchilddesign.com/
 * 
 * Copyright (C) 2001 Chuck Mason <cemason@users.sourceforge.net>
 *
 * Copyright (C) 2002 Florian Schulze <crow@icculus.org>
 *
 * This file is part of Jump'n'Bump.
 *
 * Jump'n'Bump is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Jump'n'Bump is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

///----------------------------------------------------------------------------
/// Includes
///----------------------------------------------------------------------------
#include "globals.h"

///----------------------------------------------------------------------------
/// Enumerations
///----------------------------------------------------------------------------
enum { sdljbTriangle = 0, sdljbCircle, sdljbCross, sdljbSquare, sdljbLTrig, sdljbRTrig, sdljbDown, sdljbLeft, sdljbUp, sdljbRight, sdljbSelect, sdljbStart, sdljbHome } SDLJoyBtn;


//static int num_joys=0;
//static SDL_Joystick *joys[4];
SDL_Joystick *joyPSP;

/* assumes joysticks have at least one button, could check numbuttons first? */
//#define JOY_LEFT(num) (num_joys>num && SDL_JoystickGetAxis(joys[num], 0)<-3200)
//#define JOY_RIGHT(num) (num_joys>num && SDL_JoystickGetAxis(joys[num], 0)>3200)
/* I find using the vertical axis to be annoying -- dnb */
//#define JOY_JUMP(num) (num_joys>num && SDL_JoystickGetButton(joys[num], 0))

int calib_joy(int type)
{
	return 1;
}

void update_player_actions(void)
{
	int tmp;

	if (client_player_num < 0) {
		tmp = (SDL_JoystickGetButton(joyPSP, sdljbLeft) || SDL_JoystickGetAxis(joyPSP, 0)<-3200);
		if (tmp != player[0].action_left)
			tellServerPlayerMoved(0, MOVEMENT_LEFT, tmp);
		tmp = (SDL_JoystickGetButton(joyPSP, sdljbRight) || SDL_JoystickGetAxis(joyPSP, 0)>3200);
		if (tmp != player[0].action_right)
			tellServerPlayerMoved(0, MOVEMENT_RIGHT, tmp);
		tmp = (SDL_JoystickGetButton(joyPSP, sdljbUp) || SDL_JoystickGetAxis(joyPSP, 1)<-3200);
		if (tmp != player[0].action_up)
			tellServerPlayerMoved(0, MOVEMENT_UP, tmp);

		if(SDL_JoystickGetButton(joyPSP, sdljbStart) && SDL_JoystickGetButton(joyPSP, sdljbUp))
		{
			tellServerPlayerMoved(0, CHEATPOGO, 0);
		}
		if(SDL_JoystickGetButton(joyPSP, sdljbStart) && SDL_JoystickGetButton(joyPSP, sdljbRight))
		{
			tellServerPlayerMoved(0, CHEATSPACE, 0);
		}
		if(SDL_JoystickGetButton(joyPSP, sdljbStart) && SDL_JoystickGetButton(joyPSP, sdljbDown))
		{
			tellServerPlayerMoved(0, CHEATJETPACK, 0);
		}
		if(SDL_JoystickGetButton(joyPSP, sdljbStart) && SDL_JoystickGetButton(joyPSP, sdljbLeft))
		{
			tellServerPlayerMoved(0, CHEATFLIES, 0);
		}
		if(SDL_JoystickGetButton(joyPSP, sdljbStart) && SDL_JoystickGetButton(joyPSP, sdljbLTrig))
		{
			tellServerPlayerMoved(0, CHEATBLOOD, 0);
		}
		if(SDL_JoystickGetButton(joyPSP, sdljbSelect))
		{
			tellServerPlayerMoved(0, GAMEEND, 0);
		}


		tmp = SDL_JoystickGetButton(joyPSP, sdljbSquare);
		if (tmp != player[1].action_left)
			tellServerPlayerMoved(1, MOVEMENT_LEFT, tmp);
		tmp = SDL_JoystickGetButton(joyPSP, sdljbCircle);
		if (tmp != player[1].action_right)
			tellServerPlayerMoved(1, MOVEMENT_RIGHT, tmp);
		tmp = SDL_JoystickGetButton(joyPSP, sdljbTriangle);
		if (tmp != player[1].action_up)
			tellServerPlayerMoved(1, MOVEMENT_UP, tmp);

		/*
		tmp = (key_pressed(KEY_PL3_LEFT) == 1) || JOY_LEFT(1);
		if (tmp != player[2].action_left)
			tellServerPlayerMoved(2, MOVEMENT_LEFT, tmp);
		tmp = (key_pressed(KEY_PL3_RIGHT) == 1) || JOY_RIGHT(1);
		if (tmp != player[2].action_right)
			tellServerPlayerMoved(2, MOVEMENT_RIGHT, tmp);
		tmp = (key_pressed(KEY_PL3_JUMP) == 1) || JOY_JUMP(1);
		if (tmp != player[2].action_up)
			tellServerPlayerMoved(2, MOVEMENT_UP, tmp);

		tmp = (key_pressed(KEY_PL4_LEFT) == 1) || JOY_LEFT(0);
		if (tmp != player[3].action_left)
		tellServerPlayerMoved(3, MOVEMENT_LEFT, tmp);
		tmp = (key_pressed(KEY_PL4_RIGHT) == 1) || JOY_RIGHT(0);
		if (tmp != player[3].action_right)
		tellServerPlayerMoved(3, MOVEMENT_RIGHT, tmp);
		tmp = (key_pressed(KEY_PL4_JUMP) == 1) || JOY_JUMP(0);
		if (tmp != player[3].action_up)
		tellServerPlayerMoved(3, MOVEMENT_UP, tmp);
		*/
	} else {
		tmp = SDL_JoystickGetButton(joyPSP, sdljbLeft);
		if (tmp != player[client_player_num].action_left)
			tellServerPlayerMoved(0, MOVEMENT_LEFT, tmp);
		tmp = SDL_JoystickGetButton(joyPSP, sdljbRight);
		if (tmp != player[client_player_num].action_right)
			tellServerPlayerMoved(0, MOVEMENT_RIGHT, tmp);
		tmp = SDL_JoystickGetButton(joyPSP, sdljbUp);
		if (tmp != player[client_player_num].action_up)
			tellServerPlayerMoved(0, MOVEMENT_UP, tmp);
	}
}

void init_inputs(void)
{
	int i;

//	num_joys = SDL_NumJoysticks();
//	for(i = 0; i < 4 && i < num_joys; ++i)
//		joys[i] = SDL_JoystickOpen(i);
	// Init Joystick
	if(SDL_NumJoysticks()>0)
	{
		joyPSP=SDL_JoystickOpen(0);
	}

	main_info.mouse_enabled = 0;
	main_info.joy_enabled = 0;
}
