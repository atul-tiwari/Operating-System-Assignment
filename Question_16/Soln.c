#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>

int readinput(int Line_no,int Word_no);

void Swap_struct(int *arr,int length);
void Sort_struct();
void Min_arr_at(int *,int );

char* InputFile = "Input_1.txt";
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
};

struct Process * P_ref;

int main(){

    int No_of_processes =readinput(1,0);
    struct Process P_info[No_of_processes];
    int Process_Queue[No_of_processes];
     

    for (int i=0 ;i<No_of_processes;i++){
        P_info[i].Pid = readinput(i+2,1);
        P_info[i].Arival_Time = readinput(i+2,2);
        P_info[i].Bust_Time = P_info[i].Remaning_Time = readinput(i+2,3);
    }
    P_ref = P_info;
    


    Sort_struct(No_of_processes);
    
    int count =0;
    while(Completed_process<No_of_processes){
        for (int i =0 ,count =0; i< No_of_processes ; i++){
            if ((int)P_info[i].Arival_Time <= (int)Time && (int)P_info[i].Remaning_Time > 0){
                int Cputime = P_info[i].Remaning_Time;
                if (Cputime <=10){
                    Time+= Cputime;
                    Completed_process ++;
                    P_info[i].Completion_Time = Time;
                    P_info[i].Remaning_Time = -1;
                    printf("P%dc\t",P_info[i].Pid);
                    count =1;;
                }
                else {
                    P_info[i].Remaning_Time -= 10;
                    printf("P%dr\t",P_info[i].Pid);
                    Time+=10-1;
                }
                Sort_struct(No_of_processes);
                i = No_of_processes;
            }
            count++;
        }
        if(count < 1  ) Time++;
    }

    for (int i =0; i< No_of_processes ; i++){
        P_info[i].Turnaround_Time = P_info[i].Completion_Time - P_info[i].Arival_Time;
        P_info[i].Wating_time = P_info[i].Turnaround_Time - P_info[i].Bust_Time;
    }
    printf("\n\nPid | Arival_Time | Bust_Time | Wating_time  | Turnaround_Time\n0");
    for(int i=0;i<No_of_processes;i++) {
        printf("%d \t %d \t\t%d\t\t%d \t\t%d \t" ,P_info[i].Pid, 
                                                              P_ref[i].Arival_Time,
                                                              P_ref[i].Bust_Time,
                                                              P_ref[i].Wating_time,
                                                              P_ref[i].Turnaround_Time);
        printf("\n");
    }
        printf("\n\nP1r = process 1 running \n");
        printf("P1c = process 1 complete \n");                                                              
    
    return 0;
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

void Sort_struct(int length){
    
    for(int i=0;i<length-1;i++){
        
        int min = i;
        for (int j=i;j<length;j++){
            if(P_ref[min].Remaning_Time >P_ref[j].Remaning_Time && P_ref[j].Remaning_Time >0){
                struct Process temp = P_ref[min];
                P_ref[min]=P_ref[j];
                P_ref[j]= temp;               
            }
        }
    }
    
}