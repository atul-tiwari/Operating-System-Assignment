#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include <stdlib.h>

char* InputFile = "Input_1.txt";

int readinput(int Line_no ,int Word_no);
void *barber_work(void *Customer);

int barber_Free = 0;

struct Cust{
    int customer_no;
    int arival_time;
    int seat_no;
    int Finshed ;
};
struct Cust* St_Pointer;

int main(){

int customer_Finshed =0;
int no_of_chairs =readinput(1,0);
int no_of_customers = readinput(1,1);
int Time = 0;

int chairs[no_of_chairs];
int Ocupied_chairs =0;

struct Cust Customer[no_of_customers];
St_Pointer = Customer;

for (int i=0; i<no_of_chairs;i++) chairs[i]=-1;

for (int i=0 ; i<no_of_customers;i++){
    Customer[i].customer_no = readinput(i+2,1);
    Customer[i].arival_time = readinput(i+2,3);
    Customer[i].seat_no =-1;
    Customer[i].Finshed = 0;
}

while (no_of_customers>customer_Finshed && Time<1000){
    for (int i=0 ;i <no_of_customers;i++){
       
        if(Customer[i].Finshed == 0 & Customer[i].arival_time == Time){
            
            if (barber_Free == 0){
                pthread_t t1;
                pthread_create(&t1,NULL,&barber_work,&Customer[i].customer_no);
                Customer[i].seat_no=-1;
                Customer[i].Finshed =1;
                customer_Finshed++;
            }
            else{
                int empty_chair=-1;
                for (int j=0; j<no_of_chairs;j++) if (chairs[j] == -1) empty_chair =j;
                if (empty_chair !=-1) {
                Customer[i].seat_no=i+1;
                chairs[i]=Customer[i].customer_no; 
                }
                else {
                    printf("Customer_leaves \n");
                    Customer[i].Finshed =1;
                    customer_Finshed++;
                }
            }
        }
        
    }
    Time++;
    printf("Check Time %d \n",Time);
}
 printf("Check point lasts \n");

return 0;
}

void *barber_work(void *Customer){
int * c_id= Customer;
printf("Customer_id %d \n",c_id);
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