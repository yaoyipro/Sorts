
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class Node {
public:
    int value;
    Node* next;
};

void Insert(Node** Bins, int n) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->value = n;
    temp->next = NULL;

    if (Bins[n] == NULL) { // Bins[n] is head ptr
        Bins[n] = temp;
    }
    else {
        Node* p = Bins[n];
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = temp;
    }
}

int Delete(Node** Bins, int n) {
    Node* p = Bins[n];  // Bins[n] is head ptr
    Bins[n] = Bins[n]->next;
    int x = p->value;
    delete p;
    return x;
}

void swap(int* x, int* y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void BubbleSort(int A[], int n)
{
    int i, j, flag;
    for (i = 0; i < n - 1; i++)
    {
        flag = 0;
        for (j = 0; j < n - 1 - i; j++)
        {
            if (A[j] > A[j + 1])
            {
                swap(&A[j], &A[j+1]);
                flag = 1;
            }
        }
        if (flag == 0)
            break;
    }
}

void insertionSort(int A[], int n)
{
    int i, j, x;
    for (i = 1; i < n; i++)
    {
        j=i-1;
        x = A[i];
        
        while (j>-1 && A[j] > x)
        {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = x;
    }
}

void SelectionSort(int A[], int n)
{
    int i, j, k;

    for (i = 0; i < n - 1; i++)
    {
        k = i;
        for (j = i+1; j < n; j++)
        {
            if (A[j] < A[k])
                k = j;
        }
        swap(&A[i], &A[k]);
    }
    
}

int partition(int A[], int l, int h)
{
    int pivot = A[l];
    int i = l, j = h;

    do
    {
        do { i++; } while (A[i] <= pivot);
        do { j--; } while (A[j] > pivot);
        if (i < j)
            swap(&A[i], &A[j]);
    } while (i < j);
    swap(&A[l], &A[j]);
    return j;
}

void QuickSort(int A[], int l, int h)
{
    int j;

    if (l < h)
    {
        j = partition(A, l, h);
        QuickSort(A, l, j);
        QuickSort(A, j + 1, h);
    }
}

void Merge(int A[], int l, int mid, int h)
{
    int i = l, j = mid + 1, k = l;
    int B[100];

    while (i <= mid && j <= h)
    {
        if (A[i] < A[j])
            B[k++] = A[i++];
        else
            B[k++] = A[j++];
    }
    for (; i <= mid; i++)
        B[k++] = A[i];
    for (; j <= h; j++)
        B[k++] = A[j];

    for (int i = l; i <= h; i++)
        A[i] = B[i];
}

void IMergeSort(int A[], int n)
{
    int p, l, h, mid, i;

    for (p = 2; p <= n; p = p * 2)
    {
        for (i = 0; i + p - 1 < n; i = i + p)
        {
            l = i;
            h = i + p - 1;
            mid = (l + h) / 2;
            Merge(A, l, mid, h);
        }
    }
    if (p / 2 < n)
        Merge(A, 0, p / 2 - 1, n - 1);
}

void MergeSort(int A[], int l, int h)
{
    int mid;
    if (l < h)
    {
        mid = (l + h) / 2;
        MergeSort(A, l, mid);
        MergeSort(A, mid + 1, h);
        Merge(A, l, mid, h);
    }
}

int findMax(int A[], int n)
{
    int max = INT32_MIN;
    int i;
    for (i = 0; i < n; i++)
    {
        if (A[i] > max)
            max = A[i];
    }
    return max;
}

void CountSort(int A[], int n)
{
    int max, i, j;
    int* c;

    max = findMax(A, n);
    c = (int*)malloc(sizeof(int) * (max + 1));

    for (i = 0; i < max + 1; i++)
    {
        c[i] = 0;
    }

    for (i = 0; i < n; i++)
    {
        c[A[i]]++;
    }

    i = 0; j = 0;
    
    while (j < max + 1)
    {
        if (c[j] > 0)
        {
            A[i++] = j;
            c[j]--;
        }
        else
            j++;
    }
}

int countDigits(int x) {
    int count = 0;
    while (x != 0) {
        x = x / 10;
        count++;
    }
    return count;
}

void initializeBins(Node** p, int n) {
    for (int i = 0; i < n; i++) {
        p[i] = nullptr;
    }
}

int getBinIndex(int x, int idx) {
    return (int)(x / pow(10, idx)) % 10;
}

void RadixInsert(Node** ptrBins, int value, int idx) {
    Node* temp = new Node;
    temp->value = value;
    temp->next = nullptr;

    if (ptrBins[idx] == nullptr) {
        ptrBins[idx] = temp;  // ptrBins[idx] is head ptr
    }
    else {
        Node* p = ptrBins[idx];
        while (p->next != nullptr) {
            p = p->next;
        }
        p->next = temp;
    }
}


void RadixSort(int A[], int n)
{
    int max = findMax(A, n);
    int nPass = countDigits(max);

    // Create bins array
    Node** bins = new Node * [10];

    // Initialize bins array with nullptr
    initializeBins(bins, 10);

    // Update bins and A for nPass times
    for (int pass = 0; pass < nPass; pass++) {

        // Update bins based on A values
        for (int i = 0; i < n; i++) {
            int binIdx = getBinIndex(A[i], pass);
            RadixInsert(bins, A[i], binIdx);
        }

        // Update A with sorted elements from bin
        int i = 0;
        int j = 0;
        while (i < 10) {
            while (bins[i] != nullptr) {
                A[j++] = Delete(bins, i);
            }
            i++;
        }
        // Initialize bins with nullptr again
        initializeBins(bins, 10);
    }

    // Delete heap memory
    delete[] bins;
}

void BinSort(int A[], int n)
{
    int max, i, j;
    struct Node ** Bins;

    max = findMax(A, n);
    Bins = (struct Node**)malloc(sizeof(max+1));

    for (i = 0; i < max + 1; i++)
    {
        Bins[i] = NULL;
    }

    for (i = 0; i < n; i++)
    {
        Insert(Bins, A[i]);
    }

    i = 0; j = 0;

    while (i < max + 1)
    {
        while (Bins[i] != NULL)
        {
            A[j++] = Delete(Bins,i);
        }
        i++;
    }
}

void ShellSort(int A[], int n)
{
    int gap, i, j, temp;

    for (gap = n / 2; gap >= 1; gap /= 2)
    {
        for (i = gap; i < n; i++)
        {
            temp = A[i];
            j = i - gap;
            while (j >= 0 && A[j] > temp)
            {
                A[j + gap] = A[j];
                j = j - gap;
            }
            A[j + gap] = temp;
        }
    }
}

int main()
{
    int A[] = { 11,13,7,2,6,9,4,5,10,3 }, n = 10, i;

    //BubbleSort(A, 10);
    //insertionSort(A, 10);
    //SelectionSort(A, n);
    //QuickSort(A, 0, n);
    //IMergeSort(A, n);
    //MergeSort(A, 0, n-1);
    //CountSort(A, n);
    //BinSort(A, n);
    //RadixSort(A, n);
    ShellSort(A, n);

    for (i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }

    printf("\n");

    return 0;
}

