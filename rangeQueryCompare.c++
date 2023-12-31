#include <iostream>
#include <chrono>
#include <cmath>
#include <set>
#include <vector>
#include <list>

std::vector<int> ArrayCreation(std::multiset<int> input){
    std::vector<int> arr;
    for(int elem: input){
        arr.push_back(elem);
    }
    return arr;
}

void merge(std::vector<int>* temp2,std::vector<int>* arr, std::vector<int>* temp1){
    int i = 0;
    int j = 0;
    while(i<arr->size() && j<temp1->size()){
        if((*arr)[i]<=(*temp1)[j]){
            temp2->push_back((*arr)[i++]);
        }else{
            temp2->push_back((*temp1)[j++]);
        }
    }
    //處理還沒被放入的剩餘數字
    while (i<arr->size()) {
        temp2->push_back((*arr)[i]);
        i++;
    }
    while (j<temp1->size()) {
        temp2->push_back((*temp1)[j]);
        j++;
    }
    temp1->clear();
    arr->clear();
}


void insert(std::vector<std::vector<int>*>& arrAdress, std::vector<std::vector<int>*>& tempAdress, int layer){
    //if layer is out of bound -> add new layer
    if(arrAdress[layer]->empty()){
        *arrAdress[layer] = *tempAdress[layer];
        tempAdress[layer] ->clear();
        // printf("array is empty\n");
        return;
    }else{
        if(arrAdress.size()<layer+2){
            // printf("new new vector\n");
            std::vector<int>* arr0 = new std::vector<int>;
            std::vector<int>* temp0 = new std::vector<int>;
            arr0->reserve(arrAdress[layer]->size()*2);
            temp0->reserve(tempAdress[layer]->size()*2);
            arrAdress.push_back(arr0);
            tempAdress.push_back(temp0);
        }
        merge(tempAdress[layer+1], arrAdress[layer], tempAdress[layer]);
        // printf("array is full\n");
        insert(arrAdress, tempAdress, layer+1);
    }
}

std::vector<std::vector<int>*> ArrayOfSortedArrayCreation(std::multiset<int> input){
    std::vector<std::vector<int>*> arrAdress;
    std::vector<std::vector<int>*> tempAdress;
    std::vector<int>* arr0 = new std::vector<int>;
    std::vector<int>* temp0 = new std::vector<int>;
    arrAdress.push_back(arr0);
    tempAdress.push_back(temp0);
    for(int elem: input){
        std::vector<int> input = {elem};//
        *tempAdress[0] = input;
        insert(arrAdress, tempAdress, 0);
    }
    for(std::vector<int>* temp:tempAdress){
        delete temp;
        temp = nullptr;
    }
    return arrAdress;
}

class Node{
public:
    int val;
    Node* up;
    Node* down;
    Node* left;
    Node* right;
    Node(int val){
        this->val = val;
        up = nullptr;
        down = nullptr;
        right = nullptr;
        left = nullptr;
    }
    int hight(){
        int hight = 1;
        Node* ptr = this;
        while(ptr->up != nullptr){
            ptr = ptr->up;
            hight++;
        }
        ptr = this;
        while(ptr->down != nullptr){
            ptr = ptr->down;
            hight++;
        }
        return hight;
    }
};

Node* randomUp(Node* bottom, Node* head){
    Node * downTemp = bottom;
    int times = 0;
        while(true){
            int p = rand()%2;
            if(p == 1){
                times++;
                Node* nCopy = new Node(bottom->val);
                nCopy->down = downTemp;
                downTemp->up = nCopy;
                downTemp = nCopy;
                if(nCopy->down->left != NULL){
                    if(nCopy->down->left->up != NULL){
                        nCopy->left = nCopy->down->left->up;
                        nCopy->down->left->up->right = nCopy;
                    }
                }
                if(nCopy->down->right != NULL){
                    if(nCopy->down->right->up != NULL){
                        nCopy->right = nCopy->down->right->up;
                        nCopy->down->right->up->left = nCopy;
                    }
                }
                if( bottom->val != -1 && times+1>head->hight()){
                    Node* index = nCopy;
                    while(index->left != nullptr){
                        index = index->left;
                    }
                    Node* newHead = new Node(-1);
                    newHead->down = head;
                    head->up = newHead;
                    newHead->right = index;
                    index->left = newHead;
                }
            }else{
                break;
            }
        }
    // std::cout<<times;
    return downTemp;
}

Node* skipSearch(int a, Node* head){
    Node* ptr = head;
    while(ptr->down != nullptr){
        if(ptr->right == nullptr || ptr->right->val > a){
            ptr = ptr->down;
        }else{
            ptr = ptr->right;
        }
    }
    while(ptr->val < a){
        if(ptr->right!= nullptr){
            ptr = ptr->right;
        }else{
            return nullptr;
        }
    }
    return ptr;
}

