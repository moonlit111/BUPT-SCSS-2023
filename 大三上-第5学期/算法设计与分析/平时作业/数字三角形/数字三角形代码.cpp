#include <iostream>
#include <string>
#include <math.h>
#include <numeric>
using namespace std;

int n,m[100][100],s[100][100],x[100][100];

int main() {
    /*
             7
            3 8
           8 1 0
          2 7 4 4
         4 5 2 6 5
    */
    cin >> n;
    for(int i = 1; i <= n; i++){
        for (int j = 1; j <= i; j++)
        cin >> x[i][j];
    }
     
	//初始化最底层
    for(int j = 1; j <= n; j++) m[n][j] = x[n][j];
    
    for(int i = n-1 ; i > 0; i--){
        for(int j = 1; j <= i; j++){
            m[i][j] = x[i][j] + max(m[i+1][j],m[i+1][j+1]); //计算最大值
            s[i][j] = m[i+1][j] > m[i+1][j+1] ? j : j+1; //记录路径
        }
    }
    
    cout << m[1][1] << endl;
    cout << "路径：" << endl;
    for(int i = 1, j = 1; i <= n; i++){
        cout << x[i][j] << " ";
        j = s[i][j];
    }
 }
