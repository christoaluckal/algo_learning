#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cmath>
using positional =  std::pair<int,int>; 
class Node{
    public:
        float g{};
        float h{};
        float f{};
        positional position{};
        positional parent{};
};

void print_2d_vec(std::vector<std::vector<int>> maze){
    for(int i=0;i<maze.size();i++)
    {
        for (int j = 0;j<maze[0].size();j++)
        {
            std::cout << maze[i][j];
        }
        std::cout << '\n';
    }
}

void print_1d_vec(std::vector<Node> list)
{
    for(int i =0;i<list.size();i++)
    {
        std::cout << '('<< list[i].position.first << ',' << list[i].position.second << ") " << list[i].f << ' ';
    }
}

double euclidean(positional pos1, positional pos2)
{
    double dist = sqrt(pow((pos1.first-pos2.first),2)+pow((pos1.second-pos2.second),2));
    return dist;
}

bool findInVector(std::vector<Node> list,positional pos)
{
    for(int i=0;i<list.size();i++)
    {
        if(list[i].position==pos)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    std::vector<std::vector<int>> maze=
            {{0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    Node start{};
    Node end{};
    start.position = {0,0};
    end.position = {10,0};

    std::vector<Node> optimal{};
    std::vector<Node> possible{};


    // optimal.push_back(start);
    possible.push_back(start);
    while(possible.size()>0)
    {
        Node currentnode{};
        currentnode = possible[0];

        double minimum = currentnode.f;
        for(int i=1;i<possible.size();i++)
        {
            if (possible[i].f < minimum)
            {
                currentnode = possible[i];
                minimum = currentnode.f;
            }
        }
        // std::cout << "SELECTED:" << currentnode.position.first << ',' << currentnode.position.second << '\n';
        optimal.push_back(currentnode);
        // print_1d_vec(optimal);
        maze[currentnode.position.second][currentnode.position.first] = 3;
        possible.clear();
        std::cout << '\n';
        if(currentnode.position == end.position){
            std::cout << "ENDED" << '\n';
            exit(0);
        }
        
        std::vector<positional> directions = {{-1,0},{1,0},{0,-1},{0,1},{-1,-1},{1,-1},{-1,1},{1,1}};
        // open.clear();
        for(int i=0;i< directions.size();i++)
        {
            int posx = currentnode.position.first + directions[i].first;
            int posy = currentnode.position.second + directions[i].second;
            positional tempos = {posx,posy};
            if ((posx >= 0 or posx < maze[0].size()) && (posy >= 0 or posy < maze.size()) && maze[posy][posx]!=1 && findInVector(optimal,tempos))
            {
                Node child = Node();

                child.parent = currentnode.position;
                child.position.first = posx;
                child.position.second = posy;
                child.g = currentnode.g+1;
                child.h = euclidean(tempos,end.position);
                child.f = child.g+child.h;
                possible.push_back(child);
            }
        }
        // std::cout << "POSSIBLE";
        // print_1d_vec(possible);
        print_2d_vec(maze);
        std::cout << "\n\n";
    }
}