Node* skiplistCreation(std::vector<int> input){
    Node* startb = new Node(-1);
    Node* start = randomUp(startb,startb);
    for(int i=0; i<input.size(); i++){
        Node * ptr = start;
        while(ptr->up != nullptr){
            ptr = ptr->up;
        }
        // std::cout<<"start: "<<ptr->val;
        while(ptr->down != nullptr){
            if(ptr->right == nullptr || ptr->right->val > input[i]){
                ptr = ptr->down;
            }else{
                ptr = ptr->right;
            }
        }
        while(ptr->right!= nullptr && ptr->right->val<input[i]){
            ptr = ptr->right;
        }
        Node* n = new Node(input[i]);
        if(input[i]<ptr->val){
            n->right = ptr;
            n->left = ptr->left;
            ptr->left->right = n;
            ptr->left = n;
        }else{
            n->left = ptr;
            n->right = ptr->right;
            ptr->right = n;
        }
        //random up copy
        randomUp(n,start);
    }
    return start;
}

std::multiset<int> rangeQueryArr(int a, int b, std::vector<int> arr){
    std::multiset<int> query;
    for(int elem: arr){
        if(elem<=b && elem>=a){
            query.insert(elem);
        }else if(elem>b){
            break;
        }
    }
    // for(int x: query){
    //     printf("ra: %d\n",x);
    // }
    return query;
}

std::multiset<int> rangeQueryArrOfSort(int a, int b, std::vector<std::vector<int>*> ArrOfSorted){
    std::multiset<int> query;
    for(std::vector<int>* arr: ArrOfSorted){
        for(int elem: *arr){
            if(elem<=b && elem>=a){
                query.insert(elem);
            }else if(elem>b){
                break;
            }
        }
    }
    // for(int x: query){
    //     printf("rs: %d\n",x);
    // }
    return query;
}

std::multiset<int> rangeQuerySkip(int a, int b, Node* head){
    std::multiset<int> query;
    Node* aPos = skipSearch(a, head);
    if(aPos == nullptr){
        return query;
    }else{
        while(aPos->val<=b){
            query.insert(aPos->val);
            if(aPos->right != nullptr){
                aPos = aPos->right;
            }else{
                break;
            }
        }
        // for(int x: query){
        //     printf("sk: %d\n",x);
        // }
        return query;
    }
}

bool equivalent(std::multiset<int> RangeArr, std::multiset<int> RangeAS, std::multiset<int> RangeSkip){
    if(RangeArr == RangeAS && RangeArr == RangeSkip && RangeAS == RangeSkip){
        std::cout<<"true";
        return true;
    }else{
        std::cout<<"false";
        return false;
    }
}

auto timeUsage(){
    //計時
    auto start = std::chrono::high_resolution_clock::now();

    //用於產生實驗用的陣列
    int n = pow(2,3)-1;
    std::multiset<int> input;
    for(int i=0; i<n; i++){
        int num;
        do{
            num = rand() % (n);
        }while(num>=(RAND_MAX-RAND_MAX%n));
        num%=n;
        input.insert(num);
        printf("%d ", num);
    }

    std::vector<int> array = ArrayCreation(input);
    // for(int i=0; i<array.size(); i++){
    //     printf("\n%d ", array[i]);
    // }

    std::vector<std::vector<int>*> ArrOfSorted = ArrayOfSortedArrayCreation(input);
    // for(int i=0; i<ArrOfSorted.size(); i++){
    //     std::vector<int>* layer = ArrOfSorted[i];
    //     printf("layer%d:",i);
    //     for(int number: *layer){
    //         printf(" %d", number);
    //     }
    //     printf("\n");
    // }

    //skiplist creaton
    Node* head = skiplistCreation(array);
    // Node* iterator = head;
    // std::cout<<"skip list bottom: \n";
    // while(iterator->down!=NULL){
    //     iterator = iterator->down;
    // }
    // while(iterator->right!=NULL){
    //     printf("%d, ",iterator->val);
    //     iterator = iterator->right;
    // }
    // printf("%d, ",iterator->val);

    //evaluation
    int k = pow(2,1);
    int a = rand()%n;
    printf("\na, a+k: %d, %d\n", a, a+k);
    equivalent(rangeQueryArr(a, a+k, array), rangeQueryArrOfSort(a, a+k, ArrOfSorted), rangeQuerySkip(a, a+k, head));

    //delete all the pointer that might cause problem

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
    auto usedTime_Average = getAvg(1);
    std::cout << "程式平均執行時間：" << usedTime_Average.count() << " nanoseconds" <<"\n";
    std::cout<<"finish";
    return 0;
}
