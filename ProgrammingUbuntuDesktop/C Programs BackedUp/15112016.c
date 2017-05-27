#include <stdio.h>

void sumf(int a,int b,int*sum);
void swap(int*begin,int*end);

int main()
{
	
	int a,b;
	int sum;
	scanf("%d",&a);
	scanf("%d",&b);
	sumf (a,b,&sum);
	printf("%d\n",sum);

	int i;
	int arr[10];
	for(i=0;i<10;i++){
		scanf("%d",&arr[i]);
	}
	swap(&arr[0],&arr[9]);
	for(i=0;i<10;i++){
		printf("%d ",arr[i]);
	}
	return 0;
}
void sumf(int a,int b,int* sum){
	*sum=a+b;
}
void swap(int*begin,int*end){
	int temp;
	while (*begin<*end){
		temp=*end;
		*end=*begin;
		*begin=temp;
		*begin++;
		*end--;
}

