#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include <stdlib.h>

char* InputFile = "Input_1.txt";

int readinput(int Line_no ,int Word_no);
void *barber_work();

int barber_Free = 0;
int Ocupied_chairs =0;
int *wating_qu;
int lock = 0;

struct Cust{
    int customer_no;
    int arival_time;
};
struct Cust* St_pointer;

int main(){

int customer_Finshed =0;
int no_of_chairs =readinput(1,0);
int no_of_customers = readinput(1,1);
int Time = 0;

int Wating_queue[no_of_customers];
int enque_pointer=0;
wating_qu = Wating_queue;

struct Cust Customer[no_of_customers];

for (int i=0; i<no_of_customers;i++) Wating_queue[i]=-1;

for (int i=0 ; i<no_of_customers;i++){
    Customer[i].customer_no = readinput(i+2,1);
    Customer[i].arival_time = readinput(i+2,3);
}

St_pointer = Customer;

pthread_t thread;
pthread_create(&thread,NULL,&barber_work,NULL);



while (no_of_customers>customer_Finshed && Time<1000){
    for (int i=0 ;i <no_of_customers;i++){
       
        if(Customer[i].arival_time == Time){
            if (Ocupied_chairs < no_of_chairs){
                Wating_queue[enque_pointer] = i;
                customer_Finshed++;
                Ocupied_chairs++;
                enque_pointer++;
                printf("Customer Enter %d \n ",Customer[i].customer_no);
                printf("ROCO :- %d\n ",Ocupied_chairs);
            }
            else {
                printf("Customer leave \n ");
                customer_Finshed++;
            }
        }
        }
    sleep(1); 
    Time++;
}
while(1){
    int temp = 0;
    for (int i=0; i<no_of_customers;i++) if( Wating_queue[i]!=-1) temp++;
    if(!temp) break;
}
lock = 1;
pthread_join(thread,NULL);
return 0;
}

void *barber_work(){
printf("Started at time %d\n",0);
int barber_sleeping =0; 
int deque_pointer=0;
while(!lock){
    
if (wating_qu[deque_pointer] != -1){
    barber_sleeping=0;
    
    sleep(4);
    printf("%d\n",St_pointer[wating_qu[deque_pointer]].customer_no);
    wating_qu[deque_pointer] =-1;
    deque_pointer++;
    Ocupied_chairs--;
    printf("%d WQ\n",deque_pointer);
}
else
{
    if(!barber_sleeping){
    printf("barber started sleeping \n");
    barber_sleeping = 1;
    }
}
}
printf("End \n");
}

int readinput(int Line_no,int Word_no){
    char Temp_buffer[100];
    FILE *fptr;
    int ret_val ;

    if ((fptr = fopen(InputFile, "r")) == NULL)
    {
        printf("Error! opening Input file");
        exit(1);         
    }

    while(Line_no!=0){
        fgets(Temp_buffer, 100, fptr);
        Line_no--;
    }
    
    char *token = strtok(Temp_buffer, " ");

   while( Word_no !=0) {
    token = strtok(NULL, " ");
    Word_no--;
   }
   ret_val = atoi(token);
   return ret_val;
}