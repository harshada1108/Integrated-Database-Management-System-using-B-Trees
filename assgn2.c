#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 200
#define order 4
typedef struct BNode
{
    void **pointers;
    char **keys;
    struct BNode *parent;
    bool is_leaf;
    int num_keys;
    struct BNode *next;
} BNode;
typedef struct PanNode
{
    char p_name[SIZE];
    char p_address[SIZE];
    char PanNo[SIZE];
    char p_adhar[SIZE];
    // struct PanNode *p_next;
    struct BankAccount *bankAccount;
} PanNode;

typedef struct AadharNode
{
    char a_name[SIZE];
    char a_address[SIZE];
    char AadharNo[SIZE];
    BNode *pannode;
} AadharNode;

typedef union NodeUnion
{
    AadharNode *aadharNode;
    PanNode *panNode;
} NodeUnion;

typedef struct record
{
    NodeUnion node;
    enum
    {
        AADHAR,
        PAN
    } tag;
} record;
typedef struct QueueNode {
    BNode *bnode;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
} Queue;


AadharNode *CreateAdharNode(char name[], char address[], char aadharno[]);
BNode *InitializeList();
BNode *CreateBNode(record *r, bool isleaf, char key[]);
BNode *SplitLeafNode(BNode *root, char keyval[], record *r);
BNode *InsertInParent(BNode *Parent, BNode *siblingNode, BNode *lptr, char key[]);
BNode *SplitParent(BNode *Parent, BNode *siblingNode, BNode *rootnode, char key[]);
BNode *Insert(BNode *root, char key[], record *r);
void Display(BNode *root);
PanNode *createPanNode(char name[], char address[], char panNo[], char Adharno[]);
 record* FindDataNode(char key[] , BNode* root);
void InitializePanList(BNode *root);
void FirstQuestion(BNode *root);
Queue *createQueue();
BNode *dequeue(Queue *queue);
void levelOrderTraversal(BNode *root);
void enqueue(Queue *queue, BNode *bnode);
 void PrintTree(BNode* root);
void SecondQuestion(BNode* root);

