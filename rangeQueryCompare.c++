#include <iostream>
#include <chrono>
#include <cmath>

auto timeUsage(){
    //用於產生實驗用的陣列
    int n = pow(2,20);
    int arr[n];
    // int k = pow(2,10);
    // std::cout<<"k: "<<k<<"\n";
    for(int i=0; i<n; i++){
        int num = rand() % (n);
        // int num = rand() % (k);
        arr[i] = num;
        // arr[i] = i;
    }
    
    //計時
    auto start = std::chrono::high_resolution_clock::now();
    
    auto end = std::chrono::high_resolution_clock::now();
    auto cpu__time_used = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return cpu__time_used;
}

auto getAvg(int n){
    auto sum = std::chrono::nanoseconds(0);
    for(int i=0; i<n; i++){
        auto usedTime = timeUsage();
        std::cout<<"第"<<i<<"次 : "<<usedTime.count()<<"\n";
        sum += usedTime;
    }
    return sum/n;
}

int main() {
    // Seed the random number generator
    srand(time(NULL));
    //calculate the average used time of the action
    auto usedTime_Average = getAvg(10);
    std::cout << "程式平均執行時間：" << usedTime_Average.count() << " nanoseconds" <<"\n";
    std::cout<<"finish";
    return 0;
}
