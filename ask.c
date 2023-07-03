#include <stdio.h>
#include <math.h>

int main()
{
    int i, binaryInput[] = {1, 0, 1, 1, 0, 0, 1, 0, 1, 1}; //binary input array
    int n = sizeof(binaryInput)/sizeof(binaryInput[0]); //length of binary input array
    double A, f, t1, dt;

    printf("Enter amplitude: ");
    scanf("%lf", &A);
    printf("Enter frequency: ");
    scanf("%lf", &f);
    printf("Enter initial time: ");
    scanf("%lf", &t1);
    printf("Enter time interval: ");
    scanf("%lf", &dt);
    
    for (i=0; i<n; i++) {
        if (binaryInput[i] == 1) { // binary 1
            for (double j = t1; j < t1 + dt; j += 0.001) {
                double k = A * cos(2*M_PI*f*j);
                printf("%lf\t", k);
            }
        } else { // binary 0
            for (double j = t1; j < t1 + dt; j += 0.001) {
                printf("0.000000\t"); // 0 amplitude
            }
        }
        t1 += dt;
        printf("\n");
    }
    return 0;
}
