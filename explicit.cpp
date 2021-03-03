#include <iostream>
#include "vector.h"
#include "matrix.h"

#define tau 1e-3

double f1(const vector& u) {
	return -10 * (u[0] - u[1]);
}

double f2(const vector& u) {
	return -u[0] * u[2] + 28 * u[0] - u[1];
}

double f3(const vector& u) {
	return u[0] * u[1] - 8 * u[2] / 3;
}

double (*f[])(const vector&) = {f1, f2, f3};

vector RK1(const vector& u) { // explicit Euler method
	vector k(3);
	for (int i = 0; i < 3; i++)
		k[i] = f[i](u);
	return u + tau * k;
}

vector RK2(const vector& u) { // midpoint method 
	vector k[2] = {3, 3};

	for (int i = 0; i < 3; i++)
		k[0][i] = f[i](u);

	for (int i = 0; i < 3; i++)
		k[1][i] = f[i](u + tau / 2 * k[0]);

	return u + tau * k[1];
}

vector RK3(const vector& u) { // Heun's third order method
	vector k[3] = {3, 3, 3};
	matrix A(4); // Butcher tableau
	A[1][0] = 1 / 3.0; A[1][1] = 1 / 3.0;
	A[2][0] = 2 / 3.0; A[2][2] = 2 / 3.0;
	A[3][1] = 1 / 4.0; A[3][3] = 3 / 4.0; 

	for (int r = 0; r < 3; r++) {
		vector v = u;
		for (int i = 0 ; i < r; i++)
			v += tau * A[r][i + 1] * k[i];
		for (int i = 0; i < 3; i++)
			k[r][i] = f[i](v);
	}

	vector du(3);
	for (int i = 0; i < 3; i++)
		du += A[3][i + 1] * k[i];
	return u + tau * du;
}

vector RK4(const vector& u) { // Classic RK4
	vector k[4] = {3, 3, 3, 3};
	matrix A(5); // Butcher tableau
	A[1][0] = 1 / 2.0; A[1][1] = 1 / 2.0;
	A[2][0] = 1 / 2.0; A[2][2] = 1 / 2.0;
	A[3][0] = 1; A[3][3] = 1;
	A[4][1] = 1 / 6.0; A[4][2] = 1 / 3.0; A[4][3] = 1 / 3.0; A[4][4] = 1 / 6.0; 

	for (int r = 0; r < 4; r++) {
		vector v = u;
		for (int i = 0 ; i < r; i++)
			v += tau * A[r][i + 1] * k[i];
		for (int i = 0; i < 3; i++)
			k[r][i] = f[i](v);
	}

	vector du(3);
	for (int i = 0; i < 4; i++)
		du += A[4][i + 1] * k[i];
	return u + tau * du;
}

void dump(double t, const vector& u) {
	std::cout << t << ',' << u[0] << ',' << u[1] << ',' << u[2] << std::endl;
}

int main() {
	double t = 0;
	vector u(3);
	u[0] = 1; // x(0) = 1
	u[1] = 1; // y(0) = 1
	u[2] = 1; // z(0) = 1
	//dump(t, u);

	while (t <= 50) {
		u = RK4(u);
		t += tau;
		dump(t, u);
	}
}
