#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

class KalmanPredictor {
public:
    KalmanPredictor(double initialPosition, double initialVelocity, double noiseLevel)
            : x(initialPosition), v(initialVelocity), Q(noiseLevel), R(0.1) {}

    void predict(double dt, double acceleration) {
        x = x + v * dt + 0.5 * acceleration * dt * dt;
        v = v + acceleration * dt;
    }

    void update(double measurement) {
        double K = v / (v + R);
        x = x + K * (measurement - x);
        v = v + K * (measurement - x);
    }

    double getPredictedState() {
        return x;
    }

private:
    double x; // Predicted position
    double v; // Predicted velocity
    double Q; // Process noise
    double R; // Measurement noise
};
class AcceleratedMotionSimulator {
private:
    double initialPosition;
    double initialVelocity;
    double acceleration;
    double timeStep;
    double noiseLevel;

public:
    AcceleratedMotionSimulator(double initialPos, double initialVel, double accel, double step, double noise)
            : initialPosition(initialPos),
              initialVelocity(initialVel),
              acceleration(accel),
              timeStep(step),
              noiseLevel(noise) {
        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }

    double generateNoise() {
        // Generate random noise within the specified noise level
        return (2.0 * noiseLevel * (std::rand() / static_cast<double>(RAND_MAX)) - noiseLevel);
    }

    double simulatePosition(double time) {
        // Simulate position at a given time with noise
        double truePosition = initialPosition + initialVelocity * time + 0.5 * acceleration * time * time;
        double noisyPosition = truePosition + generateNoise();
        return noisyPosition;
    }

    double runSimulation(double endTime,KalmanPredictor kalmanPredictor) {
        for (double t = 0; t <= endTime; t += timeStep) {
            double simulatedPosition = simulatePosition(t);
            kalmanPredictor.predict(0.1, acceleration);
            kalmanPredictor.update(simulatedPosition);
            std::cout << "True Measurement: " << simulatedPosition << " | Predicted Position: " << kalmanPredictor.getPredictedState() << std::endl;
        }
    }
};
int main() {
    double initialPosition = 0.0;
    double initialVelocity = 10.0;
    double acceleration = 2.0;
    double timeStep = 0.1;
    double noiseLevel = 1.0;

    AcceleratedMotionSimulator simulator(initialPosition, initialVelocity, acceleration, timeStep, noiseLevel);
    KalmanPredictor kalmanPredictor(initialPosition, initialVelocity,noiseLevel);

    double simulationTime = 5.0; // Total simulation time
    simulator.runSimulation(simulationTime,kalmanPredictor);

    return 0;
}
