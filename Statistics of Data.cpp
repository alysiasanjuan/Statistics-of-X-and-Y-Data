#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

vector <double> datavecX;
vector <double> datavecY;

double pushToVectorX (string fileName) //open file and push its content into vector x
{
  double data;
  ifstream f;
  f.clear();
  f.open(fileName.c_str());
  f.seekg(0);
  if (f.fail())
  {
    cout << "File couldn't be opened." << endl;
  }
  else
  {
    datavecX.clear();
    loop:
    while(!f.eof())
    {
      if (f >> data)
      {
        datavecX.push_back(data);
      }
    }
  }
  f.close();
}

double pushToVectorY (string fileName) //open file and push its content into vector x
{
  double data;
  ifstream f;
  f.clear();
  f.open(fileName.c_str());
  f.seekg(0);
  if (f.fail())
  {
    cout << "File couldn't be opened." << endl;
  }
  else
  {
    loop:
      while(!f.eof())
      {
        if (f >> data)
        {
          datavecY.push_back(data);
        }
      }
  }
  f.close();
}

double pushToVectorXandY (string fileName) //open file and push its content into vector x and vector y (with x and y values alternating)
{
  double dataX, dataY;
  ifstream f;
  f.clear();
  f.open(fileName.c_str());
  f.seekg(0);
  if (f.fail())
  {
    cout << "File couldn't be opened." << endl;
  }
  else
  {
    datavecX.clear();
    datavecY.clear();
    loop:
      while (!f.eof())
      {
        f>>dataX>>dataY;
        datavecX.push_back(dataX);
        datavecY.push_back(dataY);
      }
  }
  f.close();
}

double meanX () //compute for the mean of x
{
  double sum = std::accumulate(datavecX.begin(), datavecX.end(), 0.0);
  double meanX = sum / datavecX.size();
  cout << "Mean of x: " << meanX << endl;
  return meanX;
}

double meanY () //compute for the mean of y
{
  double sum = std::accumulate(datavecY.begin(), datavecY.end(), 0.0);
  double meanY = sum / datavecY.size();
  cout << "Mean of y: " << meanY << endl;
  return meanY;
}

void statsX () //compute and display statistics on the vector x
{
  sort(datavecX.begin(), datavecX.end());
  if(datavecX.size() % 2 != 0)
  {
    int middle = ((datavecX.size() + 1) / 2) - 1;
    cout << "Median of x: " << datavecX[middle] << endl;
  }
  else
  {
  cout << "Median of x: "<< (datavecX[(datavecX.size()/2)-1] +
  datavecX[datavecX.size()/2]) / 2 << endl;
  }
  double minNum = 10000, maxNum = 0;
  for(int i = 0; i < datavecX.size(); ++i)
  {
  if (datavecX[i] < minNum)
    {
      minNum = datavecX[i];
    }
  if (datavecX[i] > maxNum)
    {
      maxNum = datavecX[i];
    }
  }
  cout << "Minimum of x: " << minNum << endl << "Maximum of x: " <<
  maxNum << endl;
  double sumSquared = 0, sumThenSquared = 0, variance = 0;
  for(int i = 0; i < datavecX.size(); ++i)
  {
    sumSquared = sumSquared + datavecX[i] * datavecX[i];
  }
  for(int i = 0; i < datavecX.size(); ++i)
  {
    sumThenSquared = datavecX[i] + sumThenSquared;
  }
  sumThenSquared = sumThenSquared * sumThenSquared;
  variance = (datavecX.size() * sumSquared - sumThenSquared) /
  (datavecX.size() * (datavecX.size() - 1));
  cout << "Variance of x: " << variance << endl;
}

void statsY () //compute and display statistics on the vector y
{
  sort(datavecY.begin(), datavecY.end());
  if(datavecY.size() % 2 != 0)
  {
    int middle = ((datavecY.size() + 1) / 2) - 1;
    cout << "Median of y: " << datavecY[middle] << endl;
  }
  else
  {
    cout << "Median of y: "<< (datavecY[(datavecY.size()/2)-1] +
    datavecY[datavecY.size()/2]) / 2 << endl;
  }
  double minNum = 10000, maxNum = 0;
  for(int i = 0; i < datavecY.size(); ++i)
  {
    if (datavecY[i] < minNum)
    {
      minNum = datavecY[i];
    }
    if (datavecY[i] > maxNum)
    {
      maxNum = datavecY[i];
    }
  }
  cout << "Minimum of y: " << minNum << endl << "Maximum of y: " <<
  maxNum << endl;
  double sumSquared = 0, sumThenSquared = 0, variance = 0;
  for(int i = 0; i < datavecY.size(); ++i)
  {
    sumSquared = sumSquared + datavecY[i] * datavecY[i];
  }
  for(int i = 0; i < datavecY.size(); ++i)
  {
    sumThenSquared = datavecY[i] + sumThenSquared;
  }
  sumThenSquared = sumThenSquared * sumThenSquared;
  variance = (datavecY.size() * sumSquared - sumThenSquared) /
  (datavecY.size() * (datavecY.size() - 1));
  cout << "Variance of y: " << variance << endl;
}

