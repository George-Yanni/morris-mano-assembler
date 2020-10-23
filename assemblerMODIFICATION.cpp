#include <iostream>
#include<fstream>
#include <sstream> //convert string to int
#include <stdio.h>
#include <bitset>
using namespace std;
int main ()
{
	/*                   ---  First Pass ---*/
	ifstream reader;
	ifstream  reader_loc;
	reader.open("input.txt");/*input text file that has the assembly code*/
	freopen("locations.txt","w",stdout);/*a generated text file that contain every assembly instruction with its location*/
	string x;
	string y;
	int line=0;/*counter to counts locations*/
	int org_size=0;/*counter to deal with ORG pseudoinstruction*/
	int x_size=0;/*counter to maneuver with founded ORG pseudoinstruction*/
	int counter=0;/*counter to counts symbolic table contents*/
	string after_org;/*variable to store the number after ORG*/
	int siz=0;/*variable used at the final stage to generate hex file*/
	int optimizer=0;/*variable used to optimize the HEX file that generated as there is a duplication in the last line of the HEX file */
	int optimize2=0;
	while(!reader.eof())
   {
   		getline(reader,x);
   		if (x.at(0)=='E'&&x.at(1)=='N'&&x.at(2)=='D')
   		{
   			cout<<"END";
   		}
   		else if(x.find("ORG"))/* value will be 4294967295 which is -1 as a signed representation of this decimal value */
   		{
   			cout<<line<<" "<<x<<endl;
   			line++;
   		}
   		else if (!x.find("ORG"))/* value will be 0 */
   		{
   			cout<<x<<endl;
   			org_size=x.size();
   			for(int i=3;i<=org_size-1;i++)
   			{
   			after_org+=x.at(i);
   			}
		stringstream obj(after_org);/*conversion from string to integer*/
		obj>>line;
		after_org="";/*MUST restore to it's value to use it again without any problems*/
   		}
   		
   		
   }

/*-----------------------------------------------------*/

   reader.close();/*close the input file*/
   reader.open("locations.txt");/*open the previous generated file which associate instructions with their addresses*/
   freopen("symbolic_table.txt","w",stdout);/*creat a file called symbolic_table_ to save labels in it*/
   while(!reader.eof())
   {
   		getline(reader,x);
   		x_size=x.size();
    	for(int i=0;i<=x_size-1;i++)
    	{
    		if(x.at(i)==',')/*search till find ',' and this means that it's a label*/
    		{
    			for(int j=0;j<=i-1;j++)
    			{
    				cout<<x.at(j);/*will print the address and the label and this is the output of the first pass of designing our assembler */
    			}
    			cout<<endl;
    		}
    	}
   	}
   	reader.close();



/*-----------------------------------------------------*/

	reader.open("symbolic_table.txt");
	while(!reader.eof())
	{
	
		getline(reader,x);
		counter++;
	}
	reader.close();
	reader.open("symbolic_table.txt");
	
	string table[counter-1][2];
	while(!reader.eof())
	{
	
		
		for(int i=0;i<=counter-2;i++)
		{
			for(int j=0;j<=1;j++)
			{
				reader>>x;
				table[i][j]=x;
				
			}
		}
		break;
	}
reader.close(); 
/*now,after this section we sored all lables of symbolic_table file into an array*/

/*-----------------------------------------------------*/
	string table2[counter-1][3];
	reader.open("symbolic_table.txt");
	while(!reader.eof())
	{	
		
		for(int i=0;i<=counter-2;i++)
		{
			
			
				reader>>x>>x;
				table2[i][0]=x+=",";
				
			
		}
		break;
		
	}
	reader.close();
	/*now table2 has in its first column all the variables*/

/*-----------------------------------------------------*/

	reader.open("locations.txt");
	while(!reader.eof())
	{
		reader>>x;
		for(int i=0;i<=counter-2;i++)
		{
			if(x==table2[i][0])
			{
				reader>>x;
				table2[i][1]=x;
				reader>>x;
				table2[i][2]=x;
			}
		}
	}

	reader.close();


/*now,table2 have all variable associated with its type either
 HEX or DEC and also have its value like that :
 variable1 HEX 234
 variable2 DEC 19
 variable3 DEC -23
 etc..
 so,table2 has n rows according to variables number and 3 column
*/	


/*-----------------------------------------------------*/	

/*					  --- Second Pass ---              */

	reader.open("input.txt");
	reader_loc.open("symbolic_table.txt");
	freopen("output.txt","w",stdout);
	while(!reader.eof())
	{
		reader>>x;
		start_here_to_check_all:
		if(x=="ORG")
		{
			reader>>x>>x;

		}
		if(x=="AND")
		{
			reader>>x;
			y=x;
			reader>>x;
			if(x=="I")
			{
				for(int i=0;i<=counter-2;i++)
			{
				for(int j=0;j<=1;j++)
				{
					if(y==table[i][j])
					{
						cout<<"8"<<table[i][j-1]<<endl;
					}
				}
			}
			}
			else
			{
				for(int i=0;i<=counter-2;i++)
				{
					for(int j=0;j<=1;j++)
					{
						if(y==table[i][j])
						{
							cout<<"0"<<table[i][j-1]<<endl;
						}
					}
				}
			}
			goto start_here_to_check_all;
			
		}
		
		if(x=="ADD")
		{
			reader>>x;
			y=x;
			reader>>x;
			if(x=="I")
			{
				for(int i=0;i<=counter-2;i++)
			{
				for(int j=0;j<=1;j++)
				{
					if(y==table[i][j])
					{
						cout<<"9"<<table[i][j-1]<<endl;
					}
				}
			}
			}
			else
			{
				for(int i=0;i<=counter-2;i++)
				{
					for(int j=0;j<=1;j++)
					{
						if(y==table[i][j])
						{
							cout<<"1"<<table[i][j-1]<<endl;
						}
					}
				}
			}
			goto start_here_to_check_all;
			
		}

		if(x=="LDA")
		{
			reader>>x;
			y=x;
			reader>>x;
			if(x=="I")
			{
				for(int i=0;i<=counter-2;i++)
			{
				for(int j=0;j<=1;j++)
				{
					if(y==table[i][j])
					{
						cout<<"A"<<table[i][j-1]<<endl;
					}
				}
			}
			}
			else
			{
				for(int i=0;i<=counter-2;i++)
				{
					for(int j=0;j<=1;j++)
					{
						if(y==table[i][j])
						{
							cout<<"2"<<table[i][j-1]<<endl;
						}
					}
				}
			}
			goto start_here_to_check_all;
			
		}

		if(x=="STA")
		{
			reader>>x;
			y=x;
			reader>>x;
			if(x=="I")
			{
				for(int i=0;i<=counter-2;i++)
			{
				for(int j=0;j<=1;j++)
				{
					if(y==table[i][j])
					{
						cout<<"B"<<table[i][j-1]<<endl;
					}
				}
			}
			}
			else
			{
				for(int i=0;i<=counter-2;i++)
				{
					for(int j=0;j<=1;j++)
					{
						if(y==table[i][j])
						{
							cout<<"3"<<table[i][j-1]<<endl;
						}
					}
				}
			}
			goto start_here_to_check_all;
			
		}

		if(x=="BUN")
		{
			reader>>x;
			y=x;
			reader>>x;
			if(x=="I")
			{
				for(int i=0;i<=counter-2;i++)
			{
				for(int j=0;j<=1;j++)
				{
					if(y==table[i][j])
					{
						cout<<"C"<<table[i][j-1]<<endl;
					}
				}
			}
			}
			else
			{
				for(int i=0;i<=counter-2;i++)
				{
					for(int j=0;j<=1;j++)
					{
						if(y==table[i][j])
						{
							cout<<"4"<<table[i][j-1]<<endl;
						}
					}
				}
			}
			goto start_here_to_check_all;
			
		}

		if(x=="BSA")
		{
			reader>>x;
			y=x;
			reader>>x;
			if(x=="I")
			{
				for(int i=0;i<=counter-2;i++)
			{
				for(int j=0;j<=1;j++)
				{
					if(y==table[i][j])
					{
						cout<<"D"<<table[i][j-1]<<endl;
					}
				}
			}
			}
			else
			{
				for(int i=0;i<=counter-2;i++)
				{
					for(int j=0;j<=1;j++)
					{
						if(y==table[i][j])
						{
							cout<<"5"<<table[i][j-1]<<endl;
						}
					}
				}
			}
			goto start_here_to_check_all;
			
		}

		if(x=="ISZ")
		{
			reader>>x;
			y=x;
			reader>>x;
			if(x=="I")
			{
				for(int i=0;i<=counter-2;i++)
			{
				for(int j=0;j<=1;j++)
				{
					if(y==table[i][j])
					{
						cout<<"E"<<table[i][j-1]<<endl;
					}
				}
			}
			}
			else
			{
				for(int i=0;i<=counter-2;i++)
				{
					for(int j=0;j<=1;j++)
					{
						if(y==table[i][j])
						{
							cout<<"6"<<table[i][j-1]<<endl;
						}
					}
				}
			}
			goto start_here_to_check_all;
			
		}

		if(x=="CLA")
		{
			cout<<"7800"<<endl;
			
		}

		if(x=="CLE")
		{
			cout<<"7400"<<endl;
			
		}

		if(x=="CMA")
		{
			cout<<"7200"<<endl;
			
		}

		if(x=="CME")
		{
			cout<<"7100"<<endl;
			
		}

		if(x=="CIR")
		{
			cout<<"7080"<<endl;
			
		}

		if(x=="CIR")
		{
			cout<<"7040"<<endl;
			
		}

		if(x=="INC")
		{
			cout<<"7020"<<endl;
			
		}

		if(x=="SPA")
		{
			cout<<"7010"<<endl;
			
		}

		if(x=="SNA")
		{
			cout<<"7008"<<endl;
			
		}

		if(x=="SZA")
		{
			cout<<"7004"<<endl;
			
		}

		if(x=="SZE")
		{
			cout<<"7002"<<endl;
			
		}

		if(x=="HLT")
		{
			cout<<"7001"<<endl;
			
		}

		if(x=="INP")
		{
			cout<<"F800"<<endl;
			
		}

		if(x=="OUT")
		{
			cout<<"F400"<<endl;
			
		}

		if(x=="SKI")
		{
			cout<<"F200"<<endl;
			
		}

		if(x=="SKO")
		{
			cout<<"F100"<<endl;
			
		}

		if(x=="ION")
		{
			cout<<"F080"<<endl;
			
		}

		if(x=="IOF")
		{
			cout<<"F040"<<endl;
			
		}

	}

/*--------------------------------------------------------*/
/*		conversion of (DEC / HEX) of variable to HEX	  */	

	for(int i=0;i<=counter-2;i++)
	{
		
			
			cout<<hex<<stoi(table2[i][2])<<endl;/*must be converted to integer first as this table contain strings */
				
			
	

	}

/*--------------------------------------------------------*/

	reader.close();
	reader.open("output.txt");
	freopen("HEX.txt","w",stdout);
	while(!reader.eof())
	{
		reader>>x;
		if(x.size()==4)
		{
			cout<<x<<endl;
		}
		else if (x.size()<4)
		{
			siz=x.size();
			if(siz==1)
			{
				cout<<"000"<<x<<endl;
			}
			else if(siz==2)
			{
				cout<<"00"<<x<<endl;
			}
			else if (siz==3)
			{
				cout<<"0"<<x<<endl;
			}
		}
		else if (x.size()>4)
		{
			siz=x.size();
			for(int i=x.size()-4;i<=x.size()-1;i++)
			{
				cout<<x.at(i);

			}
			cout<<endl;
		}
	}

/* We will do the following due to there is a duplication of the last line in the hex file*/	
	reader.close();
	reader.open("HEX.txt");
	while(!reader.eof())
	{
		reader>>x;
		optimizer++;
	}
	reader.close();
	reader.open("HEX.txt");
	freopen("HEX_Final.txt","w",stdout);
	while(optimize2<=optimizer-3)
	{
		reader>>x;
		cout<<x<<endl;
		optimize2++;
	}
	optimize2=0;
reader.close();
remove("HEX.txt");
freopen("BIN.txt","w",stdout);
rename("HEX_Final.txt","HEX.txt");
reader.open("HEX.txt");


/*Now,we are ready to convert the HEX file to the BIN file */
while(!reader.eof())
{
	reader>>x;
	for(int i=0;i<=x.size()-1;i++)
	{
		switch (x.at(i))
		{
			 case '0': 
            cout << "|0000"; 
            break; 
        case '1': 
            cout << "|0001"; 
            break; 
        case '2': 
            cout << "|0010"; 
            break; 
        case '3': 
            cout << "|0011"; 
            break; 
        case '4': 
            cout << "|0100"; 
            break; 
        case '5': 
            cout << "|0101"; 
            break; 
        case '6': 
            cout << "|0110"; 
            break; 
        case '7': 
            cout << "|0111"; 
            break; 
        case '8': 
            cout << "|1000"; 
            break; 
        case '9': 
            cout << "|1001"; 
            break; 
        case 'A': 
        case 'a': 
            cout << "|1010"; 
            break; 
        case 'B': 
        case 'b': 
            cout << "|1011"; 
            break; 
        case 'C': 
        case 'c': 
            cout << "|1100"; 
            break; 
        case 'D': 
        case 'd': 
            cout << "|1101"; 
            break; 
        case 'E': 
        case 'e': 
            cout << "|1110"; 
            break; 
        case 'F': 
        case 'f': 
            cout << "|1111"; 
            break; 
		}
	}
	cout<<"|"<<endl;
}
/*Now ,The last thing , we will make the previous step of removing the duplication of the last line and the previous line to it*/

reader.close();
reader.open("BIN.txt");
freopen("BIN_Final.txt","w",stdout);
while(optimize2<=optimizer-3)
	{
		reader>>x;
		cout<<x<<endl;
		optimize2++;
	}
reader.close();
remove("BIN.txt");	
freopen("locations.txt","r",stdout);/* this trick to enable renaming the preopened file which can not be renamed while it is opened*/
rename("BIN_Final.txt","BIN.txt");
/*-------------------------------------------------------*/

/*Time this assembler it takes was almost 4 days of contious work!*/
/*Done by : George Safwat */


}