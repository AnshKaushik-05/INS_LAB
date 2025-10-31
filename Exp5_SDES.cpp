#include <iostream>
#include <vector>
using namespace std;

vector<int> P10 = {3,5,2,7,4,10,1,9,8,6};
vector<int> P8  = {6,3,7,4,8,5,10,9};

vector<int> permute(const vector<int> &key, const vector<int> &P) {
    vector<int> result;
    for (int i : P) result.push_back(key[i-1]);
    return result;
}

vector<int> leftShift(vector<int> half, int n) {
    vector<int> shifted(half.size());
    for (int i = 0; i < half.size(); i++)
        shifted[i] = half[(i + n) % half.size()];
    return shifted;
}

void generateSubkeys(const vector<int> &key) {
    vector<int> p10 = permute(key, P10);

    vector<int> left(p10.begin(), p10.begin() + 5);
    vector<int> right(p10.begin() + 5, p10.end());

    left = leftShift(left, 1);
    right = leftShift(right, 1);
    vector<int> k1in = left;
    k1in.insert(k1in.end(), right.begin(), right.end());
    vector<int> K1 = permute(k1in, P8);

    left = leftShift(left, 2);
    right = leftShift(right, 2);
    vector<int> k2in = left;
    k2in.insert(k2in.end(), right.begin(), right.end());
    vector<int> K2 = permute(k2in, P8);

    cout << "\nSubkey K1: ";
    for (int b : K1) cout << b;
    cout << "\nSubkey K2: ";
    for (int b : K2) cout << b;
    cout << endl;
}

int main() {
    string keyStr;
    cout << "Enter 10-bit key: ";
    cin >> keyStr;
    if (keyStr.size() != 10) {
        cout << "Invalid key length!" << endl;
        return 0;
    }
    vector<int> key(10);
    for (int i = 0; i < 10; i++) key[i] = keyStr[i] - '0';

    generateSubkeys(key);
    return 0;
}
