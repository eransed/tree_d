
#include "../include/util.hpp"
//#include "llutil.hpp"

void sortTest();
void sortTest2(int N);

int main(int argc, char* argv[]) {
    
        ScopedTimer mainTimer("Time in main function", true);
        
        std::cout << "__TIME__ = " << __TIME__ << std::endl;

        int N = 1000000 ;

        std::cout << (double)sizeof (int) * N / (1024 * 1024) << " mb" << std::endl;
        std::cout << "N = " << N << std::endl;

        sortTest2(N);
        logn("");

        int *a = new int [N];

        {
            ScopedTimer t("Linear heap time :", true);
            for (int i = 0; i < N; i++) {

                a[i] = i;
                if (a[i] == 45743){
                    std::cout << "if " << a[i] << std::endl;
                }

            }
        }

        delete[] a;

        logn("");

        // int b[N];

        // {
        //     ScopedTimer t("Linear stack time :", true);
        //     for (int i = 0; i < N; i++) {

        //         b[i] = i;
        //         if (b[i] == 45743){
        //             std::cout << "if " << b[i] << std::endl;
        //         }

        //     }
        // }

        logn("");

    
    
    return 0;
}


void sortTest2(int N){


    // long long N = 20000000LL;
    // long long * a = new long long [N];
    int *a = new int[N];


    {
        ScopedTimer st("\n   Fill array", true);
        Math::fillRndArr(a, N, 1, 99);
    }

    std::cout << "\n   Merge sorting " << N << " values..." << std::endl;
    Sort::isSortedPrettyPrint(a, N);
    // Sort::print(a, N);

    
    {
        ScopedTimer t("\n   Merge sort", true);
        Merge::sort(a, N);
    }


    Sort::isSortedPrettyPrint(a, N);

    delete[] a;

}



/*

void sortTest() {
    char line[6];
    int count = 0;
    int N = 140000;
    int a[N];

    {
        ScopedTimer t("File read", true);
        while( std::cin.good() ) {
            std::cin.getline(line, sizeof(line));
            a[count] = atoi(line);
            count++;
            if(count >= N){
                count--;
                break;
            }
        }
    }

    Sort::isSortedPrettyPrint(a, count);

    int sel[N], ins[N], mer[N], heap[N]; 
    for (int i = 0; i < N; i++){
        sel[i] = ins[i] = mer[i] = heap[i] = a[i];
    }

    std::cout << "\nSelection sorting " << count << " values..." << std::endl;
    {
        ScopedTimer t("Selection sort", true);
        Selection::sort(sel, count);
    }
    Sort::isSortedPrettyPrint(sel, count);


    std::cout << "\nInsertion sorting " << count << " values..." << std::endl;
    {
        ScopedTimer t("Insertion sort", true);
        Insertion::sort(ins, count);
    }
    Sort::isSortedPrettyPrint(ins, count);


    
    std::cout << "\nMerge sorting " << count << " values..." << std::endl;
    {
        ScopedTimer t("Merge sort", true);
        Merge::sort(mer, count);
    }
    Sort::isSortedPrettyPrint(mer, count);

    std::cout << "\nHeap sorting " << count << " values..." << std::endl;
    {
        ScopedTimer t("Heap sort", true);
        Merge::sort(heap, count);
    }

    Sort::isSortedPrettyPrint(heap, count);

    {
        ScopedTimer t("\nLinear sort check and print", true);
    }


    {
        ScopedTimer t("\nTimer overhead", true);
    }
}


*/