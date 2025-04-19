#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <string>
#pragma comment(lib, "winmm.lib");
using namespace std;

int main()
{
  string name;
  cout << "Enter the Name of the Music you want to Play : " << endl;
  cin >> name;
  cout << "PLaying Music " << endl;
  bool result = PlaySoundA(name.c_str(), NULL, SND_FILENAME | SND_SYNC);
  if (!result)
  {
    cout << "Failed to play the sound" << endl;
  }
  else
  {
    cout << "succesfully play the sound" << endl;
  }
}

//alhamdulilah succeed