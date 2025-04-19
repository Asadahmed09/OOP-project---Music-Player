#include<windows.h>// used for windows opr like playing music file 
#include<mmsystem.h>// same i contact with windows
#include<iostream>
#include<string>// used for string functions
#include<vector>// used for dynamic arrays for storing fav songs
#include<algorithm>// for special function known as find(), it will help us in finding songs
#include<fstream>//for filing


#pragma comment(lib,"winmm.lib")
using namespace std;

//We are making class of Functions on Music
class Action
{
  private:
  vector<string> Favourite;
  int currentIndex = -1;
  public:

  Action()
  {
    // consfortructor used for automatically loading the favourite song playlist ,
    // although we can do it in program manually
    LoadFav();
  }

  void NextSong()
  {
    if(Favourite.empty())
    {
      cout << "Playlist is Empty " << endl;
      return;
    }
    StopMusic();
    currentIndex = (currentIndex + 1) % Favourite.size(); // Circular next - current index 0 whenever first PlayMusic
                                                          // then we use distance b - a (distance(vector.begin(),filename)) 4 currentindex
    string next = Favourite[currentIndex];
    PlayMusic(next);
    cout << "Playing Next Song: " << next << endl;
  }
  
  
  
  void PreviousSong()
  {
    if(Favourite.empty())
    {
      cout << "Playlist is Empty " << endl;
      return;
    }
    StopMusic();
    currentIndex = (currentIndex - 1) % Favourite.size(); // same logic just minus
    string prev = Favourite[currentIndex];
    PlayMusic(prev);
    cout << "Playing Previous Song: " << prev << endl;
  }



  void LoadFav()
  {
    ifstream fetchSongs("MUSICFILE.txt");
    string song;
    while(getline(fetchSongs,song))
    {
      if(!song.empty())
      {
        Favourite.push_back(song);
      }
    }
    cout << "Favourite songs Load successfully ! " << endl;
    fetchSongs.close();
  }

  
  
  
  void SaveFav(string& FileName)
  {
    ofstream FILE("MUSICFILE.txt",ios::app);
    FILE << FileName << endl;
    cout << "Favourite song Saved Succesfully " << endl;
    FILE.close();
  }



  void PlayMusic(string& FileName)
  {
    string command  = "open \"" + FileName + "\" type mpegvideo alias mymusic";
    mciSendStringA(command.c_str(),NULL,0,NULL);
    bool report  = mciSendStringA("play mymusic",NULL,0,NULL);
    if(report){cout << "Music File is not opened "<<endl;}
    else
      {
        cout << "Music File is opened "<<endl;
        // Update currentIndex to the currently played file if it exists in favourites
        auto it = find(Favourite.begin(), Favourite.end(), FileName);
        if (it != Favourite.end())
        {
          currentIndex = distance(Favourite.begin(), it);
        }
      }
}

  void PauseMusic()
  {
    mciSendStringA("pause mymusic",NULL,0,NULL);
  }

  void ResumeMusic()
  {
    mciSendStringA("resume mymusic",NULL,0,NULL);
  }

  void StopMusic()
  {
    mciSendStringA("stop mymusic",NULL,0,NULL);
    mciSendStringA("close mymusic",NULL,0,NULL);
  }

  void AddToFav(string& FileName)
  {
    if(find(Favourite.begin(),Favourite.end(),FileName) == Favourite.end())
    {
      Favourite.push_back(FileName);
      cout << "Song Added successfully in your Playlist : " << FileName << endl;
    }
    else
    {
      cout << "This song is already in your Playlist " << endl;
    }
  }

  void ShowFav()
  {
    if(Favourite.empty())
    {
      cout << "There is no Favourite song in your Playlist" << endl;
    }
    else
    {
      cout << "Displaying Favourite Songs : " << endl;
      for(int i = 0 ; i < Favourite.size() ; i++)
      {
        cout << i+1 << " : " << Favourite[i] << endl;
      }
    }
  }

  void RemoveFromFav()
  {
    StopMusic();
    cout << "Enter the Song Name to remove : " << endl;
    string FileName;
    cin >> FileName;
    auto it = find(Favourite.begin(),Favourite.end(),FileName);
    if(it!=Favourite.end())
    {
      Favourite.erase(it);
      cout << "Song : " << FileName <<" Removed From the Favourite Paylist" << endl;
    }
    else
    {
      cout << "Unable to Find the Song in the given Playlist" << endl;
    }
    UpdateFile();
  }


  void UpdateFile()
  {
    ofstream Out("MUSICFILE.txt",ios::trunc);
    for(string& song:Favourite)
    {
      Out << song << endl;
    }
    Out.close();
    cout << "Updated File Successfully ! after removing the song " << endl;
  }


  string PlayNewMusic()
  {
    StopMusic();
    cout << "Enter the Name of New Music : " << endl;
    string FileName;
    cin >> FileName;
    PlayMusic(FileName);
    cout << "The song : " << FileName << " is being played " << endl;
    return FileName;
  }

};


int main()
{
  Action Player;
  string name;
  int choice;
  cout << "Enter the Name of the Music you want to Play : " << endl;
  cin >> name ;
  do
  {
    cout << "\t\t------Enter the Operation------\t\t"<<endl;
    cout << "1-PlayMusic\n2-PauseMusic\n3-ResumeMusic\n4-StopMusic\n5-Exit\n";
    cout << "6-AddFavourite\n7-ShowFavourite\n8-SavePlaylist\n9-LoadPlaylist\n";
    cout << "10-NextSong\n11-PreviousSong\n12-RemoveSong\n13-PlayNewSong"<<endl;
    cin >> choice;
    switch(choice)
    {
      case 1:Player.PlayMusic(name);break;
      case 2:Player.PauseMusic();break;
      case 3:Player.ResumeMusic();break;
      case 4:Player.StopMusic();break;
      case 5:Player.StopMusic();break;
      case 6:Player.AddToFav(name);break;
      case 7:Player.ShowFav();break;
      case 8:Player.SaveFav(name);break;
      case 9:Player.LoadFav();break;
      case 10:Player.NextSong();break;
      case 11:Player.PreviousSong();break;
      case 12:Player.RemoveFromFav();break;
      case 13:
          {
            name  = Player.PlayNewMusic();
            cout << "Testing : " << name << endl;
            break;
          }
      default : cout << "Invalid Choice" << endl;
    }
  } while (choice!=5);
  
}