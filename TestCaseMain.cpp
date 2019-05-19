/*
 * TestCaseMain.cpp
 *
 *  Created on: May 18, 2019
 *      Author: ADG
 */
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <stdio.h>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::cerr;
using std::vector;
using std::ios;
using std::getline;
using std::setw;


int CFunctionProgrammingFileProcessing(vector<double> &,vector<double> &,vector<double> &,vector<double> &,vector<double> & );
double findVOL(vector<double> &);

int main()
{

	vector <double>PredictedPHLXSemiconductorIndexModel;
	vector <double> PHLXSemiConductorIndex;
	vector<double> RegressionModelErrors;
	vector <double> Predictor1;   //ChinaConsumerIndex
	vector <double> Predictor2;  //FederalDiscountRate
	vector <double> Predictor3;           //SP500Index
	vector <double> Predictor4; //USConsumerPriceIndex

	CFunctionProgrammingFileProcessing(PHLXSemiConductorIndex,Predictor1,Predictor2,Predictor3,Predictor4);

	for (int i =0;i<120;i++)
	{
	PredictedPHLXSemiconductorIndexModel.push_back( (-46.6 + 0.3230*Predictor3[i]+23.88*Predictor2[i]+6.74*Predictor4[i]+3.55*Predictor1[i])  );
	RegressionModelErrors.push_back(PredictedPHLXSemiconductorIndexModel[i]- PHLXSemiConductorIndex[i]);
	}

	cout<<"RegressionModelErrors "<<"Predicted PHLXSemiconductorIndex "<<setw(10)<<"PHLXSemiConductorIndex "<<endl;
	for (int i =0;i<120;i++)
		cout<<RegressionModelErrors[i]<<setw(25)<<PredictedPHLXSemiconductorIndexModel[i]<<setw(30)<<PHLXSemiConductorIndex[i]<<endl;


double volatilityPercentage=findVOL(RegressionModelErrors);

double SeekingAlpha;
double averagePortfolioReturn = 0.1;
double riskFreeRate = 0.035;
double BetaValue = 1.1;
double MarketPremium = 0.075;

SeekingAlpha=(averagePortfolioReturn-(riskFreeRate + BetaValue*(MarketPremium - riskFreeRate)));

double MarketPremiumP95CI =MarketPremium+3*volatilityPercentage;
double MarketPremiumN95CI = MarketPremium-3*volatilityPercentage;
double averagePortfolioReturnP95CI =averagePortfolioReturn+3*volatilityPercentage;
double averagePortfolioReturnN95CI = averagePortfolioReturn-3*volatilityPercentage;


double SeekingAlphaP95CI=(averagePortfolioReturnP95CI-(riskFreeRate + BetaValue*(MarketPremiumP95CI - riskFreeRate)));
double SeekingAlphaN95CI=(averagePortfolioReturnN95CI-(riskFreeRate + BetaValue*(MarketPremiumN95CI - riskFreeRate)));

cout<<"\n Seeking Alpha 95 % confidence interval ("<<SeekingAlphaN95CI<<" "<<SeekingAlphaP95CI<<")"<<"where Alpha is "<<SeekingAlpha<<endl;


	return 0;
}


//********* PRIVATE IMPLEMENTATION UTILITY FUNCTION********************************/
double findVOL(vector <double> &RegressionModelErrors)
{
double sum =0;
for (int i =0;i<120;i++)
sum = RegressionModelErrors[i]+sum;

double average = sum/120;


double Variation=0;

for (int i =0;i<120;i++)
Variation= pow((average - RegressionModelErrors[i] ), 2) + Variation;

double StandardDeviation = pow(Variation/120 , 0.5);
double volatilityPercentage =  StandardDeviation/100;

return volatilityPercentage;
}


//********* PRIVATE IMPLEMENTATION UTILITY FUNCTION********************************/
int CFunctionProgrammingFileProcessing(vector<double> &PHLXSemiConductorIndex,vector<double> &Predictor1,vector<double> &Predictor2,vector<double> &Predictor3,vector<double> &Predictor4)
{
	double dataLine;


	ifstream FileHandle1("PHLXSemiConductorIndex.txt",ios::in);
	ifstream FileHandle2("Predictor1.txt",ios::in);
	ifstream FileHandle3("Predictor2.txt",ios::in);
	ifstream FileHandle4("Predictor3.txt",ios::in);
	ifstream FileHandle5("Predictor4.txt",ios::in);


	while (FileHandle1>>dataLine)
	PHLXSemiConductorIndex.push_back(dataLine);

	while (FileHandle2>>dataLine)
		Predictor1.push_back(dataLine);


	while (FileHandle3>>dataLine)
		Predictor2.push_back(dataLine);


	while (FileHandle4>>dataLine)
		Predictor3.push_back(dataLine);


	while (FileHandle5>>dataLine)
		Predictor4.push_back(dataLine);

return 0;

}


