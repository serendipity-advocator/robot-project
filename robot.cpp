#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

ifstream input("robot.data",ios::in);
ofstream output("robot.final");

class point
{
private:
  int X = -1;
  int Y = -1;
  char shape;
  int Dist_to_R = -1;
  int color = 0;
  int discover = 0;
  int finish =0;
  int predecessor = -1;
  point* right = 0;
  point* left = 0;
  point* up = 0;
  point* down = 0;
public:
  void set_X(int hor_index)
  {
    X = hor_index;
  }
  void set_Y(int ver_index)
  {
    Y = ver_index;
  }
  int get_X()
  {
    return X;
  }
  int get_Y()
  {
    return Y;
  }
  void set_shape(char ch)
  {
    shape = ch;
  }
  char get_shape()
  {
    return shape;
  }
  int Distance_counting(int x, int y)
  {
    return (abs(X-x)+abs(Y-y));
  }
  void set_D_to_R(int dist)
  {
    Dist_to_R = dist;
  }
  int get_D_to_R()
  {
    return Dist_to_R;
  }
  point* Up()
  {
    return up;
  }
  point* Down()
  {
    return down;
  }
  point* Left()
  {
    return left;
  }
  point* Right()
  {
    return right;
  }
  void Set_up(point* insert)
  {
    up = insert;
  }
  void Set_down(point* insert)
  {
    down = insert;
  }
  void Set_left(point* insert)
  {
    left = insert;
  }
  void Set_right(point* insert)
  {
    right = insert;
  }
};


