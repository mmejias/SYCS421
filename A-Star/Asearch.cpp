#include <stdio.h>

#include <cmath>
#include <time.h>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include "NodeA.h"
using namespace std;

const int MAX_X = 4;
const int MAX_Y = 4;

bool isGoal(Node, Node);
bool isAdjacent(Node, Node);
float calculatehn(Node, Node);
void checkSuccessors(Node*, vector<Node>&, vector<Node>&, Node, Node);
void collectInput(int&, int&, int&, int&);
void generateSuccessors(bool&, Node, Node*, float[MAX_X][MAX_Y]);
void printPath(vector<Node>);
void Randomize(char[MAX_X][MAX_Y], float[MAX_X][MAX_Y], int, int, int, int);

int main()
{
    srand(time(0));
    bool pathsGenerated = false;
    char display[MAX_X][MAX_Y]; 
    float grid[MAX_X][MAX_Y];
     
    for(int i = 0; i < MAX_X; i++)
        for(int j = 0; j < MAX_Y; j++)
        {
            grid[i][j] = 0;
            display[i][j] = 'O';   
        }

    int startx, starty;
    int goalx, goaly;

    collectInput(startx, starty, goalx, goaly);

    Randomize(display, grid, startx, starty, goalx, goaly);    
    

    for(int i = 0; i < MAX_X; i++) 
    {
         for(int j = 0; j < MAX_Y; j++)
            printf( "[%c]", display[i][j]);
         printf("\n");
    } 
    
    Node start(startx, starty);
    Node goal(goalx, goaly);
    Node current;
    Node successors[4];
    Node next_state;
    Node path;
    vector<Node> openlist, closelist;
    
    //Push start on openlist
    grid[start.x][start.y] = 1;
    openlist.push_back(start);
    make_heap(openlist.begin(), openlist.end());
    
    while(!openlist.empty())
    {
        
        current = openlist.front();
        pop_heap(openlist.begin(), openlist.end()); 
        openlist.pop_back();      

        if(isGoal(current, goal))
        {
           closelist.push_back(goal);
            for(int i = 0; i < closelist.size(); ++i)
                    display[closelist[i].x][closelist[i].y] = 'P';
            
           printPath(closelist);
           printf("\n");
           for(int i = 0; i < MAX_X; i++)
           {
               for(int j = 0; j < MAX_Y; j++)
                 printf("[%c]", display[i][j]);
               printf("\n");  
           }
           
           exit(EXIT_SUCCESS);
            
        }
       
        generateSuccessors(pathsGenerated, current, successors, grid);
        checkSuccessors(successors, openlist, closelist, current, goal);
         
        //Add node current to close list
            if(closelist.empty())
            {
                current.visited = true;
                closelist.push_back(current);
            }
            else
            {
                if(current > closelist.back())
                {
                    closelist.pop_back();
                    closelist.push_back(current);
                }
            
                if(closelist.back() > current && isAdjacent(closelist.back(), current))
                {
                  closelist.push_back(current);
                }
           
            }
        
        pathsGenerated = false;

    }
    //Need to add failure condition
    printf("No Path could be found.\n");
    return 42;
}

bool isGoal(Node pos, Node goal)
{
    if(pos.x == goal.x && pos.y == goal.y)
        return true;
    else 
        return false;
}

bool isAdjacent(Node curr, Node next)
{
    if(abs(curr.x-next.x) <= 1 && abs(curr.y-next.y) == 0)
        return true;
    if(abs(curr.x-next.x) == 0 && abs(curr.y-next.y) <= 1)
        return true;
    else 
        return false;
}

float calculatehn(Node curr, Node goal)
{
    //Manhattan Distance Calculation for cartersian geometry
    //Wachow Research
    //Like Emeril Bam
    //Talking bout that Taxicab Geometry
    int dx = abs(curr.x - goal.x);
    int dy = abs(curr.y - goal.y);
    
    return (MAX_X*MAX_Y)*(dx+dy);

    //Note when selecting heuristic calculation make sure to pick the right scale
    //h(n) = D * (dx+dy)
}

