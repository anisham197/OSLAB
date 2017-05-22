#include <iostream>
#include <cstdlib>

using namespace std;

struct process{
	int no, arrival, burst, start, finish, waiting, turnaround;
};

process *q;
int n;

static int cmp_arrival(const void *p1, const void *p2)
{
   process *a = (process *) p1;
   process *b = (process *) p2;
   if(a->arrival < b->arrival) return -1;
   else if(a->arrival == b->arrival) return 0;
   else return 1;
}

void printGantt()
{
    cout << "Gantt Chart:\n";
    for(int i = 0; i < n; i++)
        cout<<"\tP"<<q[i].no+1;
    cout << endl;
    for(int i = 0;i < n; i++)
        cout<<"\t@"<<q[i].start;
    cout << endl;
}

void display()
{
    float avgwait = 0, avgturn = 0;
  	cout<<"Process\tArrival\tBurst\tStart\tFinish\tWaiting\tTurnaround\n";
  	for(int i=0;i<n;i++)
  	{
  		cout<<"P"<<q[i].no+1<<"\t"<<q[i].arrival<<"\t"<<q[i].burst<<"\t";
			cout<<q[i].start<<"\t"<<q[i].finish<<"\t"<<q[i].waiting<<"\t"<<q[i].turnaround<<endl;

  		avgwait += q[i].waiting;
  		avgturn += q[i].turnaround;
  	}

  	cout<<"Average waiting time: "<< avgwait/(float)n << endl;
  	cout<<"Average turnaround time: "<< avgturn/(float)n << endl;
}

int main()
{
  cout << "Enter the number of processes\n";
  cin >> n;
  q = new process[n];

  cout << "Enter arrival and burst time of each process\n";
  for (int i = 0; i < n; i++){
      q[i].no = i;
      cin >> q[i].arrival >> q[i].burst;
      q[i].waiting = q[i].turnaround = 0;
  }

  qsort(q, n, sizeof(process), cmp_arrival);

	int current = 0;
	for(int i = 0; i < n; i++)
	{
		current = (q[i].arrival > current ? q[i].arrival : current);
		//waiting times
    q[i].start = current;
    q[i].finish = q[i].start + q[i].burst;
		q[i].waiting = current-q[i].arrival;
		q[i].turnaround = q[i].waiting + q[i].burst;
    current += q[i].burst;
	}

	printGantt();
	display();
	return 0;

}