class clean_area
{
friend class point;
private:
    int ver_vertex = 0;
    int hor_vertex = 0;
    int battery = 0;
    point** area;
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
    void set_battery(int life_span)
    {
      battery = life_span;
    }
    int get_battery()
    {
      return battery;
    }
    void print_clean_area()
    {
      for(int i=0; i<ver_vertex; i++)
      {
        for(int j=0; j<hor_vertex; j++)
        {
          cout<<area[i][j].get_shape();
          //output<<area[i][j].shape;
        }
        cout<<endl;
        //output<<endl;
      }
}
    bool edge_detection()
    {
      cout<<"Operating edge detection!"<<endl;
      cout<<"detect the horizontal edges."<<endl;
      for(int i=0; i<ver_vertex; i++)
      {
        cout<<"area["<<i<<"]["<<0<<"]"<<" = "<<area[i][0].get_shape()<<endl;
        if(area[i][0].get_shape() == '0'){return 0;}
        cout<<"area["<<i<<"]["<<hor_vertex-1<<"]"<<" = "<<area[i][hor_vertex-1].get_shape()<<endl;
        if(area[i][hor_vertex-1].get_shape() == '0'){return 0;}
      }
      cout<<"detect the vertical edges."<<endl;
      for(int j=1; j<hor_vertex-1;j++)
      {
        cout<<"area["<<0<<"]["<<j<<"]"<<" = "<<area[0][j].get_shape()<<endl;
        if(area[0][j].get_shape() == '0')
        {
          cout<<"Illegal!"<<endl;
          return 0;
        }
        cout<<"area["<<ver_vertex-1<<"]["<<j<<"]"<<" = "<<area[ver_vertex-1][j].get_shape()<<endl;
        if(area[ver_vertex-1][j].get_shape() == '0'){return 0;}
      }
      cout<<"Finished!"<<endl;
      return 1;
     }
    void set_area_from_input()
    {
      int ver;
      int hor;
      int life_span;
      int enough_battery = 0;
      int count =0;
      input>>ver;
      input>>hor;
      input>>life_span;
      //output<<ver_vertex<<" "<<hor_vertex<<" "<<life_span<<endl;
      set_ver(ver);
      set_hor(hor);
      set_battery(life_span);
      fflush(stdin);
      //getchar();

      int i, j, k;
      //cout<<"bang"<<endl;
      area = (point**)new point[(ver_vertex)*sizeof(point*) + (hor_vertex)*hor_vertex*sizeof(point)];
      //cout<<endl;
      //cout<<"bang"<<endl;
      for(i = 0; i < (ver_vertex); i++)
      {
        area[i] = ((point *)(area + ver_vertex) + i*hor_vertex*sizeof(point));
      }
      cout<<"Now, we have "<<ver_vertex<<"*"<<hor_vertex<<" clean_area."<<endl;
      for(j= 0; j < ver_vertex; j++)
        {
          for(k = 0; k < hor_vertex; k++)
          {
            area[j][k].set_shape('0');
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
            area[i][j].set_shape(ch);
            cout<<"area["<<i<<"]["<<j<<"] = "<<area[i][j].get_shape()<<endl;
          }
          else if(ch == '1')
          {
            area[i][j].set_shape(ch);
            cout<<"area["<<i<<"]["<<j<<"]"<<" = "<<area[i][j].get_shape()<<endl;
          }
          else if(ch =='R')
          {
            if(count == 0)
            {
              area[i][j].set_shape(ch);
              set_R_x(j);
              set_R_y(i);
              cout<<"area["<<i<<"]["<<j<<"]"<<" = "<<area[i][j].get_shape()<<endl;
              cout<<"The charging place (R) in this area is located at";
              cout<<"("<<R_x<<", "<<R_y<<")"<<endl;
              count++;
            }
            else
            {
              if(count>1)
              {
                cout<<"Illegal! There are "<<count;
                cout<<" charging place in the clean area!"<<endl;
                exit(1);
              }
              else
              {
                cout<<"Illegal! There doesn't exist charging place in the clean area"<<endl;
                exit(1);
              }
            }
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
      if(!edge_detection())
      {
        cout<<"illegal clean_area!"<<endl;
        exit(1);
      }

      for(int i=0; i<ver_vertex; i++)
      {
        for(int j=0; j<hor_vertex; j++)
        {
          area[i][j].set_Y(i);
          area[i][j].set_X(j);
        }
      }

      for(int i=0; i<ver_vertex; i++)
      {
        for(int j=0; j<hor_vertex; j++)
        {
          if(area[i][j].get_shape() == '1')
          {
            area[i][j].set_D_to_R(-1);
          }
          else
          {
            area[i][j].set_D_to_R(area[i][j].Distance_counting(R_x, R_y));
            if(enough_battery< area[i][j].get_D_to_R())
            {
              cout<<"The distance to R from area["<<i<<"]["<<j<<"]"<<" = ";
              cout<<area[i][j].get_D_to_R()<<endl;
              enough_battery = area[i][j].get_D_to_R();
            }
          }
        }
      }
      if(get_battery()<2*enough_battery)
      {
        cout<<"The maximum battery is "<<get_battery()<<", which is ";
        cout<<"less than the doubling of the farthest distance("<<enough_battery<<") in the clean area.";
        cout<<endl;
        print_D_to_R();
        cout<<"illegal clean area! Without enought battery."<<endl;
        exit(1);
      }
      for(int i=0; i<ver_vertex; i++)
      {
        for(int j=0; j<hor_vertex; j++)
        {
          if(i>0 && area[i-1][j].get_shape()!='1')
          {
            area[i][j].Set_up(&area[i-1][j]);
            cout<<"The upside of the area["<<i<<"]["<<j<<"] = area["<<i-1<<"]["<<j<<"]"<<endl;
          }
          if(i<(ver_vertex-1) && area[i+1][j].get_shape()!='1')
          {
            area[i][j].Set_down(&area[i+1][j]);
            cout<<"The downside of the area["<<i<<"]["<<j<<"] = area["<<i+1<<"]["<<j<<"]"<<endl;
          }
          if(j>0 && area[i][j-1].get_shape()!='1')
          {
            area[i][j].Set_left(&area[i][j-1]);
            cout<<"The leftside of the area["<<i<<"]["<<j<<"] = area["<<i<<"]["<<j-1<<"]"<<endl;
          }
          if(j<(hor_vertex-1) && area[i][j+1].get_shape()!='1')
          {
            area[i][j].Set_right(&area[i][j+1]);
            cout<<"The rightside of the area["<<i<<"]["<<j<<"] = area["<<i<<"]["<<j+1<<"]"<<endl;
          }
        }
      }
}
    point** get_area()
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
    void print_D_to_R()
    {
      cout<<"The shortest distance from R to all points in the clean area is: "<<endl;
      for(int i=0; i<ver_vertex; i++)
      {
        for(int j=0; j<hor_vertex; j++)
        {
          if(area[i][j].get_D_to_R() == 0)
          {
            cout<<"R\t";
          }
          else if(area[i][j].get_shape() == '0')
          {
            cout<<area[i][j].get_D_to_R()<<"\t";
          }
          else
          {
            cout<<"X\t";
          }
        }
        cout<<endl<<endl;
      }
    }
    /*void DFS(int Start)
    {
    int time = 0;
    int k = Start;
    for(int i=0; i<ver_vertex; i++)
    {
      for(int j=0; j<hor_vertex; j++)
      {
        if (area[i][j].color == 0)
        {// 若vertex不是白色, 則進行以該vertex作為起點之搜尋
            DFSVisit(i, j, time);
        }
      }
    }
}
    void DFSVisit(int ver, int hor, int &time)
    {   // 一旦有vertex被發現而且是白色, 便進入DFSVisit()
    area[i][j].color = 1;                         // 把vertex塗成灰色
    area[i][j].discover = ++time;                 // 更新vertex的discover時間
      for ()
      {                    // 分成兩段
          if (color[i] == 0)
          {
              predecessor[m] = vertex;        // 更新其predecessor
              DFSVisit(m, time)      // 立刻以其作為新的搜尋起點, 進入新的DFSVisit()
          }
      }
    area[i][j].color = 2;                         // 當vertex已經搜尋過所有與之相連的vertex後, 將其塗黑
    area[i][j].finish = ++time;                   // 並更新finish時間
  }*/
};
int main()
{
  clean_area eg;
  eg.set_area_from_input();
  eg.print_D_to_R();
  return 0;
}
