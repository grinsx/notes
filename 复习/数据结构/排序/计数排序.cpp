# include <iostream>

using namespace std;

/*
2017年3月19日21:03:17

计数排序 
 
 计数排序对输入的数据有附加的限制条件：
1、输入的线性表的元素属于有限偏序集S；
2、设输入的线性表的长度为n，|S|=k（表示集合S中元素的总数目为k），则k=O(n)。
在这两个条件下，计数排序的复杂性为O(n)。
计数排序的基本思想是对于给定的输入序列中的每一个元素x，
确定该序列中值小于x的元素的个数（此处并非比较各元素的大小，
而是通过对元素值的计数和计数值的累加来确定）。一旦有了这个信息，
就可以将x直接存放到最终的输出序列的正确位置上。
例如，如果输入序列中只有17个元素的值小于x的值，
则x可以直接存放在输出序列的第18个位置上。当然，如果有多个元素具有相同的值时，
我们不能将这些元素放在输出序列的同一个位置上，因此，上述方案还要作适当的修改。
 
*/ 

const int MAXN = 100000;
const int k = 1000; // range
int a[MAXN], c[MAXN], ranked[MAXN];

int main(void)
{
	int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i]; 
        ++c[a[i]];  //此操作完成后，c[i]中存放了值为i的元素的个数   	 
    }
    
    // 通过在c中记录计数和，c[i]中存放的是小于等于i元素的数字个数  
    for (int i = 1; i < k; ++i)
        c[i] += c[i-1];
    
    // 从后往前遍历  
    for (int i = n-1; i >= 0; --i)
    //c[a[i]]中存的是小于a[i]的数的个数     直接就放到了该放的位置上去了 
        ranked[--c[a[i]]] = a[i];//如果是i表达的是原数标号，a[i]就是排序后的正确序列
    
	//输出 
	for (int i = 0; i < n; ++i)
        cout << ranked[i] << endl;
        
   return 0;
}

