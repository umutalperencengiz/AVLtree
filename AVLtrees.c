#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
struct marks
{
    int mark,level,balance_factor;
    struct marks *left,*right;

};

//insertion steps
int total_levels(struct marks* start) 
{
    if (start ==NULL)  return 0;
    else if(start->left == NULL && start->right == NULL) 
    {
        int level =1;
        return level;
    }
    else 
    {

        int left_levels = total_levels(start->left);
        int right_levels = total_levels(start->right);
        if (left_levels >= right_levels)
            return left_levels+ 1;
        else
            return right_levels+ 1;
    }
}
int balance_factor(struct marks *node)
{
    if (node == NULL) return 0;


return total_levels(node->left) - total_levels(node->right);
}
struct marks* rightRotate(struct marks *node)
{
    struct marks *node2 = node->left;    
    node->left = node2->right;
    node2->right = node;
    
 
   
    //printf("enteredR");
    node->level = total_levels(node);
    node2->level = total_levels(node2);
    node->balance_factor = balance_factor(node);
    node2->balance_factor = balance_factor(node2);
 
    //Return new start
    return node2;
}
struct marks* leftRotate(struct marks *node)
{
    struct marks *node2 = node->right;
    node->right = node2->left;
    node2->left = node;
    
 
    // Update heights
    //printf("enteredL");
    node->level = total_levels(node);
    node2->level = total_levels(node2);
    node->balance_factor = balance_factor(node);
    node2->balance_factor = balance_factor(node2);
    
    
 
    // Return new start
    return node2;
}
void insert_tree(struct marks **start,int mark)
{
    struct marks *ptr = *start;
    
    if(ptr == NULL)
    {
    ptr = (struct marks*)malloc(sizeof(struct marks));
    ptr->mark = mark;
    ptr->left = NULL;
    ptr->right = NULL;
    *start = ptr;
    }
    else 
    {
        
        if(mark < ptr->mark) 
        {
        insert_tree(&ptr->left,mark);
        }
        
        else 
        {
        
        insert_tree(&ptr->right,mark);
        }
     
    }
    ptr->level = total_levels(ptr);
    ptr->balance_factor = balance_factor(ptr); 
    //Left Left rotate
    if(ptr->balance_factor > 1 && ptr->mark > ptr->left->mark)
    {   
        ptr = rightRotate(ptr);
        *start = ptr;
    }
    //Right Right rotate
    if(ptr->balance_factor < -1 && ptr->mark < ptr->right->mark)
    {
        ptr= leftRotate(ptr);
        *start = ptr;
    }
    //Right Left Rotate
    if (ptr->balance_factor > 1 && ptr->mark > ptr->left->mark) {
        ptr->left = leftRotate(ptr->left);
        ptr = rightRotate(ptr);
        *start = ptr;
    }
    //Left Right Rotate
      if (ptr->balance_factor < -1 && ptr->mark < ptr->left->mark) {
        ptr->right = rightRotate(ptr->right);
        ptr = leftRotate(ptr);
        *start = ptr;
    }
    


}


// printing parents
void print_parentL(struct marks *start,int level) 
{
  struct marks *ptr ;
  ptr = start ;
  if(ptr ==NULL) ;
  else if(level==0) ; 
  else
  {

    if(ptr->left &&level ==1) 
    {
        printf("(%d L) ",ptr->mark);
    }
 }
}
void print_parentR(struct marks *start,int level) 
{
  struct marks *ptr ;
  ptr = start ;
  if(ptr ==NULL) ;
  else if(level==0 ) ;  
  else
  {

    if(ptr->right && level == 1) 
    {
        printf("(%d R) ",ptr->mark);
    }
 }
}


// sorting algorithm I wrote
void sortMarks(struct marks *start)
{
    struct marks *ptr ;
    ptr = start ;
    if(ptr == NULL);
    else
    {
    sortMarks(ptr->left);
    
        if(ptr->left == NULL || ptr->mark > ptr->left->mark ) // or statement is essential when I dont use the output happened quite different 
        {
            printf("%d \n",ptr->mark);
            
            //printf("%d %d\n",ptr->left->studentID,ptr->left->grade);
           }
        
        else if(ptr->right ==NULL || ptr->mark < ptr->right->mark) 
        {
            
            //printf("%d %d\n",ptr->right->studentID,ptr->right->grade);
            
            printf("%d \n",ptr->mark);
            
        }
    sortMarks(ptr->right);
    }
}
// for level order printing

void print_level(struct marks* start, int level) 
{
    struct marks*ptr = start;


    
    if (ptr == NULL) return;  // if you dont use return it would go else statement then some results wont be shown in terminal
    if (level == 0) 
    {
        printf("%d ",ptr->mark);
        
        
    }
    
    else
    {
        
        print_level(ptr->left, level-1);
        print_parentL(ptr,level);
        if(level==1 && ptr->left)
        printf("(%d B) ",ptr->left->balance_factor);
        print_level(ptr->right, level-1);
        print_parentR(ptr,level);
        if(level==1 && ptr->right)
        printf("(%d B) ",ptr->right->balance_factor);
    }
    
}
void print_AVLtree_level_order(struct marks* start) {
    if (start ==NULL) return;
    int levels = total_levels(start);
    for (int i=0; i<levels; i++) {
        print_level(start, i);
        if(i ==0) printf("(%d B)",start->balance_factor);
        printf("\n");
    }
   
}



int main()
{
    struct marks* start = NULL;
    int mark;
    scanf("%d",&mark);
    while(mark != -1)
    {
        
        insert_tree(&start,mark); 
        scanf("%d",&mark);
    }
    sortMarks(start);

    puts("");
    
    print_AVLtree_level_order(start);
}