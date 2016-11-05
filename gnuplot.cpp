#include<errno.h>
#include<exception>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<vector>


class DifferentSizeVectorException: public std::exception
{
    virtual const char* what() const throw()
    {
      return "Size of x and y vector are different";
    }
} different_size_vector_exception;


class GnuPlot
{
public:
  FILE *gnuplot;
  GnuPlot();
  ~GnuPlot();
  void send_cmd(char* cmd);
  void plot2d(std::vector<double> x, std::vector<double> y);
};

GnuPlot::GnuPlot()
{
  FILE *g = popen("gnuplot", "w");
  gnuplot = g;
}

GnuPlot::~GnuPlot()
{
  pclose(gnuplot);
}

void GnuPlot::send_cmd(char* cmd)
{
  fprintf(gnuplot, "%s\n", cmd);
  fflush(gnuplot);
}

void GnuPlot::plot2d(std::vector<double> x, std::vector<double> y)
{
  std::ofstream f;
  char* cmd = "plot \"data_to_gnuplot.txt\" using 1:2";

  try
  {
    if (x.size() != y.size())
      throw different_size_vector_exception;
    else
      f.open ("data_to_gnuplot.txt");
      for(int i=0; i < x.size(); ++i)
      {
        f << x[i] << " " << y[i] << "\n";
      }
      send_cmd(cmd);
  }
  catch (std::exception& e)
  {
    std::cout << e.what() <<"\n";
  }
}

void real_time_plot();
int main()
{
  real_time_plot();
  getchar();
  return 0;
}

void real_time_plot()
{
  std::vector<double> x;
  std::vector<double> y;
  GnuPlot g;
  for (int i=0; i < 250; i++)
  {
    x.push_back(i);
    y.push_back(2*i);
    g.plot2d(x, y);
    usleep(100000);
  }
}
