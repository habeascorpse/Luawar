/***************************************************************************
 *   Copyright (C) 2009 by Alan de Oliveira Silva, Thiago Luiz Rodrigues, Gabriel Vedana Queiroz   *
 *   habeas_corpse@yahoo.com.br   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include "sound.h"
namespace Scenario {

// Constructor of Sound

Sound::Sound() {

	int audio_rate = 22050;
  Uint16 audio_format = AUDIO_S8; /* 16-bit stereo */
  int audio_channels = 2;
  int audio_buffers = 4096;
  channel = -1;

	SDL_Init(SDL_INIT_AUDIO);


	if ( Mix_OpenAudio ( audio_rate, audio_format, audio_channels, audio_buffers ) != 0 ) {
		cout << "Unable to initialize audio:s \n " << Mix_GetError() <<endl;
		exit ( 1 ) ;
	}
	Mix_AllocateChannels(4);

	cout << "abriu o audio testando 1: " << Mix_GetError() <<endl;

};

Sound::~Sound() {
  Mix_HaltChannel(0);
  Mix_HaltChannel(1);
  Mix_HaltChannel(2);
  Mix_HaltChannel(3);
	Mix_CloseAudio();
}

void Sound::play(Mix_Chunk* ref) {
  if (ref != NULL) {
      channel++;
      Mix_PlayChannel(channel,ref, 0);
      if (channel == 3)
        channel = -1;
  }
}

}

