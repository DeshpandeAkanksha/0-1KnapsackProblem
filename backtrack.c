#include <stdio.h>
#define MAX 10
 
int weight[MAX],profit[MAX];
int i,j,n;
int max_capacity;
float item[MAX];
int item_x[MAX],item_y[MAX];
int f_profit=-1,f_weight;
 
float backtrack(float c_profit,float c_wt,int cap)
{
	float bound_prof;
	float prof = c_profit;
	float wt = c_wt;
	for(i=cap;i<=n;i++)
	{
   		wt += weight[i];
   		if( wt < max_capacity)
      			prof += profit[i];
   		else
		{
			bound_prof = (prof + (1-(wt-max_capacity)/ (float)weight[i])*profit[i]);
   			return bound_prof;
		}
	}
	return prof;
}

void knap(int a,float c_profit,float c_weight)
{
	if(c_weight+weight[a] <= max_capacity)
   	{
   		item_y[a] = 1;
   		if(a <= n)
      		knap(a+1,c_profit+profit[a],c_weight+weight[a]);
   		if(((c_profit+profit[a]) > f_profit) && ( a == n))
      		{
      			f_profit = c_profit+profit[a];
      			f_weight = c_weight+weight[a];
      			for(j=0;j<=a;j++)
      			item_x[j] = item_y[j];
      		}
    	}
	if(f_profit <= backtrack(c_profit,c_weight,a))
	{
 		item_y[a] = 0;
 		if( a <= n)
 		knap(a+1,c_profit,c_weight);
 		if(((a == n) && c_profit > f_profit))
   		{
   			f_profit = c_profit;
   			f_weight = c_weight;
   			for(j=0;j<=a;j++)
   			item_x[j] = item_y[j];
   		}
	}
}


void display()
{
	float total_profit=0.0;
	float max_profit=0.0;
	printf("\nmaximum capacity: %d ", max_capacity);
	printf("\n\tItem\tProfit\tWeight");
	for(i=0;i<n;i++)
		printf("\n\t%d\t%d\t%d",i+1,profit[i],weight[i]);
	for(i=0;i<n;i++)
	if(item_x[i]==1)
   	{
		total_profit = (float) profit[i] * (float) item_x[i];
   		max_profit += total_profit;
   	} 
	printf("\n maximum Profit: %f ",max_profit);
}
 
void swap(int a, int b){
	int t;
	t=a;
	a=b;
	b=t;
}
	
void select()
{
	for(i=0;i<n;i++)
	item[i] = (float) profit[i] / (float) weight[i];
	for(i=1;i<n;i++)
   	{
   		for(j=i+1;j<n;j++)
      		{
      			if(item[i]  < item[j])
         		{
         			swap(item[i], item[j]);
	 			swap(profit[i], profit[j]);
	 			swap(weight[i], weight[j]);
         		}
      		}
    	}
}

 
int main()
{
	FILE *file = fopen("in.csv", "r");
    	fscanf(file,"%d",&n);
    	for (i=0;i<1;i++)
			fscanf(file,"%d,",&max_capacity);
	for(i=0;i<n;i++)
    			fscanf(file,"%d,",&profit[i]);
	for(i=0;i<n;i++)
			fscanf(file,"%d,",&weight[i]);
    	fclose(file);
select();
knap(0,0,0);
display();
}