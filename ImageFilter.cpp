#include "ImageFilter.h"
#include <iostream>
#include <string>
#include "SDL_Wrapper.h"
#include "SDL.h"
#include "SDL_image.h"

using namespace std;


SDL_Surface* cImageFilter::Load(const char* location)
{
        cout << "Loading Image : " << location << endl;
        m_cLoadedSurface = LoadImage(location);
 
        if (m_cLoadedSurface == NULL)
                return 0;
 
        GetPixelArray(m_cLoadedSurface,&m_nWidth,&m_nLength);
 
        m_cNewSurface = CreateNewImage(1024,768);
}

 
void cImageFilter::Negative()
{
        for(int a = m_cNewSurface->h - 1; a >= 0; a--) //reads in y values of image
        {
                for(int x = 0; x < m_cNewSurface->w; x++){ //reads in x values of image
                        GetRGBValues(m_cLoadedSurface, x, a, &R, &G, &B); //function get the values
                        SetRGBValues(m_cNewSurface,x,a,255-R,255-G,255-B); //sets the values to there inverse for a negative affect
 
                }
        }
}
 
void cImageFilter::Colourify(int c) //1 green 2 blue 3 red
{
        if (c == 1){ //green
                for(int n = m_cNewSurface->h - 1; n >= 0; n--){
                        for(int x = 0; x < m_cNewSurface->w; x++)
                        {
                                GetRGBValues(m_cLoadedSurface, x, n, &R, &G, &B);
 
                                        R=R*Gr; //uses defined values in header.h to adjust colours
                                        G=G*Gg;
                                        B=B*Gb;
       
                                SetRGBValues(m_cNewSurface,x,n,R,G,B); 
                        }
                }
        }
 
        else if (c == 2){ //blue
                for(int n = m_cNewSurface->h - 1; n >= 0; n--){
                        for(int x = 0; x < m_cNewSurface->w; x++)
                        {
                                GetRGBValues(m_cLoadedSurface, x, n, &R, &G, &B);
 
                                        R=R*Br;
                                        G=G*Bg;
                                        B=B*Bb;
       
                                SetRGBValues(m_cNewSurface,x,n,R,G,B); 
                        }
                }
        }
 
        else if (c == 3){ //red
                for(int n = m_cNewSurface->h - 1; n >= 0; n--){
                        for(int x = 0; x < m_cNewSurface->w; x++)
                        {
                                GetRGBValues(m_cLoadedSurface, x, n, &R, &G, &B);
 
                                        R=R*Rr;
                                        G=G*Rg;
                                        B=B*Rb;
       
                                SetRGBValues(m_cNewSurface,x,n,R,G,B); 
                        }
                }
        }
        SaveImageBMP(m_cNewSurface, "NewImage.bmp"); //image is saved with new filename
}
 

void cImageFilter::ResetImage()
{
        for(int a = m_cNewSurface->h - 1; a >= 0; a--)
        {
                for(int x = 0; x < m_cNewSurface->w; x++){
                        GetRGBValues(m_cLoadedSurface, x, a, &R, &G, &B);
                        SetRGBValues(m_cNewSurface,x,a,R,G,B); //default image
                }
        }
}

void cImageFilter::Brightness()
{
	here:
    int lighterOrDarker;
    cout << "Enter 1 to increase brightness" << endl; //submenu for increasing and decreasing brightness
    cout << "Enter 2 to decrease brightness" << endl;
    cout << "Enter 0 to go back to the main menu\n" << endl;
    cin >> lighterOrDarker; //takes the users input for whether to increase or decrease the brightness

    do
    {
        if (lighterOrDarker == 1) //lighter
        {
            float percent;
            float y;
            cout << "Recommended maximum @ 250%" << endl;
            cout << "Enter percentage: " << endl;
            cin >> percent;
            y = (0.2126*R) + (0.7152*G) + (0.0722*B);
            y = y/3;
            percent = percent/100;
            y = y*percent;
            floor(y);
            for(int a = m_cNewSurface->h - 1; a >= 0; a--)
            {
                for(int x = 0; x < m_cNewSurface->w; x++){
                    GetRGBValues(m_cLoadedSurface, x, a, &R, &G, &B);

                    if (R+y >280)
                        R = 255;
                    else if (R+y >255)
                    R = 250;
                    else R = R+y;

                    if (B+y >280)
                        B= 255;
                    else if (B+y >255)
                    B = 250;
                    else B = B+y;

                    if (G+y >280)
                        G= 255;
                    else if (G+y >255)
                    G = 250;
                    else G = G+y;

                    SetRGBValues(m_cNewSurface,x,a,R,G,B); //image values set
                }
				
            }
			SaveImageBMP(m_cNewSurface, "NewImage.bmp"); //and saved
			goto here;
        }
        else if (lighterOrDarker == 2) //darker
                            {

            float percent;
            float y;
            cout << "Enter percentage: " << endl;
            cin >> percent;

            y = (0.2126*R) + (0.7152*G) + (0.0722*B);
            y = y/3;
            percent = percent/100;
            y = y*percent;
            floor(y);


            for(int a = m_cNewSurface->h - 1; a >= 0; a--)
            {
                for(int x = 0; x < m_cNewSurface->w; x++){
                    GetRGBValues(m_cLoadedSurface, x, a, &R, &G, &B);

                        if (R-y <-20)
                            R = 0;
                        else if (R-y <0)
                        R = 10;
                        else R = R-y;

                        if (G-y <-20)
                            G = 0;
                        else if (G-y <0)
                        G = 10;
                        else G = G-y;
                    
                        if (B-y <-20)
                            B = 0;
                        else if (B-y <0)
                        B = 10;
                        else B = B-y;
                        
                        SetRGBValues(m_cNewSurface,x,a,R,G,B);

                }
            }
			SaveImageBMP(m_cNewSurface, "NewImage.bmp");
			goto here;
        }
		else{
			cout << "Not an option" << endl;
		lighterOrDarker = 0;
		}

    } while (lighterOrDarker !=0);

}


 
void cImageFilter::Save()
{

        SaveImageBMP(m_cNewSurface, "NewImage.bmp"); //image saved if not already
}
 
/*void textColour(char c){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (c == 'p') //pink
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY ));
	else if (c== 'g') //green
	SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_INTENSITY ));	
	else if (c=='b') //blue
	SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_INTENSITY ));	
	else if (c=='r')
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY ));	

	else if (c == 't') //reset
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));


}*/

void cImageFilter::changeSaturation(float change, int gray) {
	if (gray !=1) //this function is used for grayscale and saturation, this bit only runs for saturation
	{
	float satx;
	cout << "\nEnter a value between 0-2" << endl;
	cout << "0-1 will decrease saturation, 1-2 will increase saturation" << endl;
	cin >> satx;
	change = satx;
	}
	for(int a = m_cNewSurface->h - 1; a >= 0; a--)
            {
                for(int x = 0; x < m_cNewSurface->w; x++){
                    GetRGBValues(m_cLoadedSurface, x, a, &R, &G, &B);

					double  P=sqrt((R)*(R)*Pr+(G)*(G)*Pg+(B)*(B)*Pb);

					R=P+((R)-P)*change;
					G=P+((G)-P)*change;
					B=P+((B)-P)*change; 

					if(R > 255)
						R = 255;
					if(R < 0)
						R=0;
					if(G <0)
						G=0;
					if(B <0)
						B=0;

					if(G > 255)
						G = 255;

					if(B > 255)
						B = 255;

					SetRGBValues(m_cNewSurface,x,a,R,G,B);
					}

				SaveImageBMP(m_cNewSurface, "NewImage.bmp");
			}
}