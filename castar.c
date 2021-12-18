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
    // struct Node *parent;
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
    // printf("%p",(void *)curr);
    while(curr!=NULL)
    {
        printf("(%d,%d|%lf)-",curr->val->position->x,curr->val->position->y,curr->val->f);
        curr = curr->next;
    }
    printf("\n");
    // printf("\n");
}

struct List* pushToList(struct List **list,struct Node *node)
{
    // printf("I_LIST:%p %p %p\n",*list,list,&list);
    struct List *head = NULL;
    head = *list;
    // printf("I_HEAD:%p %p\n",head,&head);
    struct List *curr = NULL;
    curr = *list;
    // printf("I_CURR:%p %p\n",curr,&curr);

    struct List *new = NULL;
    new = (struct List*)malloc(sizeof(struct List));
    new->next = NULL;
    // printf("I_NEW:%p %p\n",new,&new);
    if(head==NULL)
    {
        *list = new;
        head = *list;
        head->val = node;
        head->next = NULL;
    }
    else{  
    while(curr->next!=NULL)
    {
        curr = curr->next;
    }
    curr->next = new;
    curr = curr->next;
    curr->val = node;
    curr->next = NULL;
    }
    // printf("I_HEAD2:%p %p\n",head,&head);

    return head;
}

struct List *removeFromList(struct List **list,struct Node *node)
{
    struct List *prev = NULL;
    struct List *curr = NULL;
    struct List *next = NULL;
    struct List *head = NULL;
    head = *list;
    prev = *list;
    curr = *list;
    next = curr->next;
    if(next==NULL)
    {
        prev = NULL;
        curr = NULL;
        next = NULL;
        return curr;
    }
    if(curr->val->position->x== node->position->x && curr->val->position->y == node->position->y)
    {
        return next;
    }
    while(curr->val->position->x!= node->position->x && curr->val->position->y != node->position->y && next!=NULL)
    {
        prev = curr;
        curr = curr->next;
        next = curr->next;
        if(next==NULL)
        {
            printf("Not present\n");
            return NULL;
        }
    }
    prev->next=next;
    return head;
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

int main(){
    struct Node *start = NULL,*end = NULL;
    start = (struct Node*)malloc(sizeof(struct Node));
    // printf("%p %p\n",start,&start);
    end = (struct Node*)malloc(sizeof(struct Node));
    start->f=0,start->g=0,start->h = 0;
    struct PosData *start_val,*end_val;
    start_val = (struct PosData*)malloc(sizeof(struct PosData));
    end_val = (struct PosData*)malloc(sizeof(struct PosData));

    start_val->x = 0;
    start_val->y = 0;
    end_val->x = 2;
    end_val->y = 3;
    start->position = start_val;
    end->position = end_val;

    struct List *optimal = NULL;

    struct List *possible = NULL;

    possible = pushToList(&possible,start);
    while(getListLength(possible)>0)
    // for(int iteration=0;iteration<2;iteration++)
    {
        printf("\n");
        // printf("SEARCHING\n");
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
        possible = removeFromList(&possible,optnode);
        printf("POSSIBLE:");
        printList(&possible);
        printf("OPTIMAL:");
        printList(&optimal);
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
            // if(posx >= 0 && posx < 10 && posy >=0 && posy < 10 && maze[posy][posx]!=1)
            if(posx >= 0 && posx < 10 && posy >=0 && posy < 10)
            {
                if(euclidean(&temp,end->position)==0 && maze[posy][posx]==1)
                {
                    printf("NOT POSSIBLE\n");
                    exit(-1);
                }
                else{
                    struct Node* posChild = makechildNode(posx,posy,min_ptr->val->g+1,euclidean(&temp,end->position));
                    possible = pushToList(&possible,posChild);
                }
                
            }
        }        
    }
    printList(&optimal);
    // printf("%p\n",(void *)possible);
    return 0;
}

    // struct List *possible = NULL;
    // // printf("START:%p %p\n",start,&start);

    // // printf("POSSIBLE 0:%p %p\n",possible,&possible);
    // possible = pushToList(&possible,start);
    // // printf("POSSIBLE 1:%p %p\n",possible,&possible);
    // // printf("%p\n",(void *)possible);
    // // printList(&possible);
    // // printf("\n\n");
    // // printf("POSSIBLE 2:%p %p\n",possible,&possible);
    // optimal = pushToList(&optimal,start);
    // // printf("%p\n",(void *)possible);
