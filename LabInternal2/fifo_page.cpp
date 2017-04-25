#include<iostream>
using namespace std;

int main (){
    int n, r, pageFaults = 0, nextToReplace = 0;

    cout << "Enter the number of page frames\n";
    cin >> n;

    int frames[n];
    for(int i = 0; i < n; i++){
            frames[i] = -1;
    }

    cout << "Enter the number of page requests\n";
    cin >> r;

    cout << "Enter the page requests\n";
    for ( int i = 0; i < r; i++){
        int request;
        cin >> request;
        int flag = 0;

        cout << request << ": ";

        for(int j = 0; j < n; j++){
            if(frames[j] == request){
                flag = 1;
                for(int k = 0; k < n; k++)
                    cout << frames[k] << " ";
                cout << endl;
            }
        }

        if(flag) continue;

        pageFaults++;
        frames[nextToReplace] = request;
        nextToReplace = (nextToReplace + 1 )% n;

        for(int k = 0; k < n; k++)
            cout << frames[k] << " ";
        cout << endl;

    }
    cout <<"Number of Page Faults: " << pageFaults << endl;

}
