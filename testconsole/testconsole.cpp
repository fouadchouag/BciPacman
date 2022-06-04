// testconsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h> 
#include <time.h>
#include <conio.h>
//#include <SDL/SDL_ttf.h>

#include <iostream>
 
#include <vrpn_Button.h>
#include <vrpn_Analog.h>


int i=10 ,possible, j=10 , a;

// Surfaces et rectangle
SDL_Rect rect_aff;

SDL_Surface *Screen , *image ;
void affichage(int ,int );


void VRPN_CALLBACK vrpn_button_callback(void* user_data, vrpn_BUTTONCB button)
{
    std::cout << "Button ID : " << button.button << " / Button State : " << button.state << std::endl;
	
    if (button.button == 1)
    {
		//   *(bool*)user_data = false;
    }
       if ((button.button == 0)& (button.state == 1))  /* right */
	   {
	              i=i+1;
                  if (a==0)
		              {image = SDL_LoadBMP("./pacman_d.bmp");}
                   if (a==1) 
                      {image = SDL_LoadBMP("./pacman_d_c.bmp");a=-1;}
                    a++  ;
                   affichage(i,j);
	   }
				   
	   if ((button.button == 1)& (button.state == 1))  /* Left */
	   {
	              i=i-1;
                  if (a==0)
		              {image = SDL_LoadBMP("./pacman_g.bmp");}
                    if (a==1) 
                      {image = SDL_LoadBMP("./pacman_g_c.bmp");a=-1;}
                    a++  ;
                   affichage(i,j);
	   }

}
 
void VRPN_CALLBACK vrpn_analog_callback(void* user_data, vrpn_ANALOGCB analog)
{
	/*
    for (int i = 0; i < analog.num_channel; i++)
    {
        std::cout << "Analog Channel : " << i << " / Analog Value : " << analog.channel[i] << std::endl;
		//std::cout << "Analog Channel : " << i << " / Analog Value : " << analog.num_channel << std::endl;
		 i=i+1;
                  if (a==0)
		              {image = SDL_LoadBMP("./pacman_d.bmp");}
                    if (a==1) 
                      {image = SDL_LoadBMP("./pacman_d_c.bmp");a=-1;}
                    a++  ;
                   affichage(i,j);
		}
	*/
}


//fonction detection case impossible, si possible=0 =>case inacessible , le n represente pour 0 1 et 2 un fantome et 3 lepakman

void impossible(int X,int Y,int n)
{
    possible=1;
    if(X==19 || X==-1 || Y==19 || Y==-1)
    {possible=0;}
}

// Surfaces et rectangle
//SDL_Rect rect_aff;

//SDL_Surface *Screen , *image ;
// Fonction d'affichage
void affichage(int x,int y)
{   SDL_FillRect(Screen, NULL, 0);//clear la fenêtre
    rect_aff.x = 32*x; // passage coordonné pixel -> coordonné sprite
    rect_aff.y = 32*y;
    SDL_BlitSurface(image,NULL,Screen,&rect_aff);//affichage pakman
    SDL_Flip(Screen);
    _sleep(80);
}



//int _tmain(int argc, _TCHAR* argv[])
int main (int argc, char **argv)
{
   SDL_Event event;
   // Initialisation de SDL
   if (SDL_Init (SDL_INIT_VIDEO) < 0) {
      fprintf (stderr, "Erreur d'initialisation de SDL: %s\n",
         SDL_GetError ());
      return 1;
   }
   atexit (SDL_Quit); // Pour quitter proprement
   // Initialisation de SDL_Video
   Screen = SDL_SetVideoMode (608, 644, 16, SDL_SWSURFACE|
      SDL_DOUBLEBUF);
   if (Screen == NULL) {
      fprintf (stderr, "Erreur d'init du mode video: %s\n",
         SDL_GetError ());
      return 2;
   }
// Allocation des surfaces 
image = SDL_LoadBMP("./pacman_d.bmp");
// Titre de fenêtre
SDL_WM_SetCaption ("BCI pacman 0.0", NULL);
_sleep(500);


/* flag used to stop the program execution */
    bool running = true;
 
    /* VRPN Button object */
    vrpn_Button_Remote* VRPNButton;
 
    /* Binding of the VRPN Button to a callback */
    VRPNButton = new vrpn_Button_Remote( "openvibe_vrpn_button@localhost" );
    VRPNButton->register_change_handler( &running, vrpn_button_callback );
 
    /* VRPN Analog object */
    vrpn_Analog_Remote* VRPNAnalog;
 
    /* Binding of the VRPN Analog to a callback */
    VRPNAnalog = new vrpn_Analog_Remote( "openvibe_vrpn_analog@localhost" );
    VRPNAnalog->register_change_handler( NULL, vrpn_analog_callback );
 
    /* The main loop of the program, each VRPN object must be called in order to process data */
    while (running)
    {
        VRPNButton->mainloop();
		//VRPNAnalog->mainloop();
		

    }
	
	// affichage(i ,j );  // affichage initial
   // Boucle infinie
/* 
  while (SDL_WaitEvent(&event)&&event.type != SDL_QUIT && event.key.keysym.sym!=SDLK_ESCAPE)
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_DOWN:
                                        
                while (SDL_PollEvent(&event)==0)
                     {
                     impossible(i,j+1,3); 
                     if (possible==1)
		            {
                    j=j+1;
		            if (a==0)
		              {image = SDL_LoadBMP("./pacman_b.bmp");}
                    if (a==1) 
                      {image = SDL_LoadBMP("./pacman_b_c.bmp");a=-1;}
                    a++;
		            affichage(i,j);
                    }
                    }
    		            break;
			case SDLK_UP:
                  while (SDL_PollEvent(&event)==0)
                     {
			    impossible(i,j-1,3);
		            if (possible==1)
				{j=j-1;
				 if (a==0)
		              {image = SDL_LoadBMP("./pacman_h.bmp");}
                    if (a==1) 
                      {image = SDL_LoadBMP("./pacman_h_c.bmp");a=-1;}
                    a++;
				  affichage(i,j);
                } 	}			
                        break;
			case SDLK_RIGHT:
                  while(SDL_PollEvent(&event)==0)
                     {
                impossible(i+1,j,3);
		            if (possible==1)
              {i=i+1;
                  if (a==0)
		              {image = SDL_LoadBMP("./pacman_d.bmp");}
                    if (a==1) 
                      {image = SDL_LoadBMP("./pacman_d_c.bmp");a=-1;}
                    a++  ;
                   affichage(i,j);
              }    }
                   break;
             case SDLK_LEFT:
                   while(SDL_PollEvent(&event)==0)
                     {
                  impossible(i-1,j,3);
		           if (possible==1)
                 { i=i-1;
                 	 if (a==0)
		              {image = SDL_LoadBMP("./pacman_g.bmp");}
                    if (a==1) 
                      {image = SDL_LoadBMP("./pacman_g_c.bmp");a=-1;}
                    a++;
                 	  affichage(i,j);
             }   }
                   break;
                  
          }
          }

      }
*/   



return 0;
}

