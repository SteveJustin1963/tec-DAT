
#include <stdio.h>
#include <math.h>

int main()
{
    int i, j, k;
    double A, f, t1, dt;
    
    printf("Enter amplitude: ");
    scanf("%lf", &A);
    printf("Enter frequency: ");
    scanf("%lf", &f);
    printf("Enter initial time: ");
    scanf("%lf", &t1);
    printf("Enter time interval: ");
    scanf("%lf", &dt);
    
    for (i=0; i<10; i++) {
        for (j=0; j<1000; j++) {
            k = A*sin(2*M_PI*f*(t1+j*dt));
            printf("%d\t", k);
        }
        printf("\n");
    }
    return 0;
}
