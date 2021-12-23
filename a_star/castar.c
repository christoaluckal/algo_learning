#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct PosData{
    int x;
    int y;
};

struct Node{
    double f;
    int g;
    double h;
    struct PosData *position;
};

struct List{
    struct Node *val;
    struct List *next;    
};


int maze[100][100]=
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

double euclidean(struct PosData *pos1,struct PosData *pos2)
{
    double dist = sqrt((pow(pos1->x-pos2->x,2)+pow(pos1->y-pos2->y,2)));
    return dist;
}

int getListLength(struct List *list)
{
    int count = 0;
    struct List *curr=list;

    while(curr!=NULL)
    {
        count++;
        curr = curr->next;
    }
    return count;
}

void printList(struct List **list){
    struct List *curr = *list;
    while(curr!=NULL)
    {
        printf("(%d,%d|%lf)-",curr->val->position->x,curr->val->position->y,curr->val->f);
        curr = curr->next;
    }
    printf("\n");
}


int isInList(struct List *list,struct Node *node)
{
    struct List *head = list;

    int count = 0;
    while(head!=NULL)
    {
        if(head->val->position->x== node->position->x && head->val->position->y == node->position->y)
        {
            return count;
        }
        else{
            count++;
        }
        head = head->next;
    }
    return -1;
}
struct List* pushToList(struct List **list,struct Node *node)
{
    struct List *head = NULL;
    head = *list;
    struct List *curr = NULL;
    curr = *list;
    struct List *new = NULL;
    new = (struct List*)malloc(sizeof(struct List));
    new->next = NULL;
    if(head==NULL)
    {
        *list = new;
        head = *list;
        head->val = node;
        head->next = NULL;
    }
    else{
        int location = 0;
        location = isInList(head,node);
        if(location==-1)
        {
            while(curr->next!=NULL)
            {
                curr = curr->next;
            }
            curr->next = new;
            curr = curr->next;
            curr->val = node;
            curr->next = NULL;
            }
        else{
            for(int i=0;i<location;i++)
            {
                curr = curr->next;
            }
        }
    }
    return head;
}


struct List *removeFromList(struct List **list,struct Node *node)
{
    struct List *head = NULL;
    head = *list;
    int location = 0;
    location = isInList(head,node);
    int listLength = getListLength(head);
    if(location>=0)
    {
        if(listLength==1)
        {
            head = NULL;
            return head;
        }
        else if (listLength==2)
        {
            if(location==1)
            {
                head = head->next;
            }
            else{
                head->next = NULL;
            }
            return head;
        }
        else{
            struct List *curr = *list;
            struct List *prev = *list;
            struct List *next = *list;
            while(location>0)
            {
                prev = curr;
                curr = curr->next;
                location--;
            }
            next = curr->next;
            if(next==NULL)
            {
                prev->next = NULL;
            }
            else
            {
                prev->next = next;
                curr = NULL;
            }
        }

    }
    return head;
}

void printMaze(int maze[100][100])
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            printf("%d",maze[i][j]);
        }
        printf("\n");
    }
}

struct Node* makechildNode(int posx,int posy,int g,double h){
    struct Node *child = (struct Node*)malloc(sizeof(struct Node));
    child->position = (struct PosData*)malloc(sizeof(struct PosData));
    child->position->x = posx;
    child->position->y = posy;
    child->g = g;
    child->h = h;
    child->f = child->g+child->h;
    return child;
}

void nullList (struct List **list)
{
    *list = NULL;
}

int main(){
    struct Node *start = NULL,*end = NULL;
    start = (struct Node*)malloc(sizeof(struct Node));
    end = (struct Node*)malloc(sizeof(struct Node));
    start->f=0,start->g=0,start->h = 0;
    struct PosData *start_val,*end_val;
    start_val = (struct PosData*)malloc(sizeof(struct PosData));
    end_val = (struct PosData*)malloc(sizeof(struct PosData));

    start_val->x = 0;
    start_val->y = 0;
    end_val->x = 7;
    end_val->y = 2;
    start->position = start_val;
    end->position = end_val;

    struct List *optimal = NULL;

    struct List *possible = NULL;

    int test_count = 0;

    possible = pushToList(&possible,start);
    while(getListLength(possible)>0)
    // for(int iteration=0;iteration<30;iteration++)
    {
        struct List *p_iter = NULL;
        struct List *min_ptr = NULL;
        p_iter = possible;
        double minimum = 9999;
        while(p_iter!=NULL)
        {
            if(p_iter->val->f < minimum)
            {
                minimum = p_iter->val->f;
                min_ptr = p_iter;
            }
            p_iter = p_iter->next;
        }
        struct Node *optnode = makechildNode(min_ptr->val->position->x,min_ptr->val->position->y,min_ptr->val->g,euclidean(min_ptr->val->position,end->position));
        printf("OPTIMAL NODE:(%d ,%d) |%lf\n",optnode->position->x,optnode->position->y,optnode->f);
        optimal = pushToList(&optimal,optnode);
        maze[optnode->position->y][optnode->position->x]=3;
        possible = removeFromList(&possible,optnode);
        printf("----------------------------------------\n");
        printMaze(maze);
        printf("----------------------------------------\n");
        nullList(&possible);
        if(min_ptr->val->position->x==end->position->x && min_ptr->val->position->y==end->position->y)
        {
            printf("ENDED\n");
            break;
        }
        int directions[8][2] = {{1,0},{-1,0},{0,-1},{0,1},{-1,-1},{1,-1},{-1,1},{1,1}};
        for(int i=0;i<8;i++)
        {
            int posx;
            int posy;
            posx = min_ptr->val->position->x+directions[i][0];
            posy = min_ptr->val->position->y+directions[i][1];
            struct PosData temp;
            temp.x = posx;
            temp.y = posy;
            struct Node* posChild = makechildNode(posx,posy,min_ptr->val->g+1,euclidean(&temp,end->position));
            if(posx >= 0 && posx < 10 && posy >=0 && posy < 10)
            {
                if(posChild->h==0 && maze[posy][posx]==1)
                {
                    printf("NOT POSSIBLE\n");
                    exit(-1);
                }
                else{
                    if(maze[posy][posx]!=1 && isInList(optimal,posChild)==-1)
                    {
                        possible = pushToList(&possible,posChild);
                    }

                }
                
            }
        }
        test_count++;      
    }
    printf("STEPS: %d\n",test_count);
    printList(&optimal);
    return 0;
}