double lineFit(double &a, double &b, double y_fit[])
{
  double xsum=0,x2sum=0,ysum=0,xysum=0;
  for (int i=0;i<datavecX.size();i++)
  {
    xsum=xsum+datavecX[i];
    ysum=ysum+datavecY[i];
    x2sum=x2sum+pow(datavecX[i],2);
    xysum=xysum+datavecX[i]*datavecY[i];
  }
  a=(datavecX.size() * xysum - xsum * ysum) / (datavecX.size() *
  x2sum - xsum * xsum);
  b=(x2sum * ysum - xsum * xysum) / (x2sum * datavecX.size() -
  xsum * xsum);
  y_fit[datavecX.size()]; //array to store the new fitted values of y
  for (int i=0;i<datavecX.size();i++)
  {
    y_fit[i]=a*datavecX[i]+b;
  }
}

double correlationCoefficient()
{
  int sum_X = 0, sum_Y = 0, sum_XY = 0, squareSum_X = 0,
  squareSum_Y = 0;
  for (int i = 0; i < datavecX.size(); i++)
  {
    sum_X = sum_X + datavecX[i];
    sum_Y = sum_Y + datavecY[i];
    sum_XY = sum_XY + datavecX[i] * datavecY[i];
    squareSum_X = squareSum_X + datavecX[i] * datavecX[i];
    squareSum_Y = squareSum_Y + datavecY[i] * datavecY[i];
  }
  double corr = (double)(datavecX.size() * sum_XY - sum_X * sum_Y)
  / (sqrt((datavecX.size() * squareSum_X - sum_X * sum_X)
  * (datavecY.size() * squareSum_Y - sum_Y * sum_Y)));
  return corr;
}

int main()
{
  string fileName;
  int options = 0;
  bool repeat = true;
  while (repeat == true)
  {
    cout << "This program loads data from native files into x and y vectors and computes for various statistics of these data."
    cout << "[1] load x data" << endl << "[2] load y data" << endl <<
    "[3] load x-y data" << endl << "[4] view x data stats" << endl <<
    "[5] view y data stats" << endl << "[6] view x-y data stats" <<
    endl << "[7] line fit" << endl << "[8] correlation" << endl <<
    "[9] exit" << endl << "choice: ";
    cin >> options;
    if (cin.good())
    {
      switch (options)
      {
        case 1:
          cout << "Enter file name: ";
          cin >> fileName;
          fileName = fileName + ".txt";
          pushToVectorX (fileName);
          cout << datavecX.size() << " samples loaded as x data."
          << endl << endl ;
          break;
        case 2:
          cout << "Enter file name: ";
          cin >> fileName;
          fileName = fileName + ".txt";
          pushToVectorY (fileName);
          cout << datavecY.size() << " samples loaded as y data."
          << endl << endl;
          break;
        case 3:
          cout << "Enter file name: ";
          cin >> fileName;
          fileName = fileName + ".txt";
          pushToVectorXandY (fileName);
          cout << datavecX.size() << " samples loaded as x data and "
          << datavecY.size() << " samples loaded as y data." << endl
          << endl;
          break;
        case 4:
          if (datavecX.size() != 0)
          {
            meanX ();
            statsX ();
            cout << endl;
          }
          else
          {
            cout << "Error. No x data loaded.\n\n";
          }
          break;
        case 5:
          if (datavecY.size() != 0)
          {
            meanY ();
            statsY ();
            cout << endl;
          }
          else
          {
            cout << "Error. No y data loaded.\n\n";
          }
          break;
        case 6:
          if (datavecX.size() != 0 || datavecY.size() != 0)
          {
            meanX ();
            statsX ();
            meanY ();
            statsY ();
            cout << endl;
          }
          else
          {
            cout << "Error. No x or y data loaded.\n\n";
          }
          break;
        case 7:
          if (datavecX.size() == datavecY.size())
          {
            double a, b, y_fit[datavecX.size()];
            lineFit(a,b, y_fit);
            cout<<"Pair no."<<setw(3)<<"x"<<setw(15)<<
            "y(observed)"<<setw(15)<<"y(fitted)"<<endl;
            cout<<"-----------------------------------------------\n";
            //print a table of x,y(obs.) and y(fit.)
            for (int i=0;i< datavecX.size();i++)
            {
              cout<<i+1<<"."<<setw(9)<<datavecX[i]<<setw(9)<<
              datavecY[i]<<setw(17)<<y_fit[i]<<endl;
            }
            cout<<"\nThe equation of the best fit line of x and y is "
            <<a<<"x + "<<b<<endl << endl;//print the best fit line
          }
          else
          {
            cout << "Error. x and y must be of the same size.\n\n";
          }
          break;
        case 8:
          if (datavecX.size() == datavecY.size())
          {
            cout<<"Correlation (R): " << correlationCoefficient()<<"\n";
            cout<<"Determination (R^2): "<<
            correlationCoefficient()*correlationCoefficient()<<"\n\n";
          }
          else
          {
            cout << "Error. x and y must be of the same size.\n\n";
          }
          break;
        case 9:
          repeat = false;
          return repeat;
        default:
          cout << "Invalid input." << endl << endl;
      }
    }
    else
    {
      cin.clear();
      cin.sync();
      cout << "Invalid input. \n\n";
    }
  }
  return 0;
}

