#include <iostream>
#include <string>

using namespace std;

void get_dp(string T, int dp[][256]);
int index_KMP(string S, string T, int pos);


int main(){
    string s = "abababcabx";
    string t = "abcabx";
    cout << "Start  match [ " <<  t << " ] in " << "[ " << s << " ]" << endl;
    int len_t = t.length();
    int res = index_KMP(s, t, 0);
    cout << res << endl;
}


// 返回子串T在主串中第pos个字符之后的位置。若不存在，则返回-1
int index_KMP(string S, string T, int pos){
    int j = pos;
    int len_S = S.length();
    int const len_T = T.length();
    int dp[len_T][256];
    int char_idx;
    get_dp(T, dp);
    for(int i = 0; i < len_S; i++){
        char_idx = S[i];
        cout << "Find " << S[i];
        cout << " next j=" << dp[j][char_idx] << endl;
        j = dp[j][char_idx];
        if( j == len_T){
            int res = i - len_T + 1;
            cout << "The string [ " <<  T << " ] in " << "[ " << S << " ]: \n";
            cout << "from " << res << " to " << i << endl;
            return res;
        }
    }
    return -1;
}


// 构建动态规划数组
void get_dp(string T, int dp[][256]){
    // dp [len_t][255]
    int len_T = T.length();
    for(int r=0; r<len_T; r++){
        fill(dp[r], dp[r]+256, 0);
    }
    int char_idx = T[0];
    dp[0][char_idx] = 1;
    cout << "T[0]= " << T[0] << " : " << char_idx  << endl;
    // same state x
    int x = 0;
    for(int j = 1; j < len_T; j++){
        char_idx = T[j];
        cout << "T[" << j << "]= " << T[j] << " : " << char_idx << endl;
        for(int c = 0; c < 256; c++){
            // 未匹配上则初始化
            dp[j][c] = dp[x][c];
        }
        // 匹配到则下一个
        dp[j][char_idx] = j + 1;
        x = dp[x][char_idx];
    }
}


