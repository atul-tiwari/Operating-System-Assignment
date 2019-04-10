#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>

int readinput(int Line_no,int Word_no);
void Calculate_Queue(int No_of_processes,int time_instance );
void  QueueSort(int arr[], int n) ;
void swap(int *xp, int *yp) ;

int create_Queue();

char* InputFile = "Input_1.txt";
int* Queue_pointer;
int Completed_process = 0;
int Time=0;

struct Process
{
    int Pid;
    int Arival_Time;
    int Bust_Time;
    int Remaning_Time;
    int Turnaround_Time;
    int Completion_Time;
    int Wating_time ;
    int turn;
};

struct Process * P_ref;

int main(){

    int No_of_processes =readinput(1,0);
    struct Process P_info[No_of_processes];
    int Process_Queue[No_of_processes];
    Queue_pointer = Process_Queue;
    

    for (int i=0 ;i<No_of_processes;i++){
        P_info[i].Pid = readinput(i+2,1);
        P_info[i].Arival_Time = readinput(i+2,2);
        P_info[i].Bust_Time = P_info[i].Remaning_Time = readinput(i+2,3);
        P_info[i].turn = -1;
    }
    P_ref = P_info;
    
    create_Queue(No_of_processes);
    /*
    while (Completed_process<No_of_processes){
        x:
        Calculate_Queue(No_of_processes,Time);
    }

    */
    return 0;
}

void Calculate_Queue(int No_of_processes,int time_instance ){
    int processes_to_schedule[No_of_processes];
    
    for (int i=0 ;i<No_of_processes;i++){
        processes_to_schedule[i] = (P_ref[i].Arival_Time <= time_instance && P_ref[i].Remaning_Time>0)? P_ref[i].Pid:-1; 
    }
    
    QueueSort(processes_to_schedule,No_of_processes);
    int count=0;
    for (int i =0 ;i <No_of_processes;i++){
            count=0;
            if (Queue_pointer[i] != -1){
                count++;
                int Cputime = P_ref[Queue_pointer[i]-1].Remaning_Time;
                 
                if (Cputime>10){
                    P_ref[Queue_pointer[i]-1].Remaning_Time-=10;
                    Time+=10;
                     printf("Checkpoint  %d %d %d\n",Cputime,P_ref[Queue_pointer[i]-1].Pid,Time);
                }
                else{
                    P_ref[Queue_pointer[i]-1].Remaning_Time=0;
                    Time+=Cputime;
                    P_ref[Queue_pointer[i]-1].Completion_Time = Time;
                    Completed_process++;
                   
                    printf("%d is complited at %d \n",P_ref[Queue_pointer[i]-1].Pid,P_ref[Queue_pointer[i]-1].Completion_Time);
                
                }
               
            }
            
        }
        if(count == 0) Time++;
    

   
   
}

void QueueSort(int arr[], int n) 
{ 
    int i, j, min_idx; 
  
    for (i = 0; i < n-1; i++) 
    { 
        
        min_idx = i; 
        for (j = i+1; j < n; j++) 
        if(arr[j]>=0)
          if (P_ref[arr[j]-1].Remaning_Time < P_ref[arr[min_idx]-1].Remaning_Time) 
            min_idx = j; 
  
        swap(&arr[min_idx], &arr[i]); 
    } 
    
    Queue_pointer = arr;
} 

void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

int readinput(int Line_no,int Word_no){
    char Temp_buffer[100];
    FILE *fptr;
    int ret_val ;

    if ((fptr = fopen(InputFile, "r")) == NULL)
    {
        printf("Error! opening Input file NOT FOUND");
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

int create_Queue(int No_of_processes){

    int Runtime_queue[No_of_processes];
    int current = 0;

    while(current<No_of_processes){
        int min[No_of_processes];
        min[0] = P_ref[current].Arival_Time;
        for (int i = 1 ;i <No_of_processes;i++){
            if (P_ref[min[0]].Arival_Time>P_ref[i].Arival_Time){
                min[0] = P_ref[i].Arival_Time;
            }
        }
        
        int count = 1 ;
        for (int i = 1 ;i <No_of_processes;i++){
            if (P_ref[min[0]].Arival_Time==P_ref[i].Arival_Time){
                min[count]=P_ref[i].Arival_Time;
                count++;
            }
        }
        printf("%d \n",count);
        for (int i = 0 ;i <count;i++) printf("%d \t",min[i]);
        for (int i = 0;i <count-1;i++){
            int min_arival = i;
             for (int j = 1;j <count;j++){
                 if(P_ref[min[i]].Arival_Time>P_ref[min[j]].Arival_Time){
                     int temp = min[i];
                     min[i] = min[j];
                     min[j] = temp;
                 }
            }
            current++;
        }
        for (int i = 0;i <count-1;i++){
            Runtime_queue[i] = min[i];
        }
        current++;
    }
    //for (int i = 1 ;i <No_of_processes;i++) printf("%d \t",Runtime_queue[i]);
    return 0;
}

