# Competitive Programming Helpfull concepts

### Number Theory

1. 	**n** is in Fibinacci Sequence if, **5x(n^2) + 4** or **5x(n^2) - 4** or both are perferct square
2. 	(a+b)%m = (a%m + b%m)%m
3. 	(a-b)%m = (a%m - b%m)%m 
	-	if (a%m - b%m)%m < 0 then (a%m - b%m)%m = (a%m - b%m)%m + m
4. 	(ab)%m = (a%m * b%m)%m 
5. 	A year is caled leap year if:
		- year is divisible by 400
		- OR year is divisible by 4 but not by 100
6. 	n^2 = sum(2i+1) where i = 0,1,2... n terms
		- for eg: 5^2 = 1+3+5+7+9 = 25

7. 	GCD(a,b)  
   	{  
   		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;// GCD - largest number that divides both of them  
   		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;// Euclid’s algorithm.&nbsp; **O(log(min(a,b)))**    
 		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;if(a == 0) return b;  
		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return GCD(b%a,a);   
   	}
8. 	LCM(a,b) = (a*b)/GCD(a,b)
9. 	For an odd prime **p**,&nbsp; **(2^k)%p == 1** if and only of &nbsp; **(k)%(p-1) == 0**  
	> #### Fermant's little theorm :
	1. 	If **p** is a prime number and **a** is any integer, than &nbsp;
		**(a^p)%p == a**, i.e &nbsp; **((a^p)-a)%p == 0**
	2. 	If **a** is not divisible by **p**, than &nbsp;
		**(a^(p-1))%p == 1**	 


