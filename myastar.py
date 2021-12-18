maze = [[0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0],
       [0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0],
       [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
       [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
       [0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
       [0,0,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0],
       [0,0,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0],
       [0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0],
       [0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1],
       [0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1],
       [0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1],
       [0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,0],
       [0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,0],
       [0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,1,0],
       [0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,1,0],
       [0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1]]

solution = [[0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0],
       [0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0],
       [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
       [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
       [0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
       [0,0,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0],
       [0,0,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0],
       [0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0],
       [0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1],
       [0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1],
       [0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1],
       [0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,0],
       [0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,0],
       [0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,1,0],
       [0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,1,0],
       [0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1]]

import math
import time

def euclidean(pos1,pos2):
    dist = math.sqrt((pos1[0]-pos2[0])**2+(pos1[1]-pos2[1])**2)
    return dist


class Node:
    def __init__(self,parent=None,position=None) -> None:
        self.parent = parent
        self.position = position
        self.g = 0
        self.h = 0
        self.f =0

    def __eq__(self, test) -> bool:
        return self.position == test.position

    def __repr__(self) -> str:
        return "@{}|{}|{}@".format(self.parent,self.position,self.f)





def get_children(maze,current):
    maze_width = len(maze[0])
    maze_height = len(maze)

    left = (-1,0)
    right = (1,0)
    up = (0,-1)
    down = (0,1)
    up_left = (-1,-1)
    up_right = (1,-1)
    bot_left = (-1,1)
    bot_right = (1,1)

    # directions = [left,right,up,down,up_left,up_right,bot_left,bot_right]
    directions = [left,right,up,down]

    child_list = []
    for x in range(len(directions)):
        newposx = current.position[0]+directions[x][0]
        newposy = current.position[1]+directions[x][1]
        if (newposx >= 0 and newposx < maze_width) and (newposy >= 0 and newposy < maze_height):
            child_list.append((newposx,newposy))

    return child_list

    
def astar(maze,start,end):
    startnode = Node(None,start)
    startnode.f = 0
    endnode = Node(None,end)
    visited = []
    optimal = []

    visited.append(startnode)
    while len(visited)>0:
        currentnode = visited[0]
        min = currentnode.f
        for x in range(0,len(visited)):
            if visited[x].f < min:
                currentnode = visited[x]
                min = currentnode.f
        optimal.append(currentnode)
        visited = []
        currentnode = optimal[-1]
        if currentnode == endnode:
            for x in optimal:
                print(x.position,x.f)
                posx,posy = x.position
                solution[posy][posx]=3
            break
        else:
            children = get_children(maze,currentnode)
            for child in children:
                child_posx,child_posy = child[0],child[1]
                if maze[child_posy][child_posx]==1:
                    continue
                child_node = Node(currentnode,child)
                if child_node not in visited and child_node not in optimal:
                    child_node.g = currentnode.g +1
                    child_node.h = euclidean(child_node.position,endnode.position)
                    child_node.f = child_node.g+child_node.h
                    visited.append(child_node)


start = (2,15)
end = (13,1)

astar(maze,start,end)

for x in solution:
    print(x)