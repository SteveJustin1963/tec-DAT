#include <stdio.h>
#include <math.h>

#define PI 3.14159265359

// Function to generate BFSK signal
void generateBFSK(int binaryInput[], int length, double amplitude, double Fc1, double Fc2, double samplingFrequency, double duration) {
    FILE *file = fopen("bfsk_signal.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.");
        return;
    }

    int i, j;
    double t, signal;

    // Calculate the time step
    double dt = 1 / samplingFrequency;

    // Calculate the number of samples
    int numSamples = duration * samplingFrequency;

    for (i = 0; i < length; i++) {
        for (j = 0; j < numSamples; j++) {
            t = i * duration + j * dt;
            if (binaryInput[i] == 1) {
                signal = amplitude * cos(2 * PI * Fc1 * t);
            } else {
                signal = amplitude * cos(2 * PI * Fc2 * t);
            }
            fprintf(file, "%f\n", signal);
        }
    }

    fclose(file);
}

int main() {
    // Binary input sequence
    int binaryInput[] = {1, 0, 1, 0, 1, 1};

    // Parameters for BFSK signal generation
    double amplitude = 1.0;
    double Fc1 = 1000.0;  // Carrier frequency for digital 1
    double Fc2 = 2000.0;  // Carrier frequency for digital 0
    double samplingFrequency = 8000.0;
    double duration = 0.1; // Duration of each bit in seconds

    // Calculate the length of the binary input sequence
    int length = sizeof(binaryInput) / sizeof(binaryInput[0]);

    // Generate BFSK signal
    generateBFSK(binaryInput, length, amplitude, Fc1, Fc2, samplingFrequency, duration);

    return 0;
}
