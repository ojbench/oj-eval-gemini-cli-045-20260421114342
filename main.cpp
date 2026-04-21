#include <cstdio>

using namespace std;

const int MAXN = 1000005;

template<typename Comp>
struct Heap {
    int arr[MAXN];
    int sz;
    Comp comp;

    Heap() : sz(0) {}

    void push(int x) {
        arr[++sz] = x;
        int cur = sz;
        while (cur > 1) {
            int p = cur / 2;
            if (comp(arr[cur], arr[p])) {
                int tmp = arr[cur];
                arr[cur] = arr[p];
                arr[p] = tmp;
                cur = p;
            } else {
                break;
            }
        }
    }

    void pop() {
        if (sz == 0) return;
        arr[1] = arr[sz--];
        int cur = 1;
        while (cur * 2 <= sz) {
            int child = cur * 2;
            if (child + 1 <= sz && comp(arr[child + 1], arr[child])) {
                child++;
            }
            if (comp(arr[child], arr[cur])) {
                int tmp = arr[cur];
                arr[cur] = arr[child];
                arr[child] = tmp;
                cur = child;
            } else {
                break;
            }
        }
    }

    int top() { return arr[1]; }
    bool empty() { return sz == 0; }
};

struct Less {
    bool operator()(int a, int b) { return a < b; }
};

struct Greater {
    bool operator()(int a, int b) { return a > b; }
};

Heap<Less> up_h, up_del;
Heap<Greater> down_h, down_del;

void clean_up() {
    while (!up_h.empty() && !up_del.empty() && up_h.top() == up_del.top()) {
        up_h.pop();
        up_del.pop();
    }
}

void clean_down() {
    while (!down_h.empty() && !down_del.empty() && down_h.top() == down_del.top()) {
        down_h.pop();
        down_del.pop();
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int current_floor = 0;
    int dir = 1; // 1 for UP, -1 for DOWN

    char op[20];
    for (int i = 0; i < n; ++i) {
        if (scanf("%s", op) != 1) break;
        if (op[0] == 'a' && op[1] == 'd') { // add
            int x;
            scanf("%d", &x);
            if (x > current_floor) {
                up_h.push(x);
            } else {
                down_h.push(x);
            }
        } else if (op[0] == 'c' && op[1] == 'a' && op[2] == 'n') { // cancel
            int x;
            scanf("%d", &x);
            if (x > current_floor) {
                up_del.push(x);
            } else {
                down_del.push(x);
            }
        } else if (op[0] == 'a' && op[1] == 'c') { // action
            clean_up();
            clean_down();
            if (dir == 1) {
                if (!up_h.empty()) {
                    current_floor = up_h.top();
                    up_h.pop();
                } else {
                    clean_down();
                    if (!down_h.empty()) {
                        dir = -1;
                        current_floor = down_h.top();
                        down_h.pop();
                    }
                }
            } else {
                if (!down_h.empty()) {
                    current_floor = down_h.top();
                    down_h.pop();
                } else {
                    clean_up();
                    if (!up_h.empty()) {
                        dir = 1;
                        current_floor = up_h.top();
                        up_h.pop();
                    }
                }
            }
        } else if (op[0] == 'l') { // locate
            printf("%d\n", current_floor);
        }
    }

    return 0;
}
