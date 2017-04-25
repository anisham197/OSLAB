#include<iostream>
#include<cstdlib>

#define MAX_BURST 1000

using namespace std;

struct process {
    int pno;
    int arrival;
    int burst;
    int start;
    int finish;
    int wait;
    int turnaround;
    int scheduled;
};

static int cmp_arrival(const void* p1, const void* p2){
    process* a = (process* )p1;
    process* b = (process* )p2;
    if(a->arrival < b->arrival)return -1;
    else if (a->arrival == b->arrival)return 0;
    else return 1;
}

void display (process* q, int n ){

    float avgwait = 0,avgturn = 0;
    cout<<"Process\tArrival\tBurst\tStart\tFinish\tWaiting\tTurnaround"<< endl;
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<q[i].pno<<"\t"<<q[i].arrival<<"\t"<<q[i].burst<<"\t"<<q[i].start<<"\t"<<q[i].finish<<"\t"<<q[i].wait<<"\t"<<q[i].turnaround<<endl;
        avgwait += q[i].wait;
        avgturn += q[i].turnaround;
    }
    cout<<"Average waiting time: "<<avgwait/(float)n<<endl;
    cout<<"Average turnaround time: "<<avgturn/(float)n<<endl;
}

void calc_times(process* q, int n){
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

process getMinBurst( process* q, int n, int arrival, int burst){
    int min = -1;
    for(int i = 0; i < n; i++){
        if(q[i].scheduled == 0 && q[i].arrival <= arrival && q[i].burst < burst ){
            min = i;
            burst = q[i].burst;
        }
    }
    q[min].scheduled = 1;
    return q[min];
}

process* schedule (process* q, int n){
    process* order = new process[n];
    int current = q[0].arrival;

    for (int i = 0; i < n; i++){
        order[i] = getMinBurst(q, n, current, MAX_BURST);
        current += order[i].burst;
    }
    return order;
}

int main () {
    int n;
    cout << "Enter the number of processes\n";
    cin >> n;
    process q[n];

    cout << "Enter arrival and burst of each process\n";
    for (int i = 0; i < n; i++){
        q[i].pno = i+1;
        q[i].scheduled = 0;
        cin >> q[i].arrival >> q[i].burst;
    }

    qsort(q, n, sizeof(process), cmp_arrival);

    process* order = schedule(q, n);
    calc_times(order, n);

    cout <<"Priority Order\n";
    display(order, n);
    return 0;
}
