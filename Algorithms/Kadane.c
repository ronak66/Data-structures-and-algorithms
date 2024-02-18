/*
* CODE SUBMITTED BY- SUBHAM SAHU
* GITHUB URL - https://github.com/subhamx
* LINKED URL - https://www.linkedin.com/in/subhamX/
* 
*/


/*

INPUT FORMAT - 
    SIZE OF ARRAY
    ARRAY ELEMENTS

OUTPUT FORMAT - 
    MAXIMUM SUM OF SUBARRAY

*/

#include<stdio.h>
#include<limits.h>

int main(){
    int n, temp;
    scanf("%d", &n);
    int A[n];
    for(int i=0; i<n; i++){
        scanf("%d", A+i);
    }
    int ans = INT_MIN;
    temp = 0;
    for(int i=0; i<n; i++){
        temp += A[i];
        if(temp>ans){
            ans=temp;
        }
        if(temp<0){
            temp=0;
        }
    }
    printf("%d\n", ans);
}

/*
ANALYSIS - 
    This Algorithm returns the maximum sum in O(n).
*/
