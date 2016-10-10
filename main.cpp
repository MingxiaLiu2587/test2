#include <string>
#include <iostream>  
using namespace std;

#define MAXLENGTH 100


// Get the length of two strings' LCSs, and print one of the LCSs  
// Input: pStr1         - the first string  
//        pStr2         - the second string  
// Output: the length of two strings' LCSs  

int LCS(string s1, string s2,string &lcsubstring)
{
	int len1 = s1.size();
	int len2 = s2.size();
	int clineLast[MAXLENGTH][MAXLENGTH] = { 0 };
	int cup, cleft, cdiag,ctemp;
	int line = len1;
	int col = len2;
	for (int index1 = 1; index1 < len1 + 1; index1++)
	{	
		for (int index2 = 1; index2 < len2 + 1; index2++)
		{
			if (s2[index2 - 1] == s1[index1 - 1])
			{
				clineLast[index1][index2] = clineLast[index1 - 1][index2 - 1] + 1;
			}
			else
			{
				cleft = clineLast[index1][index2 - 1];
				cup = clineLast[index1 - 1][index2];
				clineLast[index1][index2] = cup >= cleft ? cup : cleft;
			}
			//
		}
	}
	// 重构 lcsubstring
	while (col > 0)
	{
		cup = clineLast[line - 1][col];
		cleft = clineLast[line][col - 1];
		cdiag = clineLast[line - 1][col - 1];
		ctemp = clineLast[line][col];
		
		if (ctemp == cup) // up
		{
			line--;
		}
		else
		{
			if (ctemp != cleft) // diag + 1
			{
				lcsubstring = s2[col- 1] + lcsubstring;
				line--;
			}
			col--;  // diag + 1 or left
		}
	}
	return clineLast[len1][len2];
}

int LCSLen (string s1, string s2) // 用一行多几个的空间算最长公共子序列的长度，但是重构公共子序列有点麻烦
{
	int len1 = s1.size();
	int len2 = s2.size();
	int clineLast[MAXLENGTH] = { 0 };
	int cleft = 0;
	int cleftTemp;
	for (int index1 = 1; index1 < len1 + 1; index1++)
	{
		cleft = 0;
		for (int index2 = 1; index2 < len2 + 1; index2++)
		{
			// 
			cleftTemp = cleft;	
			if (s2[index2 - 1] == s1[index1 - 1])
			{
				cleft = clineLast[index2 - 1] + 1;
			}
			else
			{
				if (cleft <= clineLast[index2])
				{
					cleft = clineLast[index2];	
				}
				else
				{
					cleft = cleft;
				}
			}
			clineLast[index2 - 1] = cleftTemp;
			//
		}
		clineLast[0] = 0;
		clineLast[len2] = cleft; //最后一个 
	}
	return clineLast[len2];
}



int main()
{
	string pStr1 = "akqrshrengxqiyxuloqk";
	string pStr2 = "tdzbujtlqhecaqgwfzbc";
	string lcsubstring = "";
	int lcslen = LCS(pStr1, pStr2,lcsubstring);
	cout << "Length: " << lcsubstring << "  "<< lcslen << endl;
	int l2 = LCSLen(pStr1, pStr2);
	cout << l2 << endl;
	system("pause");
	return 0;
}