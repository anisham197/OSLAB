#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

struct process{
	int no, arrival, burst, remaining, finish, waiting, turnaround;
};

process *q;
int n;
int quantum;

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
      cout<<"\t@"<<gantt[i].time;
  cout<<endl;
}

void display()
{
  int avgw = 0,avgt = 0;
	cout<<"\nProcess\tArrival\tBurst\tFinish\tWaiting\tTurnaround\n";
	for(int i = 0;i < n; i++)
	{
      q[i].waiting = q[i].finish - q[i].arrival - q[i].burst;
      q[i].turnaround = q[i].finish - q[i].arrival;

      cout<<"P"<<q[i].no+1<<"\t"<<q[i].arrival<<"\t"<<q[i].burst;
      cout<<"\t"<<q[i].finish<<"\t"<<q[i].waiting<<"\t"<<q[i].turnaround << endl;

      avgt += q[i].turnaround;
      avgw += q[i].waiting;
	}
  cout<<"Average waiting time: "<<avgw/(float)n<<endl;
	cout<<"Average turnaround time: "<<avgt/(float)n<<endl;
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
	cout << "Enter arrival and burst times of each process:\n";
	for(int i = 0;i < n; i++)
	{
  		q[i].no = i;
  		cin >> q[i].arrival >> q[i].burst;
      q[i].remaining = q[i].burst;
	}

  cout << "Enter quantum:\n";
  cin >> quantum;

	//sort based on arrival
	qsort(q, n, sizeof(process), cmp_arrival);

	int current = q[0].arrival;
  int count = 0;

  for( int i = 0; isRemaining(); i = (i+1)%n )
  {
      if(q[i].arrival <= current && q[i].remaining > 0)
      {
          count = 0;
          //add to gantt chart
          order g;
          g.pno = q[i].no;
          g.time = current;
          gantt.push_back(g);
          g_count++;

          current = current + ( ( q[i].remaining >= quantum) ? quantum : q[i].remaining );
          q[i].remaining = ( q[i].remaining >= quantum) ? q[i].remaining - quantum : 0;

          if(q[i].remaining == 0)
          {
              q[i].finish = current;
          }
      }
      else
      {
          count++;
      }
      if( count == n )
      {
          // To handle gaps
          for(int j = 0;j < n; j++)
          {
              if(q[j].arrival > current)
              {
                  current = q[j].arrival;
                  break;
              }
          }
          count = 0;
      }
  }
  printGantt();
  display();
  return 0;
}
