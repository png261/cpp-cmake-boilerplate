#include <SDL2/SDL.h>
#include <algorithm>
#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 910;
const int SCREEN_HEIGHT = 750;

const int arrSize = 130;
const int rectSize = 7;

int arr[arrSize];
int Barr[arrSize];

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool complete = false;

void printArr(int arr[], int n)
{
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void generateRandomArr()
{
    srand(time(0));
    for (int i = arrSize - 1; i > 0; --i) {
        swap(arr[i], arr[rand() % (i + 1)]);
    }
}

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Couldn't initialize SDL. SDL_Error: " << SDL_GetError();
        return false;
    }

    if (!(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))) {
        cout << "Warning: Linear Texture Filtering not enabled.\n";
    }

    window = SDL_CreateWindow(
        "Sorting Visualizer",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        cout << "Couldn't create window. SDL_Error: " << SDL_GetError();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        cout << "Couldn't create renderer. SDL_Error: " << SDL_GetError();
        return false;
    }

    for (int i = 0; i < arrSize; ++i) {
        arr[i] = i + 1;
    }
    generateRandomArr();

    return true;
}

void close()
{
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();
}

void visualize(int x = -1, int y = -1, int z = -1)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    int j = 0;
    for (int i = 0; i <= SCREEN_WIDTH - rectSize; i += rectSize) {
        SDL_PumpEvents();

        SDL_Rect rect = {i, 0, rectSize, arr[j]};
        if (complete) {
            SDL_SetRenderDrawColor(renderer, 100, 180, 100, 0);
            SDL_RenderDrawRect(renderer, &rect);
        } else if (j == x || j == z) {
            SDL_SetRenderDrawColor(renderer, 100, 180, 100, 0);
            SDL_RenderFillRect(renderer, &rect);
        } else if (j == y) {
            SDL_SetRenderDrawColor(renderer, 165, 105, 189, 0);
            SDL_RenderFillRect(renderer, &rect);
        } else {
            SDL_SetRenderDrawColor(renderer, 170, 183, 184, 0);
            SDL_RenderDrawRect(renderer, &rect);
        }
        j++;
    }
    SDL_RenderPresent(renderer);
}


/* SELECTION SORT */
void selectionSort()
{
    for (int i = 0; i < arrSize - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < arrSize; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
                visualize(i, minIndex);
            }
            SDL_Delay(1);
        }

        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

/* BUBBLE SORT */
void bubbleSort()
{
    for (int i = arrSize - 1; i >= 0; --i) {
        bool isSwapped = false;

        for (int j = 0; j <= i; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                isSwapped = true;
                visualize(j + 1, j, arrSize - i);
            }
        }

        if (!isSwapped) {
            return;
        }
        SDL_Delay(1);
    }
}

/* INSERTION SORT */
void insertionSort()
{
    for (int i = 1; i < arrSize; ++i) {
        const int current = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > current) {
            swap(arr[j], arr[j + 1]);
            j--;

            visualize(i, j + 1);
            SDL_Delay(5);
        }
        arr[j + 1] = current;
    }
}

/* HEAP SORT */
int leftChild(int i)
{
    return (i * 2) + 1;
}

int rightChild(int i)
{
    return (i * 2) + 2;
}

void heapify(int i, int n)
{
    int largest = i;
    const int left = leftChild(i);
    const int right = rightChild(i);
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(largest, n);
    }
}

void buildMaxHeap()
{
    for (int i = arrSize / 2 - 1; i >= 0; --i) {
        heapify(i, arrSize);
    }
}

void heapSort()
{
    buildMaxHeap();
    for (int i = arrSize - 1; i >= 0; --i) {
        swap(arr[0], arr[i]);
        heapify(0, i);
    }
}

/* MERGE SORT */
void merge(int begin, int mid, int end)
{
    const int leftSize = mid - begin + 1;
    const int rightSize = end - mid;

    int* const leftArr = new int[leftSize];
    int* const rightArr = new int[rightSize];

    for (int i = 0; i < leftSize; ++i) {
        leftArr[i] = arr[begin + i];
    }

    for (int i = 0; i < rightSize; ++i) {
        rightArr[i] = arr[mid + 1 + i];
    }


    int* pLeft = leftArr;
    int* pRight = rightArr;
    int* pLeftEnd = leftArr + leftSize;
    int* pRightEnd = rightArr + rightSize;

    int* pMerge = arr + begin;

    while ((pLeft != pLeftEnd) || (pRight != pRightEnd)) {
        if ((pRight == pRightEnd) || pLeft != pLeftEnd && *pLeft <= *pRight) {
            *pMerge = *pLeft;
            pLeft++;
        } else {
            *pMerge = *pRight;
            pRight++;
        }
        pMerge++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

void mergeSort(int begin = 0, int end = arrSize - 1)
{
    if (begin >= end) {
        return;
    }

    const int mid = begin + (end - begin) / 2;
    mergeSort(begin, mid);
    mergeSort(mid + 1, end);

    merge(begin, mid, end);
}

/* QUICK SORT */
int partition(int begin, int end)
{
    srand(time(0));
    const int randomPivotIndex = rand() % (end - begin + 1) + begin;
    const int pivot = arr[randomPivotIndex];

    int pivotIndex = begin;
    for (int i = begin; i <= end; ++i) {
        if (arr[i] < pivot) {
            pivotIndex++;
        }
    }
    swap(arr[randomPivotIndex], arr[pivotIndex]);


    int i = begin;
    int j = end;

    while (true) {
        while (i < arrSize && arr[i] <= pivot) {
            ++i;
        }

        while (j >= 0 && arr[j] > pivot) {
            --j;
        }

        if (i >= pivotIndex || j <= pivotIndex) {
            break;
        }

        swap(arr[i], arr[j]);
    }

    return pivotIndex;
}

void quickSort(int begin = 0, int end = arrSize - 1)
{
    if (begin >= end) {
        return;
    }
    const int i = partition(begin, end);
    quickSort(begin, i - 1);
    quickSort(i + 1, end);
}

int main(int argc, char* argv[])
{
    init();
    visualize();
    insertionSort();
    return 0;
}