void checkSuccessors(Node* successors, vector<Node>& openlist, vector<Node>& closelist, Node current, Node goal)
{
        //For each node_successor of node_current
        for(int i = 0; i < 4; i++)
        {
            successors[i].g = current.f+10;
            successors[i].h = calculatehn(successors[i], goal);
            successors[i].calculatefn();

            //Step 13
            for(int j = 0; j < openlist.size(); ++j)
            {
                if(successors[i] == openlist[j] && successors[i].visited)
                    if(openlist[j] >= successors[i])
                        successors[i].visited = false;
            }
            //Step 14
            for(int k = 0; k < closelist.size(); ++k)
            {
                if(successors[i] == closelist[k] && successors[i].visited)
                    if(closelist[k] >= successors[i])
                        successors[i].visited = false;
            }
            
            //Step 15
            for(int j = 0; j < openlist.size(); ++j)
            {
                if(successors[i] == openlist[j] && successors[i].visited)
                {
                   openlist.erase(openlist.begin()+j, openlist.begin()+j+1);
                }
                make_heap(openlist.begin(), openlist.end());          
            }
            make_heap(openlist.begin(), openlist.end());          

            for(int k = 0; k < closelist.size(); ++k)
            {
                if(successors[i] == closelist[k] && successors[i].visited)
                {
                    closelist.erase(closelist.begin()+k, closelist.begin()+k+1);
                }
            }//End of Step 15           
                 
                //Add node successor to the open list
                if(successors[i].visited)
                {
                    openlist.push_back(successors[i]);  
                    push_heap(openlist.begin(), openlist.end());
                }
                successors[i].visited = false;
        }
}

void collectInput(int& startx, int& starty, int& goalx, int& goaly)
{
    do
    {
    printf("Enter starting point: ");
    scanf("%d %d", &startx, &starty);         
    }while((startx >= MAX_X || startx < 0) || (starty >= MAX_Y || starty < 0));

    do
    {
    printf("Enter goal point: ");
    scanf("%d %d", &goalx, &goaly); 
    }while((goalx >= MAX_X || goalx < 0) || (goaly >= MAX_Y || goaly < 0));
}

void generateSuccessors(bool& pathsGenerated, Node current, Node* successors, float grid[MAX_X][MAX_Y])
{
        //Generate each state node_successor that can come after node_current
        if(current.y-1 >= 0)
        {
            if(grid[current.x][current.y-1] != 1)   //Check North
            {
                successors[0].x = current.x;
                successors[0].y = current.y-1;
                grid[current.x][current.y-1] = 1;
                successors[0].visited = true;
                pathsGenerated = true;
            }
        }
        if(current.y+1 < MAX_Y)
        {
            if(grid[current.x][current.y+1] != 1)   //Check South
            {
                successors[1].x = current.x;
                successors[1].y = current.y+1;
                grid[current.x][current.y+1] = 1;
                successors[1].visited = true;
                pathsGenerated = true;
            }
        }
        if(current.x-1 >= 0)
        {
            if(grid[current.x-1][current.y] != 1)  //Check West
            {
                successors[2].x = current.x-1;
                successors[2].y = current.y;
                grid[current.x-1][current.y] = 1;
                successors[2].visited = true;
                pathsGenerated = true;
            }
        }
        if(current.x+1 < MAX_X)
        {
            if(grid[current.x+1][current.y] != 1)   //Check East
            {
                successors[3].x = current.x+1;
                successors[3].y = current.y;
                grid[current.x+1][current.y] = 1;
                successors[3].visited = true;
                pathsGenerated = true;
            }
        }
}

void printPath(vector<Node> path)
{
    printf("Print Path \n\n");

    while(!path.empty())
    {
        path.front().print();
        path.erase(path.begin(), path.begin()+1);
    }
          
    //exit(EXIT_SUCCESS);
}

void Randomize(char display[MAX_X][MAX_Y], float grid[MAX_X][MAX_Y], int startx, int starty, int goalx, int goaly)
{
    int flip = 0;
    //Place random obstacles
    for(int i = 0; i < MAX_X; i++)
        for(int j = 0; j < MAX_Y; j++)
        {
            if((startx == i && starty ==j) || (goalx == i && goaly ==j))
                continue;

            flip  = rand() % 100 + 1;
            if(flip > 90)
            {
                grid[i][j] = 1;
                display[i][j] = 'X';
            }
        }
}

/***DEBUGGING NOTE:::
 *
 *
 * THE PROGRAM COMPLETES SEARCH
 * FINDS PATH 
 * SOMETIMES SKIPS NODES
 * THERE MIGHT BE A PROBLEM WITH HEURISTIC CALCULATION
 *
 *
 * CHECK HEURISTICS 
 *
 *
 */
