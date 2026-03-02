#include<stdio.h>
int main()
{
int n,i;
scanf("%d",&n);
int arr[n];
printf("enter elements");
for(i=0;i<n;i++)
{
//printf("enter elements");
scanf("%d",&arr[i]);
}
int l=arr[0],sl=arr[0];
for(i=1;i<=n;i++)
{
if(arr[i]>l)
{
sl=l;
l=arr[i];
}
else if(arr[i]>sl && arr[i]!=l)
{
sl=arr[i];
}
}
printf("secomd largest=%d",sl);
return 0;
}
