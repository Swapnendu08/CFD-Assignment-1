#include<bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
    //initiatialization of parameters ,variaters and 2D vector arrays.
    int m,n;
    cin>>m>>n;
    int length;
    cin>>length;
    vector<vector<double>> theta(n,vector<double>(m,0)); //all values are initially 0;
    double dx=length/double(m-1);
    double dy=length/double(n-1);
    double Er=0.00000001;
    double E=10;
    double Tl,Th,delTh;
    cin>>Tl;
    cin>>delTh;
    Th=Tl+delTh;
    double heat_gen_Q;
    double heat_cond_K;
    cin>>heat_gen_Q>>heat_cond_K;
    double alpha=(heat_cond_K*(Th-Tl))/(heat_gen_Q*m*m);

    //Boundary Conditions
    //BC1
    for (int j = 0; j < n; j++)
    {
        theta[j][0]=alpha;
    }
    //BC2
    for (int j = 0; j < n; j++)
    {
        theta[j][m-1]=0.00;
    }
    //BC3
    for (int i = 0; i< m; i++)
    {
        theta[0][i]=0.00;
    }
    //BC4
    for (int i = 0; i< m; i++)
    {
        theta[n-1][i]=0.00;
    }

    //handling the corner points;
    theta[0][0]=alpha/2;
    theta[n-1][0]=alpha/2;

    //calculation part
    vector<vector<double>>Theta_new(n,vector<double>(m,0));
    Theta_new=theta;
    while(E>Er){
        // cout<<"hello"<<endl;
        for(int i=1;i<m-1;i++){
            for(int j=1;j<n-1;j++){
                Theta_new[i][j]=0.25*((dx*dx)+Theta_new[i-1][j]+Theta_new[i][j-1]+Theta_new[i][j+1]+Theta_new[i+1][j]);
            }
        }
        //error calculation
        double sum=0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                sum += pow((Theta_new[i][j] - theta[i][j]), 2);
            }
        }
        E=sqrt(sum/((n-1)+(m-1)));
        cout<<"value of E--->"<<E<<endl;
        //final=initial for next iteration
        theta=Theta_new;
    }

    cout<<endl<<endl;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cout<<i<<"-->"<<j<<"-->"<<theta[i][j]<<endl;
        }
    }
    
    //calculation for Temp value at x=0.5L
    double Tval;
    double sum=0.00;
    for (int j = 0; j < n; j++)
    {
       double temp=Tl+((heat_gen_Q*length*length*theta[m/2][j])/heat_cond_K);
        sum+=temp*dy;
    }
    Tval=sum;
    cout<<"The average Temperature at value X=0.5L is "<<Tval<<" degree";
    return 0;
}