int main()
{
    BNode *root = NULL;
    root = InitializeList();
    InitializePanList(root);
    Display(root);
    levelOrderTraversal(root);
    //PrintTree(root);
    printf("First question \n");
    FirstQuestion(root);
    SecondQuestion(root);
}
int StringCompare(char s1[], char s2[], int n)
{
    printf("%s \n", s1);
    printf("%s \n", s2);

    int flag = 0;
    for (int i = 0; i < n; i++)
    {
        if (s1[i] != s2[i])
        {
            flag = 1;
            break;
        }
    }
    return flag;
}
AadharNode *CreateAdharNode(char n[], char address[], char aadharno[])
{
    AadharNode *newNode = (AadharNode *)malloc(sizeof(AadharNode));
    strcpy(newNode->a_name, n);
    strcpy(newNode->a_address, address);
    strcpy(newNode->AadharNo, aadharno);
    newNode->pannode = NULL;
    return newNode;
}
PanNode *createPanNode(char name[], char address[], char panNo[], char Adharno[])
{
    PanNode *newNode = (PanNode *)malloc(sizeof(PanNode));

    strcpy(newNode->PanNo, panNo);

    strcpy(newNode->p_name, name);
    strcpy(newNode->p_address, address);
    strcpy(newNode->p_adhar, Adharno);

    newNode->bankAccount = NULL;

    return newNode;
}
void InitializePanList(BNode *root)
{

    FILE *fp;
    fp = fopen("PANList2.csv", "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    char line[SIZE];
    fgets(line, SIZE, fp);
    BNode *lptr = NULL;

    PanNode *pnode;
    record *r = NULL;
    BNode *Root = NULL;

    while (fgets(line, SIZE, fp) != NULL)
    {
        // lptr = root ;
        char name[SIZE];
        char address[SIZE];
        char aadharNo[SIZE], panNo[SIZE];

        sscanf(line, "%[^,],%[^,],%[^,],%[^,]", name, address, aadharNo ,panNo);
        pnode = createPanNode(name, address, panNo, aadharNo);
        record *rec = (record *)malloc(sizeof(record));
        rec->node.panNode = pnode;

        rec->tag = PAN;
        char keyval[SIZE];
        strcpy(keyval, aadharNo);

        // printf("%s\n",rec->node.panNode->p_adhar);
        // printf("%d \n",strlen(keyval));
        
        Root = root;
       // r = FindDataNode(aadharNo ,Root);
      //  printf("%s\n",r->node.aadharNode->a_name);
       
       while (Root->is_leaf == false) {
       
        int i = Root->num_keys - 1;
        while (i >= 0 && strcmp(Root->keys[i], aadharNo) > 0) {
            i--;
        }
        i++;
        Root = Root->pointers[i];
    }
     printf("Root pointers %s\n",Root->keys[0]);
    int i = 0;
    int flag = 0;
    while(i<=Root->num_keys && flag == 0)
    {
        printf("Hello...");
        if(strcmp(Root->keys[i], aadharNo) == 0)
        {
            printf("%s  %s %d %d \n",aadharNo,Root->keys[i],strlen(aadharNo),strlen(Root->keys[i]));
            flag = 1 ;
        }
        else
        {
            i++;
        }
    }
     lptr = ((record*)Root->pointers[i])->node.aadharNode->pannode ;
     lptr =Insert(lptr,panNo,rec);
     ((record*)Root->pointers[i])->node.aadharNode->pannode = lptr;

    // if(r!=NULL)
    // {
    //     r =  Root->pointers[i];
    // }
     
    //  printf("%s\n",r->node.aadharNode->a_name);

        // while (Root->is_leaf == false)
        // {
        //     Root = Root->pointers[0];
        // }
        // int k = 0;
        // int ans;
        // int flag = 0;
        // while (Root != NULL && flag == 0)
        // {

        //     for (int i = 0; i < Root->num_keys; i++)
        //     {
        //         if (strcmp(Root->keys[i], aadharNo) == 0)
        //         {
        //             ans = i;
        //            // printf("%s pan %s \n", Root->keys[i], aadharNo);
        //             lptr = ((record *)Root->pointers[i])->node.aadharNode->pannode;
        //             lptr = Insert(lptr, panNo, rec);
        //             ((record *)Root->pointers[i])->node.aadharNode->pannode = lptr;
        //             break;
        //             flag = 1;
        //         }
        //     }
        //     if (flag == 0)
        //     {
        //         Root = Root->next;
        //     }
        // }
        // printf("%s pan %s \n",Root->keys[ans],aadharNo);
    }

    fclose(fp);
}

BNode *InitializeList()
{

    FILE *fp;
    fp = fopen("AadharList2.csv", "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    char line[SIZE];

    fgets(line, SIZE, fp);

    AadharNode *aadhar = NULL;
    BNode *root = NULL;

    while (fgets(line, SIZE, fp) != NULL)
    {
        char name[SIZE], address[SIZE], aadharNo[SIZE];
        sscanf(line, "%[^,],%[^,],%[^,]", aadharNo, name, address);
        aadhar = CreateAdharNode(name, address, aadharNo);
        record *rec = (record *)malloc(sizeof(record));
        rec->node.aadharNode = aadhar;

        rec->tag = AADHAR;

        // check .. it is working uptill here
        root = Insert(root, aadharNo, rec);
    }

    fclose(fp);

    return root;
}
void Display(BNode *root)
{

    BNode *Root = root;
    while (Root->is_leaf == false)
    {
        Root = Root->pointers[0];
    }
    int k = 0;
    while (Root != NULL)
    {
        for (int i = 0; i < Root->num_keys; i++)
        {
            printf("%s %d\n", ((record *)(Root->pointers[i]))->node.aadharNode->AadharNo ,strlen(Root->keys[i]));
            if ((((record *)(Root->pointers[i]))->node.aadharNode->pannode != NULL))
            {
                printf("Yes bnode are created  for %s\n", Root->keys[i]);
            }
        }
        printf("(%d)End one root..........;....................................................\n", ++k);
        Root = Root->next;
    }
}

record* FindDataNode(char key[], BNode* root) {
    BNode* lptr = root;
    record* r = NULL; // Initialize r to NULL

    while (lptr->is_leaf == false) {
        int i = lptr->num_keys - 1;
        while (i >= 0 && strcmp(lptr->keys[i], key) > 0) {
            i--;
        }
        i++;
        lptr = lptr->pointers[i];
    }

    int i = 0;
    while ((i < lptr->num_keys) && strcmp(lptr->keys[i], key) != 0) {
        i++;
    }

     r = lptr->pointers[i];

    return r;
}

BNode *CreateBNode(record *r, bool isleaf, char key[])
{
    BNode *newNode = (BNode *)malloc(sizeof(BNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    // Initialize pointers
    newNode->pointers = (void **)malloc(sizeof(void *) * (order + 1));
    if (newNode->pointers == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    for (int i = 0; i < order; i++)
    {
        newNode->pointers[i] = NULL;
    }

    // Initialize keys
    newNode->keys = (char **)malloc(sizeof(char *) * (order));
    if (newNode->keys == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    for (int i = 0; i < order; i++)
    {
        newNode->keys[i] = (char *)malloc(sizeof(char) * SIZE); // Allocate memory for each key
        if (newNode->keys[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            exit(1);
        }
        if (i == 0 && key != NULL)
        {
            strcpy(newNode->keys[i], key);
        }
    }

    newNode->parent = NULL;
    newNode->is_leaf = isleaf;
    newNode->num_keys = 0;
    newNode->next = NULL;

    // Set record pointer
    if (r != NULL)
    {
        newNode->pointers[0] = r;
    }

    return newNode;
}

BNode *SplitLeafNode(BNode *root, char keyval[], record *r)
{
    // printf("In splitnode %s\n ",keyval);
    BNode *siblingNode = CreateBNode(NULL, true, NULL);
    if (root->num_keys == order - 1)
    {
        // insert and then split

        int i = root->num_keys - 1;
        while (i >= 0 && strcmp(root->keys[i], keyval) > 0)
        {
            strcpy(root->keys[i + 1], root->keys[i]);

            root->pointers[i + 1] = root->pointers[i];

            i--;
        }

        strcpy(root->keys[i + 1], keyval);
        root->pointers[i + 1] = r;
        root->num_keys++;

        // now splitting
        int k = 0;
        for (int j = order / 2; j < root->num_keys; j++)
        {
            strcpy(siblingNode->keys[k], root->keys[j]);

            siblingNode->pointers[k] = root->pointers[j];
            k++;
        }
        for (int i = order / 2; i < root->num_keys; i++)
        {

            siblingNode->pointers[i] = NULL;
        }
        root->num_keys = order / 2;
        if (order % 2 == 0)
        {
            siblingNode->num_keys = order / 2;
        }
        else
        {
            siblingNode->num_keys = order / 2 + 1;
        }
        // connection
        BNode *dptr;

        dptr = root->next;
        root->next = siblingNode;
        siblingNode->next = dptr;
    }
    return siblingNode;
}

BNode *InsertInParent(BNode *Parent, BNode *lptr, BNode *siblingNode, char keyval[])
{

    if (Parent->num_keys < order - 1)
    {
        int i = Parent->num_keys - 1;
        while (i >= 0 && strcmp(Parent->keys[i], keyval) > 0)
        {
            strcpy(Parent->keys[i + 1] ,Parent->keys[i]);
            
            Parent->pointers[i + 2] = Parent->pointers[i + 1];
            i--;
        }
         
        strcpy(Parent->keys[i + 1], keyval);
        Parent->pointers[i + 1] = lptr;
        Parent->pointers[i + 2] = siblingNode;
        Parent->num_keys++;
        for(int i = 0 ; i<Parent->num_keys ;i++)
        {
            printf("In sert parent %s \n",Parent->keys[i]);
        }
    }

    return Parent;
}

BNode *SplitParent(BNode *Parent, BNode *siblingNode, BNode *rootnode, char key[])
{
    BNode *ans;
    if (Parent->num_keys == order - 1)
    {
        int i = Parent->num_keys - 1;
        while (i >= 0 && strcmp(Parent->keys[i], key) > 0)
        {
            strcpy(Parent->keys[i + 1] , Parent->keys[i]);
            
            Parent->pointers[i + 2] = Parent->pointers[i + 1];
            i--;
        }

        strcpy(Parent->keys[i + 1], key);
        Parent->pointers[i + 1] = rootnode;
        Parent->pointers[i + 2] = siblingNode;
    }
    Parent->num_keys++;
    for(int i = 0 ; i<Parent->num_keys ;i++)
    {
        printf("Of parent %s\n",Parent->keys[i]);
    }
    BNode *newsibling = CreateBNode(NULL, false, NULL);
    int k = 0;
    for (int i = (order/2) + 1; i < order; i++)
    {
        strcpy(newsibling->keys[k], Parent->keys[i]);

        newsibling->pointers[k] = Parent->pointers[i];
        ((BNode*)newsibling->pointers[k])->parent = newsibling;
        k++;
    }
    
    newsibling->pointers[k] = Parent->pointers[Parent->num_keys];
    // now remove the keyval
    char newkeyval[SIZE];
    strcpy(newkeyval,Parent->keys[order / 2] );
    
    for (int i = order / 2 + 1; i < order; i++)
    {
        Parent->pointers[i] = NULL;
    }
    Parent->num_keys = Parent->num_keys - k - 1;
    newsibling->num_keys = k;
    for(int i = 0 ; i<newsibling->num_keys ; i++)
    {
        printf("newsibling %s\n",newsibling->keys[i]);
    }
    BNode *grandparent = (BNode *)Parent->parent;
    if (Parent->parent == NULL)
    {
        grandparent = CreateBNode(NULL, false, NULL);
        strcpy(grandparent->keys[0], newkeyval);
         printf("Grandparent %s..\n", grandparent->keys[0]);
        grandparent->pointers[0] = Parent;
        grandparent->pointers[1] = newsibling;
        grandparent->num_keys++;
        ans = grandparent;
        Parent->parent = grandparent;
        siblingNode->parent = grandparent;
    }
    else if (grandparent->num_keys < order - 1)
    {
         printf("Grandparent %s ,%s..\n", grandparent->keys[0],newkeyval);
        ans = InsertInParent(grandparent, Parent, newsibling, newkeyval);
        if (grandparent->parent != NULL)
        {
            while (grandparent->parent != NULL)
            {
                grandparent = grandparent->parent;
            }
            ans = grandparent;
        }
    }
    else
    {
        ans = SplitParent(grandparent, Parent, newsibling, newkeyval);
        if (grandparent->parent != NULL)
        {
            while (grandparent->parent != NULL)
            {
                grandparent = grandparent->parent;
            }
            ans = grandparent;
        }
    }

    return ans;
}

BNode *Insert(BNode *root, char key[], record *r)
{

    // case 1 : tree is null
    if (root == NULL)
    {
        root = CreateBNode(r, true, key);
        root->num_keys++;
    }
    else
    {
        char keyval[SIZE]; // got the key val
        if (r != NULL)
        {
            if (r->tag == AADHAR)
            {

                strcpy(keyval, r->node.aadharNode->AadharNo);
            }
            if (r->tag == PAN)
            {

                strcpy(keyval, r->node.panNode->PanNo);
            }
        }

        // case 2 : tree is at root , data node
        if (root->is_leaf == true)
        {

            // if node is not full
            if (root->num_keys < order - 1)
            {

                int i = root->num_keys - 1;
                while (i >= 0 && strcmp(root->keys[i], keyval) > 0)
                {

                    strcpy(root->keys[i + 1], root->keys[i]);

                    root->pointers[i + 1] = root->pointers[i];

                    i--;
                }

                strcpy(root->keys[i + 1], keyval);

                root->pointers[i + 1] = r;

                root->num_keys++;

                // its working uptill here
            }
            else
            {

                // node is full
                if (root->num_keys == order - 1)
                {

                    // insert and then split
                    BNode *siblingNode = CreateBNode(NULL, true, NULL);
                    BNode *parenT = CreateBNode(NULL, false, NULL);
                    int i = root->num_keys - 1;
                    while (i >= 0 && strcmp(root->keys[i], keyval) > 0)
                    {
                        strcpy(root->keys[i + 1], root->keys[i]);

                        root->pointers[i + 1] = root->pointers[i];

                        i--;
                    }
                    strcpy(root->keys[i + 1], keyval);

                    root->pointers[i + 1] = r;
                    root->num_keys++;

                    // now splitting
                    int k = 0;
                    for (int j = order / 2; j < root->num_keys; j++)
                    {
                        strcpy(siblingNode->keys[k], root->keys[j]);

                        siblingNode->pointers[k] = root->pointers[j];
                        k++;
                    }
                    siblingNode->num_keys = k;
                    for (int i = order / 2; i < root->num_keys; i++)
                    {
                        // root->keys[i] = NULL;
                        root->pointers[i] = NULL;
                    }
                    root->num_keys = order / 2;
                    if (order % 2 == 0)
                    {
                        siblingNode->num_keys = order / 2;
                    }
                    else
                    {
                        siblingNode->num_keys = order / 2 + 1;
                    }

                    // connection
                    BNode *dptr;

                    dptr = root->next;
                    root->next = siblingNode;
                    siblingNode->next = dptr;

                    // now parent
                    strcpy(parenT->keys[0], siblingNode->keys[0]);
                    parenT->num_keys++;

                    parenT->pointers[0] = root;
                    parenT->pointers[1] = siblingNode;
                    root->parent = parenT;
                    siblingNode->parent = (BNode *)parenT;
                    root = parenT;
                    // its working uptill here
                }
            }
        }
        else
        {

            // if it is not at root and root is not full // search uptill root
            BNode *lptr = (BNode *)root;
            // printf("%s\n",lptr->keys[0]);

            while (lptr->is_leaf == false)
            {
                //  printf("internal %s\n",lptr->keys[0]);
                int i = lptr->num_keys - 1;

                while (i >= 0 && strcmp(lptr->keys[i], keyval) > 0)
                {
                    i--;
                }
                i++;
                lptr = lptr->pointers[i];
            }
            // printf("Rootnode==%s\n",lptr->keys[0]);

            // now i got the leaf node
            //  cases : leaf node is full . leaf node is not full
            if (lptr->num_keys < order - 1)
            {

                int i = lptr->num_keys - 1;
                while (i >= 0 && strcmp(lptr->keys[i], keyval) > 0)
                {
                    // strcpy(lptr->keys[i+1],'\0');
                    strcpy(lptr->keys[i + 1], lptr->keys[i]);
                    // printf("Hello i am ");
                    lptr->pointers[i + 1] = lptr->pointers[i];
                    i--;
                }

                strcpy(lptr->keys[i + 1], keyval);

                lptr->pointers[i + 1] = r;
                lptr->num_keys++;
                // this is working
            }
            else
            {

                // now is the main part
                BNode *siblingNode = SplitLeafNode(lptr, keyval, r);
                // printf("%s \n",siblingNode->keys[0]);
                siblingNode->parent = lptr->parent;
                BNode *Parent = (BNode *)lptr->parent;
                // only insert
                if (Parent->num_keys < order - 1)
                {
                    int i = Parent->num_keys - 1;
                    while (i >= 0 && strcmp(Parent->keys[i], siblingNode->keys[0]) > 0)
                    {
                        strcpy(Parent->keys[i + 1], Parent->keys[i]);

                        Parent->pointers[i + 2] = Parent->pointers[i + 1];
                        i--;
                    }

                    strcpy(Parent->keys[i + 1], siblingNode->keys[0]);

                    Parent->pointers[i + 1] = (BNode *)lptr;
                    Parent->pointers[i + 2] = (BNode *)siblingNode;
                    Parent->num_keys++;
                }
                // if parent is full  , split parent
                else
                {
                    if (Parent->num_keys == order - 1)
                    {
                        
                        for(int i = 0 ; i<Parent->num_keys ; i++)
                        {printf("PArentsss %s\n",Parent->keys[i]);

                        }
                        printf("keyval is %s\n",keyval);
                        root = SplitParent(Parent, siblingNode, lptr, siblingNode->keys[0]);
                    }
                }
            }
        }
    }
    return root;
}
void FirstQuestion(BNode* root)
{
    
    BNode *Root = root;
    while (Root->is_leaf == false)
    {
        Root = Root->pointers[0];
    }
    int k = 0;
    while (Root != NULL)
    {
        for (int i = 0; i < Root->num_keys; i++)
        {
           
            if ((((record *)(Root->pointers[i]))->node.aadharNode->pannode == NULL))
            {
                printf("%s\n ", ((record *)(Root->pointers[i]))->node.aadharNode->a_name);
                printf("%s\n ", ((record *)(Root->pointers[i]))->node.aadharNode->a_address);
                printf("%s\n\n", ((record *)(Root->pointers[i]))->node.aadharNode->AadharNo);
            }
        }
        
        Root = Root->next;
    }

}
void SecondQuestion(BNode* root)
{
     BNode *Root = root;
    while (Root->is_leaf == false)
    {
        Root = Root->pointers[0];
    }
    int k = 0;
    while (Root != NULL)
    {
        for (int i = 0; i < Root->num_keys; i++)
        {
           
            if ((((record *)(Root->pointers[i]))->node.aadharNode->pannode!= NULL))
            {
              BNode* panroot =((record *)(Root->pointers[i]))->node.aadharNode->pannode;
              while(panroot->is_leaf == false)
              {
                 panroot = panroot->pointers[0];
              }
              
                BNode* temp = panroot ;
                int sum = 0;
                while(temp!=NULL)
                {
                    sum = sum + temp->num_keys;
                    temp = temp->next;
                }
              if(sum>1)
              {
                printf("Name :%s \n",((record*)panroot->pointers[0])->node.panNode->p_name);
                printf("Address :%s \n",((record*)panroot->pointers[0])->node.panNode->p_address);
                printf("AadharNo :%s \n",((record*)panroot->pointers[0])->node.panNode->p_adhar);
                while(panroot!=NULL)
                {
                   for(int i = 0 ; i<panroot->num_keys ; i++)
                   {
                    printf("%s \n",panroot->keys[i]);
                   }
                   panroot = panroot->next;
                }

              }

            }
        }
        
        Root = Root->next;
    }
}



Queue *createQueue() {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(Queue *queue, BNode *bnode) {
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->bnode = bnode;
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}
BNode *dequeue(Queue *queue) {
    if (queue->front == NULL) {
        return NULL;
    }
    QueueNode *temp = queue->front;
    BNode *bnode = temp->bnode;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return bnode;
}

void levelOrderTraversal(BNode *root) {
    if (root == NULL) {
        return;
    }
    Queue *queue = createQueue();
    enqueue(queue, root);

    while (queue->front != NULL) {
        BNode *current = dequeue(queue);
        for (int i = 0; i < current->num_keys; i++) {
            printf("%s ", current->keys[i]);
        }
        printf("\n");

        if (!current->is_leaf) {
            for (int i = 0; i <= current->num_keys; i++) {
                if (current->pointers[i] != NULL) {
                    enqueue(queue, (BNode *)current->pointers[i]);
                }
            }
        }
    }
    free(queue);
}
void PrintTree(BNode* root)
{
    BNode* lptr = root ;
    
    for(int i = 0 ; i<lptr->num_keys ; i++)
    {
        printf("%s ",lptr->keys[i]);
    }
    printf("..........\n");
    int flag = 0 ;
    int i = 0;
    while(flag = 0)
    {
    if(lptr->is_leaf != false)
    {
       PrintTree(lptr->pointers[i++]);
    }
    else
    {
        flag =1 ;
    }
    }
    


}