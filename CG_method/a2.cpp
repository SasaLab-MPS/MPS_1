#include <bits/stdc++.h>
#include "Eigen/Dense"
using namespace Eigen;
using namespace std;


#define N 10
#define TMAX 100
#define EPS 1.0e-8      // 許される誤差の上限

// CG法：共役勾配法
VectorXd CG_method(MatrixXd A, VectorXd b, VectorXd x) {
    VectorXd p(N), r(N), Ax(N), Ap(N);

    // Axを計算
    Ax = A * x;
    // pとrを計算 p = r := b - Ax
    p = b - Ax; // p:初期勾配ベクトル
    r = p;      // 初期残差ベクトル
    // 反復計算
    for (int i = 0; i < TMAX; i++)
    {
        double alpha, beta, error = 0;

        // alphaを計算
        Ap = A * p;
        alpha = p.dot(r) / p.dot(Ap);
        // x, rを更新
        x += alpha * p;
        r -= alpha * Ap;
        // 誤差を計算
        error = r.norm();
        printf("LOOP : %d\t Error : %g\n", i, error);

        if (error < EPS)
        {
            break;
        }
        else
        {
            // betaの計算
            beta = -r.dot(Ap) / p.dot(Ap);
        }

        p = r + beta * p;
    }
    return x;
}

int main(int argc, char const *argv[])
{
    /* code */
    MatrixXd A(N, N); // MatrixXd:動的配列の行列
    A << 5.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        2.0, 5.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 2.0, 5.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 2.0, 5.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 2.0, 5.0, 2.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 2.0, 5.0, 2.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 5.0, 2.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 5.0, 2.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 5.0, 2.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 5.0;

    VectorXd b(N), x(N); // 行ベクトル
    b << 3.0, 1.0, 4.0, 0.0, 5.0, -1.0, 6.0, -2.0, 7.0, -15.0;
    x << 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0;

    // CG法
    x = CG_method(A, b, x);
    // 出力
    cout << x << endl;

    return 0;
}
