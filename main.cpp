//
// 分岐予測の効果を測定するためのプログラム
//

// 必要なライブラリを読み込む
#include <random>   // 乱数関係
#include <time.h>   // 時刻関係
#include <stdio.h>  // 標準入出力


// テスト回数の指定
// 測定誤差を減らすために十分な回数を繰り返す
// 実行時間が安定しない場合，すこし増やしてみる
static const int NUM_TEST = 1000;   

// 入力データの要素数
static const int SIZE = 1000000;

// 入力データの周期
// PERIOD ごとに同じデータが繰り返される
static const int PERIOD = 1000000;

// 入力データ
char buf[SIZE];


int main(int argc, char* argv[]){

    //
    // 入力データの初期化
    //
    std::mt19937 mt(0); // 乱数生成器
    for (int i = 0; i < SIZE; i++) {
        if (i < PERIOD){
            // 0 から 9 までの数字をランダムに代入する
            // 乱数を10で割った余りで初期化
            buf[i] = mt() % 10; 
        }
        else{
            // PERIOD 以降は繰り返す
            buf[i] = buf[i % PERIOD];
        }
    }

    //
    // 測定部分
    //
    clock_t start = clock();    // 開始時刻
    int total = 0;
    for (int i = 0; i < NUM_TEST; i++) {    
        // 十分な回数を測定するために繰り返す

        total = 0;
        for (int j = 0; j < SIZE; j++) {
            // buf の中身を順に見ていき，5 以上なら total に加算
            // 以下なら減算する
            if (buf[j] >= 5) {
                total += buf[j];
            }
            else{
                total -= buf[j];
            }
        }
    }
    clock_t end = clock();  // 終了時刻

    // ループ一回あたりの処理時間（ナノ秒）を計算
    // CLOCKS_PER_SEC: 1 秒あたりに clock() が返す数
    // 1000000000: ナノ (10^9)
    // NUM_TEST * SIZE: 総実行回数
    double nsec = (double)(end - start) / CLOCKS_PER_SEC * 1000000000 / ((double)NUM_TEST * SIZE);

    // 結果表示
    printf("result: %d, time: %f nano seconds",  total, nsec);

    return 0;
}
