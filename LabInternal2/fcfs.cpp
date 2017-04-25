#include<iostream>
#include<cstdlib>

using namespace std;

struct process {
    int pno;
    int arrival;
    int burst;
    int start;
    int finish;
    int wait;
    int turnaround;
};

static int cmp_arrival(const void* p1, const void* p2){
    process* a = (process* )p1;
    process* b = (process* )p2;

    if (a->arrival < b->arrival)return -1;
    else if (a->arrival == b->arrival)return 0;
    else return 1;
}

void display (process* q, int n ){
    int avg_wait = 0, avg_turn = 0;
    cout<<"Process"<<"\t"<<"Arrival"<<"\t"<<"Burst"<<"\t"<<"Start"<<"\t"<<"Finish"<<"\t"<<"Wait"<<"\t"<<"Turnaround"<<endl;
    for(int i = 0; i < n; i++){
        cout<<q[i].pno<<"\t"<<q[i].arrival<<"\t"<<q[i].burst<<"\t"<<q[i].start<<"\t"<<q[i].finish<<"\t"<<q[i].wait<<"\t"<<q[i].turnaround<<endl;
        avg_wait += q[i].wait;
        avg_turn += q[i].turnaround;
    }
    cout << "Average Waiting Time: " << avg_wait/(float)n << endl;
    cout << "Average Turnaround Time: " << avg_turn/(float)n << endl;
}

void calc_times( process* q, int n){
    int current = 0;
    for(int i = 0; i < n; i++){
        current = (q[i].arrival > current ? q[i].arrival : current);
        q[i].start = current;
        q[i].wait = current - q[i].arrival;
        q[i].turnaround = q[i].wait + q[i].burst;
        current += q[i].burst;
        q[i].finish = current;
    }
}

int main(){

    int n;
    cout << "Enter the number of processes\n";
    cin >> n;
    process q[n];

    cout << "Enter arrival and burst time of each process\n";
    for (int i = 0; i < n; i++){
        q[i].pno = i+1;
        cin >> q[i].arrival >> q[i].burst;
        q[i].wait = q[i].turnaround = 0;
    }

    qsort(q, n, sizeof(process), cmp_arrival);
    calc_times(q, n);

    cout << "FCFS order\n";
    display(q, n);
    return 0;
}
