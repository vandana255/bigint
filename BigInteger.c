struct Node {
    int data;
    struct Node* next;
};


struct BigInteger {
    struct Node* head;
};




void displayHelper(struct Node* head) {
    if (head == NULL) {
        return;
    } else {
        displayHelper(head->next);
        printf("%d", head->data);
    }
}




struct Node* addTwoNumbersHelper(struct Node* num1, struct Node* num2, int* carry) {
    if (num1 == NULL && num2 == NULL) {
        if (*carry == 1) {
            struct Node* sum = (struct Node*)malloc(sizeof(struct Node));
            sum->data = 1;
            sum->next = NULL;
            return sum;
        }
        return NULL;
    }

    struct Node* sum = (struct Node*)malloc(sizeof(struct Node));
    sum->next = addTwoNumbersHelper(num1 ? num1->next : NULL, num2 ? num2->next : NULL, carry);

    int val1 = num1 ? num1->data : 0;
    int val2 = num2 ? num2->data : 0;

    sum->data = (val1 + val2 + *carry) % 10;
    *carry = (val1 + val2 + *carry) / 10;

    return sum;
}

struct BigInteger sub(struct BigInteger a, struct BigInteger b) {
    struct Node* result = NULL;
    struct Node* current = NULL;
    int borrow = 0;

    while (a.head || b.head) {
        int x = a.head ? a.head->data : 0;
        int y = b.head ? b.head->data : 0;
        int diff = x - y - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = diff;
        newNode->next = NULL;

        if (result == NULL) {
            result = newNode;
            current = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }

        if (a.head) a.head = a.head->next;
        if (b.head) b.head = b.head->next;
    }

    struct BigInteger resultBigInt;
    resultBigInt.head = result;

    return resultBigInt;
}

struct BigInteger add(struct BigInteger a, struct BigInteger b) {
    int carry = 0;
    struct Node* result = addTwoNumbersHelper(a.head, b.head, &carry);

    struct BigInteger sum;
    sum.head = result;

    return sum;
}

struct BigInteger multiplyByDigit(struct BigInteger a, int digit) {
    struct Node* current = a.head;
    struct Node* result = NULL;
    struct Node* resultTail = NULL;
    int carry = 0;

    while (current != NULL) {
        int product = current->data * digit + carry;
        carry = product / 10;
        product = product % 10;

        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = product;
        newNode->next = NULL;

        if (result == NULL) {
            result = newNode;
            resultTail = newNode;
        } else {
            resultTail->next = newNode;
            resultTail = newNode;
        }

        current = current->next;
    }

    if (carry > 0) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = carry;
        newNode->next = NULL;

        if (result == NULL) {
            result = newNode;
        } else {
            resultTail->next = newNode;
        }
    }

    struct BigInteger resultBigInt;
    resultBigInt.head = result;
    return resultBigInt;
}

struct BigInteger mul(struct BigInteger a, struct BigInteger b) {
    struct BigInteger result = initialize("0");

    struct Node* currentB = b.head;
    struct BigInteger partialResult;
    int shift = 0;

    while (currentB != NULL) {
        partialResult = multiplyByDigit(a, currentB->data);
        
        
        for (int i = 0; i < shift; i++) {
            struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
            newNode->data = 0;
            newNode->next = partialResult.head;
            partialResult.head = newNode;
        }
        
        result = add(result, partialResult);
        currentB = currentB->next;
        shift++;
    }

    return result;
}


struct BigInteger initialize(char* s) {
    struct BigInteger BigInt;
    BigInt.head = NULL;
    struct Node* temp = NULL;

    for (int i = 0; s[i] != '\0'; i++) {
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->data = s[i] - '0';
        temp->next = BigInt.head;
        BigInt.head = temp;
    }

    return BigInt;
}

void display(struct BigInteger a) {
    displayHelper(a.head);
}
