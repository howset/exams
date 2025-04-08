#include <unistd.h>
#include <stdlib.h>

void	print_solution(char *str)
{
	for(int i =0; str[i]; i++)
	{
		write(1, &str[i],1);
	}
	write(1, "\n",1);
}

void 	solve(char *str, int pos, int open, int to_remove, char *temp, int temp_pos, int *found)
{
	if(!str[pos])
	{
		if(open == 0 && to_remove ==0)
		{
			temp[temp_pos]='\0';
			print_solution(temp);
			*found=1;
		}
		return;
	}
	if(to_remove > 0)
	{
		temp[temp_pos] ='_';
		solve(str, pos +1, open, to_remove -1, temp, temp_pos+1,found);
	}
	if(str[pos] =='(')
	{
		temp[temp_pos]= '(';
		solve(str,pos+1,open +1 , to_remove,temp,temp_pos+1,found);
	}
	else if(str[pos] =='(')
	{
		temp[temp_pos]= ')';
		solve(str,pos+1,open -1 , to_remove,temp,temp_pos+1,found);
	}
	else
	{
		temp[temp_pos]= str[pos];
		solve(str,pos+1,open  , to_remove,temp,temp_pos+1,found);
	}
}

int get_min_removals(char *str)
{
	int open =0, close =0;
	for(int i = 0;str[i];i++)
	{
		if(str[i] == '(')
			open++;
		else if(str[i] == ')')
		{
			if(open >0)
				open--;
			else
				close++;
		}
	}
	return open + close;
}

int main(int argc, char **argv)
{
	if(argc!= 2)return 1;
	int n=0;
	while(argv[1][n])
		n++;
	char temp[n+1];
	int min_removals = get_min_removals(argv[1]);
	int found = 0;
	solve(argv[1],0,0,min_removals,temp,0,&found);
	return 0;
}
