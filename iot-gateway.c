typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

 #define TCP 1
 #define UDP 2
 #define HTTP 3

 #define INUSE 1
 #define NOUSE 0

typedef struct gateway_opr
{
    u8 ID;/* data */
    u8 flag;
    int sockfd;
    u8 *send_buffer;
    u32 (*Init)(struct gateway_opr_t* pdata);
    int (*sendfunction)(struct gateway_opr_t *pdata,void *send_buffer)
}gateway_opr_t;
typedef gateway_opr_t* gateway_opr_pt;



typedef struct gateway_node
{
    void *data;
    struct gateway_node * prev;
    struct gateway_node * next;/* data */
}gateway_node_t;
typedef gateway_node_t* gateway_node_pt;


typedef struct gateway_list
{
    u32 size;/* data */
    gateway_node_pt head;
    gateway_node_pt tail;
}gateway_list_t;
typedef gateway_list_t* gateway_list_pt;

int gateway_manage_create(gateway_list_pt * list)
{
    (*list)=(gateway_list_pt)malloc(sizeof(gateway_list_t));
    if((*list)==NULL)
    {   
        perror("malloc error!\n");
        return -1;
    }
    (*list)->size=0;
    (*list)->head=(gateway_node_pt)malloc(sizeof(gateway_node_t));
    if((*list)->head==NULL)
    {
        perror("malloc error!\n");
        return -1;
    }
    (*list)->head->next=(*list)->head->prev=NULL;
    (*list)->head->data=NULL;
    (*list)->tail=(*list)->head;
    return 0;
}
int gateway_insert_before(gateway_list_pt* list,int num,void *new_node_data)
{
    u32 counter=1;
    gateway_node_pt current=NULL;
    gateway_node_pt new_node=NULL;
    if((*list)==NULL||list==NULL)
    {
        perror("Invaile argment!\n");
        return -1;
    }
    if((*list)->size!=0)
    {
        new_node=(gateway_node_pt)malloc(sizeof(gateway_node_t));
        if(new_node==NULL)
        {
            perror("malloc error!\n");
            return -1;
        }
        new_node->data=new_node_data;
        new_node->prev=new_node->next=NULL;
        if(num>0&&num<(*list)->size)
        {
            current=(*list)->head;
            while(counter<num)
            {
                counter++;
                current=current->next;
            }
            if(counter==1)
            {
                (*list)->head->prev=new_node;
                new_node->next=(*list)->head;
                (*list)->head=new_node;
                (*list)->size++;
            }
        }
        else
        {
            free(new_node);/* code */
            new_node=NULL;
            return -1;
        }
        

    }
    else
    {
        if(num!=0)/* code */
        {
            perror("Invaile argment!\n");
            return -1;
        }
        (*list)->head->data=new_node_data;
        (*list)->size++;
        return 0;
    }
     
}


