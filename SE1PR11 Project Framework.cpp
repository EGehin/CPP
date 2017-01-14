#include <iostream>
#include <string>
#include "SDL_Wrapper.h"
#include "ImageFilter.h"
#include <fstream> //used for checking if file exists
#include <Windows.h>
#include "extras.h"

using namespace std;

int main(int argc, char * argv[])
{
	extras extras;

	extras.textColour('p');
	cout << "\tImage Editing\n\n" << endl;
	extras.textColour('t');

        string x; //name of image to be edited
        //cout << "\tImage Editing\n\n";
        cout << "Put image to be edited in Debug folder" << endl;
        cout << "Remember to include file extension" << endl;
		tryagain:
        cout << "\nEnter file name: ";
        cin >> x;
        string Location = x; //string for the name of the image to be loaded
 
        try{ //throws 404 error if file name does not exist
                ifstream myFile(x);
 
                if(myFile.fail()){
                        throw 404;
			}
        
			cImageFilter cImageFilter; //image filter object
			cImageFilter.Load(Location.c_str()); // Load in the Image

 
			int menu; //variables used for loops and stuff
			int colourpicker;
			int brightnessPicker;
			int exitg;
			int darker = 2;
 			float satx= 1;


			begin:
			do //main menu with options for difference filters
			{
					cout << "\n\tFILTERS:" << endl;
					cout << "Enter 1 to NEGATIZE1!!!" << endl;
					cout << "Enter 2 to apply a colour filter" << endl;
					cout << "Enter 3 to change brightness" << endl;
					cout << "Enter 4 to convert to grayscale" << endl;
					cout << "Enter 5 to change saturation\n" << endl;
					
					cout << "\tOPTIONS:" << endl;
					cout << "Enter 6 to clear the CMD" << endl;
					cout << "Enter 7 to reset the image" << endl;
					cout << "Enter 8 to exit" << endl;
					cout << "Enter 9 to reset image and exit" << endl;
					cin >> menu; //users input taken

					if(cin.fail()){
						cout << "\nPlease only enter numbers" << endl;
						cout << "\nProgram will now exit..." << endl;
						break;
					}
					if (menu == 1) //NEGATIZE!
							cImageFilter.Negative();
					else if (menu==2) //colours
					{
							do
							{
									cout << "Please choose a colour: \n " << endl; //difference colour filters
									cout << "Press 1 for ";
									extras.textColour('g');
									cout << "green" << endl;
									extras.textColour('t');

									cout << "Press 2 for ";
									extras.textColour('b');
									cout <<"blue" << endl;
									extras.textColour('t');

									cout << "Press 3 for ";
									extras.textColour('r');
									cout << "red" << endl;
									extras.textColour('t');

									cout << "Press 0 to go back to the main menu\n" << endl;
									cin >> colourpicker;
 
									switch (colourpicker)
									{
											case 1:
											case 2:
											case 3:
													cImageFilter.Colourify(colourpicker);
													break;
											default:
													colourpicker = 0;
													break;
									}
							} while (colourpicker =0);
					}
					else if (menu == 4){ //grayscale
						cImageFilter.changeSaturation(0, 1);} //0 sets the image to grayscale
					else if (menu == 5){ //saturation
						cImageFilter.changeSaturation(satx, 0);} //takes user defined value
					else if (menu == 6){
						extras.clearCMD();
						goto begin;
					}
					else if (menu == 3) //brightness
						cImageFilter.Brightness();
					else if (menu == 7) //reset image
						cImageFilter.ResetImage();
					else if (menu == 8) //exit
						continue;
					else if (menu == 9){ //exit + reset
						cImageFilter.ResetImage();
						cImageFilter.Save();
						goto skip;
					}
					else
							cout << "Not an option!" << endl;

					cImageFilter.Save(); //image saved if not already
 
					cout << "Save image and exit? y/n" << endl; //allows the user to change to a different effect
					char diffEffect;
					cin >> diffEffect;
 
					if (diffEffect != 'y'){ //if the user enters y for yes
							cout << "Try a difference effect then!" << endl;
					}
					else
					menu = 0;
			} while (menu != 0); //user enters 0 to exit the program

		} catch(int e){
                cout << "\nFile does not exist. Error number: " << e << "\n" << endl;
				cout << "Enter file name again? y/n" << endl;
				char quit;
				cin >> quit;
				if (quit == 'y' || quit == 'Y')
					goto tryagain; //user enters filename again
				else goto fullskip; //user exits program

        }
		skip:
		cout << "\nThanks for using Elliot's Image Editing tool!\n" << endl; //exit message
		fullskip:
        return 0;
}