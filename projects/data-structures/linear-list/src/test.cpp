#include "include/sequential_list.hpp"
int main() {
    SeqList<int> IntList(100);
    for(int i = 0; i < 100; ++i) {
        IntList[i] = i;
    }
    return 0;
}