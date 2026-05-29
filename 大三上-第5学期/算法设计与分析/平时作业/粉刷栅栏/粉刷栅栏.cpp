#include <iostream>
#include <string>
#include <math.h>
#include <numeric>
using namespace std;

int n, h[5010]; // 全局变量n表示栅栏的数量，h[]数组存储每个栅栏的高度（索引从1开始）

// 递归函数，计算从位置left到right 栅栏，在已涂刷高度为baseH的情况下，所需的最少涂刷次数
int paint_fences(int left, int right, int baseH) {
    // 基本情况：如果区间无效，返回 0，不需要额外的涂刷
    if (left > right) {
        return 0;
    }

    // 初始化变量
    int minH = 11;    // 当前区间的最小高度，初始化为11（题目中栅栏高度最大为10）
    int pos_min = 0;  // 最小高度所在的位置
    int paint_column = 0; // 垂直涂刷次数（逐个栅栏涂刷）
    int paint_row = 0;    // 水平涂刷次数（从baseH涂刷到minH所需的次数）

    // 遍历区间，找到最小高度minH，位置pos_min，并计算垂直涂刷次数paint_column
    for (int i = left; i <= right; i++) {
        // 更新最小高度和其位置
        if (minH > h[i]) {
            minH = h[i];
            pos_min = i;
        }
        // 如果当前栅栏高度大于已涂刷高度，需要涂刷
        if (h[i] > baseH) {
            paint_column++; // 垂直涂刷次数加一
        }
    }

    // 计算水平涂刷到 minH 所需的次数
    paint_row = minH - baseH;

    // 递归处理最小高度位置左侧和右侧的子区间，新的已涂刷高度为minH
    int left_min = paint_fences(left, pos_min - 1, minH);
    int right_min = paint_fences(pos_min + 1, right, minH);

    // 计算选择水平涂刷的总涂刷次数
    int total_paint_row = paint_row + left_min + right_min;

    // 返回垂直涂刷和水平涂刷方案中较小的次数
    return min(paint_column, total_paint_row);
}

int main() {
    // 输入栅栏的数量
    cin >> n;
    // 输入每个栅栏的高度，索引从1开始
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }
    // 调用递归函数，初始区间为[1,n]，已涂刷高度为0
    cout << paint_fences(1, n, 0);
}