/* OUTPUT

RegressionModelErrors Predicted PHLXSemiconductorIndex PHLXSemiConductorIndex
13.9787                  437.849                        423.87
19.6426                  452.953                        433.31
35.3985                  439.359                        403.96
22.8227                  460.053                        437.23
38.0711                  455.061                        416.99
61.1165                  446.766                        385.65
29.9445                  458.894                        428.95
43.3518                  462.422                        419.07
6.84594                  481.286                        474.44
10.2832                  484.033                        473.75
23.1502                   498.47                        475.32
63.6742                  496.314                        432.64
22.7129                  504.353                        481.64
31.0665                  510.556                        479.49
-7.30206                  531.808                        539.11
2.52018                   525.71                        523.19
34.7765                  534.426                        499.65
70.4016                  535.142                        464.74
104.209                  545.929                        441.72
136.728                  549.488                        412.76
106.191                  555.411                        449.22
109.862                  564.562                         454.7
13.3095                   471.45                        458.14
-5.65161                  473.368                        479.02
17.2727                  485.193                        467.92
36.3852                  536.035                        499.65
22.5342                  481.464                        458.93
-11.1448                  462.405                        473.55
8.19085                  473.761                        465.57
-19.4468                  473.493                        492.94
3.48292                  491.743                        488.26
-11.4355                  489.724                        501.16
-24.426                  474.654                        499.08
-14.5935                  482.846                        497.44
5.69832                  505.788                        500.09
36.1107                  499.501                        463.39
80.0381                  494.618                        414.58
75.3424                  483.382                        408.04
111.042                  470.042                           359
105.502                  453.552                        348.05
120.294                  464.234                        343.94
92.0564                  477.216                        385.16
59.2606                  474.461                         415.2
77.1447                  445.305                        368.16
97.6391                  438.499                        340.86
93.0312                  399.921                        306.89
93.7225                  333.192                        239.47
102.73                   446.67                        343.94
52.5441                  250.784                        198.24
64.978                  277.148                        212.17
33.2418                  241.502                        208.26
-5.24554                  193.754                           199
-13.8904                   324.97                        338.86
-14.1036                  244.436                        258.54
-8.94369                  262.366                        271.31
-9.17111                  253.979                        263.15
-27.16                   274.58                        301.74
-26.7383                  279.442                        306.18
-33.2976                  292.452                        325.75
8.45554                  305.066                        296.61
33.8114                  343.861                        310.05
2.29157                  362.202                        359.91
30.2061                  346.276                        316.07
16.8329                  355.693                        338.86
-41.3825                  417.237                        458.62
8.64308                  384.713                        376.07
-14.0329                  341.627                        355.66
-11.6                    320.7                         332.3
6.22538                  355.035                        348.81
32.8587                  340.349                        307.49
12.8046                  362.045                        349.24
4.73054                  377.371                        372.64
-3.46079                  386.659                        390.12
-3.29149                  408.529                        411.82
-18.4317                  422.078                        440.51
-33.607                  425.013                        458.62
1.48063                  438.841                        437.36
1.67946                  451.239                        449.56
-0.06805                  439.532                         439.6
40.2458                  450.596                        410.35
47.4153                  434.355                        386.94
51.79                   407.58                        355.79
35.2801                    374.1                        338.82
21.6416                  408.132                        386.49
37.8189                  411.139                        373.32
53.7593                  418.199                        364.44
25.9518                  434.892                        408.94
21.5329                  445.703                        424.17
21.6254                  460.265                        438.64
39.4654                  452.855                        413.39
37.8549                  406.225                        368.37
45.9081                  431.368                        385.46
47.5826                  431.303                        383.72
47.5582                  443.738                        396.18
75.8034                  458.073                        382.27
86.056                  453.086                        367.03
71.32                   445.67                        374.35
80.2853                  464.345                        384.06
65.257                  477.987                        412.73
59.8348                  486.465                        426.63
20.9071                  584.737                        563.83
53.791                  498.151                        444.36
40.2304                   514.66                        474.43
53.8092                  522.439                        468.63
67.5379                  545.318                        477.78
62.624                  520.324                         457.7
46.7457                  537.576                        490.83
51.0956                  558.186                        507.09
61.8293                  572.079                        510.25
46.9945                  582.025                        535.03
24.2492                  553.429                        529.18
18.1895                  582.019                        563.83
12.2094                  598.959                        586.75
23.3016                  599.272                        575.97
16.6455                  616.236                        599.59
-4.97884                  630.951                        635.93
7.12555                  614.676                        607.55
-8.68106                  636.569                        645.25
-21.5854                  616.895                        638.48
-0.92897                  639.931                        640.86

 Seeking Alpha 95 % confidence interval (0.134628 -0.0926278)where Alpha is 0.021

*/



