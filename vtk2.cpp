/* VTK - Virtual Tomasz Kłoczko v. 0.3 (20060803)
 * Author: Bartosz Świątek (shadzik@gmail.com)
 * License: GPL
 *
 * ChangeLog
 * v. 0.3 - added zmien(); function
 * v. 0.2 - added functionality, works now
 * v. 0.1 - init version
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <cstdlib>

#define book ".vtkdatabase"

using namespace std;

/*
 * No comment :D
*/
void help()
{
        cout << "Usage:\tvtk2 <options>\n"
                "-a word tk_word - add word and it's TK version to database\n"
                "-r word         - remove word from database\n"
                "-s string       - convert to pl_TK\n"
                "-l              - print every entry\n"
                "-h              - shows this help\n";
}

/*
 * Adds entries to the file, nothing special at this moment.
*/

void add(string nick, string mail)
{
   ofstream file(book, ios::app);
   if (file.is_open())
   {
      file << nick 
           << endl 
           << mail 
           << endl;
      file.close();
   } else {
      cout << "Write file error.\n";
   }
}

/* 
 * stolen from my C code
 * change place of letters in a word, beginning with a random letter
*/

int los(void);

string zmien(string ch)
{
  char temp;
  unsigned int i=0;
  for(i=0;i<ch.size();i++)
  {
    if(i!=0)
    {
      if((i%los()==0) && (isalpha(ch[i])) && (isalpha(ch[i+1])))
      {
        temp=ch[i];
        ch[i]=ch[i+1];
        ch[i+1]=temp;
      }
    }
    //cout << ch[i];
  }
  //cout << endl;
  return ch;
}

int los(void)
{
  srand(time(0));
  int i;
  i = rand()%10;
/* This should help get smaller random numbers
 * but acctually it just sucks
 * if(i>6)
 *   i = i/2;
*/
  return i;
}


/*
 * Searches for an entry
*/

string search(string s_nick)
{
   ifstream file(book);
   vector<map<string, string> > dane;

   if (! file.is_open())
   {
      cout << "File read error.\n";
      exit (1);
   }

   while (!file.eof())
   {
      string pobrana_linia;
      map<string, string> mapa;

      getline(file, pobrana_linia); //gets the whole line
      mapa.insert(map<string, string>::value_type("nick", pobrana_linia)); //puts it into the map
      dane.push_back(mapa); //inserts the map into the vector
   }

   for(unsigned int i=0;i < dane.size(); ++i) //start searching :)
   {
      if ((dane[i]["nick"] == s_nick) && (i+1 < dane.size()))
      {
         return dane[i+1]["nick"];
      } else if ((dane[i]["nick"] != s_nick) && (i+1 >= dane.size())) {
         return zmien(s_nick);
      }
   }
   return "";
}

/*
 * Shows the whole list using the same idea as in search(string arg);
*/

void list()
{
   ifstream file(book);
   vector<map<string, string> > dane;

   if (! file.is_open())
   {
      cout << "File read error.\n";
      exit (1);
   }

   while (!file.eof())
   {
      string pobrana_linia;
      map<string, string> mapa;

      getline(file, pobrana_linia);
      mapa.insert(map<string, string>::value_type("nick", pobrana_linia));
      dane.push_back(mapa);
   }

   for(unsigned int i=0;i < dane.size(); ++i)
   {
      if (i+1 < dane.size()) //in order not to get an segfault in case that we were beyond our memory
      {
         cout << dane[i]["nick"] << " -> " << dane[i+1]["nick"] << endl;
         i++;
      }
   }
}

/*
 * Removes entries from the file if existent
*/

void rm(string r_nick)
{
   ifstream file(book);
   vector<map<string, string> > dane;

   if (! file.is_open())
   {
      cout << "File read error.\n";
      exit (1);
   }

   while (!file.eof())
   {
      string pobrana_linia;
      map<string, string> mapa;

      getline(file, pobrana_linia); //gets the whole line
      mapa.insert(map<string, string>::value_type("nick", pobrana_linia)); //puts it into the map
      dane.push_back(mapa); //inserts the map into the vector
   }
   
   ofstream file2(book, ios::trunc);
   for(unsigned int i=0;i < dane.size(); ++i) //start searching :)
   {
      if ((dane[i]["nick"] == r_nick) && ((i+2) < dane.size()))
      {
         dane.erase(dane.begin()+i,dane.begin()+i+2);
      }

      if (file2.is_open())
      {
         if (dane[i]["nick"].size() != 0) //in case not to put empty data to the file
         {
            file2 << dane[i]["nick"]
                  << endl;
         }
      } else {
         cout << "Write file error.\n";
      }
   } //end for
   file2.close();
}

/*
 * The main method, nothing special.
*/

int main(int argc, char *argv[])
{
   int ch,i=1;
   try {
   while ((ch = getopt(argc, argv, "hls:a:r:")) != -1)
   {
       switch(ch)
       {
          case 'a':
                    add(optarg, argv[optind]);
                    exit(0);
                    break;
          case 's':
                    while (argv[++i]!=0)
                    	cout << search(argv[i]) << " ";
                    cout << endl;
                    exit(0);
                    break;
          case 'l':
                    list();
                    exit(0);
                    break;
          case 'r':
                    rm(optarg);
                    exit(0);
                    break;
          case 'h':
                    help();
                    exit(0);
                    break;
          default:
                    help();
                    exit(0);
                    break;
       }
   }
   } catch (...) {
   cout << "Cought Exception.\n";
   }
}
