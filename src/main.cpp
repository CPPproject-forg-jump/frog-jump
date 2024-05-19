#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

struct Log {
    int position;
    int speed;
};

// 函数：canCross
// 描述：判断青蛙能否过河
// 参数：logs - 河中浮木的位置和速度
//       index - 当前所在浮木的索引
//       k - 上一次跳跃的距离
// 返回：是否能成功过河
bool canCross(vector<Log>& logs, int index, int k) {
    for (int i = index + 1; i < logs.size(); i++) {
        int gap = logs[i].position - logs[index].position;
        if (gap >= k - 1 && gap <= k + 1) {
            if (canCross(logs, i, gap)) {
                return true;
            }
        } else if (gap > k + 1) {
            break;
        }
    }
    return index == logs.size() - 1;
}

// 函数：canCross
// 描述：判断青蛙能否过河（包装函数）
// 参数：logs - 河中浮木的位置和速度
// 返回：是否能成功过河
bool canCross(vector<Log>& logs) {
    if (logs[0].position != 0) return false; // 第一个浮木必须是0
    return canCross(logs, 0, 0);
}

int main() {
    // 随机数生成器
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> pos_dist(1, 100); // 浮木位置的随机分布
    uniform_int_distribution<int> speed_dist(1, 10); // 浮木速度的随机分布

    vector<Log> logs;
    int num_logs = 5; // 浮木的数量
    for (int i = 0; i < num_logs; ++i) {
        Log log;
        log.position = pos_dist(gen);
        log.speed = speed_dist(gen);
        logs.push_back(log);
    }

    // 按照位置排序
    sort(logs.begin(), logs.end(), [](const Log& a, const Log& b) {
        return a.position < b.position;
    });

    if (canCross(logs)) {
        cout << "青蛙可以成功过河！" << endl;
    } else {
        cout << "青蛙无法成功过河！" << endl;
    }
    return 0;
}