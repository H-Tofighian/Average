#include <cmath>
#include <stdlib.h>
#include <iostream>
using namespace std;
#include <fstream>
ifstream infile("data.dat");
int main ()
{
double x, y, z, Q;

int nZ;
int nTheta;
int nR;
cout << "Enter nZ : ";
cin>>nZ;
cout << "Enter nTheta : ";
cin>>nTheta;
cout << "Enter nR : ";
cin>>nR;

double **arr;
arr = new double*[nR];
for (int i = 1 ; i <= nR ; i++)
{
	arr[i - 1] = new double[nTheta];
}
double *Ri;
Ri = new double[nR];

int indexRT=0;
int indexR=0;
int indexTheta=0;

fstream output_file ("out.dat",ios::out);
if(!output_file)
{
	cerr<<"File can not open."<<endl;
	exit(1);
}

string Vname;
cout << "Enter variable name : ";
cin>>Vname;

string Zname;
cout << "Enter Zone name : ";
cin>>Zname;

output_file<<"VARIABLES = \"X\" \"Y\" \"Z\" \""<<Vname<<"\""<<endl;
output_file<<"ZONE T=\""<<Zname<<"\""<<endl;
output_file<<"I="<<nR<<", J="<<nZ<<", K=1, ZONETYPE=Ordered"<<endl;
output_file<<"DATAPACKING=POINT"<<endl;

while (infile >> x >> y >> z >> Q)
{
	arr [indexR][indexTheta] = Q;
	if (indexTheta ==0)
	{
		Ri [indexR] = sqrt(x*x+y*y);
	}
	indexR++;
	if (indexR == nR)
	{
		indexR=0;
		indexTheta++;
	}
	indexRT++;
	if (indexRT == (nR*nTheta))
	{
		indexRT =0;
		indexTheta =0;
		
		 for (int i=1; i <= nR ; i++)
		 {
			double sumMean = 0;
			for (int j=1; j <= nTheta; j++)
			{
				sumMean += arr [i-1][j-1];
			}
			sumMean = sumMean/nTheta;
			output_file<<Ri [i-1]<<"	"<<z<<"	0	"<<sumMean<<endl;
		}
	}
}
return 0;
}
