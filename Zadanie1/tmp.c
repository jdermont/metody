#include <stdio.h>

int main(){
int k, i, t=0, j, tmp_x, tmp;
printf("Podaj k: ");
scanf("%i", &k);
int x[k];
for(i=0; i<k; i++){
	tmp = 0;
	printf("Podaj x: ");
	scanf("%i", &tmp_x);
	for(j=0; j<k; j++){
		if(tmp_x == x[j]){
			printf("Podaj inny x.\n");
			tmp = 1;
			break;
		}
	}
	if(tmp == 1){
		i--;
		continue;
	}
	x[i+t] = tmp_x;
	if((i+1)%3 == 0){
		t++;
		x[i+t] = x[i+t-1];
	}
	tmp = 0;
}

for(i=0; i<k; i++){
	printf("%i ", x[i]);
	printf("\n");
}
return 0;
}
