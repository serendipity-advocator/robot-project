#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ifstream input("robot.data",ios::in);
ofstream output("robot.final");

class clean_area
{
private:
    int ver_vertex = 0;
    int hor_vertex = 0;
    char** area;
    int R_x = 0;
    int R_y = 0;
public:
    void set_ver(int ver)
    {
      ver_vertex = ver;
    }
    void set_hor(int hor)
    {
      hor_vertex = hor;
    }
    int get_ver()
    {
      return ver_vertex;
    }
    int get_hor()
    {
      return hor_vertex;
    }
    void print_clean_area()
    {
      for(int i=0; i<ver_vertex; i++)
      {
        for(int j=0; j<hor_vertex; j++)
        {
          cout<<area[i][j];
          //output<<area[i][j];
        }
        cout<<endl;
        //output<<endl;
      }
}
    bool edge_detection()
    {
      cout<<"Operating edge detection!"<<endl;
      cout<<"detect the hor_vertexizontal edges."<<endl;
      for(int i=0; i<ver_vertex; i++)
      {
        cout<<"area["<<i<<"]["<<0<<"]"<<" = "<<area[i][0]<<endl;
        if(area[i][0] == '0'){return 0;}
        cout<<"area["<<i<<"]["<<hor_vertex-1<<"]"<<" = "<<area[i][hor_vertex-1]<<endl;
        if(area[i][hor_vertex-1] == '0'){return 0;}
      }
      cout<<"detect the ver_vertextical edges."<<endl;
      for(int j=1; j<hor_vertex-1;j++)
      {
        cout<<"area["<<0<<"]["<<j<<"]"<<" = "<<area[0][j]<<endl;
        if(area[0][j] == '0')
        {
          cout<<"illegal!"<<endl;
          return 0;
        }
        cout<<"area["<<ver_vertex-1<<"]["<<j<<"]"<<" = "<<area[ver_vertex-1][j]<<endl;
        if(area[ver_vertex-1][j] == '0'){return 0;}
      }
      cout<<"Finished!"<<endl;
      return 1;
     }
    bool charging_place_detection()
    {
      int count =0;
      for(int i=0; i<ver_vertex; i++)
      {
        for(int j=0; j<hor_vertex; j++)
        {
          if(area[i][j] == 'R')
          {
            count++;
          }
          if(count>1)
          {
            cout<<"Illegal! There are "<<count;
            cout<<" charging place in the clean area!"<<endl;
            return 0;
          }
        }
      }
      if(count ==0)
      {
        cout<<"Illegal! There doesn't exist charging place in the clean area"<<endl;
        return 0;
      }

      else return 1;
}
    void set_area_from_input()
    {
      int ver;
      int hor;
      int life_span;
      input>>ver;
      input>>hor;
      input>>life_span;
      //output<<ver_vertex<<" "<<hor_vertex<<" "<<life_span<<endl;
      set_ver(ver);
      set_hor(hor);
      fflush(stdin);
      //getchar();

      int ch;
      int i, j, k;
      //cout<<"bang"<<endl;
      area = (char**)new char[(ver_vertex)*sizeof(char*) + (hor_vertex)*hor_vertex*sizeof(char)];
      //cout<<endl;
      //cout<<"bang"<<endl;
      for(i = 0; i < (ver_vertex); i++)
      {
        area[i] = ((char *)(area + ver_vertex) + i*hor_vertex*sizeof(char));
      }
      cout<<"Now, we have "<<ver_vertex<<"*"<<hor_vertex<<" clean_area."<<endl;
      for(j= 0; j < ver_vertex; j++)
        {
          for(k = 0; k < hor_vertex; k++)
          {
            area[j][k] = 0;
          }
        }
      for(i=0; i<ver_vertex; i++)
      {
        for(j=0; j<hor_vertex; j++)
        {
          char ch;
          cout<<"try to get area["<<i<<"]["<<j<<"]"<<endl;
          input.get(ch);
          if(ch == '\n')
          {
            input.get(ch);
          }
          cout<<"What we've just get from file is "<<ch<<endl;
          //cout<<ch<<endl;
          if(ch == '0')
          {
            area[i][j] = ch;
            cout<<"area["<<i<<"]["<<j<<"] = "<<area[i][j]<<endl;
          }
          else if(ch == '1')
          {
            area[i][j] = ch;
            cout<<"area["<<i<<"]["<<j<<"]"<<" = "<<area[i][j]<<endl;
          }
          else if(ch =='R')
          {
            area[i][j] = ch;
            cout<<"area["<<i<<"]["<<j<<"]"<<" = R"<<endl;
          }
          else
          {
            cout<<"invalid clean area!"<<endl;
            return;
          }
        }
      }
      cout<<"Area build complete!"<<endl;
      cout<<"Display clean area as follows: "<<endl;
      print_clean_area();
      if(!edge_detection()||!charging_place_detection())
      {
        cout<<"illegal clean_area!"<<endl;
      }
}
    char** get_area()
    {
      return area;
    }
    void set_R_x(int x)
    {
      R_x = x;
    }
    void set_R_y(int y)
    {
      R_y = y;
    }
    void R_finding()
    {
      for(int j= 0; j < ver_vertex; j++)
        {
          for(int k = 0; k < hor_vertex; k++)
          {
            if(area[j][k] == 'R')
            {
              set_R_x(j);
              set_R_y(k);
              break;
            }
          }
        }
    }
    void get_R()
    {
      cout<<"The charging place in this area is locted at";
      cout<<"("<<R_x<<", "<<R_y<<")"<<endl;
    }
    void clean_area_initializing()
    {
      set_area_from_input();
      R_finding();
      get_R();
    }
};
int main()
{
  clean_area eg;
  eg.clean_area_initializing();
  return 0;
}
