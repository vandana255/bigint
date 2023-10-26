struct BigInteger initialize(char* s);
void display(struct BigInteger a);
struct BigInteger add(struct BigInteger a, struct BigInteger b);
struct BigInteger sub(struct BigInteger a, struct BigInteger b);
struct BigInteger mul(struct BigInteger a, struct BigInteger b);
struct BigInteger multiplyByDigit(struct BigInteger a, int digit);
struct Node* addTwoNumbersHelper(struct Node* num1, struct Node* num2, int* carry);
