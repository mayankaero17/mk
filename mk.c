#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Airport Simulation
** Author: Giancarlo M. Guerra
** Date: 19/02/2015
**
** Procedure: This simulation has two runways: one for landings and another for takeoffs. 
**            Two separate queues, built with linked lists, are used to represent these runways. 
**            Airplanes are randomly generated by the add_plane function, and are removed
**            from queues by the pop_plane function. 
**
** Assumptions:
** 
**              The concept of time shall be abstracted by "steps". This simulation will run in 120 steps. 
**              Neither queue can contain more than 10 planes for more than one step. 
**              Landings are given priority over takeoffs. 
**
*/

#define MAXSIZE 100



typedef struct airplane{

    int ID;
    struct airplane *next;

} airplane_t;


/*used to count the number of elements in a given linked list(queue)*/

int count(airplane_t *head){

    int i = 0;
    airplane_t *current = head->next;

    while(current->next != NULL){

        i++;
        current = current->next;

    }

    return i;
}

/*prints the contents of each element stored in the queue at a given time*/

void print_list(airplane_t *head){

    airplane_t *current = head;

    while(current != NULL){

        printf("%d\n",current->ID);
        current = current->next;
    }
}


/* Also called enqueue, adds a plane to the end of the queue */
void add_plane(airplane_t *head, int value){



    airplane_t *current = head;

    while(current->next != NULL){

        current=current->next;
    }

    current->next = malloc(sizeof(airplane_t));
    current->next->ID = value;
    current->next->next = NULL;
}



/* Also called dequeue, pops an element from the front of the queue */
int pop_plane(airplane_t **head){

    int retval = -1; /*in case of error or empty list*/
    airplane_t *next_plane = NULL;

    if(*head == NULL){

        return -1;
    }

    next_plane = (*head)->next;
    retval = (*head)->ID;
    free(*head);
    *head = next_plane;

    return retval;
}




int main(){



    /*counter for both the amount of takeoffs and landings for every given simulation of 120 steps*/
    int takeoff = 0;
    int landing = 0;

    

    
    /*Setup both queues*/
    airplane_t *takeoff_queue = malloc(sizeof(airplane_t));
    takeoff_queue->ID = rand() % 50;

    airplane_t *landing_queue = malloc(sizeof(airplane_t));
    landing_queue->ID = rand() % 50;


    /*initial population of each queue starts here
     * Airplane numbers are assigned a random number from 0 to 49
    */
    srand(time(NULL));
    int r = rand() % 50;

    int i = 0;

    for(i=0;i<(rand() % 10) + 1;i++){
   
        add_plane(landing_queue, r);
        r = rand() % 50;
    }

    
    for(i=0;i<(rand() % 10) + 1;i++){

        add_plane(takeoff_queue, r);
        r = rand() % 50;
    }

    /*and ends here*/

    int a = count(landing_queue);
    int b = count(takeoff_queue);
    int c = 0;


   
    int active = 1;



    puts("Please press enter to start");

    char INIT = getchar();

    while(INIT == '\n' && c < 121){

        int i = 0;
    

        printf("The time is %i\n",c);
        printf("There are %i planes waiting to land\n", a);
        printf("There are %i planes waiting to take off\n", b);

        

        if(landing_queue != NULL && takeoff_queue == NULL){

            int val = pop_plane(&landing_queue);
            printf("Plane #%i is cleared to land\n",val);

            a = count(landing_queue);
            b = count(takeoff_queue);

            landing++;

            if(count(landing_queue) < 10){

                /*This condition checks that only 0-3 planes can be added to a queue each step */
                for(i=0;i<rand() % 4;i++){

                    add_plane(landing_queue, rand() % 50);
                 }
            }
            if(count(takeoff_queue) < 10){

                for(i=0;i<rand() % 4;i++){

                    add_plane(takeoff_queue, rand() % 50);
                }


            }
            
        }

        if((landing_queue == NULL || count(landing_queue) == 0) && takeoff_queue != NULL){

            int val = pop_plane(&takeoff_queue);
            printf("Plane #%i is cleared for takeoff\n",val);

            a = count(landing_queue);
            b = count(takeoff_queue);

            takeoff++;

            printf("Number of landings: %i\n",landing);
            printf("Number of takeoffs: %i\n", takeoff);
            
            puts("Contents of takeoff_queue: ");
            print_list(takeoff_queue);

            if(count(landing_queue) < 10){


                for(i=0;i<rand() % 4;i++){

                    add_plane(landing_queue, rand() % 50);
                 }
            }
            if(count(takeoff_queue) < 10){

                for(i=0;i<rand() % 4;i++){

                    add_plane(takeoff_queue, rand() % 50);
                }


            }


        }

            
            
        

        if(landing_queue != NULL && takeoff_queue != NULL){

            int random = rand() % 11;

            if(random <= 5){
            
                int val = pop_plane(&landing_queue);
                printf("Plane #%i is clared to land\n",val);

                a = count(landing_queue);
                b = count(takeoff_queue);

                landing++;

                printf("Number of landings: %i\n",landing);
                printf("Number of takeoffs: %i\n", takeoff);
                
                puts("Contents of landing_queue: ");
                print_list(landing_queue);
            }

            else if(random > 5){

                

                int val = pop_plane(&takeoff_queue);
                printf("Plane #%i is clared for takeoff\n",val);

                a = count(landing_queue);
                b = count(takeoff_queue);

                takeoff++;

                printf("Number of landings: %i\n",landing);
                printf("Number of takeoffs: %i\n", takeoff);
               
                
                puts("Contents of takeoff_queue: ");
                print_list(takeoff_queue);

                
                

            }

            if(count(landing_queue) < 10){


                for(i=0;i<rand() % 4;i++){

                    add_plane(landing_queue, rand() % 50);
                 }
            }
            if(count(takeoff_queue) < 10){

                for(i=0;i<rand() % 4;i++){

                    add_plane(takeoff_queue, rand() % 50);
                }


            }
        }





        c++;
        INIT = getchar();

    }

    printf("At simulation's end, there were still %i airplanes waiting to land\n", count(landing_queue));
    printf("At simulation's end, there were still %i airplanes waiting to take off\n", count(takeoff_queue));

    
    
    


    

     
}
