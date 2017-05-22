#include <iostream>
#include <cstdlib>
#include <vector>
#define MAX 9999
using namespace std;

struct process{
	int no, arrival, burst, priority, remaining, finish, waiting, turnaround;
};

process *q;
int n;

struct order{
    int pno, time;
};

vector<order> gantt;
int g_count = 0;

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
    cout<<"\nGantt Chart:\n";
    for(int i = 0;i < g_count; i++)
        cout <<"\tP"<< gantt[i].pno+1;
    cout<<endl;
    for(int i=0;i<g_count;i++)
        cout<<"\t@"<< gantt[i].time;
    cout<<endl;
}

void display()
{
	int avgw = 0,avgt = 0;
	cout<<"\nProcess\tArrival\tBurst\tPrty\tFinish\tWaiting\tTurnaround\n";
	for(int i = 0;i < n; i++)
	{
      q[i].waiting = q[i].finish - q[i].arrival - q[i].burst;
      q[i].turnaround = q[i].finish - q[i].arrival;

      cout<<"P"<<q[i].no+1<<"\t"<<q[i].arrival<<"\t"<<q[i].burst<<"\t"<<q[i].priority;
      cout<<"\t"<<q[i].finish<<"\t"<<q[i].waiting<<"\t"<<q[i].turnaround << endl;

      avgt += q[i].turnaround;
      avgw += q[i].waiting;
	}
  cout<<"Average waiting time: "<<avgw/(float)n<<endl;
	cout<<"Average turnaround time: "<<avgt/(float)n<<endl;
}

process* getMinPriority (int current)
{
    int min_prior = MAX, index = -1;
    for(int i = 0; i < n; i++)
    {
        if(q[i].priority < min_prior && q[i].arrival <= current && q[i].remaining > 0)
        {
            min_prior = q[i].priority;
            index = i;
        }
    }
    if( index == -1) return NULL;
    return &q[index];
}

bool isRemaining()
{
    for(int i = 0; i < n; i++)
        if(q[i].remaining > 0)
            return true;

    return false;
}

int main()
{
  cout << "Enter number of processes:\n";
	cin >> n;
	q = new process[n];
	cout << "Enter arrival and burst times and priority of each process:\n";
	for(int i = 0;i < n; i++)
	{
  		q[i].no = i;
  		cin >> q[i].arrival >> q[i].burst >> q[i].priority;
      q[i].remaining = q[i].burst;
	}
	//sort based on arrival
	qsort(q, n, sizeof(process), cmp_arrival);

	int current = q[0].arrival;
  process *p = NULL;
  while( isRemaining() )
  {
      p = getMinPriority( current );
      if( p != NULL)
      {
          p->remaining--;   // non preem: decrement by burst
          if(p->remaining == 0)
          {
              p->finish = current + 1; // non preem: increment by burst
          }
          if(g_count == 0 || ( gantt[g_count-1].pno != p->no ))
          {
              order g;
              g.pno = p->no;
              g.time = current;
              gantt.push_back(g);
              g_count++;
          }
      }
      current++; // non preem: increment by burst
  }
  printGantt();
  display();
  return 0;
}
