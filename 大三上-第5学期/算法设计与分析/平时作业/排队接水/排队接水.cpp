#include <bits/stdc++.h>
#include <iomanip> // 用于设置输出精度
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<int> Ti(n);
    for(int i = 0; i < n; ++i){
        cin >> Ti[i];
    }
    
    // 按照接水时间从小到大排序
    sort(Ti.begin(), Ti.end());
    
    long long sum_wait = 0;      // 总等待时间
    long long current_sum = 0;   // 当前累计接水时间
    
    for(int i = 0; i < n; ++i){
        // 每个人的等待时间为前面所有人的接水时间之和
        sum_wait += current_sum;
        current_sum += Ti[i];
    }
    
    // 计算平均等待时间
    double average_wait = (double)sum_wait / n;
    
    // 输出结果，保留一位小数
    cout << fixed << setprecision(1) << average_wait;
    
    return 0;
}
