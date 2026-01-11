//Dynamic array of pointer having size 10 using new is created as,
int **arr = new int *[10];

int *ar = new int[4];

Class* C= new Class[4];//array of class instances
//or similar to
Class* B = (Class*)malloc(sizeof(Class));

delete C;
delete[] ar;
delete[] arr;
